#pragma once

namespace DES_WND {
	class LoginWindow : public WndBase
	{
	public:
		explicit LoginWindow(LPCTSTR pszXMLName);
		~LoginWindow(void);

	public:
		DUI_DECLARE_MESSAGE_MAP();
		virtual void OnFinalMessage( HWND hWnd );
		virtual void InitWindow();
		virtual void Notify(TNotifyUI& msg);
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void OnClick(TNotifyUI& msg);
		void OnShowActive(TNotifyUI& msg);

	private:
		IShockwaveFlash* m_pIShockwaveFlash;
	};
}

