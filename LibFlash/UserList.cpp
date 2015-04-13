#include "stdafx.h"
#include "UserList.h"

namespace DES_WND {
	
#define  ANIMATION_ELLAPSE 15
#define  ANIMATION_FRAME_COUNT 10
#define  ANIMATION_ID 2

#define DEFAULT_LEFT 1
#define DEFAULT_TOP 120

	CUserListUI::CUserListUI(CPaintManagerUI& paint_manager, LPCTSTR szPath)
		: CUIAnimation(this)
		, m_bDirection(false)
		, m_lCurWidth(0)
		, m_lFixWidth(0)
		, m_lOldWidth(0)
	{
		CControlUI* pViewControl = m_dlgBuilder.Create(szPath, NULL, NULL, &paint_manager, NULL);
		ASSERT(pViewControl!=NULL);
		if (pViewControl) {
			this->Add(pViewControl);
		} else {
			this->RemoveAll();
		}
	}

	CUserListUI::~CUserListUI(void)
	{
	}

	LPCTSTR CUserListUI::GetClass() const {
		return _T("CUserListUI");
	}

	LPVOID CUserListUI::GetInterface(LPCTSTR pstrName) {
		if (_tcscmp(pstrName, _T("UserList")) == 0) {
			return static_cast<CUserListUI*>(this);
		}
		return __super::GetInterface(pstrName);
	}

	//IMPLEMENT_BK_CLASS(UserListWindow, WndBase)外部实现背景。内部停用
	void CUserListUI::SetDelayVisible(bool bVisible /* = true */) {
		if( m_bVisible == bVisible ) return;
		
		bool v = IsVisible();
		m_bVisible = bVisible;
		if( m_bFocused ) m_bFocused = false;
		if (!bVisible && m_pManager && m_pManager->GetFocus() == this) {
			m_pManager->SetFocus(NULL) ;
		}
		
		for( int it = 0; it < m_items.GetSize(); it++ ) {
			static_cast<CControlUI*>(m_items[it])->SetInternVisible(IsVisible());
		}
	}

	void CUserListUI::SetAnimaVisible(bool bVisible /* = true */) {
		if (IsVisible() == bVisible) return;

		m_bDirection = bVisible;
		if (GetFixedWidth()>1) {
			m_lFixWidth = GetFixedWidth();
		}
		if (!bVisible) {
			SwitchShow(FALSE);
		} else {
			//SetVisible(bVisible);
			SetDelayVisible(bVisible);
			SwitchShow(TRUE);
		}
	}
	
	void CUserListUI::SwitchShow(LONG ltype) {
		if (GetFixedWidth() < 0) return;
		
		StopAnimation(ANIMATION_ID);
		StartAnimation(ANIMATION_ELLAPSE, ANIMATION_FRAME_COUNT, ANIMATION_ID);
	}

	void CUserListUI::DoEvent(TEventUI& event) {
		if( event.Type == UIEVENT_TIMER )
		{
			OnTimer(  event.wParam );
		}

		__super::DoEvent( event );
	}

	void CUserListUI::OnTimer(int nTimerID) {
		OnAnimationElapse(nTimerID);
	}

	void CUserListUI::OnAnimationStep(INT nTotalFrame, INT nCurFrame, INT nAnimationID) {
		float nAver = 0;
		if (m_bDirection) {
			nAver = m_lFixWidth * 1 / (nTotalFrame);
			if (nCurFrame == nTotalFrame) {
				m_lCurWidth = m_lFixWidth;
			} else {
				m_lCurWidth += nAver;
			}
		} else {
			nAver = m_lFixWidth * (-1) / (nTotalFrame);
			if (nCurFrame == nTotalFrame) {
				m_lCurWidth = m_lOldWidth;
			} else {
				m_lCurWidth += nAver;
			}
		}
		SetFixedWidth(m_lCurWidth);
	}

	void CUserListUI::OnAnimationStop(INT nAnimationID) {
		if (!m_bDirection) SetVisible(m_bDirection);
	}

}
