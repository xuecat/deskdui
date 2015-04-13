#pragma once

namespace DES_CONTROL {
	const TCHAR* const g_pstrClass = _T("SkinButtonUI");
	const TCHAR* const g_pstrInterface = _T("SkinButtonItem");
	const TCHAR* const c_pstrHoverImage = _T("file='control\\bkskin\\tool_pushed.png' fade='200'");
	class SkinButton : public CButtonUI, public CUIAnimation
	{
	public:
		SkinButton();
		virtual ~SkinButton();
		enum FADESTATE {
			NOFADE		= 0L,
			FADESHOW	= 1L,
			DOWNUPSHOW	= 2L,
			SIMPLEDOWNUP= 3L
		};

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		void DoEvent(TEventUI& event);
		void SetFadeEffect(FADESTATE hasFadeEffect);

		void OnTimer( int nTimerID );
		void PaintStatusImage(HDC hDC);

		virtual void OnAnimationStep(INT nTotalFrame, INT nCurFrame, INT nAnimationID);
		
	protected:
		CDuiString m_sOldImage;
		CDuiString m_sNewImage;
		CDuiString m_sLastImage;
		BYTE          m_bFadeAlpha;
		BOOL        m_bMouseHove;
		BOOL        m_bMouseLeave;
		enum{
			FADE_IN_ID    = 8,
			FADE_OUT_ID = 9,

			FADE_ELLAPSE = 10,
			FADE_FRAME_COUNT = 50,
		};

	private:
		/** 
		 *  @ [in]param
		 *  @ [out]param
		 *  @ return
		 *  @ note 注意图片设置（最好没有source dest fade，相关代码以后添加）
		 */
		CDuiString UpdateFadeAttribute(const CDuiString& imageAttribute, int fadeAlpha);

		//当前是上下的顺序
		//如果想要改变成下上的顺序，只需把if else里面交换了
		CDuiString UpdateFadeAttribute(const CDuiString& imageAttribute, int fadeAlpha, bool a, bool b);

		CDuiString UpdateFadeAttribute(int fadeAlpha, bool bImage);
	private:
		FADESTATE m_hasFadeEffect;
	};
}
