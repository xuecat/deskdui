#pragma once

namespace DES_WND {

	//���뿪ʼΪpos׼���ġ���Ч������
	//���淢����width��������㡣��Ч��չ��

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

		virtual void OnAnimationStart(INT nAnimationID, BOOL bFirstLoop) {}//һ��ѭ�������Բ�����
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