#include <ailib/aierror.h>
#include <iostream>

int main()
{
    std::cout << ai::formatError(-1, "msg") << std::endl;
    std::cout << ai::formatError(-11345325, "msg") << std::endl;
    std::cout << ai::formatError(5424432, "msg") << std::endl;
    return 0;
}
