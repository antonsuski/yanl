#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

constexpr std::string_view def_port{ "7777" };
constexpr std::string_view def_dns{ "127.0.0.1" };

int main(int argc, char* argv[])
{
    addrinfo         hint;
    addrinfo*        addr;
    sockaddr_storage incomming_addr;
    int              local_socket_fd, external_socket_fd;
    int              status;

    char addr_str[INET6_ADDRSTRLEN];

    memset(&hint, 0, sizeof(hint));
    hint.ai_family   = AF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags    = AI_PASSIVE;

    if (0 !=
        (status = getaddrinfo(def_dns.data(), def_port.data(), &hint, &addr)))
    {
        std::cerr << status << " getaddrinfo error: " << gai_strerror(status)
                  << std::endl;
        return 0;
    }

    addrinfo*   iter = addr;
    std::string ipv;
    void*       address;
    int         yes = 1;
    while (iter != nullptr)
    {
        if (iter->ai_family == AF_INET)
        {
            // taking IPv4 address
            sockaddr_in* ipv4 = reinterpret_cast<sockaddr_in*>(iter->ai_addr);
            address           = &(ipv4->sin_addr);
            ipv               = "IPv4";
        }
        else
        {
            // taking IPv6 address
            sockaddr_in6* ipv6 = reinterpret_cast<sockaddr_in6*>(iter->ai_addr);
            address            = &(ipv6->sin6_addr);
            ipv                = "IPv6";
        }

        // converting to presentation
        inet_ntop(iter->ai_family, address, addr_str, sizeof(addr_str));
        std::cout << ipv << ": " << addr_str << std::endl;

        local_socket_fd =
            socket(iter->ai_family, iter->ai_socktype, iter->ai_protocol);
        if (local_socket_fd == -1)
        {
            perror("socket");
            close(local_socket_fd);
            iter = iter->ai_next;
            continue;
        }
        std::cout << "Socket was created\n";

        if (setsockopt(local_socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(yes)) == -1)
        {
            perror("setsockopt");
            continue;
        }
        if (bind(local_socket_fd, iter->ai_addr, iter->ai_addrlen) == -1)
        {
            perror("bind");
        }
        std::cout << "Socket was bind\n";

        if (-1 == listen(local_socket_fd, 5))
        {
            perror("listen");
        }
        std::cout << "Starting listen...\n";

        iter = iter->ai_next;
    }

    // todo: clarify:
    // all the time ip address is 16.0.0.0
    // std::cout << "ip:"
    //           << inet_ntop(addr->ai_family, &addr->ai_addrlen, addr_str,
    //                        sizeof(addr_str))
    //           << std::endl;

    close(local_socket_fd);
    freeaddrinfo(addr);
    return EXIT_SUCCESS;
}