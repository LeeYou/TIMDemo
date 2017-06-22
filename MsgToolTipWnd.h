#pragma once
#include "resource.h"
#include <functional>
#include <map>

class CMsgToolTipWnd : public SHostWnd
{
public:
	CMsgToolTipWnd(std::function<void(UINT)> fun);
	~CMsgToolTipWnd(void);
			
	void OnBtnIgnore();
	void OnBtnViewAll();
public:
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void MoveButtomRight(int nPadding=10);
	
	void ShowUnreadMsg();				// ��ʾ ����

	void AddUnreadMsg(UINT uUserId, LPCTSTR lpUserAlias, LPCTSTR lpContent, UINT uCount=1);
	void SetTotalCount(UINT uCount);
protected:
	//�¼�����ӳ���
	EVENT_MAP_BEGIN()
		
		EVENT_NAME_COMMAND(L"btn_ignore", OnBtnIgnore)
		EVENT_NAME_COMMAND(L"btn_viewall", OnBtnViewAll)
	EVENT_MAP_END()

	//������Ϣ����ӳ���
	BEGIN_MSG_MAP_EX(CNotifyWnd)
		MSG_WM_INITDIALOG(OnInitDialog)
		CHAIN_MSG_MAP(SHostWnd)
	END_MSG_MAP()

protected:
	template<class T>
	inline void InitWnd(T*& pWnd, LPCTSTR lpWndName)
	{
		pWnd = FindChildByName2<T>(lpWndName);
		if(NULL == pWnd)
		{
			SStringT sErrorText;
			sErrorText.Format(_T("û��nameΪ <%s> �Ŀؼ�"), lpWndName);
			SMessageBox(m_hWnd, sErrorText, _T("����"), MB_ICONERROR);
		}
	}
private:
	std::function<void(UINT)>			m_funClick;			// ����¼� �ص�
	UINT											m_uSenderId;
	UINT											m_uTotalCount;							// ���� δ��������
	std::map<UINT, UINT>				m_mapSenderCount;			// ���� sender ��δ���� 
private:
	SImageWnd*			m_pImgUser;
	SStatic*					m_pTextSender;				//������ 
	SStatic*					m_pTextSendMsg;				//���͵���Ϣ
	SWindow*				m_pWinTotalCount;
	SWindow*				m_pWinCount;
};

