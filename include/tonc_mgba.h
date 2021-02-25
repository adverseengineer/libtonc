//
//  mGBA logging functionality
//
//! \file tonc_mgba.h
//! \author Nick Sells
//! \date 20210221

#ifndef TONC_MGBA_H
#define TONC_MGBA_H

#include "tonc_types.h"

#define LOG_FATAL               (u32) 0x100
#define LOG_ERR                 (u32) 0x101
#define LOG_WARN                (u32) 0x102
#define LOG_INFO                (u32) 0x103
#define LOG_MAX_CHARS_PER_LINE  (u32) 256
#define REG_LOG_STR             (char*) 0x4FFF600
#define REG_LOG_LEVEL           *(vu16*) 0x4FFF700
#define REG_LOG_ENABLE          *(vu16*) 0x4FFF780

void mgba_log(const u32 level, const char* str);
void mgba_printf(const u32 level, const char* str, ...);

#endif
