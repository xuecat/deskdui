#pragma once

namespace DES_WND {
	class CTabList;

	class CTabTreeListUI : public CContainerUI,
		public IDialogBuilderCallback
	{
	public:
		explicit CTabTreeListUI(CPaintManagerUI& paint, LPCTSTR szpath);
		~CTabTreeListUI(void);

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);

		virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	private:
		CTabTreeListUI(void);
		bool AddItem();

	private:
		CPaintManagerUI* m_pPaintManager;
	};
}


