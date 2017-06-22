
#ifndef __CUSTOM_EVENT_H__
#define __CUSTOM_EVENT_H__

//#include "core/SWnd.h"
namespace SOUI
{

	/////////////////////////////////֪ͨ���� �첽 �¼�   /////////////////////////////////////////

	// һ��ʼ�ĳ�ʼ�� 
	class EventStartInit : public TplEventArgs<EventStartInit>
	{
		SOUI_CLASS_NAME(EventStartInit, L"on_event_startinit")
	public:
		EventStartInit(SObject *pSender)
			: TplEventArgs<EventStartInit>(pSender)
			, bSuccess(false)
		{
			
		}
		enum{EventID=EVT_EXTERNAL_BEGIN+10001};
		bool bSuccess;
		
		SStringT szErrorText;
	};
	
	//֪ͨ����  �첽��ȡ δ����Ϣ �¼� 
	class EventGetUnreadMsg : public TplEventArgs<EventGetUnreadMsg>
	{
		SOUI_CLASS_NAME(EventGetUnreadMsg, L"on_event_gerunread")
	public:
		EventGetUnreadMsg(SObject *pSender)
			: TplEventArgs<EventGetUnreadMsg>(pSender)
			, bSuccess(false)
			, uSenderId(0)
		{
		
		}
		~EventGetUnreadMsg()
		{
			for each(auto var in bodyList)
			{
				delete var;
			}
		}
		enum{EventID=EVT_EXTERNAL_BEGIN+10003};
		bool bSuccess;
		IMBodyContentList bodyList;
		UINT uSenderId;
		SStringT szErrorText;
	};

	// ֪ͨ���� ���� ��Ϣ ״̬֪ͨ
	class EventSendMsg : public TplEventArgs<EventSendMsg>
	{
		SOUI_CLASS_NAME(EventSendMsg, L"on_event_sendmsg")
	public:
		EventSendMsg(SObject *pSender)
			: TplEventArgs<EventSendMsg>(pSender)
			, uRecipierId(0)
		{
			bSuccess = false;
			
			lTime = 0;
			lBodyId = 0;
		}
		enum{EventID=EVT_EXTERNAL_BEGIN+10004};
		bool bSuccess;
		UINT uRecipierId;
		SStringT szRichObjId;
		__int64 lBodyId;
		__int64 lTime;
		
	};

	// ֪ͨ���� �ϴ����� ����״̬ 
	class EventHttpUploadFile : public TplEventArgs<EventHttpUploadFile>
	{
		SOUI_CLASS_NAME(EventHttpUploadFile, L"on_event_httpuploadfile")
	public:
		EventHttpUploadFile(SObject *pSender)
			: TplEventArgs<EventHttpUploadFile>(pSender)
			, uRecipierId(0)
			, nFileId(0)
		{
		}
		enum{EventID=EVT_EXTERNAL_BEGIN+10005};
		UINT uRecipierId;
		int nFileId;				// ����0  �ɹ� �ļ�id  ����  -100 - 0  ����   -101 ��ʼ ��ʾ����
	};

	// ֪ͨ���� ���ظ��� ���� ״̬
	class EventHttpDownFile : public TplEventArgs<EventHttpDownFile>
	{
		SOUI_CLASS_NAME(EventHttpDownFile, L"on_event_httpdownfile")
	public:
		EventHttpDownFile(SObject *pSender)
			: TplEventArgs<EventHttpDownFile>(pSender)
			, uRecipientId(0)
			, lBodyId(0)
			, nAttachId(0)
			, nPercent(0)
		{
		}
		enum{EventID=EVT_EXTERNAL_BEGIN+10006};
		UINT uRecipientId;
		__int64 lBodyId;			// �Ǹ�  �������� ����Ԫ�� Ҫ���½���
		UINT nAttachId;
		int nPercent;				// <0  ����  > 100  �ɹ�
	};

	// ֪ͨ���� ��������Ա 
	class EventSaveApprover : public TplEventArgs<EventSaveApprover>
	{
		SOUI_CLASS_NAME(EventHttpUploadFile, L"on_event_saveapprover")
	public:
		EventSaveApprover(SObject *pSender)
			: TplEventArgs<EventSaveApprover>(pSender)
		{
		}
		enum{EventID=EVT_EXTERNAL_BEGIN+10007};
		
	};

}



#endif	//__PATHBAR_H__