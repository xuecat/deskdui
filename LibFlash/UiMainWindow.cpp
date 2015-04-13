#include "stdafx.h"
#include "UiMainWindow.h"

namespace DES_WND {
	UiMainWindow::UiMainWindow(LPCTSTR pszXMLName)
		: WndBase(pszXMLName)
	{
	}


	UiMainWindow::~UiMainWindow(void)
	{
	}

	DUI_BEGIN_MESSAGE_MAP(UiMainWindow, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_SHOWACTIVEX, OnShowActive)
	DUI_END_MESSAGE_MAP()

		void UiMainWindow::InitWindow() {

			__super::InitWindow();
	}

	CControlUI* UiMainWindow::CreateControl(LPCTSTR pstrClassName) {
		return NULL;
	}

	LRESULT UiMainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		LRESULT lRes =  __super::HandleMessage(uMsg, wParam, lParam);

		switch (lRes)
		{
		default:
			break;
		}

		return lRes;
	}

	void UiMainWindow::Notify(TNotifyUI& msg) {
		__super::Notify(msg);
	}

	void UiMainWindow::OnClick(TNotifyUI& msg) {
		if (msg.pSender->GetName() == _T("closebtn")) {
			PostQuitMessage(0); 
			return;
		}
		__super::OnClick(msg);
	}

	void UiMainWindow::OnShowActive(TNotifyUI& msg) {
		if (msg.pSender->GetName() == _T("flashActiveX")) {
			IShockwaveFlash* pFlash = NULL;
			CActiveXUI* pActivex = static_cast<CActiveXUI*>(msg.pSender);

			pActivex->GetControl(__uuidof(IShockwaveFlash), (void**)&pFlash);

			if (pFlash != NULL) {
				pFlash->put_WMode(_bstr_t(_T("Transparent") ));
				pFlash->put_Movie(_bstr_t(CPaintManagerUI::GetInstancePath() + _T("\\skin\\Flash\\noon.swf")) );
				pFlash->DisableLocalSecurity();
				pFlash->put_AllowScriptAccess(L"always");

				BSTR request,response;
				request = SysAllocString(L"<invoke name=\"setButtonText\" returntype=\"xml\"><arguments><string>Click me!</string></arguments></invoke>");  
				response = SysAllocString(L"");
				pFlash->CallFunction(request, &response);
				SysFreeString(request);
				SysFreeString(response);
			}
		}
	}

	LRESULT UiMainWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
	}

	LRESULT UiMainWindow::ResponseDefaultKeyEvent(WPARAM wParam) {
		if (wParam == VK_ESCAPE) {
		}
		return __super::ResponseDefaultKeyEvent(wParam);
	}
}
