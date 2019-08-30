#include <coil/stringutil.h>
#include <iostream>

void test(std::string&& a, std::string const& expect)
{
  std::cout << "result=" << (a == expect) << " <" << a << ">\n";
}

std::string f(){ return "aiueo "; }

int main(void)
{
  test(coil::eraseTailBlank("aiueo"), "aiueo");
  test(coil::eraseTailBlank("aiueo "), "aiueo");
  test(coil::eraseTailBlank("aiueo  "), "aiueo");
  test(coil::eraseTailBlank("aiueo   "), "aiueo");
  std::string a0 = "aiueo  ";
  test(coil::eraseTailBlank(a0), "aiueo");
  test(coil::eraseTailBlank(std::move(a0)), "aiueo");
  test(coil::eraseTailBlank("aiueo	 "), "aiueo");
  std::string a1 = "aiueo	 ";
  test(coil::eraseTailBlank(a1), "aiueo");
  test(coil::eraseTailBlank(std::move(a1)), "aiueo");
  test(coil::eraseTailBlank(f()), "aiueo");
  test(coil::eraseTailBlank("aiu eo"), "aiu eo");
  test(coil::eraseTailBlank(std::string()), "");
  test(coil::eraseTailBlank(""), "");
  test(coil::eraseTailBlank(" "), "");
  test(coil::eraseTailBlank("\t"), "");
  test(coil::eraseTailBlank("\n"), "\n");
  test(coil::eraseTailBlank("\v"), "\v");
  test(coil::eraseTailBlank("\f"), "\f");
  test(coil::eraseTailBlank("\r"), "\r");
  test(coil::eraseTailBlank("\r\n"), "\r\n");
}
