#pragma once
#include <boost/optional.hpp>
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
#include <mutex>
#include <thread>
#include <string>
#include <stdexcept>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>

namespace adas::asio::can {
	using namespace boost::asio;
    class CanRawEndpoint;
    class CanRaw {
    public:
        typedef CanRawEndpoint endpoint;
        typedef boost::asio::basic_raw_socket<adas::asio::can::CanRaw> socket;
        int family() const {
            return PF_CAN;
        }
        int type() const {
            return SOCK_RAW;

        }
        int protocol() const {
            return CAN_RAW;

        }

    };
    class CanRawEndpoint {
    private:
        sockaddr_can _addr;
    public:
        CanRawEndpoint() = default;
        explicit CanRawEndpoint(const std::string & ifname) {
            _addr.can_family  = AF_CAN;
            unsigned ifindex = if_nametoindex(ifname.c_str());
            if(0 == ifindex) {
                std::string what = "interface name not exists: ";
                what += ifname;
                throw std::invalid_argument(what);
            }
            _addr.can_ifindex = ifindex;
        }
    public:
        typedef CanRaw protocol_type;
        protocol_type protocol() const {
            return CanRaw();
        }
        sockaddr * data() {
            return reinterpret_cast<sockaddr*>(&_addr);
        }
        const sockaddr * data() const {
            return reinterpret_cast<const sockaddr*>(&_addr);
        }
        std::size_t size() const {
            return sizeof(sockaddr_can);
        }
        void resize(std::size_t new_size) {
            if(new_size > sizeof(_addr)) {
                std::string what = "invalid new_size";
                throw std::invalid_argument(what);
            }

        }
        std::size_t capacity() const {
            return sizeof(_addr);
        }



    };
}
