// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <afx.h>
#include <windows.h>
// C RunTime Header Files
#include "Duilib.h"

// TODO: reference additional headers your program requires here
#define DEL_P(p) if (p) {\
	delete p;\
	p = NULL;\
}

#define TOCHAR(a)\
	#a

#define TOPNGCHAR(a)\
	#a _T(".png")

#define TCHARXML(a) a## _T(".xml")

#define CONNECT(a, b) a##b