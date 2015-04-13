#include "stdafx.h"
namespace DES_CONTROL {
	SkinButton::SkinButton(void)
		: CUIAnimation(this)
		, m_bMouseHove(false)
		, m_bMouseLeave(false)
		, m_hasFadeEffect(NOFADE)
	{
	}

	SkinButton::~SkinButton(void)
	{
		StopAnimation();
		CControlUI::~CControlUI();
	}

	LPCTSTR SkinButton::GetClass() const {
		return g_pstrClass;
	}

	LPVOID SkinButton::GetInterface(LPCTSTR pstrName) {
		if (_tcscmp(pstrName, g_pstrInterface)) {
			return static_cast<SkinButton*>(this);
		}
		return CButtonUI::GetInterface(pstrName);
	}

	void SkinButton::DoEvent(TEventUI& event) {
		if (!m_hasFadeEffect)
		{
			CButtonUI::DoEvent(event);
			return;
		}

		if( event.Type == UIEVENT_MOUSEENTER && !IsAnimationRunning( FADE_IN_ID ) )
		{
			m_bFadeAlpha = 0;
			m_bMouseHove = TRUE;
			StopAnimation( FADE_OUT_ID );
			StartAnimation( FADE_ELLAPSE, FADE_FRAME_COUNT, FADE_IN_ID );
			Invalidate();
			return;
		}
		if( event.Type == UIEVENT_MOUSELEAVE && !IsAnimationRunning( FADE_OUT_ID ) )
		{
			m_bFadeAlpha = 0;
			m_bMouseLeave = TRUE;
			StopAnimation(FADE_IN_ID);
			StartAnimation(FADE_ELLAPSE, FADE_FRAME_COUNT, FADE_OUT_ID);
			Invalidate();
			return;
		}
		if( event.Type == UIEVENT_TIMER ) 
		{
			OnTimer(  event.wParam );
		}
		CButtonUI::DoEvent( event );
	}

	void SkinButton::SetFadeEffect(FADESTATE hasFadeEffect) {
		m_hasFadeEffect = hasFadeEffect;
	}

	void SkinButton::OnTimer( int nTimerID ) {
		OnAnimationElapse( nTimerID );
	}

