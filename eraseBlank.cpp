#include <coil/stringutil.h>
#include <iostream>

void test(std::string&& a, std::string const& expect)
{
  std::cout << "result=" << (a == expect) << " <" << a << ">\n";
}

std::string f(){ return "  ai u  eo  "; }

int main(void)
{
  test(coil::eraseBlank("aiueo"), "aiueo");
  test(coil::eraseBlank("aiueo "), "aiueo");
  test(coil::eraseBlank("aiueo  "), "aiueo");
  test(coil::eraseBlank(" aiueo"), "aiueo");
  test(coil::eraseBlank("  aiueo"), "aiueo");
  test(coil::eraseBlank("ai ueo"), "aiueo");
  test(coil::eraseBlank("ai  ueo"), "aiueo");
  test(coil::eraseBlank(" a i u  e o "), "aiueo");
  test(coil::eraseBlank("  a  i  u  e  o  "), "aiueo");
  std::string a0 = "  ai u  eo  ";
  test(coil::eraseBlank(a0), "aiueo");
  test(coil::eraseBlank(std::move(a0)), "aiueo");
  test(coil::eraseBlank("	 aiueo"), "aiueo");
  std::string a1 = "	 ai u  eo  ";
  test(coil::eraseBlank(a1), "aiueo");
  test(coil::eraseBlank(std::move(a1)), "aiueo");
  test(coil::eraseBlank(f()), "aiueo");
  test(coil::eraseBlank(std::string()), "");
  test(coil::eraseBlank(""), "");
  test(coil::eraseBlank(" "), "");
  test(coil::eraseBlank("\t"), "");
  test(coil::eraseBlank("\n"), "\n");
  test(coil::eraseBlank("\v"), "\v");
  test(coil::eraseBlank("\f"), "\f");
  test(coil::eraseBlank("\r"), "\r");
  test(coil::eraseBlank("\r\n"), "\r\n");
}
