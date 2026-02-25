#include <algorithm>
#include <cctype>
#include <string>

std::string to_lower(std::string_view input) {
    std::string result(input);
    for (char& c : result) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
    return result;
}

std::string to_upper(std::string_view input) {
    std::string result(input);
    for (char& c : result) {
        c = std::toupper(static_cast<unsigned char>(c));
    }
    return result;
}

std::string to_trim(std::string_view input) {
    auto is_space = [](unsigned char c) { return std::isspace(c); };

    auto first = std::find_if_not(input.begin(), input.end(), is_space);
    if (first == input.end()) return {};

    auto last = std::find_if_not(input.rbegin(), input.rend(), is_space).base();

    return std::string(first, last);
}
