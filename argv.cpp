#include <coil/stringutil.h>
#include <iostream>

// A=1 B=2 AB=3 a=4 ./a.out
int main(void)
{
    coil::Argv a0{coil::split("aiueo.exe -a a123 -b b345 -c c567", " ")};
    char** argv = a0.get();
    for (uint64_t i = 0; i < a0.size(); ++i)
    {
        std::cout << "<" << argv[i] << ">";
    }
    std::cout << std::endl;

    std::string s{"aiueo"};
    std::vector<char> tmp{s.c_str(), s.c_str() + 4};
    for(int i = 0; i < tmp.size(); i++) printf("'%x', ", tmp[i]);
    printf("\nsize=%zu,%lu\n", tmp.size(), s.size());
    printf("%s\n", tmp.data());
}
