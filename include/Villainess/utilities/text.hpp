#pragma once

#include <string>

void enableAnsi();

namespace ansi
{
    const char *const RESET = "\033[0m";
    const char *const DIM = "\033[2m";
    const char *const UNDERLINE = "\033[4m";
    const char *const BLACK = "\033[30m";
    const char *const RED = "\033[31m";
    const char *const GREEN = "\033[32m";
    const char *const YELLOW = "\033[33m";
    const char *const BLUE = "\033[34m";
    const char *const MAGENTA = "\033[35m";
    const char *const CYAN = "\033[36m";
    const char *const WHITE = "\033[37m";
    const char *const BRIGHT_RED = "\033[91m";
    const char *const BRIGHT_GREEN = "\033[92m";
    const char *const BRIGHT_YELLOW = "\033[93m";
    const char *const BRIGHT_BLUE = "\033[94m";
    const char *const BRIGHT_MAGENTA = "\033[95m";
    const char *const BRIGHT_CYAN = "\033[96m";
    const char *const BRIGHT_WHITE = "\033[97m";
    const char *const BG_RED = "\033[41m";
    const char *const BG_GREEN = "\033[42m";
    const char *const BG_YELLOW = "\033[43m";
    const char *const BG_BLUE = "\033[44m";
}

std::string colored(const std::string &text, const char *color);
std::string dim(const std::string &text);

void delay_ms(int milliseconds);
void print_pause(const std::string &text, int pause_ms = 400);
void print_narrative(const std::string &text, int pause_ms = 300);
