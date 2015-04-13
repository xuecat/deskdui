#pragma once

namespace DES_WND {
	class UiMainWindow :
		public WndBase
	{
	public:
		explicit UiMainWindow(LPCTSTR pszXMLName);
		~UiMainWindow(void);

		DUI_DECLARE_MESSAGE_MAP();
		virtual void InitWindow();
		virtual CControlUI* CreateControl(LPCTSTR pstrClassName);
		virtual void Notify(TNotifyUI& msg);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);

		virtual void OnClick(TNotifyUI& msg);
		virtual void OnShowActive(TNotifyUI& msg);
	private:
		CPaintManagerUI m_PaintManager;
	};


}
