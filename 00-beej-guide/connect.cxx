// todo: clarify how to setup local ip from where connection is made
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    // getting parameters
    if (argc < 2)
    {
        std::cout << "Wrong usage\n";
        return 0;
    }

    // initializing and creation local structs
    int         status{ 0 };
    int         socketfd;
    addrinfo    hints;
    addrinfo*   res;
    addrinfo*   res_iter;
    char        ipstr[INET6_ADDRSTRLEN];
    std::string dns{ argv[1] };
    std::string port{ "3490" };

    if (argc == 3)
    {
        port = argv[2];
    }

    // setting up addrinfo hint struct
    memset(&hints, 0, sizeof(hints));
    hints.ai_family =
        AF_UNSPEC; // IP version (uncpecified maybe any IPv4 or IPv6)
    hints.ai_socktype = SOCK_STREAM; // Socket type (TCP is set up)
    // if you what to set up your self IP set AI_PASSIVE
    // hints.ai_flags = AI_PASSIVE;

    // checking getaddrinfo call. getaddrinfo just seting up all neccessary
    // strctures and resturn
    if ((status = getaddrinfo(dns.c_str(), port.c_str(), &hints, &res)) != 0)
    {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        freeaddrinfo(res);
        return 0;
    }

    // checking structures and trying connect with valid structure
    for (res_iter = res; res_iter != nullptr; res_iter = res_iter->ai_next)
    {
        socketfd = socket(res_iter->ai_family, res_iter->ai_socktype,
                          res_iter->ai_protocol);
        if (socketfd == -1)
        {
            perror("Can't open socket\n");
            continue;
        }
        if (connect(socketfd, res_iter->ai_addr, res_iter->ai_addrlen) == -1)
        {
            close(socketfd);
            perror("Can't connect\n");
            continue;
        }
    }

    std::cout << "Connected to: " << dns << ":" << port << std::endl;

    freeaddrinfo(res);
    return 0;
}