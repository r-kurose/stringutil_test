#include <coil/stringutil.h>
#include <iostream>

void test (std::string x, std::string exp)
{
    std::cout << "** TEST START(size=" << x.length() << ")\n";
    std::string out{coil::unescape(x)};
    std::cout << " [" << (exp == out ? "OK" : "FAIL") << ":size=" << out.length() <<"]";
    for(unsigned i = 0; i < out.length(); i++)
    {
        printf("%x ", out[i]);
    }
    printf("\n");
}

int main(void)
{
    // empty
    test(std::string(), "");
    // replace
    test("\\t", "\t");
    test("\\n", "\n");
    test("\\f", "\f");
    test("\\r", "\r");
    test("\\\"", "\"");
    test("\\\'", "\'");
    test("\\\\", "\\");
    test("abcd\\", "abcd");
    // no-replace
    test("\\v", "v");
    test("\\a", "a");
    test("a", "a");
    // replace and no-repalce
    test("a\\tb\\n", "a\tb\n");
}
