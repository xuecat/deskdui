#pragma once
namespace DES_CONTROL {
	const TCHAR kPalletClassName[] = _T("ColorPaletteUI");
	const TCHAR kPalletInterface[] = _T("ColorPalette");

	class CColorPaletteUI : public CControlUI
	{
	public:
		CColorPaletteUI();
		virtual ~CColorPaletteUI();

		//��ȡ���ձ�ѡ�����ɫ������ֱ����������duilib����ɫ
		DWORD GetSelectColor();
		void SetSelectColor(DWORD dwColor);

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		//����/��ȡ Pallet����ɫ�������棩�ĸ߶�
		void SetPalletHeight(int nHeight);
		int	GetPalletHeight() const;

		//����/��ȡ �·�Bar������ѡ�������ĸ߶�
		void SetBarHeight(int nHeight);
		int GetBarHeight() const;
		//����/��ȡ ѡ��ͼ���·��
		void SetThumbImage(LPCTSTR pszImage);
		LPCTSTR GetThumbImage() const;

		virtual void SetPos(RECT rc);
		virtual void DoInit();
		virtual void DoEvent(TEventUI& event);
		virtual void DoPaint(HDC hDC, const RECT& rcPaint);
		virtual void PaintPallet(HDC hDC);

	protected:
		//��������
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