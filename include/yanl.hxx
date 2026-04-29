/**
 * @file yanl.hxx
 * @author Anton Suskiy (anton.syski@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-04-26
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include <string>
#include <string_view>

namespace yanl
{
class socket
{
private:
    std::string m_dest_address{ "localhost" };
    std::string m_dest_port{ "7777" };

    struct addrinfo* m_servinfo;

    int m_fd{ -1 };

    socket* init();

public:
    socket(const std::string_view& dest_address = "localhost",
           const std::string_view& dest_port    = "7777");

    bool        send(const std::string& buffer);
    std::string receive();

    ~socket();
};

} // namespace yanl
