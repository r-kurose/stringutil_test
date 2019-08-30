#include <coil/stringutil.h>
#include <iostream>
#include <cstdio>

static unsigned failure_count;

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
    std::vector<int> const port_in_range = {0, 9, 99, 999, 9999, 59999,
                                            64999, 65499, 65529, 65535};
    for (auto& a : ip_in_range)
    for (auto& b : ip_in_range)
    for (auto& c : ip_in_range)
    for (auto& d : ip_in_range)
        for (auto& p : port_in_range)
        {
            std::array<char, 100> str;
            std::sprintf(&str[0], "%d.%d.%d.%d:%d", a, b, c, d, p);
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
            std::sprintf(&str[0], "%d.%d.%d.%d:0", a, b, c, out);
            test(&str[0], false);
            std::sprintf(&str[0], "%d.%d.%d.%d:0", a, b, out, c);
            test(&str[0], false);
            std::sprintf(&str[0], "%d.%d.%d.%d:0", a, out, b, c);
            test(&str[0], false);
            std::sprintf(&str[0], "%d.%d.%d.%d:0", out, a, b, c);
            test(&str[0], false);
        }

    std::vector<int> const port_out_range = {-1, 65536, 69999, 100000};
    for (auto& out : port_out_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "0.0.0.0:%d", out);
        test(&str[0], false);
    }

    // hex format (not support)
    for (auto& a : ip_in_range)
    for (auto& b : ip_in_range)
    for (auto& c : ip_in_range)
    for (auto& d : ip_in_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "%#x.%#x.%#x.%#x:0", a, b, c, d);
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
        std::sprintf(&str[0], "%#o.%#o.%#o.%#o:0", a, b, c, d);
        if (a != 0 && b != 0 && c != 0 && d != 0)
            test(&str[0], false);
    }

    // less than three dot (not support)
    test("1:0", false); // no dot
    test("01:0", false); // no dot, oct
    test("0x1:0", false); // no dot, hex
    test("1.0:0", false); // one dot
    test("1.00:0", false); // one dot, oct
    test("1.0x0:0", false); // one dot, hex
    test("1.0.0:0", false); // two dot
    test("1.0.00:0", false); // two dot, oct
    test("1.0.0x0:0", false); // two dot, hex

    // illegal
    test("", false); // empty
    test("abcd", false); // non number
    test("192.168.0.1", false); // ip only
    test("...", false); // dot only
    test("...:", false); // dot only
    test("1.1.1.1.1:100", false); // four dot
    test("a.0.0.0:0", false); // non number in ip
    test("0.0.0.0:a", false); // non number in port
    //oct port
    for (auto& p : port_in_range)
    {
        if (p == 0) continue;
        std::array<char, 100> str;
        std::sprintf(&str[0], "%d.%d.%d.%d:%#o", 0, 0, 0, 0, p);
        test(&str[0], false);
    }
    //hex port
    for (auto& p : port_in_range)
    {
        if (p == 0) continue;
        std::array<char, 100> str;
        std::sprintf(&str[0], "%d.%d.%d.%d:%#x", 0, 0, 0, 0, p);
        test(&str[0], false);
    }
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
    std::vector<int> const port_in_range = {0, 9, 99, 999, 9999, 59999,
                                            64999, 65499, 65529, 65535};
    for (auto& a : ip_in_range)
        for (auto& p : port_in_range)
    {
        std::array<char, 100> str;
        // lower char
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", a, 0, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, a, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, a, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, a, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, a, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, a, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, 0, a, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, 0, 0, a, p);
        test(&str[0], true);

        //upper char
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", a, 0, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, a, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, 0, a, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, 0, 0, a, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, 0, 0, 0, a, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, 0, 0, 0, 0, a, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, 0, 0, 0, 0, 0, a, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%X:%X:%X:%X:%X:%X:%X:%X]:%d", 0, 0, 0, 0, 0, 0, 0, a, p);
        test(&str[0], true);

        // lower char with zeros.
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", a, 0, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, a, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, 0, a, 0, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, 0, 0, a, 0, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, 0, 0, 0, a, 0, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, 0, 0, 0, 0, a, 0, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, 0, 0, 0, 0, 0, a, 0, p);
        test(&str[0], true);
        std::sprintf(&str[0], "[%04x:%04x:%04x:%04x:%04x:%04x:%04x:%04x]:%d", 0, 0, 0, 0, 0, 0, 0, a, p);
        test(&str[0], true);

    }

    // Fail
    std::vector<int> const ip_out_range = {0x10000};
    for (auto& a : ip_out_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", a, 0, 0, 0, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, a, 0, 0, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, a, 0, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, a, 0, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, a, 0, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, a, 0, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, 0, a, 0, 0);
        test(&str[0], false);
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, 0, 0, a, 0);
        test(&str[0], false);
    }

    std::vector<int> const port_out_range = {-1, 65536, 69999, 100000};
    for (auto& p : port_out_range)
    {
        std::array<char, 100> str;
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%d", 0, 0, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], false);
    }

    // not support format
    test("[::1]:1", false);
    test("[1::]:1", false);
    test("[1:1:1:1::1:1]:1", false);

    // illegal
    test("", false); // empty
    test("abcd", false); // non-nmber
    test("1:2:3:4:5:6:7:8", false); // ip only
    test("[1:2:3:4:5:6:7:8]", false); // ip only
    test("[1:2:3:4:5:6:7:8]:", false); // ip only
    test("[:::::::]:", false); // separator only
    test("[1:2:3:4:5:6:7]:100", false); // too few parts in ip
    test("[1:2:3:4:5:6:7:8:9]:100", false); // too many parts in ip
    test("[1:2:3:4:5:6:7:g]:100", false); // non number in ip
    test("[1:2:3:4:5:6:7:8]:g", false); // non number in port
    // oct port
    for (auto& p : port_in_range)
    {
        if (p == 0) continue;
        std::array<char, 100> str;
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%#o", 0, 0, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], false);
    }
    // hex port
    for (auto& p : port_in_range)
    {
        if (p == 0) continue;
        std::array<char, 100> str;
        std::sprintf(&str[0], "[%x:%x:%x:%x:%x:%x:%x:%x]:%#x", 0, 0, 0, 0, 0, 0, 0, 0, p);
        test(&str[0], false);
    }
}

int main ()
{
    test_isIPv4();
    test_isIPv6();
    std::cout << "SUMMARY: The number of failure = " << failure_count << std::endl;
    return 0;
}
