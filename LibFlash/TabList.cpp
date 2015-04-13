#include "stdafx.h"
#include "TabList.h"

namespace DES_WND {
#define UP_DIRECT UIEVENT__LAST+10
#define DOWN_DIRECT UIEVENT__LAST+11

	const TCHAR* const c_szTabListItem	  = _T("TabListItem");
	CTabList::CTabList(CPaintManagerUI* p)
		: m_pPaintManager(p)
	{
	}

	CTabList::~CTabList(void) {
	}

	LPCTSTR CTabList::GetClass() const {
		return _T("CTabList");
	}

	LPVOID CTabList::GetInterface(LPCTSTR pstrName) {
		if (_tcscmp(pstrName, _T("TabListGroup"))==0) {
			return this;
		}
		return __super::GetInterface(pstrName);
	}

	CControlUI* CTabList::CreateControl(LPCTSTR pstrClass) {
		if (_tcsicmp(pstrClass, c_szTabListItem)  == 0) {
			return new CTabListItem;
		}
		return NULL;
	}

	bool CTabList::AddItem() {
		CDialogBuilder cDialogBuilder;
		CTabListItem* p_temp = static_cast<CTabListItem*>(cDialogBuilder.Create(c_szTabListItemXML, NULL, this, m_pManager));
		if (p_temp == NULL) return false;

		this->Add(p_temp);
		return true;
	}

