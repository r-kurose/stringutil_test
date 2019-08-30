#include <coil/stringutil.h>
#include <iostream>

void test (std::string x)
{
    std::cout << "** TEST START\n";
    std::stringbuf buf{x.c_str()};
    std::istream is{&buf};

    for (unsigned i = 0; i < 100; ++i)
    {
        std::string out;
#if 1
        out = coil::getlinePortable(is);
#else
        coil::getlinePortable(is, out);
#endif
        if(!out.empty())
        {
            for(int i = 0; out[i] != '\0'; ++i){
                printf("%x ", out[i]);
            }
            printf("[EOL]\n");
        }
    }
}

int main(void)
{
    test(std::string());
    test("\n");
    test("\r");
    test("\r\n");
    test("0");
    test("1\n");
    test("2\r");
    test("3\r\n");
    test("4\n\n5");
    test("6\r\r7");
    test("8\r\n\r\n9");

    test("a\rb\rc\r");
    test("d\r\re\r\rfg\r\rn");
}
