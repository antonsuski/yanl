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
public:
    enum network_protocol
    {
        ipv4 = 0,
        ipv6
    };
    enum transport_protocol
    {
        tcp = 0,
        udp
    };

private:
    int                fd{ -1 };
    bool               is_addr_valid{ false };
    network_protocol   np = { ipv4 };
    transport_protocol tp = { udp };
    std::string        port{ "7777" };
    std::string        address{ "localhost" };

public:
    socket();
    ~socket();
    int init(const std::string_view address = "localhost",
             const std::string_view port = "7777", network_protocol np = ipv4,
             transport_protocol tp = udp);
};

} // namespace yanl
