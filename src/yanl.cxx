/**
 * @file yanl.cxx
 * @author Anton Suskiy (anton.syski@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "yanl.hxx"

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

static char _addr_in6_buff[INET6_ADDRSTRLEN];
// static int  translate(yanl::socket::network_protcol np);
// static int  translate(yanl::socket::trasport_protcol tp);

namespace yanl
{
socket::socket(const std::string_view& dest_address,
               const std::string_view& dest_port)
    : m_dest_address{ dest_address }
    , m_dest_port{ dest_port }
    , m_fd{ -1 }
{
    std::cout << "socket ctor\n";
}

socket* socket::init()
{
    struct addrinfo hints{};
    return this;
}

bool        socket::send(const std::string& buffer) {}
std::string socket::receive() {}

socket::~socket()
{
    if (m_fd != -1)
    {
        int res = shutdown(m_fd, SHUT_RDWR);
        if (res)
        {
            std::cout << std::format("file descriptor was closed with err:{}\n",
                                     std::strerror(errno));
        }
    }
    std::cout << "socket dtor\n";
}

} // namespace yanl
