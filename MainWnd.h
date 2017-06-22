#pragma once
#include "resource.h"
#include "CacheHandle.h"
#include "MsgToolTipWnd.h"
#include "ui\MessageBoxLayout.h"
#include "TrayHandle.h"
#include "ui\CustomEvent.h"
#include "ui\SIconRadio.hpp"
#include "ui\imre\SImRichedit.h"
#include "skin\SVscrollbar.h"
#include "skin\SAntialiasSkin.h"
#include "skin\WinFileIconSkin.hpp"
#include "skin\MaskSkin.hpp"
#include "adapter/RecentListAdapter.hpp"
#include "adapter/ContactTreeAdapter.hpp"
#include "adapter/EmotionTileAdapter.hpp"
#include "AsynFunctionT.hpp"
#include "SharkWinHandle.hpp"

#define WM_TRAYNOTIFY							WM_USER + 201
//*Ҫ���������������ʵ�����벻����Ϣӳ�䣬������ͨ����Ϣӳ�����е㲻ͬ��
//explorer������ʱ����׳�WM_TASKBAR_CREATED��Ϣ�����ǵĳ���Ҫ�������Ϣ����Ӧ��
// ��֮ͬ������Ҫ��ע�������Ϣ��
static UINT WM_TASKBAR_CREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));

//#define		LAYOUT_MODULE		1

class CMainWnd : public SHostWnd
							, public TAutoEventMapReg<CMainWnd>//֪ͨ�����Զ�ע��
{
private:
	struct AsyncSaveApproverParam
	{
		__int64			lBodyId;
		SStringT			szApproverText;
	};
public:
	CMainWnd(void);
	~CMainWnd(void);
	
	void OnBtnMin()
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
	}
	void OnBtnClose()
	{
#ifdef LAYOUT_MODULE
		CloseMain();
#else
		//if(NULL == m_pWndMsgToolTip)
			CloseMain();
		//else
		//	ShowWindow(SW_HIDE);
#endif
	}
	void SetDlgItemVisible(LPCTSTR lpName, bool bShow)
	{
		auto p = FindChildByName(lpName);
		if(NULL != p)
			p->SetVisible(bShow ? TRUE : FALSE, TRUE);
	}
	void SetDlgItemText(LPCTSTR lpName, LPCTSTR lpText)
	{
		auto p = FindChildByName(lpName);
		if(NULL != p)
			p->SetWindowText(lpText);
	}
	void ShowInfoBox(LPCTSTR lpText, LPCTSTR lpCaption=L"��ʾ", UINT uType=MB_ICONINFORMATION)
	{
		//return SMessageBox(m_hWnd, lpText, lpCaption, uType);
		m_pAsynMessageBox->ShowAsyncMsgBox(lpText, lpCaption, uType);
	}
	void ShowErrorBox(LPCTSTR lpText=L"����")
	{
		//return SMessageBox(m_hWnd, lpText, _T("����"), MB_ICONERROR);
		m_pAsynMessageBox->ShowAsyncMsgBox(lpText, _T("����"), MB_ICONERROR);
	}
	void FlashWindow(DWORD dwFlags=FLASHW_TRAY | FLASHW_TIMERNOFG)
	{
		FLASHWINFO fwi;
		fwi.cbSize = sizeof(fwi);
		fwi.hwnd = m_hWnd;
		fwi.dwFlags = dwFlags;
		fwi.uCount = 0;
		fwi.dwTimeout = 0;

		::FlashWindowEx(&fwi);
	}
	void CloseMain()
	{
		m_Tray.Delete();
		__super::DestroyWindow();
	}
	// ���� ���� 
	void SharkWindow();
public:
	BOOL OnInitDialog(HWND wndFocus, LPARAM lInitParam);
	void OnTimer(UINT_PTR idEvent);
	//�Զ���ؼ��¼�����
	void OnBtnSendMsg();
	void OnClickRadioTalk();
	void OnClickRadioContact();
	void OnClickRadioNotice();
	void OnBtnSendPic();
	void OnBtnLoadTalk();			// ���� �Ự ��ť
	void OnBtnUploadFile();			// ���͸���
	
public:	// ֪ͨ���� �¼� �ӿ�
	bool OnCenterEventStartInit(EventStartInit* pEvt);
	bool OnCenterEventGetUnreadMsg(EventGetUnreadMsg* pEvt);	
	bool OnCenterEventSendMsg(EventSendMsg* pEvt);
public:  // im rich �¼�
	bool OnRecordRichObjEvent(EventRichEditObj* pEvt);
	bool OnInputRichMenu(EventCtxMenu* pEvt);
