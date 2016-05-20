#include <locale>

#include "hexstring.hpp"


HexString::HexString(const std::string &initHexStr)
{
    // save original hex string in class
    hexStr = initHexStr;

    // all letters('A' 'B' .. 'F') should be in upper casses
    std::locale loc;
    for (auto& ch : hexStr) { ch = std::toupper(ch,loc); }

    isCorrect = true;
    number = 0;

    for (const auto& ch : hexStr)
    {
        if (ch >= '0' && ch <= '9')
        {
            number <<= 4;
            number += ch - '0';
        }
        else if (ch >= 'A' && ch <= 'F')
        {
            number <<= 4;
            number += ch - 'A' + 10;
        }
        else
        {
            isCorrect = false;
            break;
        }
    }
}
