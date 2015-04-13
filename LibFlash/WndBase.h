#pragma once
#ifdef UILIB
#include <UiLib/UIlib.h>
#include <UiLib/Utils/WinImplBase.h>
	using namespace UiLib;

	// 以XML生成界面的窗口基类
	class WndBase : public WindowImplBase
	{
	public:
		explicit WndBase(LPCTSTR pszXMLName) 
			: m_strXMLName(pszXMLName){}

	public:
		virtual LPCTSTR GetWindowClassName() const
		{
			return _T("UiLib_Demos");
		}

		virtual CDuiString GetSkinFile()
		{
			return m_strXMLName;
		}

		virtual CDuiString GetSkinFolder()
		{
			return _T("skin");
		}

	protected:
		CDuiString m_strXMLName;    // XML的名字
	};

#else
#include <UIlib.h>
#include <Utils/WinImplBase.h>
using namespace DuiLib;

namespace DES_WND {

#define DECLEAR_BK_BASE(CCBase)								\
public:														\
	static void Register(CContainerUI* p, bool b);			\
	static void Destructe(CContainerUI* p, bool b);			\
public:														\
	static bool SetBKIndex(int num)/*图片编号是0开始*/;		\
	static bool SetBKIndex(DWORD dcolor)/*设置颜色*/;		\
	static int  GetBKIndex();								\
	static DWORD GetBKColors();								\
private:													\
	static void SetBKImages(std::pair<CContainerUI*, bool>& p);	\
	static void SetBKColors(std::pair<CContainerUI*, bool>& p);	\
private:													\
	static int m_nImageIndex;								\
	static DWORD m_dBKColor;								\
	static std::deque<std::pair<CContainerUI*, bool>> m_bk_control;

#define IMPLEMENT_BK_BASE(CCBase)							\
	int CCBase::m_nImageIndex = -1;							\
	DWORD CCBase::m_dBKColor = 0;							\
	std::deque<std::pair<CContainerUI*, bool>> CCBase::m_bk_control;	\
	\
	void CCBase::Register(CContainerUI* p, bool b) {		\
		std::pair<CContainerUI*, bool> t_p(p, b);			\
		if (WndBase::m_nImageIndex != -1) SetBKImages(t_p);	\
		if (WndBase::m_dBKColor != 0) SetBKColors(t_p);		\
		m_bk_control.push_back(std::make_pair(p, b));		\
	}														\
	int  CCBase::GetBKIndex() {								\
		return CCBase::m_nImageIndex;						\
	}														\
	DWORD CCBase::GetBKColors() {							\
		return CCBase::m_dBKColor;							\
	}														\
	bool CCBase::SetBKIndex(int num)/*图片编号是0开始*/ {	\
		if (m_bk_control.empty()) return false;				\
		if (m_nImageIndex == num) return false;				\
			else m_nImageIndex = num;						\
			for_each(m_bk_control.begin(), m_bk_control.end(), SetBKImages);\
		return true;										\
	}														\
	bool CCBase::SetBKIndex(DWORD dcolor) {					\
	if (m_dBKColor == dcolor) return false;					\
			else m_dBKColor = dcolor;						\
			for_each(m_bk_control.begin(), m_bk_control.end(), SetBKColors);\
		return true;										\
	}														\
	void CCBase::SetBKColors(std::pair<CContainerUI*, bool>& p) {\
		if (p.first->GetBkColor() == m_dBKColor) return;	\
			p.first->SetBkImage(_T("layout\\bktrans.png"));	\
			p.first->SetBkColor(m_dBKColor);				\
			CCBase::m_nImageIndex = -1;						\
	}														\
	void CCBase::SetBKImages(std::pair<CContainerUI*, bool>& p) {\
		string_t str_name;									\
		str_name.append(_T("file='layout\\"));				\
		str_name.append(N_TOSTR(m_nImageIndex).c_str());	\
		if (p.second == false) {							\
			str_name.append(_T(".png' source='1,120,166,576'"));\
		} else str_name.append(_T(".png'"));				\
		p.first->SetBkImage(str_name.c_str());				\
		CCBase::m_dBKColor = 0;								\
	}														\
	void CCBase::Destructe(CContainerUI* p, bool b) {		\
		std::pair<CContainerUI*, bool> fin(p, b);				\
		std::deque<std::pair<CContainerUI*, bool>>::iterator i;	\
		i = std::find(m_bk_control.begin(), m_bk_control.end(), fin);\
		if (i != m_bk_control.end()) {						\
			m_bk_control.erase(std::remove(m_bk_control.begin(), m_bk_control.end(), *i), m_bk_control.end());\
		}													\
	}														


#define DECLEAR_BK_CLASS(CDerived) /*传入派生和基类*/		\
private:													\
	static bool m_bRegistered;								\
	static void CDerived##Register(CContainerUI* p, bool b);\
	static void CDerived##Destructe(CContainerUI* p, bool b);\
	void CreateBK()/*派生类每次调用一下*/;					\
	void CreateBK(LPCTSTR lpstr);/*为单个控件背景服务*/		\
	void Destructe();

#define IMPLEMENT_BK_CLASS(CDerived, CCBase)/*传入背景控件（类型，但我当字符串处理）*/\
	bool CDerived::m_bRegistered = false;					\
															\
	void CDerived::CDerived##Register(CContainerUI* p, bool b) {\
		if (!m_bRegistered) {								\
			CCBase::Register(p, b);							\
			m_bRegistered = true;							\
		}													\
	}														\
	void CDerived::CDerived##Destructe(CContainerUI* p, bool b) {\
		if (m_bRegistered) {								\
			CCBase::Destructe(p, b);						\
			m_bRegistered = false;							\
		}													\
	}														\
	void CDerived::Destructe() {							\
		CContainerUI* p_control = static_cast<CContainerUI*>(CDerived::m_PaintManager.FindControl(_T(#CDerived)));\
		CDerived##Destructe(p_control, true);				\
	}														\
	void CDerived::CreateBK()/*派生类每次调用一下*/ {			\
		CContainerUI* p_control = static_cast<CContainerUI*>(CDerived::m_PaintManager.FindControl(_T(#CDerived)));\
		CDerived##Register(p_control, true);				\
	}														\
	void CDerived::CreateBK(LPCTSTR lpstr) {				\
		m_bRegistered = false;								\
		CContainerUI* p_control = static_cast<CContainerUI*>(CDerived::m_PaintManager.FindControl(lpstr));\
		CDerived##Register(p_control, false);				\
	}

	// 以XML生成界面的窗口基类
	class WndBase : public WindowImplBase
	{
		DECLEAR_BK_BASE(WndBase)
	public:
		explicit WndBase(LPCTSTR pszXMLName);
		~WndBase();
		static std::wstring N_TOSTR(int d);

	public:
		virtual LPCTSTR GetWindowClassName() const
		{
			return _T("XMLWnd");
		}

		virtual CDuiString GetSkinFile()
		{
			return m_strXMLName;
		}

		virtual CDuiString GetSkinFolder()
		{
			return _T("skin");
		}

	protected:
		CDuiString m_strXMLName;    // XML的名字
	};
#endif
}




