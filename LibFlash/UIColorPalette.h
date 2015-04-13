#pragma once
namespace DES_CONTROL {
	const TCHAR kPalletClassName[] = _T("ColorPaletteUI");
	const TCHAR kPalletInterface[] = _T("ColorPalette");

	class CColorPaletteUI : public CControlUI
	{
	public:
		CColorPaletteUI();
		virtual ~CColorPaletteUI();

		//获取最终被选择的颜色，可以直接用于设置duilib背景色
		DWORD GetSelectColor();
		void SetSelectColor(DWORD dwColor);

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		//设置/获取 Pallet（调色板主界面）的高度
		void SetPalletHeight(int nHeight);
		int	GetPalletHeight() const;

		//设置/获取 下方Bar（亮度选择栏）的高度
		void SetBarHeight(int nHeight);
		int GetBarHeight() const;
		//设置/获取 选择图标的路径
		void SetThumbImage(LPCTSTR pszImage);
		LPCTSTR GetThumbImage() const;

		virtual void SetPos(RECT rc);
		virtual void DoInit();
		virtual void DoEvent(TEventUI& event);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintPallet(HDC hDC);

	protected:
		//更新数据
		void UpdatePalletData();
		void UpdateBarData();

	private:
		HDC			m_MemDc;
		HBITMAP		m_hMemBitmap;
		BITMAP		m_bmInfo;
		BYTE		*m_pBits;
		UINT		m_uButtonState;
		bool		m_bIsInBar;
		bool		m_bIsInPallet;
		int			m_nCurH;
		int			m_nCurS;
		int			m_nCurB;

		int			m_nPalletHeight;
		int			m_nBarHeight;
		DuiLib::CPoint		m_ptLastPalletMouse;
		DuiLib::CPoint		m_ptLastBarMouse;
		CDuiString  m_strThumbImage;
	};

}