#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Helo, world!" < std::endl;
    for (size_t i = 0; i < argc; i++)
    {
        std::cout << argv[i] << std::endl;
    }

    return 0;
}
