#include "utilities/string.hpp"
#include <cctype>
#include <string>

std::string to_lower(const std::string &input)
{
    std::string result = input;
    for (char &c : result)
    {
        c = std::tolower(c);
    }
    return result;
}

std::string to_upper(const std::string &input)
{
    std::string result = input;
    for (char &c : result)
    {
        c = std::toupper(c);
    }
    return result;
}

std::string to_trim(const std::string &input)
{
    int start = 0;
    while (start < static_cast<int>(input.size()) && std::isspace(input[start]))
    {
        start++;
    }

    int end = static_cast<int>(input.size()) - 1;
    while (end > start && std::isspace(input[end]))
    {
        end--;
    }

    if (start > end)
    {
        return "";
    }

    return input.substr(start, end - start + 1);
}
