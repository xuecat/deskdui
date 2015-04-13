#include "stdafx.h"

namespace DES_WND {
	UserSettingWindow::UserSettingWindow(LPCTSTR pszXMLName)
		: WndBase(pszXMLName) {
	}


	UserSettingWindow::~UserSettingWindow(void)
	{
	}

	IMPLEMENT_BK_CLASS(UserSettingWindow, WndBase)
	DUI_BEGIN_MESSAGE_MAP(UserSettingWindow, CNotifyPump)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_END_MESSAGE_MAP()

		void UserSettingWindow::InitWindow() {
			UserSettingWindow::CreateBK();
	}

	LRESULT UserSettingWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

	void UserSettingWindow::Notify(TNotifyUI& msg) {
		__super::Notify(msg);
	}

	void UserSettingWindow::OnClick(TNotifyUI& msg) {
		if (msg.pSender->GetName() == _T("closebtn")) {
			this->Close();return;
		}
		__super::OnClick(msg);
	}

	void UserSettingWindow::Close(UINT nRet /* = IDOK */) {
		UserSettingWindow::Destructe();
	}

	LRESULT UserSettingWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
	}
}
