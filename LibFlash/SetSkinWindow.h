#pragma once

namespace DES_WND {
	extern CControlUI* g_pFadeGround;

	class SetSkinWindow : public WndBase
{
public:
	explicit SetSkinWindow(LPCTSTR pszXMLName);
	~SetSkinWindow(void);

	DECLEAR_BK_CLASS(SetSkinWindow)
public:
	DUI_DECLARE_MESSAGE_MAP();
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void Close();
	virtual LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void OnClick(TNotifyUI& msg);

private:
	CButtonUI* m_pSliderButton;

private:
	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note �����ؼ�����͸����
	 */
	bool OnSliderMove(void* param);

	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note ����ͼƬ����
	 */
	void OnChangeImage(TNotifyUI& msg);

	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note �ֶ���ӻ���ͼƬ��Ϊ�˺��������ȡͼƬ����
	 */
	bool CreateTileChirld(int number);

	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note ������ɫ����
	 */
	void OnChangeColor();

	void SetSliderMove(LONG nSlider);
};

class ColorPaletWindow : public WndBase {
public:
	explicit ColorPaletWindow(LPCTSTR pszXMLName);
	~ColorPaletWindow();

	DECLEAR_BK_CLASS(ColorPaletWindow)
public:
	DUI_DECLARE_MESSAGE_MAP();
	virtual void InitWindow();
	virtual void Notify(TNotifyUI& msg);
	virtual void OnClick(TNotifyUI& msg);
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	void Close();
};

}
