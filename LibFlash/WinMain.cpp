#include "stdafx.h"
#include "UiMainWindow.h"
#include "DuiMainWindow.h"
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

using namespace DES_WND;
using namespace Gdiplus;
Gdiplus::GdiplusStartupInput g_gdiplusStartupInput;
ULONG_PTR g_gdiplusToken; 

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	HRESULT hr = ::CoInitialize(NULL);
	if (FAILED(hr)) {
		assert(0);
		return 0;
	}
#ifdef UILIB
	if( ::LoadLibrary(_T("d3d9.dll")) == NULL ) 
		::MessageBox(NULL, _T("���� d3d9.dll ʧ�ܣ�һЩ��Ч�����޷���ʾ��"),
		_T("��Ϣ��ʾ"),MB_OK|MB_ICONWARNING);
#endif

	GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);

	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));

#ifdef UILIB
	UiMainWindow* pMainWindow = new UiMainWindow(_T("MainUI.xml"));
	pMainWindow->Create(NULL, _T("�������"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
	pMainWindow->CenterWindow();
	pMainWindow->ShowModal();
	
	delete pMainWindow;
#else
	DuiMainWindow* pMainWindow = new DuiMainWindow(_T("MainUI.xml"));
	pMainWindow->Create(NULL, _T("�������"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
	pMainWindow->CenterWindow();
	pMainWindow->ShowModal();

	delete pMainWindow;
#endif

	CPaintManagerUI::MessageLoop();
	Gdiplus::GdiplusShutdown(g_gdiplusToken);
	::CoUninitialize();
	return 0;
}