#include "stdafx.h"

namespace DES_WND {
	CControlUI* g_pFadeGround;

	const TCHAR* const c_UserList			= _T("UserList");
	const TCHAR* const c_UserListXML		= TCHARXML(_T("UserList"));
	const TCHAR* const c_SettingsDialog		= _T("SettingsDialog");
	const TCHAR* const c_SettingsDialogXML	= TCHARXML(_T("UserList"));
	const TCHAR* const c_SettingSkin		= _T("SettingSkin");
	const TCHAR* const c_SettingSkinXML		= TCHARXML(_T("UserList"));
	const TCHAR* const c_LoginWnd			= _T("LoginWnd");
	const TCHAR* const c_LoginWndXML		= TCHARXML(_T("UserList"));
	const TCHAR* const c_TabTreeList		= _T("TabTreeList");
	const TCHAR* const c_TabTreeListXML		= TCHARXML(_T("TabTreeList"));

	DuiMainWindow::DuiMainWindow(LPCTSTR pszXMLName)
		: WndBase(pszXMLName)
		, m_pLoginWindows(NULL)
	{
	}

	DuiMainWindow::~DuiMainWindow(void)
	{
		DEL_P(m_pLoginWindows);
	}

	IMPLEMENT_BK_CLASS(DuiMainWindow, WndBase)
	DUI_BEGIN_MESSAGE_MAP(DuiMainWindow, CNotifyPump)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_END_MESSAGE_MAP()

	void DuiMainWindow::CreateFadeBk() {
		g_pFadeGround = m_PaintManager.FindControl(_T("fadeground"));
	}

	void DuiMainWindow::InitWindow() {
		
#ifdef DUILIB
			DuiMainWindow::CreateBK();
			DuiMainWindow::CreateBK(_T("UserListWindow"));
			DuiMainWindow::CreateFadeBk();

			__super::InitWindow();
#endif
	}

	CControlUI* DuiMainWindow::CreateControl(LPCTSTR pstrClassName) {
		CDialogBuilder dlg;
		if (_tcsicmp(pstrClassName, c_UserList) == 0) {
			return new CUserListUI(m_PaintManager, c_UserListXML);
		} else if (_tcsicmp(pstrClassName, c_TabTreeList) == 0) {
			return new CTabTreeListUI(m_PaintManager, c_TabTreeListXML);
		}
		
		return NULL;
	}

	LRESULT DuiMainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {

		switch (uMsg)
		{
		case WM_CREATE: {
						}
		default:
			break;
		}

		LRESULT lRes =  __super::HandleMessage(uMsg, wParam, lParam);
		return lRes;
	}

	void DuiMainWindow::Notify(TNotifyUI& msg) {
		
		if (msg.sType == DUI_MSGTYPE_SELECTCHANGED) {
			CDuiString name = msg.pSender->GetName();
			CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("switch")));

			if (name == _T("account")) {
				pControl->SelectItem(0);
			} else if (name == _T("message")) {
				pControl->SelectItem(1);
			} else if (name == _T("file")) {
				pControl->SelectItem(2);
			} else if (name == _T("tool")) {
				pControl->SelectItem(3);
			} else if (name == _T("map")) {
				pControl->SelectItem(4);
			} else if (name == _T("recycle")) {
				pControl->SelectItem(5);
			}
		} else if (msg.sType == DUI_MSGTYPE_WINDOWINIT) {
			
			//flash问题暂时停用
			//if(!m_pLoginWindows) m_pLoginWindows = new LoginWindow(_T("LoginWnd.xml"));
			//m_pLoginWindows->Create(this->m_hWnd, _T("login"),  WS_CAPTION, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
			//m_pLoginWindows->CenterWindow();
			//m_pLoginWindows->ShowModal();
			//
			////return;//ACtiveX控件原因，拒绝吧
		}
		__super::Notify(msg);
	}

	void DuiMainWindow::OnClick(TNotifyUI& msg) {
		if (msg.pSender->GetName() == _T("closebtn")) {
			PostQuitMessage(0);
			return;
		}
		else if (msg.pSender->GetName() == _T("sysmenu")) {
			UserSettingWindow* p_UserSetting = new UserSettingWindow(c_SettingsDialogXML);
			p_UserSetting->Create(m_hWnd, c_SettingsDialog, WS_CAPTION, WS_EX_WINDOWEDGE | WS_EX_ACCEPTFILES);
			p_UserSetting->CenterWindow();
			p_UserSetting->ShowModal();

			DEL_P(p_UserSetting);
		} else if (msg.pSender->GetName() == _T("btskin")) {
			SetSkinWindow* p_SetSkin = new SetSkinWindow(c_SettingSkinXML);
			p_SetSkin->Create(m_hWnd, c_SettingSkin, UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
			p_SetSkin->CenterWindow();
			p_SetSkin->ShowModal();

			DEL_P(p_SetSkin);
		}
		else if (msg.pSender->GetName() == _T("showlist")) {
			ShowList(true);
		} else if (msg.pSender->GetName() == _T("hidelist")) {
			ShowList(false);
		}

#ifdef DUILIB
		__super::OnClick(msg);
#endif
	}

	LRESULT DuiMainWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
	}

	LRESULT DuiMainWindow::ResponseDefaultKeyEvent(WPARAM wParam) {
		if (wParam == VK_ESCAPE) {
		}
		return __super::ResponseDefaultKeyEvent(wParam);
	}

	BOOL DuiMainWindow::ShowList(bool bShow) {
		bool Bjudge = bShow^true;
		if (bShow) {
			m_PaintManager.FindControl(_T("showlist"))->SetVisible(Bjudge);
			static_cast<CUserListUI*>(m_PaintManager.FindControl(_T("UserList")))->SetAnimaVisible(!Bjudge);
		} else {
			static_cast<CUserListUI*>(m_PaintManager.FindControl(_T("UserList")))->SetAnimaVisible(!Bjudge);
			m_PaintManager.FindControl(_T("showlist"))->SetVisible(Bjudge);
		}
		return bShow;
	}
}
