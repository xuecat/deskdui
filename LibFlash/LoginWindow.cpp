#include "stdafx.h"

namespace DES_WND {
	LoginWindow::LoginWindow(LPCTSTR pszXMLName)
		:WndBase(pszXMLName)
		, m_pIShockwaveFlash(NULL)
	{
	}

	LoginWindow::~LoginWindow(void)
	{
	}

	DUI_BEGIN_MESSAGE_MAP(LoginWindow, CNotifyPump)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_SHOWACTIVEX, OnShowActive)
	DUI_END_MESSAGE_MAP()

	void LoginWindow::OnFinalMessage( HWND hWnd ) {
		__super::OnFinalMessage(hWnd);
	}

	void LoginWindow::InitWindow() {
		__super::InitWindow();
	}

	LRESULT LoginWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		return __super::HandleMessage(uMsg, wParam, lParam);
	}

	void LoginWindow::Notify(TNotifyUI& msg) {
		if (msg.sType == _T("click")) {
			if( msg.pSender->GetName() == _T("closebtn") ) { PostQuitMessage(0); return; }
			else if( msg.pSender->GetName() == _T("ButtonLogin") ) { this->Close();return;}
		}
		__super::Notify(msg);
	}               

	void LoginWindow::OnClick(TNotifyUI& msg) {
		
	}

	void LoginWindow::OnShowActive(TNotifyUI& msg) {
		if (msg.pSender->GetName() == _T("lflashActiveX")) {
			CActiveXUI* pActivex = static_cast<CActiveXUI*>(msg.pSender);

			IShockwaveFlash* IShockwaveFlash = NULL;
			pActivex->GetControl(__uuidof(IShockwaveFlash), (void**)&IShockwaveFlash);

			if (IShockwaveFlash != NULL) {
				IShockwaveFlash->put_WMode(_bstr_t(_T("Transparent") ));
				IShockwaveFlash->put_Movie(_bstr_t(CPaintManagerUI::GetInstancePath() + _T("\\skin\\Flash\\noon.swf")) );
				IShockwaveFlash->DisableLocalSecurity();
				IShockwaveFlash->put_AllowScriptAccess(L"always");
				
				BSTR request,response;
				request = SysAllocString(L"<invoke name=\"setButtonText\" returntype=\"xml\"><arguments><string>Click me!</string></arguments></invoke>");  
				response = SysAllocString(L" ");
				IShockwaveFlash->CallFunction(request, &response);
				SysFreeString(request);
				SysFreeString(response);
				m_pIShockwaveFlash = IShockwaveFlash;
				IShockwaveFlash->Release();
			}
			
		}
	}



}
