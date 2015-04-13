#pragma once

namespace DES_WND {
	const TCHAR* const c_szTabListItemXML = _T("listxml\\TabListItem.xml");

	class CTabList : public CListUI, public IDialogBuilderCallback
	{
	public:
		CTabList(CPaintManagerUI* p);
		~CTabList(void);

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		CControlUI* CreateControl(LPCTSTR pstrClass);
		void DoEvent(TEventUI& event);

		bool AddItem();

	private:
		bool SwitchItem(POINT uMouse, int nDirect);
		bool UpMoveItem(POINT uMouse);
		bool DownMoveItem(POINT uMouse);

	private:
		CPaintManagerUI* m_pPaintManager;
	};

	class CTabListItem : public CListContainerElementUI
	{
	public:
		CTabListItem();
		~CTabListItem();

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);

		bool Select(bool bSelect = true);
		void SetPos(RECT rc);
		void DoEvent(TEventUI& event);
		void DoPaint(HDC hDC, const RECT& rcPaint);
		void DoPostPaint(HDC hDC, const RECT& rcPaint);

		void CreatItemData();

		void SetShowItem(bool bShow);
	protected:
		void SetListShow();
		void KillListShow();
	private:
		CDuiString ToListItemName(int n, LPCTSTR name = _T("TabListItem"));

		int JudgeItemRect(POINT uMouse);
	private:
		POINT m_rOldPoint;
		RECT m_rcCurRect;
		HBITMAP m_hBitmap;
		std::vector<CControlUI*> m_vControl;
	};
}

