//
//  mGBA logging functionality
//
//! \file tonc_mgba.h
//! \author Nick Sells
//! \date 20210401
//

#ifndef TONC_MGBA
#define TONC_MGBA

#include "tonc_types.h"

// --------------------------------------------------------------------
// MACROS
// --------------------------------------------------------------------

#define LOG_FATAL               (u32) 0x100
#define LOG_ERR                 (u32) 0x101
#define LOG_WARN                (u32) 0x102
#define LOG_INFO                (u32) 0x103

#define LOG_MAX_CHARS_PER_LINE  (u32) 256
#define REG_LOG_STR             (char*) 0x4FFF600
#define REG_LOG_LEVEL           *(vu16*) 0x4FFF700
#define REG_LOG_ENABLE          *(vu16*) 0x4FFF780

//shorthand log and printf because specifying a log level gets really old really fast
#define log(str)                mgba_log(LOG_INFO, (str))
#define printf(str, args...)    mgba_printf(LOG_INFO, (str), (args));

// --------------------------------------------------------------------
// PROTOTYPES
// --------------------------------------------------------------------

void mgba_log(u32 level, const char* str);
void mgba_printf(u32 level, const char* str, ...);

#endif // TONC_MGBA

// EOF
