#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/types.h>

bool uniqueChar(std::string str)
{
    // Use bit array to check if more than 1 chars are the same (the same bit set)
    uint32_t asciTable[8];

    memset(asciTable, 0, sizeof(asciTable));

    auto len = str.length();
    for (size_t i = 0; i < len; i++)
    {
        int unit = (int)str[i] / 32;
        int offset = (int)str[i] % 32;

        // check if bit already set, if yes, return false.
        // if no, set it.

        auto isBitSet = [](uint32_t val, uint32_t k)
        {
            if ((val & (1 << k)) > 0)
            {
                return true;
            }
            else
            {
                return false;
            }
        };

        if (isBitSet(asciTable[unit], offset))
        {
            return false;
        }
        else
        {
            // set the bit
            asciTable[unit] |= (1 << offset);
        }
    }
    return true;
}

int main(int argc, const char** argv) {

    std::string word1("copyrightable");

    if (uniqueChar(word1)) {
        std::cout << "right!" << std::endl;

    }

    return 0;
}
