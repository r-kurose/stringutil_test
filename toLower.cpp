#include <coil/stringutil.h>
#include <iostream>

void test(std::string const& a, std::string const& expect)
{
  std::cout << "result=" << (a == expect) << " <" << a << ">\n";
}

std::string f(){ return "AIUEO"; }

int main(void)
{
  test(coil::toLower("AIUEO"), "aiueo");
  test(coil::toLower("Aiueo"), "aiueo");
  test(coil::toLower("aiueo"), "aiueo");
  std::string a0 = "AIUEO";
  test(coil::toLower(a0), "aiueo");
  test(coil::toLower(std::move(a0)), "aiueo");
  test(coil::toLower(f()), "aiueo");
  test(coil::toLower(""), "");
  test(coil::toLower(std::string()), "");
}
