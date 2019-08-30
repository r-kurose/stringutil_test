#include <coil/stringutil.h>
#include <iostream>

void test(std::string&& a, std::string const& expect)
{
  std::cout << "result=" << (a == expect) << " <" << a << ">\n";
}

std::string f_head(){ return "  aiueo"; }
std::string f_tail(){ return "aiueo  "; }

int main(void)
{
  // nochange
  test(coil::eraseBothEndsBlank("aiueo"), "aiueo");
  test(coil::eraseBothEndsBlank("aiu eo"), "aiu eo");
  test(coil::eraseBothEndsBlank(std::string()), "");
  test(coil::eraseBothEndsBlank(""), "");
  test(coil::eraseBothEndsBlank(" "), "");
  test(coil::eraseBothEndsBlank("\t"), "");
  test(coil::eraseBothEndsBlank("\n"), "\n");
  test(coil::eraseBothEndsBlank("\v"), "\v");
  test(coil::eraseBothEndsBlank("\f"), "\f");
  test(coil::eraseBothEndsBlank("\r"), "\r");
  test(coil::eraseBothEndsBlank("\r\n"), "\r\n");

  //head
  test(coil::eraseBothEndsBlank(" aiueo"), "aiueo");
  test(coil::eraseBothEndsBlank("  aiueo"), "aiueo");
  test(coil::eraseBothEndsBlank("   aiueo"), "aiueo");
  std::string a0 = "  aiueo";
  test(coil::eraseBothEndsBlank(a0), "aiueo");
  test(coil::eraseBothEndsBlank(std::move(a0)), "aiueo");
  test(coil::eraseBothEndsBlank("	 aiueo"), "aiueo");
  std::string a1 = "	 aiueo";
  test(coil::eraseBothEndsBlank(a1), "aiueo");
  test(coil::eraseBothEndsBlank(std::move(a1)), "aiueo");
  test(coil::eraseBothEndsBlank(f_head()), "aiueo");

  //tail
  test(coil::eraseBothEndsBlank("aiueo "), "aiueo");
  test(coil::eraseBothEndsBlank("aiueo  "), "aiueo");
  test(coil::eraseBothEndsBlank("aiueo   "), "aiueo");
  std::string b0 = "aiueo  ";
  test(coil::eraseBothEndsBlank(b0), "aiueo");
  test(coil::eraseBothEndsBlank(std::move(b0)), "aiueo");
  test(coil::eraseBothEndsBlank("aiueo	 "), "aiueo");
  std::string b1 = "aiueo	 ";
  test(coil::eraseBothEndsBlank(b1), "aiueo");
  test(coil::eraseBothEndsBlank(std::move(b1)), "aiueo");
  test(coil::eraseBothEndsBlank(f_tail()), "aiueo");

  //Both
  test(coil::eraseBothEndsBlank(" aiueo "), "aiueo");
  test(coil::eraseBothEndsBlank("  aiueo  "), "aiueo");
  test(coil::eraseBothEndsBlank("   aiueo   "), "aiueo");
  std::string c0 = "  aiueo  ";
  test(coil::eraseBothEndsBlank(c0), "aiueo");
  test(coil::eraseBothEndsBlank(std::move(c0)), "aiueo");
  test(coil::eraseBothEndsBlank("	aiueo	 "), "aiueo");
  std::string c1 = " 	aiueo	 ";
  test(coil::eraseBothEndsBlank(c1), "aiueo");
  test(coil::eraseBothEndsBlank(std::move(c1)), "aiueo");
  test(coil::eraseBothEndsBlank(f_tail()), "aiueo");
}