	void CTabList::DoEvent(TEventUI& event) {
		
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pParent != NULL ) m_pParent->DoEvent(event);
			else CVerticalLayoutUI::DoEvent(event);
			return;
		}

		if( event.Type == UIEVENT_SETFOCUS ) 
		{
			m_bFocused = true;
			return;
		}
		if( event.Type == UIEVENT_KILLFOCUS ) 
		{
			m_bFocused = false;
			return;
		}
		if (event.Type == UIEVENT_BUTTONDOWN) {
			if( IsEnabled() ){
				CControlUI* t_cur = m_pManager->FindSubControlByPoint(this, event.ptMouse);
				if (this->GetCurSel() != this->GetItemIndex(t_cur)) {
					static_cast<CTabListItem*>(this->GetItemAt(this->GetCurSel()))->Select(false);
					return;
				}
			}
			return;
		}
		if (event.Type == UP_DIRECT) {
			SwitchItem(event.ptMouse, UP_DIRECT);
			return;
		}
		if (event.Type == DOWN_DIRECT) {
			SwitchItem(event.ptMouse, DOWN_DIRECT);
			return;
		}

		switch( event.Type ) {
		case UIEVENT_KEYDOWN:
			switch( event.chKey ) {
			case VK_UP:
				SelectItem(FindSelectable(m_iCurSel - 1, false), true);
				return;
			case VK_DOWN:
				SelectItem(FindSelectable(m_iCurSel + 1, true), true);
				return;
			case VK_PRIOR:
				PageUp();
				return;
			case VK_NEXT:
				PageDown();
				return;
			case VK_HOME:
				SelectItem(FindSelectable(0, false), true);
				return;
			case VK_END:
				SelectItem(FindSelectable(GetCount() - 1, true), true);
				return;
			case VK_RETURN:
				if( m_iCurSel != -1 ) GetItemAt(m_iCurSel)->Activate();
				return;
			}
			break;
		case UIEVENT_SCROLLWHEEL:
			{
				switch( LOWORD(event.wParam) ) {
				case SB_LINEUP:
					if( m_bScrollSelect ) SelectItem(FindSelectable(m_iCurSel - 1, false), true);
					else LineUp();
					return;
				case SB_LINEDOWN:
					if( m_bScrollSelect ) SelectItem(FindSelectable(m_iCurSel + 1, true), true);
					else LineDown();
					return;
				}
			}
			break;
		}
		
		CVerticalLayoutUI::DoEvent(event);
	}

	bool CTabList::SwitchItem(POINT uMouse, int nDirect) {
		switch (nDirect)
		{
		case UP_DIRECT: 
			{
				CControlUI* p_hover = m_pManager->FindSubControlByPoint(this, uMouse);
				if (p_hover) {
					int n_index = this->GetItemIndex(p_hover);
					if (n_index <= 0) return false;
					////////////////先测试看看/////////////////////////
					this->SetItemIndex(p_hover, n_index-1);
					/*this->SetAutoDestroy(true);
					this->Remove(p_hover);
					this->SetItemIndex()
					this->SetAutoDestroy(false);*/
				}
			} break;

		case DOWN_DIRECT: {} break;
		default: break;
		}

		return false;
	}

	bool CTabList::UpMoveItem(POINT uMouse) {
		return false;
	}

	bool CTabList::DownMoveItem(POINT uMouse) {
		////////////////先测试看看/////////////////////////
		return false;
	}

	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////

	CTabListItem::CTabListItem():m_hBitmap(NULL) {}

	CTabListItem::~CTabListItem() {}

	LPCTSTR CTabListItem::GetClass() const {
		return _T("CTabListItem");
	}

	LPVOID CTabListItem::GetInterface(LPCTSTR pstrName) {
		if (_tcscmp(pstrName, _T("TabListItem")) == 0) {
			return static_cast<CTabListItem*>(this);
		}
		return __super::GetInterface(pstrName);
	}

	void CTabListItem::CreatItemData() {
		CControlUI* p_temp = NULL;
		for (int i = 0; i < 4; i++) {
			p_temp = m_pManager->FindControl(ToListItemName(i));
			if (p_temp) m_vControl.push_back(p_temp);
		}
	}
	
	void CTabListItem::DoEvent(TEventUI& event) {
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pOwner != NULL ) m_pOwner->DoEvent(event);
			else CContainerUI::DoEvent(event);
			return;
		}

		if( event.Type == UIEVENT_DBLCLICK )
		{
			if( IsEnabled() ) {
				Activate();
				Invalidate();
			}
			return;
		}
		if( event.Type == UIEVENT_KEYDOWN && IsEnabled() )
		{
			if( event.chKey == VK_RETURN ) {
				Activate();
				Invalidate();
				return;
			}
		}
		if( event.Type == UIEVENT_BUTTONDOWN )
		{
			if( IsEnabled() ){
				Select();
				m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);

				m_uButtonState |= UISTATE_CAPTURED;
				m_rOldPoint = event.ptMouse;
				m_rcCurRect = GetPos();
				m_pManager->AddPostPaint(this);

				if (m_hBitmap) {
					::DeleteObject(m_hBitmap);
				}
				m_hBitmap = CRenderEngine::GenerateBitmap(m_pManager, this, m_rcItem);
			}
			return;
		}
		if (event.Type == UIEVENT_RBUTTONDOWN) {
			if (IsEnabled()) {
				Select();
				m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);
			}
		}
		
		if( event.Type == UIEVENT_BUTTONUP ) 
		{
			if ((m_uButtonState &UISTATE_CAPTURED) != 0) {
				m_uButtonState &= ~UISTATE_CAPTURED;
				m_pManager->RemovePostPaint(this);
				event.Type &= ~UIEVENT_BUTTONUP;
				if (JudgeItemRect(event.ptMouse) == 1){
					event.Type |= UP_DIRECT;
				} else if(JudgeItemRect(event.ptMouse) == 0) {
					event.Type |= DOWN_DIRECT;
				} else {m_pManager->Invalidate(m_rcCurRect);return;}

				this->GetOwner()->DoEvent(event);
				m_pManager->Invalidate(m_rcCurRect);
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSEMOVE )
		{
			if ((m_uButtonState&UISTATE_CAPTURED)!=0) {
				LONG cy = event.ptMouse.y - m_rOldPoint.y;

				m_rOldPoint = event.ptMouse;

				CDuiRect t_rect;
				t_rect.left = m_rcCurRect.left;
				t_rect.top  =  m_rcCurRect.top + cy;
				t_rect.right = m_rcCurRect.right;
				t_rect.bottom = m_rcCurRect.bottom + cy;

				CDuiRect temp = m_rcCurRect;
				m_rcCurRect = t_rect;
				temp.Join(t_rect);

				SetShowItem(false);
				if (m_pManager)m_pManager->Invalidate(temp);
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSEENTER )
		{
			if( IsEnabled() ) {
				m_uButtonState |= UISTATE_HOT;
				Invalidate();
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSELEAVE )
		{
			if( (m_uButtonState & UISTATE_HOT) != 0 ) {
				m_uButtonState &= ~UISTATE_HOT;
				Invalidate();
			}
			return;
		}

		if( m_pOwner != NULL ) {
			m_pOwner->DoEvent(event);
		} else {
			CControlUI::DoEvent(event);
		}
	}

	void CTabListItem::SetPos(RECT rc) {
		CHorizontalLayoutUI::SetPos(rc);
		if( m_pOwner == NULL ) return;		

		CListUI* pList = static_cast<CListUI*>(m_pOwner);
		if (pList == NULL ||  _tcscmp(_T("CTabList"), pList->GetClass()) != 0 ) return;

		CListHeaderUI *pHeader = pList->GetHeader();
		if (pHeader == NULL || !pHeader->IsVisible())
			return;

		int nCount = m_items.GetSize();
		for (int i = 0; i < nCount; i++)
		{
			CControlUI *pListItem = static_cast<CControlUI*>(m_items[i]);

			CControlUI *pHeaderItem = pHeader->GetItemAt(i);
			if (pHeaderItem == NULL)
				return;

			RECT rcHeaderItem = pHeaderItem->GetPos();
			if (pListItem != NULL && !(rcHeaderItem.left ==0 && rcHeaderItem.right ==0) )
			{
				RECT rt = pListItem->GetPos();
				rt.left =rcHeaderItem.left;
				rt.right = rcHeaderItem.right;
				pListItem->SetPos(rt);
			}

		}
	}

	void CTabListItem::DoPaint(HDC hDC, const RECT& rcPaint) {
		if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;
		DrawItemBk(hDC, m_rcItem);
		CContainerUI::DoPaint(hDC, rcPaint);
	}

	void CTabListItem::DoPostPaint(HDC hDC, const RECT& rcPaint) {
		if( (m_uButtonState & UISTATE_CAPTURED) != 0 ) {
			RECT bmp = {0};
			RECT coner = {0};
			bmp.right = GetWidth();
			bmp.bottom = GetHeight();
			CDuiRect pcrect = m_rcPaint;
			pcrect.bottom += GetHeight();
			CRenderEngine::DrawImage(hDC, m_hBitmap, m_rcCurRect, pcrect, bmp, coner, true, 190);
			//CRenderEngine::DrawColor(hDC, m_rcCurRect, 0xAA000000);
		}
	}

	bool CTabListItem::Select(bool bSelect /* = true */) {
		if( !IsEnabled() ) return false;
		if( bSelect == m_bSelected ) return true;

		m_bSelected = bSelect;

		if( bSelect && m_pOwner != NULL ) m_pOwner->SelectItem(m_iIndex);
		if (bSelect) {SetListShow();}
		else { KillListShow();}

		return true;
	}

	void CTabListItem::SetListShow() {
		CControlUI* p_temp2 = NULL;
		int n = this->GetFixedHeight();
		this->SetFixedHeight(n+15);
		for (int i = 1; i < 4; i++) {
			p_temp2 = m_pManager->FindSubControlByName(this, ToListItemName(i));
			if (p_temp2 && !p_temp2->IsVisible()) p_temp2->SetVisible(true);
		}
		
	}

	void CTabListItem::KillListShow() {
		CControlUI* p_temp2 = NULL;
		int n = this->GetFixedHeight();
		this->SetFixedHeight(n-15);
		for (int i = 1; i < 4; i++) {
			p_temp2 = m_pManager->FindSubControlByName(this, ToListItemName(i));
			if (p_temp2 && p_temp2->IsVisible()) p_temp2->SetVisible(false);
		}
	}

	void CTabListItem::SetShowItem(bool bShow) {
		if (bShow) {
			if (this->IsVisible()) return;
			for (int i = 0; i < 4; i++) {
				this->FindSubControl(ToListItemName(i, _T("ListItem")))->SetVisible(true);
			}
		} else {
			for (int i = 0; i < 4; i++) {
				this->FindSubControl(ToListItemName(i, _T("ListItem")))->SetVisible(false);
			}
		}
	}

	CDuiString CTabListItem::ToListItemName(int n, LPCTSTR name /* = _T("TabListItem") */) {
		CDuiString temp;
		CDuiString szreturn;
		temp.Format(_T("%d"), n);

		szreturn.Append(name);
		szreturn.Append(temp);
		return szreturn;
	}

	int CTabListItem::JudgeItemRect(POINT uMouse) {
		if (uMouse.y<m_rcItem.top) return 1;
		if(uMouse.y > m_rcItem.bottom) return 0;
		return -1;
	}
	
}
