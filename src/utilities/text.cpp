#include "utilities/text.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

void enableAnsi()
{
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return;
    }
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode))
    {
        return;
    }
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
#endif
}

std::string colored(const std::string &text, const char *color)
{
    std::string result;
    result += color;
    result += text;
    result += ansi::RESET;
    return result;
}

std::string bold(const std::string &text)
{
    return colored(text, ansi::BOLD);
}

std::string dim(const std::string &text)
{
    return colored(text, ansi::DIM);
}

std::string italic(const std::string &text)
{
    return colored(text, ansi::ITALIC);
}

void delay_ms(int milliseconds)
{
    if (milliseconds > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}

void print_pause(const std::string &text, int pause_ms)
{
    std::cout << text;
    std::cout.flush();
    delay_ms(pause_ms);
}

void print_narrative(const std::string &text, int pause_ms)
{
    std::cout << text << "\n";
    std::cout.flush();
    delay_ms(pause_ms);
}