	void SkinButton::PaintStatusImage(HDC hDC) {
		if (!m_hasFadeEffect)
		{
			CButtonUI::PaintStatusImage(hDC);
			return;
		}

		if( IsFocused() ) m_uButtonState |= UISTATE_FOCUSED;
		else m_uButtonState &= ~ UISTATE_FOCUSED;
		if( !IsEnabled() ) m_uButtonState |= UISTATE_DISABLED;
		else m_uButtonState &= ~ UISTATE_DISABLED;

		if( (m_uButtonState & UISTATE_DISABLED) != 0 ) {
			if( !m_sDisabledImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sDisabledImage) ) m_sDisabledImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_PUSHED) != 0 ) {
			if( !m_sPushedImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sPushedImage) ) m_sPushedImage.Empty();
				else return;
			}
		}
		else if( (m_uButtonState & UISTATE_FOCUSED) != 0 ) {
			if( !m_sFocusedImage.IsEmpty() ) {
				if( !DrawImage(hDC, (LPCTSTR)m_sFocusedImage) ) m_sFocusedImage.Empty();
				else return;
			}
		}

		if( !m_sNormalImage.IsEmpty() ) {
			if( IsAnimationRunning(FADE_IN_ID) || IsAnimationRunning(FADE_OUT_ID))
			{
				if( m_bMouseHove )
				{
					m_bMouseHove = FALSE;
					m_sLastImage = m_sHotImage;
					if( !DrawImage(hDC, (LPCTSTR)m_sNormalImage) ) 
						m_sNormalImage.Empty();
					return;
				}

				if( m_bMouseLeave )
				{
					m_bMouseLeave = FALSE;
					m_sLastImage = m_sNormalImage;
					if( !DrawImage(hDC, (LPCTSTR)m_sHotImage)) 
						m_sHotImage.Empty();
					return;
				}

				m_sOldImage = m_sNormalImage;
				m_sNewImage = m_sHotImage;
				if( IsAnimationRunning(FADE_OUT_ID) )
				{
					m_sOldImage = m_sHotImage;
					m_sNewImage = m_sNormalImage;
				}

				switch (m_hasFadeEffect)
				{
				case DOWNUPSHOW: {
					m_sOldImage = UpdateFadeAttribute(m_sOldImage, 255 - m_bFadeAlpha, IsAnimationRunning(FADE_OUT_ID), true);
					m_sNewImage = UpdateFadeAttribute(m_sNewImage, m_bFadeAlpha, IsAnimationRunning(FADE_OUT_ID), false);
					} break;

				case FADESHOW: {
					m_sOldImage = UpdateFadeAttribute(m_sOldImage, 255 - m_bFadeAlpha);
					m_sNewImage = UpdateFadeAttribute(m_sNewImage, m_bFadeAlpha);
					} break;

				case SIMPLEDOWNUP: {
					m_sOldImage = UpdateFadeAttribute(m_bFadeAlpha, true);
					if (IsAnimationRunning(FADE_OUT_ID)) {
						m_sNewImage = UpdateFadeAttribute(255 - m_bFadeAlpha, false);
					} else m_sNewImage = UpdateFadeAttribute(m_bFadeAlpha, false);
					} break;
				}
				
				if( !DrawImage(hDC, (LPCTSTR)m_sOldImage, NULL) ) 
					m_sOldImage.Empty();
				if( !DrawImage(hDC, (LPCTSTR)m_sNewImage, NULL) ) 
					m_sNewImage.Empty();
				return;
			}
			else
			{
				if (m_sLastImage.IsEmpty())
				{
					m_sLastImage = m_sNormalImage;
				}

				if( !DrawImage(hDC, (LPCTSTR)m_sLastImage) ) 
					m_sLastImage.Empty();
				return;
			}
		}
	}

	void SkinButton::OnAnimationStep(INT nTotalFrame, INT nCurFrame, INT nAnimationID) {
		m_bFadeAlpha = (nCurFrame / (double)nTotalFrame) * 255;
		if(m_bFadeAlpha <= 0) 
			m_bFadeAlpha = 5;
		
		Invalidate();
	}

	CDuiString SkinButton::UpdateFadeAttribute(const CDuiString& imageAttribute, int fadeAlpha) {
		CDuiString updateImageAttribute = imageAttribute;
		if (updateImageAttribute.Find(L"file='") == -1)
		{
			updateImageAttribute = L"file='";
			updateImageAttribute += imageAttribute;
			updateImageAttribute += L"' ";
		}

		if (int startFadePos = imageAttribute.Find(L"fade='") != -1)
		{
			int endFadePos = imageAttribute.Find(L"'", startFadePos + 6);
			ASSERT(endFadePos == -1);
			updateImageAttribute = imageAttribute.Mid(startFadePos, endFadePos - startFadePos);
		}

		updateImageAttribute += L" fade='%d' ";
		updateImageAttribute.Format(updateImageAttribute.GetData(), fadeAlpha);

		return updateImageAttribute;
	}

	CDuiString SkinButton::UpdateFadeAttribute(const CDuiString& imageAttribute, int fadeAlpha, bool a, bool b) {
		CDuiString t_strImage = imageAttribute;
		int t_n = 67*fadeAlpha/255;
		if (t_n >= GetHeight()) t_n = GetHeight();
		if (t_n <= 0) t_n = 0;
		
		if (t_strImage.Find(L"file='") == -1)
		{
			t_strImage = L"file='";
			t_strImage += imageAttribute;
			t_strImage += L"' ";
		}
		
		//当前是上下的顺序
		//如果想要改变成下上的顺序，只需把if else里面交换了
		if (a ^ b) {
			t_strImage += L" source='0,%d,%d,%d' dest='0,0,%d,%d' ";
			t_strImage.Format(t_strImage.GetData(), GetHeight()-t_n, GetWidth(), GetHeight(), GetWidth(), t_n);
		} else {
			t_strImage += L" source='0,0,%d,%d' dest='0,%d,%d,%d' ";
			t_strImage.Format(t_strImage.GetData(), GetWidth(), t_n, GetHeight()-t_n, GetWidth(), GetHeight());
		}

		return t_strImage;
	}

	CDuiString SkinButton::UpdateFadeAttribute(int fadeAlpha, bool bImage) {
		CDuiString t_strImage;
		int t_n = 67*fadeAlpha/255;
		if (t_n >= GetHeight()) t_n = GetHeight();
		if (t_n <= 0) t_n = 0;

		if (bImage) {
			t_strImage = m_sNewImage;
			return m_sNormalImage;
		} else t_strImage = m_sHotImage;

		if (t_strImage.Find(L"file='") == -1)
		{
			t_strImage = L"file='";
			t_strImage += t_strImage;
			t_strImage += L"' ";
		}
		
		t_strImage += L" source='0,0,%d,%d' dest='0,%d,%d,%d' ";
		t_strImage.Format(t_strImage.GetData(), GetWidth(), t_n, GetHeight()-t_n, GetWidth(), GetHeight());

		return t_strImage;
	}
}