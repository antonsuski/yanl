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

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

static char _addr_in6_buff[INET6_ADDRSTRLEN];
// static int  translate(yanl::socket::network_protcol np);
// static int  translate(yanl::socket::trasport_protcol tp);

namespace yanl
{
socket::socket()
{
    std::cout << "socket default constructor\n";

    addrinfo  hint;
    addrinfo* result = nullptr;

    std::memset(&hint, 0U, sizeof(hint));
    hint.ai_family = AF_UNSPEC;
    std::cout.flush();
}

socket::~socket()
{
    if (this->fd != -1)
    {
        shutdown(this->fd, SHUT_RDWR);
    }
}

int socket::init(const std::string_view address, const std::string_view port,
                 network_protocol np, transport_protocol tp)
{
    this->port    = port;
    this->address = address;

    addrinfo  hint;
    addrinfo* result = nullptr;

    std::memset(&hint, 0U, sizeof(hint));

    return -1;
}
} // namespace yanl
