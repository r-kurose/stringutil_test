#include <coil/stringutil.h>
#include <string>
#include <iostream>

static uint32_t failure_count;

void test(std::string in, std::string const& exp)
{
    auto out{coil::replaceEnv(in)};
    std::cout << '[' << (out == exp ? "OK" : "Failure") << "] <" << in << ">";
    if (out != exp)
    {
        ++failure_count;
        std::cout << " out=<" << out << ">" << " exp=<" << exp  << ">";
    }
    std::cout << "\n";
}

// A=1 B=2 AB=3 A_B=4 _A=5 a=6 ab=7 a_b=8 _a=9 C='${A}' ./a.out
int main(void)
{
    // empty
    test("", "");

    // replace
    test("${A}", "1");
    test("${AB}", "3");
    test("${A_B}", "4");
    test("${_A}", "5");
    test("${a}", "6");
    test("${ab}", "7");
    test("${a_b}", "8");
    test("${_a}", "9");
    // replace recurse
    test("${C}", "1");
    //replace more than one
    test("${A}${A}", "11");
    test("${A}${B}", "12");
    test("${A}${B}${A}", "121");
    test("A${A}", "A1");
    test("${A}A", "1A");
    test("A${A}A", "A1A");
    test("AAAA${A}AABB${B}BBBB", "AAAA1AABB2BBBB");
    test("A${A}\n${A}", "A1\n1");

    // no-replace
    test("AAAA_BB", "AAAA_BB");
    test("${AA}", "");
    test("${ABC}", "");
    test("${Z}", "");
    test("A${Z}", "A");
    test("${Z}A", "A");
    test("${X}${Y}${Z}", "");
    test("${X}A${Y}A${Z}", "AA");

    // both
    test("A${A}${Z}${A}", "A11");
    test("A${A}${B}${z}${C}${AB}${a_b_c}${a}${a_b}", "A121368");
}
