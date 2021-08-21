#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>

using namespace std;

int strstr(const std::string& haystack, const std::string& needle) // return the index of the substring, -1 if not found
{
    if (needle.empty())
    {
        return -1;
    }
    for (size_t i(0); i < haystack.size(); ++i)
    {
        if (haystack[i] == needle[0])
        {
            size_t j(1);
            for (; j < needle.size() && i + j < haystack.size(); ++j)
            {
                if (haystack[i + j] != needle[j])
                {
                    break;
                }
            }
            if (j == needle.size())
            {
                return i;
            }
        }
    }
    return -1;
}
int main() {
    assert(strstr(string(""), string(""))==-1);
    assert(strstr(string(" "), string(""))==-1);
    assert(strstr(string(""), string(" "))==-1);
    assert(strstr(string(" "), string(" "))==0);
    assert(strstr(string(" "), string("  "))==-1);
    assert(strstr(string("    "), string("  "))==0);
    assert(strstr(string("abcd"), string("bcd"))==1);
    assert(strstr(string("abcd"), string("bc"))==1);
    assert(strstr(string("abcd"), string("bcde"))==-1);
    assert(strstr(string("abcd"), string("d"))==3);
    return 0;
}
