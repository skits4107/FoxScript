#include <iostream>

int main() {
    #if __cplusplus
        std::cout << "C++ version: " << __cplusplus << std::endl;
    #else
        std::cout << "C++ is not defined" << std::endl;
    #endif
    return 0;
}