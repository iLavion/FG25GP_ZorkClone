#include <algorithm>
#include <cctype>
#include <string>

std::string to_lower(std::string_view s) {
    std::string result(s);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::tolower(c); });
    return result;
}

std::string to_upper(std::string_view s) {
    std::string result(s);
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::string to_trim(std::string_view s) {
    auto is_space = [](unsigned char c) { return std::isspace(c); };
    auto left = std::find_if_not(s.begin(), s.end(), is_space);
    if (left == s.end()) return {};
    auto right = std::find_if_not(s.rbegin(), s.rend(), is_space);
    return std::string(left, right.base());
}
