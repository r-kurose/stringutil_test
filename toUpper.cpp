#include <coil/stringutil.h>
#include <iostream>

void test(std::string const& a, std::string const& expect)
{
  std::cout << "result=" << (a == expect) << " <" << a << ">\n";
}

std::string f(){ return "aiueo"; }

int main(void)
{
  test(coil::toUpper("AIUEO"), "AIUEO");
  test(coil::toUpper("Aiueo"), "AIUEO");
  test(coil::toUpper("aiueo"), "AIUEO");
  std::string a0 = "aiueo";
  test(coil::toUpper(a0), "AIUEO");
  test(coil::toUpper(std::move(a0)), "AIUEO");
  test(coil::toUpper(f()), "AIUEO");
  test(coil::toLower(""), "");
  test(coil::toLower(std::string()), "");
}
