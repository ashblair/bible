#pragma once

#pragma warning(disable : 4100)

// uncomment following for cross compilation
//#define _CROSS_COMPILE

#ifndef _M_AMD64
#define _M_AMD64
#endif // !_M_AMD64


#ifdef SIGCXX_DISABLE_DEPRECATED
#undef SIGCXX_DISABLE_DEPRECATED
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <assert.h>

#include <gtkmm.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector> 
#include <map> 
#include <algorithm>

typedef unsigned int UINT, *pUINT;
typedef unsigned char UCHAR, *pUCHAR;
typedef unsigned short USHRT, *pUSHRT;

#define _MAX(a, b) (a > b? a: b)
#define _MIN(a, b) (a < b? a: b)
#define INIT_UINT 0xffffffff
//#define INIT_IDX 0x7fff
#define CHAR_IDX 0x7ffe
#define INIT_UCHAR 0xff
#define INIT_USHRT 0xffff

bool lo2hi(void);