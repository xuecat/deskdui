#include "stdafx.h"

namespace DES_WND {
	WndBase::WndBase(LPCTSTR pszXMLName)
		: m_strXMLName(pszXMLName) {
	}

	WndBase::~WndBase() {
	}

	string_t WndBase::N_TOSTR(int d) {								
		string_t str;
		TCHAR buffer[10] = {0};
		_itow_s(d, buffer, 10, 10);
		str.append(buffer);
		return str;
		
	}
	IMPLEMENT_BK_BASE(WndBase)
}
