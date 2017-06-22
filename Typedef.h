#pragma once
#include <list>

#pragma pack(push, 1)

struct UserInfo
{
	UINT				uId;
	SStringT			sName;
	SStringT			sContent;
};

typedef std::list<UserInfo>				UserList;

//����� ����Ϣ �ṹ 
struct IMBodyContent
{
public:
	__int64			lBodyId;					// id  ÿ����Ϣ ��Ψһ��
	//std::wstring	sBodyContent;		// body ����			// ��wstring  ���� �� move  ��Ϊ����п��� �ܴ� 
	SStringT			sBodyContent;		// body ����	�Ժ� ���� ���Ż���  
	__int64			lTime;					// ÿ����Ϣ ����ʱ�� 
};

typedef std::list<IMBodyContent*>		IMBodyContentList;

// ����msg ����
enum EnChatType
{
	eChT_Left = 0,
	eChT_Center = 1,
	eChT_Right = 2,
	eChT_More = 3,
	eChT_Split = 4,
	eChT_CenterWithoutBk = 5,
};

//���� ��¼  ���� �ṹ 
struct ChatRecord
{
	EnChatType		eType;
	__int64			lBodyId;
	SStringT			szContent;
	__int64			lTime;
};
typedef std::list<ChatRecord*>		ChatRecordList;


// soap ������Ϣ �ṹ��
struct SendMsgParam
{
	UINT				uRecipientId;				// ������ id
	SStringT			szContent;					// �������� 
};

// �첽 ���� ��Ϣ ����
struct AsyncSendMsgParam : public SendMsgParam		
{
	SStringT			szChatId;				// ����� rich ��Ϣ id ���� ���ҵ�
};

// ���ڷ��� ����Ϣ״̬  �ɹ����� ��Ϣ�� �Ͳ���Ҫ����� 
enum EnChatState
{
	eCST_Waiting = 0,
	eCST_Sending = 1,
	eCST_Error = 2,
};

// ���� ���͵� ��Ϣ �ṹ�� 
struct SendingChatInfo : public AsyncSendMsgParam				
{
	EnChatState			eState;						// ״̬
	SStringT					szChatContent;			// ���� 
	SendingChatInfo(EnChatState e, LPCTSTR lpChatContent, const AsyncSendMsgParam& info)
		: AsyncSendMsgParam(info)
		, eState(e)
		, szChatContent(lpChatContent)
	{

	}
};

typedef std::list<SendingChatInfo*>		SendingChatList;


struct SendMsgResult
{
	__int64		lBodyId;
	bool			bApprove;
	__int64		lTime;
};

#pragma pack(pop)