#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    // getting parameters
    if (argc > 2)
    {
        std::cout << "Wrong usage\n";
        return 0;
    }

    // initializing and creation local structs
    int       status{ 0 };
    addrinfo  hints;
    addrinfo* res;
    addrinfo* res_iter;
    char      ipstr[INET6_ADDRSTRLEN];

    // setting up addrinfo hint struct
    memset(&hints, 0, sizeof(hints));
    hints.ai_family =
        AF_UNSPEC; // IP version (uncpecified maybe any IPv4 or IPv6)
    hints.ai_socktype = SOCK_STREAM; // Socket type (TCP is set up)
    // if you what to set up your self IP set AI_PASSIVE
    // hints.ai_flags = AI_PASSIVE;

    // checking getaddrinfo call. getaddrinfo just seting up all neccessary
    // strctures and resturn
    if ((status = getaddrinfo(argv[1], "3490", &hints, &res)) != 0)
    {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        return 0;
    }

    // reading result
    for (res_iter = res; res_iter != nullptr; res_iter = res_iter->ai_next)
    {
        void*       address;
        std::string ipver;

        if (res_iter->ai_family == AF_INET)
        {
            // taking IPv4 address
            sockaddr_in* ipv4 =
                reinterpret_cast<sockaddr_in*>(res_iter->ai_addr);
            address = &(ipv4->sin_addr);
            ipver   = "IPv4";
        }
        else
        {
            // taking IPv6 address
            sockaddr_in6* ipv6 =
                reinterpret_cast<sockaddr_in6*>(res_iter->ai_addr);
            address = &(ipv6->sin6_addr);
            ipver   = "IPv6";
        }
        // converting to presentation
        inet_ntop(res_iter->ai_family, address, ipstr, sizeof(ipstr));
        std::cout << ipver << ": " << ipstr << std::endl;
    }

    // free memory
    freeaddrinfo(res);

    return 0;
}
