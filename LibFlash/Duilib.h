#pragma once
//#include "stdafx.h"
#include <windows.h>
#include <math.h>
#include <deque>
#include <string>
#include <map>
#include <vector>
#include <UIlib.h>
#include <tchar.h>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <iostream>
#include <algorithm>
#include <atltypes.h>
#include <atlbase.h>

#include <Core/UIControl.h>
#include <Core/UIRender.h>
#include <Core/UIBase.h>
#include <Core/UIManager.h>
#include <Control/UIAnimation.h>

#include "WndBase.h"
#include "SliderWnd.h"
#include "SkinButton.h"
#include "DuiMainWindow.h"
#include "SetSkinWindow.h"
#include "UIColorPalette.h"
#include "UserSettingWindow.h"
#include "UserList.h"
#include "LoginWindow.h"
#include "WndShadow.h"
#include "TabTreeListUI.h"
#include "TabList.h"

using std::make_pair;
using std::pair;
using std::find;
using std::remove;
using std::deque;

using std::string;
using std::wstring;
using std::fstream;
using std::wfstream;
using std::stringstream;
using std::wstringstream;

#ifdef _UNICODE
typedef wchar_t              char_t;
typedef std::wstring         string_t;
typedef std::wstringstream   stringstream_t;   
typedef std::wfstream        fstream_t;   
#else
typedef char                 char_t;
typedef std::string          string_t;
typedef std::stringstream    stringstream_t;  
typedef std::fstream         fstream_t;   
#endif

#define DUILIB

#ifdef UILIB
#	ifdef _DEBUG
#	ifndef UILIB_EXPORTS
#		pragma comment(lib, "Static_Debug_2012/UiLib_d.lib")
#	else
#		pragma comment(lib, "DLL_Debug_2012/UiLib_d.lib")
#	endif
#	else
#		ifndef UILIB_EXPORTS
#			pragma comment(lib, "Static_Release_2012/UiLib.lib")
#		else
#			pragma comment(lib, "DLL_Release_2012/UiLib.lib")
#		endif
#	endif
#else
#	ifdef _DEBUG
#		ifdef _UNICODE
#			pragma comment(lib, "DuiLib_ud.lib")
#		else
#			pragma comment(lib, "DuiLib_d.lib")
#		endif
#else
#		ifdef _UNICODE
#			pragma comment(lib, "DuiLib_u.lib")
#		else
#			pragma comment(lib, "DuiLib.lib")
#		endif
#	endif
#endif
