#pragma once
namespace DES_WND {
	class UserSettingWindow
		: public WndBase
	{
	public:
		explicit UserSettingWindow(LPCTSTR pszXMLName);
		~UserSettingWindow(void);

	public:
		DECLEAR_BK_CLASS(UserSettingWindow)
		DUI_DECLARE_MESSAGE_MAP();
		void Close(UINT nRet = IDOK);
		virtual void InitWindow();
		virtual void Notify(TNotifyUI& msg);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

		virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual void OnClick(TNotifyUI& msg);
	};
}
