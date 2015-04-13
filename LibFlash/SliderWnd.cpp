#include "stdafx.h"

namespace DES_CONTROL {
	SliderWnd::SliderWnd(void)
		: m_pManager(new CPaintManagerUI)
	{
	}

	SliderWnd::~SliderWnd(void)
	{
		DEL_P(m_pManager);
	}

	void SliderWnd::Init(CControlUI* pOwner) {
		m_pControl = pOwner;
		RECT rc = pOwner->GetPos();
		POINT lpoint = {rc.left, rc.top};
		POINT rpoint = {rc.right, rc.bottom};
		::ClientToScreen(pOwner->GetManager()->GetPaintWindow(), &lpoint);
		::ClientToScreen(pOwner->GetManager()->GetPaintWindow(), &rpoint);
		m_rect.left  = lpoint.x;
		m_rect.top	 = lpoint.y;
		m_rect.right = rpoint.x;
		m_rect.bottom= rpoint.y;

		Create(pOwner->GetManager()->GetPaintWindow(), NULL, WS_VISIBLE | WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_TOPMOST);

		//激活父窗口，保证子窗口有焦点变化
		HWND hwnd = m_hWnd;
		while (::GetParent(hwnd) != NULL) {
			hwnd = ::GetParent(hwnd);
		}

		::ShowWindow(m_hWnd, TRUE);
		::SendMessage(hwnd, WM_NCACTIVATE, TRUE, 0L);
	}

	bool SliderWnd::OnSliderChanged(void* param) {
		TNotifyUI* pMsg = (TNotifyUI*)param;
		if (pMsg->sType == DUI_MSGTYPE_VALUECHANGED_MOVE) {
			CSliderUI* p_slider = static_cast<CSliderUI*>(m_pManager->FindControl(_T("sliderVol")));
			if (!p_slider) {
				return false;
			}
			long a = p_slider->GetValue();

			m_pControl->GetManager()->SendNotify(m_pControl, _T("slidermove"),
				0, a, false);
		}
		return true;
	}

	void SliderWnd::PrepareSlider() {
		CSliderUI* pSilder = static_cast<CSliderUI*>(m_pManager->FindControl(_T("sliderVol")));
		pSilder->SetCanSendMove(true);
		if (pSilder) pSilder->OnNotify += MakeDelegate(this, &SliderWnd::OnSliderChanged);
	}

	void SliderWnd::Notify(TNotifyUI& msg) {

	}

	LRESULT 
		SliderWnd::OnNcCalcSize(
		UINT uMsg,
		WPARAM wParam, LPARAM lParam,
		BOOL& bHandled) {

			return 0;
	}

	LRESULT 
		SliderWnd::OnNcPaint(
		UINT uMsg, 
		WPARAM wParam, LPARAM lParam,
		BOOL& bHandled) {

			return 0;
	}

	LRESULT 
		SliderWnd::OnNcActivate(
		UINT uMsg, 
		WPARAM wParam, LPARAM lParam,
		BOOL& bHandled) {

			if (::IsIconic(*this)) {
				bHandled = FALSE;
			}
			return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT 
		SliderWnd::OnKeyDown(
		UINT uMsg,
		WPARAM wParam, LPARAM lParam,
		BOOL& bHandled) {

			if (wParam == VK_ESCAPE) Close();
			return 0;
	}

	LRESULT 
		SliderWnd::OnKillFocus(
		UINT uMsg,
		WPARAM wParam, LPARAM lParam,
		BOOL& bHandled) {

			Close();
			bHandled = FALSE;
			return 0;
	}

	LRESULT
		SliderWnd::OnClose(
		UINT uMsg,
		WPARAM wParam, LPARAM lParam,
		BOOL& bHandled) {

			Close();
			bHandled = FALSE;
			return 0;
	}

	LRESULT 
		SliderWnd::OnCreate(
		UINT uMsg,
		WPARAM wParam, LPARAM lParam, 
		BOOL& bHandled) {
			LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
			styleValue &= ~WS_CAPTION;
			::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

			m_pManager->Init(m_hWnd);
			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("SkinSlider.xml"),
				(UINT)0, NULL, m_pManager);

			ASSERT(pRoot && "Failed to parse XML");
			m_pManager->AttachDialog(pRoot);
			m_pManager->AddNotifier(this);

			AdjustPosion();
			PrepareSlider();
			return 0;
	}

	LRESULT 
		SliderWnd::HandleMessage(
		UINT uMsg,
		WPARAM wParam, 
		LPARAM lParam) {

			LRESULT lRes = 0;
			BOOL bHandled = TRUE;

			switch (uMsg)
			{
			case WM_CREATE:		lRes = OnCreate(uMsg, wParam, lParam, bHandled);	break;
			case WM_CLOSE:		lRes = OnClose(uMsg, wParam, lParam, bHandled);		break;
			case WM_KILLFOCUS:	lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); break;
			case WM_KEYDOWN:	lRes = OnKeyDown(uMsg, wParam, lParam, bHandled);	break;
			case WM_NCACTIVATE: lRes = OnNcActivate(uMsg, wParam, lParam, bHandled);break;
			case WM_NCCALCSIZE: lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled);break;
			case WM_NCPAINT:    lRes = OnNcPaint(uMsg, wParam, lParam, bHandled);	break;
			case  WM_MOUSELEAVE:lRes = OnClose(uMsg, wParam, lParam, bHandled);		break;
			default: bHandled = FALSE; break;
			}

			if (uMsg == 7) {
				int th;
				th = bHandled;
			}
			if( bHandled ) return lRes;
			if (m_pManager->MessageHandler(uMsg, wParam, lParam, lRes)) return lRes; 
			return __super::HandleMessage(uMsg, wParam, lParam);
	}

	void SliderWnd::AdjustPosion() {
		CDuiRect rcWnd;
		::GetWindowRect(m_hWnd, &rcWnd);
		int nWidth = rcWnd.GetWidth();
		int nHeight = rcWnd.GetHeight();

		rcWnd.right  = m_rect.right;
		rcWnd.bottom = m_rect.top;
		rcWnd.left   = rcWnd.right - nWidth;
		rcWnd.top	 = rcWnd.bottom - nHeight;
		::SetWindowPos(m_hWnd, NULL, rcWnd.left, rcWnd.top,
			rcWnd.GetWidth(), rcWnd.GetHeight(),
			SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}
}
