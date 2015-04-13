#include "stdafx.h"

namespace DES_WND {

	const TCHAR* const c_TabListGroup = _T("TabListGroup");
	const TCHAR* const c_TabListGroupXML = TCHARXML(_T("listxml\\TabListGroup.xml"));

	CTabTreeListUI::CTabTreeListUI(void)
		: m_pPaintManager(NULL)
	{
	}

	CTabTreeListUI::CTabTreeListUI(CPaintManagerUI& paint, LPCTSTR szpath)
		: m_pPaintManager(NULL) 
		 {
		CDialogBuilder dlg;
		m_pPaintManager = &paint;
		ASSERT(m_pPaintManager != NULL);

		CControlUI* p = dlg.Create(szpath, NULL, this, &paint);
		ASSERT(p != NULL);
		if (p) {
			Add(p);
			CTabList* pList = static_cast<CTabList*>(paint.FindSubControlByName(p, _T("TabList")));
			pList->AddItem();
			pList->AddItem();
			pList->AddItem();
		} else {
			RemoveAll();
		}
	}

	CTabTreeListUI::~CTabTreeListUI(void)
	{
	}

	LPCTSTR CTabTreeListUI::GetClass() const {
		return _T("CTabTreeListUI");
	}

	LPVOID CTabTreeListUI::GetInterface(LPCTSTR pstrName) {
		if (_tcscmp(pstrName, _T("TabTreeList")) == 0) {
			return static_cast<CTabTreeListUI*>(this);
		}
		return __super::GetInterface(pstrName);
	}

	CControlUI* CTabTreeListUI::CreateControl(LPCTSTR pstrClass) {
		if (_tcsicmp(pstrClass, c_TabListGroup) == 0) {
			return new CTabList(m_pPaintManager);
		} /*else if (_tcsicmp(pstrClass, _T("TabListItem")) == 0) {
			return new CTabListItem;
		}*/
		return NULL;
	}

	bool CTabTreeListUI::AddItem() {
			bool b = false;/*
		CDialogBuilder t_bdlg;
		CTabListItem* p_item = static_cast<CTabListItem*>(t_bdlg.Create(c_szTabListItemXML, NULL, this, m_pList->GetManager()));
		if (m_pList && p_item) {
		b = m_pList->Add(p_item);
		}*/
		return b;
	}

}
