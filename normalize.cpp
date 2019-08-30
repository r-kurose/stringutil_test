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
  test(coil::normalize("aiueo"), "aiueo");
  test(coil::normalize("aiu eo"), "aiu eo");
  test(coil::normalize(std::string()), "");
  test(coil::normalize(""), "");
  test(coil::normalize(" "), "");
  test(coil::normalize("\t"), "");
  test(coil::normalize("\n"), "\n");
  test(coil::normalize("\v"), "\v");
  test(coil::normalize("\f"), "\f");
  test(coil::normalize("\r"), "\r");
  test(coil::normalize("\r\n"), "\r\n");

  //head
  test(coil::normalize(" aiueo"), "aiueo");
  test(coil::normalize("  aiueo"), "aiueo");
  test(coil::normalize("   aiueo"), "aiueo");
  std::string a0 = "  aiueo";
  test(coil::normalize(a0), "aiueo");
  test(coil::normalize(std::move(a0)), "aiueo");
  test(coil::normalize("	 aiueo"), "aiueo");
  std::string a1 = "	 aiueo";
  test(coil::normalize(a1), "aiueo");
  test(coil::normalize(std::move(a1)), "aiueo");
  test(coil::normalize(f_head()), "aiueo");

  //tail
  test(coil::normalize("aiueo "), "aiueo");
  test(coil::normalize("aiueo  "), "aiueo");
  test(coil::normalize("aiueo   "), "aiueo");
  std::string b0 = "aiueo  ";
  test(coil::normalize(b0), "aiueo");
  test(coil::normalize(std::move(b0)), "aiueo");
  test(coil::normalize("aiueo	 "), "aiueo");
  std::string b1 = "aiueo	 ";
  test(coil::normalize(b1), "aiueo");
  test(coil::normalize(std::move(b1)), "aiueo");
  test(coil::normalize(f_tail()), "aiueo");

  //Both
  test(coil::normalize(" aiueo "), "aiueo");
  test(coil::normalize("  aiueo  "), "aiueo");
  test(coil::normalize("   aiueo   "), "aiueo");
  std::string c0 = "  aiueo  ";
  test(coil::normalize(c0), "aiueo");
  test(coil::normalize(std::move(c0)), "aiueo");
  test(coil::normalize("	aiueo	 "), "aiueo");
  std::string c1 = " 	aiueo	 ";
  test(coil::normalize(c1), "aiueo");
  test(coil::normalize(std::move(c1)), "aiueo");
  test(coil::normalize(f_tail()), "aiueo");

  //lower
  test(coil::normalize("AIueo"), "aiueo");
  test(coil::normalize(" AiUeO "), "aiueo");
}
