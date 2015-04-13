#include "stdafx.h"

using namespace  DES_CONTROL;
namespace DES_WND {
	SetSkinWindow::SetSkinWindow(LPCTSTR pszXMLName)
		: WndBase(pszXMLName)
	{
	}

	SetSkinWindow::~SetSkinWindow(void)
	{
	}

	IMPLEMENT_BK_CLASS(SetSkinWindow, WndBase)
	DUI_BEGIN_MESSAGE_MAP(SetSkinWindow, CNotifyPump)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
		DUI_ON_CLICK_CTRNAME(_T("bkskin"), OnChangeImage)
	DUI_END_MESSAGE_MAP()

		void SetSkinWindow::InitWindow() {
			//透明渐隐显示以后还是要写的。最好延迟一点试看看。
			/*LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
			styleValue &= ~WS_CAPTION;
			::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);*/

			m_pSliderButton = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("skinwnd")));
			if (m_pSliderButton) m_pSliderButton->OnNotify += MakeDelegate(this, &SetSkinWindow::OnSliderMove);

			SetSliderMove(255);
			SetSkinWindow::CreateBK();
			SetSkinWindow::CreateTileChirld(20);
			__super::InitWindow();
	}

	LRESULT SetSkinWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

	void SetSkinWindow::Notify(TNotifyUI& msg) {
		__super::Notify(msg);
	}

	void SetSkinWindow::OnClick(TNotifyUI& msg) {
		if (msg.pSender->GetName() == _T("skinwnd")) {
			SliderWnd* p_sliderwnd = new SliderWnd;
			p_sliderwnd->Init(msg.pSender);
			//OnFinalMessage已经delete了。

		} else if (msg.pSender->GetName() == _T("closebtn")) {
			this->Close();return;
		} else if (msg.pSender->GetName() == _T("changecolor")) {
			ColorPaletWindow* p_ColorPalet = new ColorPaletWindow(_T("ColorPalette.xml"));
			p_ColorPalet->Create(m_hWnd, _T("palette"), UI_WNDSTYLE_DIALOG, WS_EX_WINDOWEDGE);
			p_ColorPalet->CenterWindow();
			p_ColorPalet->ShowModal();

			DEL_P(p_ColorPalet);
		}

		__super::OnClick(msg);
	}

	bool SetSkinWindow::OnSliderMove(void* param) {
		TNotifyUI* p_msg = (TNotifyUI*) param;
		if (p_msg->sType == _T("slidermove")) {
			int nSliderValue = p_msg->lParam;

			SetSliderMove(nSliderValue);
		}
	
		return true;
	}

	void SetSkinWindow::SetSliderMove(LONG nSlider) {
		if (g_pFadeGround) {
			CDuiString bk_str(_T("file='control\\mainframe_background.png' "));
			string_t t_str(_T("fade='"));
			t_str.append(WndBase::N_TOSTR(nSlider));
			t_str.append(_T("'"));
			bk_str.Append(t_str.c_str());

			g_pFadeGround->SetBkImage(bk_str);
		}

		m_pSliderButton->SetText(WndBase::N_TOSTR(nSlider).c_str());
	}

	bool SetSkinWindow::CreateTileChirld(int number) {
		CTileLayoutUI* p_title = static_cast<CTileLayoutUI*>(m_PaintManager.FindControl(_T("listctrl")));
		if (!p_title) {
			return false;
		}

		for (int i = 0; i < number; i++) {
			string_t strpath = _T("control\\bkskin\\");
			strpath.append(N_TOSTR(i));
			strpath.append(_T(".png"));

			SkinButton* p_button = new SkinButton;
			p_button->ApplyAttributeList(_T("width=\"120\" height=\"67\" "));
			//p_button->SetBkImage();
			p_button->SetNormalImage(strpath.c_str());
			p_button->SetHotImage(_T("file='control\\bkskin\\tool_pushed.png'"));
			p_button->SetTag(i);
			p_button->SetName(_T("bkskin"));
			p_button->SetFadeEffect((SkinButton::FADESTATE)1);

			p_title->Add(p_button);
		}

		return true;
	}

	void SetSkinWindow::OnChangeImage(TNotifyUI& msg) {
		int nflag = static_cast<CButtonUI*>(msg.pSender)->GetTag();
		WndBase::SetBKIndex(nflag);
	}

	LRESULT SetSkinWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
		return __super::OnNcHitTest(uMsg, wParam, lParam, bHandled);
	}

	void SetSkinWindow::Close() {
		SetSkinWindow::Destructe();
		DuiLib::CWindowWnd::Close();
	}

	/////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////

	ColorPaletWindow::ColorPaletWindow(LPCTSTR pszXMLName)
		: WndBase(pszXMLName) {

	}

	ColorPaletWindow::~ColorPaletWindow() {

	}

	IMPLEMENT_BK_CLASS(ColorPaletWindow, WndBase)
		DUI_BEGIN_MESSAGE_MAP(ColorPaletWindow, CNotifyPump)
		DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
		DUI_END_MESSAGE_MAP()

		void ColorPaletWindow::InitWindow() {
			ColorPaletWindow::CreateBK();
			__super::InitWindow();
	}

	void ColorPaletWindow::Notify(TNotifyUI& msg) {
		__super::Notify(msg);
	}

	void ColorPaletWindow::OnClick(TNotifyUI& msg) {

		if (msg.pSender->GetName() == _T("closebtn")) {
			Close();
			return;
		} else if (msg.pSender->GetName() == _T("colorok")) {
			CColorPaletteUI* p_Color = static_cast<CColorPaletteUI*>(m_PaintManager.FindControl(_T("Pallet")));
			WndBase::SetBKIndex(p_Color->GetSelectColor());

			Close();
			return;
		} else if (msg.pSender->GetName() == _T("colorcancle")) {
			Close();
			return;
		}

		return __super::OnClick(msg);
	}

	CControlUI* ColorPaletWindow::CreateControl(LPCTSTR pstrClass) {
		CDuiString		strXML;
		CDialogBuilder	builder;

		if (_tcsicmp(pstrClass, _T("Pallet")) == 0) {
			CColorPaletteUI* p_ColorPalet = new CColorPaletteUI;
			p_ColorPalet->SetThumbImage(_T("button\\cursor.png"));
			return p_ColorPalet;
		}

		if (!strXML.IsEmpty()) {
			CControlUI* pUI = builder.Create(strXML.GetData(), NULL, NULL, &m_PaintManager, NULL);
			return pUI;
		}
		return NULL;
	}

	void ColorPaletWindow::Close() {
		ColorPaletWindow::Destructe();
		DuiLib::CWindowWnd::Close();
	}
}