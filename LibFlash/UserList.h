#pragma once

namespace DES_WND {

	//代码开始为pos准备的。特效是推移
	//后面发现用width坐标更方便。特效是展开

	class CUserListUI : public CContainerUI,
		public CUIAnimation
	{
	public:
		//DECLEAR_BK_CLASS(UserListWindow);
		explicit CUserListUI(CPaintManagerUI& paint_manager, LPCTSTR szPath);
		~CUserListUI(void);

		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);

		virtual void DoEvent(TEventUI& event);
		virtual void OnTimer(int nTimerID);

		virtual void OnAnimationStart(INT nAnimationID, BOOL bFirstLoop) {}//一次循环。所以不处理
		virtual void OnAnimationStep(INT nTotalFrame, INT nCurFrame, INT nAnimationID);
		virtual void OnAnimationStop(INT nAnimationID);

		void SetAnimaVisible(bool bVisible = true);

	private:
		void SwitchShow(LONG ltype);
		void SetDelayVisible(bool bVisible = true);
	private:
		bool m_bDirection;
		LONG m_lCurWidth;
		LONG m_lFixWidth;
		LONG m_lOldWidth;
		CDialogBuilder m_dlgBuilder;
	};

}