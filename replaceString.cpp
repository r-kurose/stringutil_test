#include <coil/stringutil.h>
#include <iostream>

int main(void)
{
    std::cout << coil::replaceString("", "", "") << std::endl;
    std::cout << coil::replaceString("AAAA", "A", "B") << std::endl;
    std::cout << coil::replaceString("AAAA", "AA", "B") << std::endl;
    std::cout << coil::replaceString("AAAA", "AAA", "B") << std::endl;
    std::cout << coil::replaceString("AAAA", "C", "B") << std::endl;
    std::cout << coil::replaceString("ABCD", "B", "") << std::endl;
    std::cout << coil::replaceString("ABCD", "BC", "") << std::endl;
}
