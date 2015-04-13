#pragma once
namespace DES_CONTROL {
	class SliderWnd : public CWindowWnd ,
	public INotifyUI
{
public:
	SliderWnd();
	~SliderWnd();

public:
	void Init(CControlUI* pOwner);

private:
	void Notify(TNotifyUI& msg);
	LPCTSTR GetWindowClassName() const {
		return _T("SKinSlider");
	}
	void OnFinalMessage(HWND hWnd) {
		delete this;
	}

	LRESULT OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	/*LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);*/

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void AdjustPosion();
	void PrepareSlider();
	bool OnSliderChanged(void* param);
private:
	CPaintManagerUI *m_pManager;
	CControlUI* m_pControl;
	CDuiRect m_rect;
};
}