protected:
	//�¼�����ӳ���  Ƶ���� ��������д��ǰ���� ���� �ж� ����� �� 
	EVENT_MAP_BEGIN()
		EVENT_NAME_COMMAND(L"btn_chat_upload", OnBtnUploadFile)
		EVENT_NAME_COMMAND(L"btn_chat_sendpic", OnBtnSendPic)
		EVENT_NAME_COMMAND(L"btn_close", OnBtnClose)
		EVENT_NAME_COMMAND(L"btn_min", OnBtnMin)
		EVENT_NAME_COMMAND(L"btn_send", OnBtnSendMsg)
		EVENT_NAME_COMMAND(L"radio_talk", OnClickRadioTalk)
		EVENT_NAME_COMMAND(L"radio_contact", OnClickRadioContact)
		EVENT_NAME_COMMAND(L"radio_notice", OnClickRadioNotice)
		EVENT_NAME_COMMAND(L"pagec_img_talk", OnBtnLoadTalk)
	EVENT_MAP_END()

	void OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags);
	LRESULT OnTrayNotify(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnTaskbarCreated(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//������Ϣ����ӳ���
	BEGIN_MSG_MAP_EX(CMainWnd)
		MSG_WM_KEYDOWN(OnKeyDown)
		MESSAGE_HANDLER_EX(WM_TRAYNOTIFY, OnTrayNotify)
		MESSAGE_HANDLER_EX(WM_TASKBAR_CREATED, OnTaskbarCreated)//
		MSG_WM_TIMER(OnTimer)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_CLOSE(OnBtnClose)
		CHAIN_MSG_MAP(SHostWnd)
	END_MSG_MAP()
public:
	// �����ϵ�� item ��� �ص�
	void CallBack_RecentListItemClick(int nIndex);
	// �����ϵ�� item �� btn �ص�
	void CallBack_RecentListBtnClick(int nIndex);
	// ��ϵ�˽��� tree  ���� �¼� �ص�
	void CallBack_ContactTvItemClick(UINT uId);
	// ��ϵ�˽��� tree  ˫�� �¼� �ص�
	void CallBack_ContactTvItemDbClick(UINT uId);
	// ������� ѡ�� �ص� 
	void CallBack_Emotion(UINT uIndex);
	// ��Ϣ ��ʾ�� �Ļص�
	void CallBack_MsgToolTip(UINT uId);

	// ��ʼ��  �߳� ����
	void ThreadFun_StartInit(LPARAM lParam);
	// ��ȡδ����Ϣ �߳� ������
	void ThreadFun_GetUnreadMsg(LPARAM lParam);
	// ������Ϣ �߳� ������
	void ThreadFun_SendMsg(LPARAM lParam);
	
private:
	// �����ϵ�� ѡ�� �� 
	void RecentListSelect(int nIndex);
	// �л� �û� �Ự 
	void SwitchUserTalkSession(UINT uId, LPCTSTR lpUserAlias, LPCTSTR lpUserLevel);
	// ��� ���ڷ��͵���Ϣ һ�㶼���� right 
	void AddStateChatMsg(LPCTSTR lpRichName, LPCTSTR lpContent, EnChatState eState);
	// �����������֮ǰ �����õ�ǰ�����û� 
	void AddChatMsg(EnChatType eType, __int64 lBodyId, LPCTSTR lpMsgBody);
private:
	template<class T>
	inline void InitWnd(T*& pWnd, LPCTSTR lpWndName)
	{
		pWnd = FindChildByName2<T>(lpWndName);
		if(NULL == pWnd)
		{
			SStringT sErrorText;
			sErrorText.Format(_T("û��nameΪ <%s> �Ŀؼ�"), lpWndName);
			ShowErrorBox(sErrorText);
		}
	}
	void ShowLoadingPage(BOOL bShow)
	{
		m_pLayLoading->SetVisible(bShow, TRUE);
	}
	
	void StartTrayTwinkle()
	{
		//m_Tray.Modify(lpTipInfo);
		//SetTimer(10, 500);
	}
	void EndTrayTwinkle()
	{
		//KillTimer(10);
		//m_Tray.Update();
	}
	// �л� ҳ�� �� �Ự ����ϵ�� 
	void SwitchPage(int nSel);
	// �� �����ϵ���б����
	int NewTalkSession(UINT uUserId, LPCTSTR lpUserAlias, LPCTSTR lpContent, UINT uCount=0);
	void DelRecentTalk(UINT uUserId);
	// δ����Ϣ ����
	void NewIMMsgHandle(UINT uSenderId, LPCTSTR lpMsg);
	//����  �Ự ���� δ�� ����
	UINT UpdateTalkSessionUnreadCount();
		
	void LoadUserPng(LPCTSTR lpSkinName, LPCTSTR lpPngName);
	SStringT GetUserIconSkin(UINT uUserId);
	SStringT ParseContentToIM(const SStringW& sHtml, SStringT* pszBriefInfo);
public:
	SWindow*					m_pUnreadCount;				// 
	STabCtrl*					m_pTabMain;
	SWindow*					m_pLayLoading;					// ����ҳ��
	SWindow*					m_pLaySession;
	
	SStatic*						m_pSessionTitle;					//
	SWindow*					m_pSessionLevel;
	SImRichEdit*				m_pChatRecord;					// ��Ϣ ��¼ ��
	SImRichEdit*				m_pChatInput;					// ����� 
	RecentListAdapter*		m_pRecentListAdapter;			// ������� ����
	ContactTreeAdapter*		m_pContactTreeAdapter;			// ��ϵ�� 
	EmotionTileAdapter*		m_pEmotionTileAdapter;		// ����
	
	CMsgToolTipWnd*			m_pWndMsgToolTip;						// ���½� ������

	MessageBoxLayout*			m_pAsynMessageBox;					 // ��ģ��� ��Ϣ ��ʾ��	

private:
	SStringT									m_szUserAlias;
	AsynTaskHandle<LPARAM>		m_AsynNetTask;
	UINT										m_uCurrentTalkUserId;
	//SStringT									m_sCurrentTalkTitle;
	SStringT									m_szUserIconPath;
	TrayHandle								m_Tray;
	std::map<UINT, SStringT>		m_mapUserSkin;
	SharkWinHandle						m_SharkWin;
};

