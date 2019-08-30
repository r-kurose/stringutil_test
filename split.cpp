#include <coil/stringutil.h>
#include <iostream>

void test(std::string x, std::string delim, bool ignore, std::vector<std::string> exp)
{
    std::cout << "** TEST START(" << x << ")\n";
    auto out{coil::split(x, delim, ignore)};
    std::cout << " [" << (exp == out ? "OK" : "FAIL") << ":size=" << out.size() <<"]";
    for(auto itr : out)
    {
        std::cout << '<' << itr << ">";
    }
    std::cout << "[FIN]\n";
}

int main(void)
{
    // ignore == false
    //// empty
    test(std::string(), "a", false, {});
#if 1
    test("aaaa,bbbb", std::string(),  false, {"aaaa,bbbb"});
    test(" aaaa,bbbb ", std::string(),  false, {"aaaa,bbbb"});
    test(std::string(), std::string(),  false, {""});
#endif
    //// split, delimiter=,
    test("aaaa,bbbb,cccc", ",", false, {"aaaa", "bbbb", "cccc"});
    test("aaaa,bbbb,cccc,", ",", false, {"aaaa", "bbbb", "cccc", ""});  // right
    test(",aaaa,bbbb,cccc", ",", false, {"", "aaaa", "bbbb", "cccc"}); //left
    test("aaaa,bbbb,,cccc", ",", false, {"aaaa", "bbbb", "", "cccc"}); //centor
    test("aaaa,bbbb,cccc,,", ",", false, {"aaaa", "bbbb", "cccc", "", ""}); // right x2
    //// split no-inogre space
    test(" , aaaa ,  bbbb  ,   cccc", ",", false, {"", "aaaa", "bbbb", "cccc"});
    //// split, delimiter=" "
    test("aaaa bbbb cccc",  " ", false, {"aaaa", "bbbb", "cccc"});
    test("aaaa bbbb cccc ", " ", false, {"aaaa", "bbbb", "cccc", ""}); // right
    test(" aaaa bbbb cccc",  " ", false, {"", "aaaa", "bbbb", "cccc"}); // left
    test("aaaa bbbb  cccc",  " ", false, {"aaaa", "bbbb", "", "cccc"}); // centor
    test("aaaa bbbb cccc  ", " ", false, {"aaaa", "bbbb", "cccc", "", ""}); // right x2
    //// split, delimiter="@@"
    test("aaaa@@bbbb@@cccc", "@@", false, {"aaaa", "bbbb", "cccc"});
    test("aaaa@@bbbb@@cccc@@", "@@", false, {"aaaa", "bbbb", "cccc", ""});  // right
    test("@@aaaa@@bbbb@@cccc", "@@", false, {"", "aaaa", "bbbb", "cccc"}); //left
    test("aaaa@@bbbb@@@@cccc", "@@", false, {"aaaa", "bbbb", "", "cccc"}); //centor
    test("aaaa@@bbbb@@cccc@@@@", "@@", false, {"aaaa", "bbbb", "cccc", "", ""}); // right x2
    test("aaaa@bbbb@@cccc", "@@", false, {"aaaa@bbbb", "cccc"}); // include a part of delim.
    test("aaaa@@bbbb@@@cccc", "@@", false, {"aaaa", "bbbb", "@cccc"}); // include a part of delim.

    // ignore == true
    //// empty
    test(std::string(), "a", true, {});
#if 1
    test("aaaa,bbbb", std::string(),  true, {"aaaa,bbbb"});
    test(" aaaa,bbbb ", std::string(),  true, {"aaaa,bbbb"});
    test(std::string(), std::string(),  false, {});
#endif
    //// split, delimiter=,
    test("aaaa,bbbb,cccc", ",", true, {"aaaa", "bbbb", "cccc"});
    test("aaaa,bbbb,cccc,", ",", true, {"aaaa", "bbbb", "cccc"});  // right
    test(",aaaa,bbbb,cccc", ",", true, {"aaaa", "bbbb", "cccc"}); //left
    test("aaaa,bbbb,,cccc", ",", true, {"aaaa", "bbbb", "cccc"}); //centor
    test("aaaa,bbbb,cccc,,", ",", true, {"aaaa", "bbbb", "cccc"}); // right x2
    //// split no-inogre space
    test(" , aaaa ,  bbbb  ,   cccc", ",", true, {"aaaa", "bbbb", "cccc"});
    //// split, delimiter=" "
    test("aaaa bbbb cccc",  " ", true, {"aaaa", "bbbb", "cccc"});
    test("aaaa bbbb cccc ", " ", true, {"aaaa", "bbbb", "cccc"}); // right
    test(" aaaa bbbb cccc",  " ", true, {"aaaa", "bbbb", "cccc"}); // left
    test("aaaa bbbb  cccc",  " ", true, {"aaaa", "bbbb", "cccc"}); // centor
    test("aaaa bbbb cccc  ", " ", true, {"aaaa", "bbbb", "cccc"}); // right x2
    //// split, delimiter="@@"
    test("aaaa@@bbbb@@cccc", "@@", true, {"aaaa", "bbbb", "cccc"});
    test("aaaa@@bbbb@@cccc@@", "@@", true, {"aaaa", "bbbb", "cccc"});  // right
    test("@@aaaa@@bbbb@@cccc", "@@", true, {"aaaa", "bbbb", "cccc"}); //left
    test("aaaa@@bbbb@@@@cccc", "@@", true, {"aaaa", "bbbb", "cccc"}); //centor
    test("aaaa@@bbbb@@cccc@@@@", "@@", true, {"aaaa", "bbbb", "cccc"}); // right x2
    test("aaaa@bbbb@@cccc", "@@", true, {"aaaa@bbbb", "cccc"}); // include a part of delim.
    test("aaaa@@bbbb@@@cccc", "@@", true, {"aaaa", "bbbb", "@cccc"}); // include a part of delim.
}
