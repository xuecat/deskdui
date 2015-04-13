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
	 *  @ note 滑动控件设置透明度
	 */
	bool OnSliderMove(void* param);

	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note 换肤图片函数
	 */
	void OnChangeImage(TNotifyUI& msg);

	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note 手动添加换肤图片，为了后期网络获取图片换肤
	 */
	bool CreateTileChirld(int number);

	/** 
	 *  @ [in]param
	 *  @ [out]param
	 *  @ return
	 *  @ note 换肤颜色函数
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
