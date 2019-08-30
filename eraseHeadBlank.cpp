#include <coil/stringutil.h>
#include <iostream>

void test(std::string&& a, std::string const& expect)
{
  std::cout << "result=" << (a == expect) << " <" << a << ">\n";
}

std::string f(){ return "  aiueo"; }

int main(void)
{
  test(coil::eraseHeadBlank("aiueo"), "aiueo");
  test(coil::eraseHeadBlank(" aiueo"), "aiueo");
  test(coil::eraseHeadBlank("  aiueo"), "aiueo");
  test(coil::eraseHeadBlank("   aiueo"), "aiueo");
  std::string a0 = "  aiueo";
  test(coil::eraseHeadBlank(a0), "aiueo");
  test(coil::eraseHeadBlank(std::move(a0)), "aiueo");
  test(coil::eraseHeadBlank("	 aiueo"), "aiueo");
  std::string a1 = "	 aiueo";
  test(coil::eraseHeadBlank(a1), "aiueo");
  test(coil::eraseHeadBlank(std::move(a1)), "aiueo");
  test(coil::eraseHeadBlank(f()), "aiueo");
  test(coil::eraseHeadBlank("aiu eo"), "aiu eo");
  test(coil::eraseHeadBlank(std::string()), "");
  test(coil::eraseHeadBlank(""), "");
  test(coil::eraseHeadBlank(" "), "");
  test(coil::eraseHeadBlank("\t"), "");
  test(coil::eraseHeadBlank("\n"), "\n");
  test(coil::eraseHeadBlank("\v"), "\v");
  test(coil::eraseHeadBlank("\f"), "\f");
  test(coil::eraseHeadBlank("\r"), "\r");
  test(coil::eraseHeadBlank("\r\n"), "\r\n");
}
