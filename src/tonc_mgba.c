//
//  mGBA logging functionality
//
//! \file tonc_mgba.c
//! \author Nick Sells
//! \date 20210221

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "tonc_math.h"
#include "tonc_mgba.h"

//adapted from https://github.com/GValiente/butano/blob/8017ce68628a86d8eb26b5077b84346c3143b54e/butano/hw/src/bn_hw_log.cpp#L22
void mgba_log(const u32 level, const char* str) {
    REG_LOG_ENABLE = 0xC0DE;
    u32 chars_left = strlen(str);

    while(chars_left) { //splits the message into 256-char log entries
        u32 chars_to_write = min(chars_left, LOG_MAX_CHARS_PER_LINE);

        memcpy(REG_LOG_STR, str, chars_to_write);
        REG_LOG_LEVEL = level; //every time this is written to, mgba creates a new log entry

        str += chars_to_write;
        chars_left -= chars_to_write;
    }
}

void mgba_printf(const u32 level, const char* fmt, ...) {
	va_list args;
	va_start(args, fmt);

	char buf[LOG_MAX_CHARS_PER_LINE];
	vsprintf(buf, fmt, args);
	mgba_log(level, buf);

	va_end(args);
}
