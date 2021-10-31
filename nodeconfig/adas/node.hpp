//
// Created by 刘典 on 2021/9/17.
//

#ifndef NODEDRIVING_NODE_HPP
#define NODEDRIVING_NODE_HPP

#include <memory>
#include <functional>
#include <chrono>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include "asio_can.h"
#include <utility>
#include "runtime.hpp"
#include <iostream>
#include <map>
#include <queue>

namespace adas::node {
    class sync_out {
    private:
        bool ignore_{false};
    public:
        sync_out(const sync_out &) = delete;

        sync_out &operator=(const sync_out &) = delete;

        explicit sync_out(bool ignore_when_nested = false) {
            if (runtime::this_task::context().in_sync_out()) {
                if (ignore_when_nested) {
                    ignore_ = true;
                    return;
                } else {
                    throw std::logic_error("nested sync out");
                }
            }
            runtime::this_task::context().begin_sync_out();
        }

        ~sync_out() {
            if (ignore_)
                return;
            runtime::this_task::context().end_sync_out();

        }

    };

    class in_base {
        friend class runtime::task_context;

    public:
        using update_handler_type = std::function<void()>;
    private:
        update_handler_type update_handler_;
        bool is_updated_{false};

        void reset_updated() {
            is_updated_ = false;
        }

        void set_updated() {
            is_updated_ = true;
        }


    protected:
        void add_to_update_list() {
            runtime::this_task::context().update_list_.push_back(this);

        }

    public:
        bool is_updated() const {
            return is_updated_;
        }

    public:
        explicit in_base(update_handler_type update_handler) : update_handler_(std::move(update_handler)) {

        }

        in_base() : in_base(nullptr) {}

        virtual ~in_base() = 0;
    };

    template<typename T>
    class in : public in_base {
    private:
        T value_;
    public:
        explicit in(const T &value, update_handler_type update_handler) : in_base(update_handler), value_(value) {}

        const T &get() const noexcept {
            return value_;
        }

        void set(const T &value) {
            value_ = value;
            add_to_update_list();
        }

    };

    template<typename T>
    class in<std::shared_ptr<T>> : public in_base {
    private:
        std::shared_ptr<const T> value_;
    public:
        explicit in(const std::shared_ptr<const T> &value, update_handler_type update_handler) : in_base(
                update_handler), value_(value) {}

        const std::shared_ptr<const T> &get() const noexcept {
            return value_;
        }

        void set(const std::shared_ptr<const T> &value) {
            value_ = value;
            add_to_update_list();
        }

        const T &operator*() {
            return value_.operator*();
        }

        const T *operator->() {
            return value_.operator->();
        }
    };

    template<>
    class in<void> : public in_base {
        using in_base::in_base;
    public:
        void set(void*) {
            add_to_update_list();
        }

    };

    template<typename T>
    class out {
    public:
        using handler_type = std::function<void(const T &)>;

        void handler(handler_type h) {
            handler_ = h;
        }

        void operator()(const T &value) {
            if (handler_) {
                sync_out so(true);
                handler_(value);
            }
        }

    private:
        handler_type handler_;
    };

    template<>
    class out<void> {
    public:
        using handler_type = std::function<void(void*)>;

        void handler(handler_type h) {
            handler_ = std::move(h);
        }

        void operator()() {
            if (handler_) {
                sync_out so(true);
                handler_(nullptr);
            }
        }

    private:
        handler_type handler_;

    };

    class timer {
    public:
        enum class mode {
            single,
            cycle
        };
        using duration_type = std::chrono::steady_clock::duration;
        using handler_type = std::function<void()>;

        timer(mode m, duration_type interval, handler_type handler) : mode_(m), interval_(interval),
                                                                      handler_(std::move(handler)),
                                                                      timer_(adas::runtime::this_task::context().io_) {}

        void interval(duration_type d) {
            interval_ = d;
        }

        duration_type interval() const {
            return interval_;
        }

        void start() {
            stop();
            timer_.expires_after(interval_);
            timer_.async_wait([this](const auto &ec) { wait_handler(ec); });
        }


        void stop() {
            timer_.cancel();

        }

        timer(const timer &) = delete;

        timer(timer &&) = delete;

        timer &operator=(const timer &) = delete;

        timer &operator=(timer &&) = delete;

    private:
        mode mode_;
        duration_type interval_;
        handler_type handler_;
        boost::asio::steady_timer timer_;

        void wait_handler(const boost::system::error_code &ec) {
            if (ec) {
                if (boost::asio::error::operation_aborted != ec)
                    std::cerr << "error: " << ec.message() << std::endl;
                return;
            }
            if (mode_ == mode::cycle)
                start();
            handler_();


        }


    };

    class can_io {
    public:
        using receive_handler_type = std::function<void(const can_frame &msg)>;
    private:
        static const int MaxQueuedSize = 10;
        adas::asio::can::CanRaw::socket socket_{adas::runtime::this_task::context().io_};
        receive_handler_type receive_handler_;
        can_frame msg_receive_buffer_;
        can_frame msg_send_buffer_;
        std::queue<can_frame> sending_queue_;
        bool is_sending_{false};

        void start_receive() {
            socket_.async_receive(boost::asio::buffer(&msg_receive_buffer_, sizeof(msg_receive_buffer_)),
                                  [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
                                      if (error) {
                                          std::cerr << "can receive error: " << error.message() << std::endl;
                                          return;
                                      }
                                      if (receive_handler_)
                                          receive_handler_(msg_receive_buffer_);
                                      start_receive();
                                  });
        }

        void start_send() {
            if (sending_queue_.empty()) {
                is_sending_ = false;
                return;
            }
            is_sending_ = true;
            msg_send_buffer_ = sending_queue_.front();
            sending_queue_.pop();
            socket_.async_send(boost::asio::buffer(&msg_send_buffer_, sizeof(msg_send_buffer_)),
                               [this](const boost::system::error_code &error, std::size_t bytes_transferred) {
                                   if (error) {
                                       std::cerr << "can send error: " << error.message() << std::endl;
                                       return;
                                   }
                                   start_send();
                               });


        }

    public:
        explicit can_io(const std::string &can_interface) {
            adas::asio::can::CanRawEndpoint endpoint(can_interface);
            socket_.open();
            socket_.bind(endpoint);
            start_receive();

        }

        const receive_handler_type &receive_handler() {
            return receive_handler_;
        }

        void receive_handler(const receive_handler_type &handler) {
            receive_handler_ = handler;
        }

        void send(const can_frame &msg) {
            if (sending_queue_.size() >= MaxQueuedSize) {
                std::cout << "warning: sending queue full" << std::endl;
                return;
            }
            sending_queue_.push(msg);
            if(is_sending_)
                return;
            start_send();
        }
    //static
    private:
        inline static std::map<std::string, std::unique_ptr<can_io>> channels_;
    public:
        static can_io & get(const std::string & channel) {
            if(channels_.find(channel) == channels_.end())
                channels_.insert({channel, std::make_unique<can_io>(channel)});
            return *channels_.find(channel)->second;
        }




    };


}
#endif //NODEDRIVING_NODE_HPP
