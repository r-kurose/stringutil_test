#include <coil/stringutil.h>
#include <string>
#include <iostream>
#include <cstdio>

static unsigned failure_count;

void test_isAbsolutePath()
{
    auto test = [](std::string const str, bool exp) {
      auto res = coil::isAbsolutePath(str);
      std::cout << '[' << (res == exp ? "OK" : "Fail") << ']'
                << " \"" << str << "\" exp=(" << (exp ? "true" : "false") << ')'
                << '\n';
      if (res != exp) {
          failure_count += 1;
      }
      return res;
    };

    // OK
    test("/", true);
    test("/aiueo", true);
    // ASCII or UTF only
    for (char c = 'a'; c <= 'z'; ++c) {
        test(std::string{c} + ":\\", true);
        test(std::string{c} + ":\\aiueo", true);
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        test(std::string{c} + ":\\", true);
        test(std::string{c} + ":\\aiueo", true);
    }
    test("\\\\", true);

    // Failure
    test("", false); // empty
    // add char to head.
    test("a/", false);
    test("ac:\\", false);
    test("aC:\\", false);
    test("a\\\\", false);
    // lack chars
    test(":\\", false);
    test("\\", false);
    test(":", false);
    test("\\", false);
    test(":\\a", false);
    test("\\a", false);
    test("\\a", false);
}

void test_isURL()
{
    auto test = [](char const* str, bool exp) {
      auto res = coil::isURL(str);
      std::cout << '[' << (res == exp ? "OK" : "Fail") << ']'
                << " \"" << str << "\" exp=(" << (exp ? "true" : "false") << ')'
                << '\n';
      if (res != exp) {
          failure_count += 1;
      }
      return res;
    };

    // OK
    test("http://xxx", true);
    test("h://xxx", true);

    // Failure
    test("", false); // empty
    test("http", false); // normal string
    test("://", false); // "://" is top
    test("://xxx", false); // "://" is top
    test(":", false);      // only :
    test(":/", false);     // only :/
    test("http:", false);  // only :
    test("http:/", false); // only :/
}

void test_isIPv4()
{
    auto test = [](char const* str, bool exp) {
      auto res = coil::isIPv4(str);
      std::cout << '[' << (res == exp ? "OK" : "Fail") << ']'
                << " \"" << str << "\" exp=(" << (exp ? "true" : "false") << ')'
                << '\n';
      if (res != exp) { failure_count += 1; }
      return res;
    };

    // OK
    std::vector<int> const ip_in_range = {0, 9, 99, 199, 249, 255};
    for (auto& a : ip_in_range)
    for (auto& b : ip_in_range)
    for (auto& c : ip_in_range)
    for (auto& d : ip_in_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "%d.%d.%d.%d", a, b, c, d);
        test(&str[0], true);
    }

    // Fail
    std::vector<int> const ip_out_range = {-1, 256, 1000, 1000};
    for (auto& a : ip_in_range)
    for (auto& b : ip_in_range)
    for (auto& c : ip_in_range)
        for (auto& out : ip_out_range)
        {
            std::array<char, 100> str;
            std::sprintf(&str[0], "%d.%d.%d.%d", a, b, c, out);
            test(&str[0], false);
            std::sprintf(&str[0], "%d.%d.%d.%d", a, b, out, c);
            test(&str[0], false);
            std::sprintf(&str[0], "%d.%d.%d.%d", a, out, b, c);
            test(&str[0], false);
            std::sprintf(&str[0], "%d.%d.%d.%d", out, a, b, c);
            test(&str[0], false);
        }

    // hex format (not support)
    for (auto& a : ip_in_range)
    for (auto& b : ip_in_range)
    for (auto& c : ip_in_range)
    for (auto& d : ip_in_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "%#x.%#x.%#x.%#x", a, b, c, d);
        if (a != 0 && b != 0 && c != 0 && d != 0)
            test(&str[0], false);
    }

    // oct format (not support)
    for (auto& a : ip_in_range)
    for (auto& b : ip_in_range)
    for (auto& c : ip_in_range)
    for (auto& d : ip_in_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "%#o.%#o.%#o.%#o", a, b, c, d);
        if (a != 0 && b != 0 && c != 0 && d != 0)
            test(&str[0], false);
    }

    // less than three dot (not support)
    test("1", false); // no dot
    test("01", false); // no dot, oct
    test("0x1", false); // no dot, hex
    test("1.0", false); // one dot
    test("1.00", false); // one dot, oct
    test("1.0x0", false); // one dot, hex
    test("1.0.0", false); // two dot
    test("1.0.00", false); // two dot, oct
    test("1.0.0x0", false); // two dot, hex

    // illegal
    test("", false); // empty
    test("abcd", false); // non number
    test("192.168.0.1:100", false); // ip with port
    test("...", false); // dot only
    test("...:", false); // dot only
    test("1.1.1.1.1", false); // four dot
    test("a.0.0.0", false); // non number in ip
}

void test_isIPv6()
{
    auto test = [](char const* str, bool exp) {
      auto res = coil::isIPv6(str);
      std::cout << '[' << (res == exp ? "OK" : "Fail") << ']'
                << " \"" << str << "\" exp=(" << (exp ? "true" : "false") << ')'
                << '\n';
      if (res != exp) { failure_count += 1; }
      return res;
    };

    // OK
    std::vector<int> const ip_in_range = {0, 0xf, 0xff, 0xff, 0xfff, 0xffff};
    for (auto& a : ip_in_range)
    {
        std::array<char, 100> str;
        // lower char
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", a, 0, 0, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, a, 0, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, a, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, a, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, a, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, 0, a, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, 0, 0, a, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, 0, 0, 0, a);
        test(&str[0], true);

        //upper char
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", a, 0, 0, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, a, 0, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, 0, a, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, 0, 0, a, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, 0, 0, 0, a, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, 0, 0, 0, 0, a, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, 0, 0, 0, 0, 0, a, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%X:%X:%X:%X:%X:%X:%X:%X", 0, 0, 0, 0, 0, 0, 0, a);
        test(&str[0], true);

        // lower char with zeros.
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", a, 0, 0, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, a, 0, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, 0, a, 0, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, 0, 0, a, 0, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, 0, 0, 0, a, 0, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, 0, 0, 0, 0, a, 0, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, 0, 0, 0, 0, 0, a, 0);
        test(&str[0], true);
        std::sprintf(&str[0], "%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x", 0, 0, 0, 0, 0, 0, 0, a);
        test(&str[0], true);
    }

    // Fail
    std::vector<int> const ip_out_range = {0x10000};
    for (auto& a : ip_out_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", a, 0, 0, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, a, 0, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, a, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, a, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, a, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, 0, a, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, 0, 0, a, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "%x:%x:%x:%x:%x:%x:%x:%x", 0, 0, 0, 0, 0, 0, 0, a);
        test(&str[0], false);
    }

    // not support format
    test("::1", false);
    test("1::", false);
    test("1:1:1:1::1:1", false);

    // illegal
    test("]:1", false); // empty
    test("", false); // empty
    test("abcd", false); // non-nmber
    test("[1:2:3:4:5:6:7:8]:9", false); // ip with port
    test(":::::::", false); // separator only
    test("1:2:3:4:5:6:7", false); // too few parts in ip
    test("1:2:3:4:5:6:7:8:9", false); // too many parts in ip
    test("1:2:3:4:5:6:7:g", false); // non number in ip
}

int main ()
{
    test_isAbsolutePath();
    test_isURL();
    test_isIPv4();
    test_isIPv6();
    std::cout << "SUMMARY: The number of failure = " << failure_count << std::endl;
    return 0;
}
