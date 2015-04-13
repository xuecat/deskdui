#pragma once

namespace DES_WND {
	class LoginWindow;
	class CUserListUI;

	class DuiMainWindow
		: public WndBase
	{
	public:
		explicit DuiMainWindow(LPCTSTR pszXMLName);
		~DuiMainWindow(void);

		DECLEAR_BK_CLASS(DuiMainWindow)
	public:
		DUI_DECLARE_MESSAGE_MAP();
		virtual void InitWindow();
		virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
		virtual void Notify(TNotifyUI& msg);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
		//virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		virtual void OnClick(TNotifyUI& msg);

		void CreateFadeBk();

	private:
		BOOL ShowList(bool bShow);

		LoginWindow* m_pLoginWindows;
	};
}
