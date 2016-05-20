#pragma once

#include <string>

class HexString
{
public:
    HexString(const std::string &initHexStr);

    bool        is_correct()        const { return isCorrect; }
    std::string get_hex_string()    const { return hexStr; }
    unsigned    get_number()        const { return number; }

private:
    std::string hexStr;
    unsigned number     {0};
    bool isCorrect      {false};
};

