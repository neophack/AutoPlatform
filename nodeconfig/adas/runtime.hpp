//
// Created by 刘典 on 2021/9/17.
//

#ifndef NODEDRIVING_RUNTIME_HPP
#define NODEDRIVING_RUNTIME_HPP
#include <boost/asio/io_context.hpp>
#include <thread>
#include <vector>
#include <stdexcept>
namespace adas {
    namespace node {
        class in_base;
        class sync_out;
        class timer;
        class can_io;
    }
    namespace runtime {
        class task_context {
            friend class node::in_base;
            friend class node::sync_out;
            friend class node::timer;
            friend class node::can_io;
            template<typename Process> friend class task;

        public:
            task_context(const task_context &) = delete;
            task_context(task_context &&) = delete;
            task_context & operator=(const task_context &) = delete;
            task_context & operator=(task_context &&) = delete;
        private:
            boost::asio::io_context io_;
            std::vector<node::in_base*> update_list_;
            bool in_sync_out_{false};
            bool in_sync_out() const {
                return in_sync_out_;
            }
            void begin_sync_out() {
                if(in_sync_out_)
                    throw std::logic_error("nested sync out");
                in_sync_out_ = true;
                update_list_.clear();
            }
            void end_sync_out();
            task_context() = default;
        private:
            static void set_this(task_context *context);

        };
        namespace this_task {
            task_context & context();
        }
        template<typename Process>
        class task {
        private:
            task_context context_;
            std::thread thread_{&task<Process>::run, this};

            void run() {
                task_context::set_this(&context_);
                Process p;
                context_.io_.run();
            }

        public:
            ~task() noexcept {
                context_.io_.stop();
                thread_.join();

            }

        };

    }

}

#endif //NODEDRIVING_RUNTIME_HPP
