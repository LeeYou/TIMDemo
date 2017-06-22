#pragma once
#include "Typedef.h"
#include "SQLiteBase.h"
#include <map>
//IM  �� ���� ����

class CacheHandle
{
public:
	CacheHandle(void);
	~CacheHandle(void);
	void Init(LPCTSTR lpDataPath, LPCTSTR lpUserName);
	SStringT GetImgCachePath() const{return m_szImgCachePath;}
public:
	//  ��� �Ự ��Ϣ 
	void InitRecentTalkInfo(UserList& recentList);
	void NewTalkInfo(UINT uId, LPCTSTR lpUserAlias, LPCTSTR lpContent);
	void UpdateTalk(UINT uId, LPCTSTR lpUserAlias, LPCTSTR lpContent=NULL);
	void MoveTalkTo(UINT uId);

	// ���ڷ��͵���Ϣ
	const SendingChatList* GetSendingChatList(UINT uUserId);
	void AddSendingChat(UINT uUserId, LPCTSTR lpChatContent, const AsyncSendMsgParam& info);
	bool GetSendChatInfo(UINT uUserId, LPCTSTR lpChatId, AsyncSendMsgParam& info);
	void UpdateStateChat(UINT uUserId, LPCTSTR lpChatId, EnChatState eState);
	void DelStateChatAndSave(UINT uUserId, LPCTSTR lpChatId, __int64 lBodyId, __int64 lTime);
	
	//  �����¼
	const ChatRecordList* GetChatRecordList(UINT uUserId);
	void AddChatRecord(UINT uUserId, EnChatType eType, __int64 lBodyId, LPCTSTR lpContent, __int64 lTime);
	SStringT GetBodyContentBy(UINT uUserId, __int64 lBodyId);
	void UpdateBodyContent(UINT uUserId, __int64 lBodyId, LPCTSTR lpContent);

protected:
	void InsertSqlite(UINT uUserId, const ChatRecord& chatInfo);
	void SelectRecord(UINT uUserId, ChatRecordList& pList);
private:
	
	std::map<UINT, SendingChatList*>				m_mapStateChat;			// ��״̬����Ϣ 
	std::map<UINT, ChatRecordList*>				m_mapChatRecord;			// �����¼  

	SStringT														m_szUserCachePath;		// ��ǰ�û���cachepath
	
	pugi::xml_document									m_docRecentTalk;
	SStringT														m_szRecentTalkXml;

	SStringT														m_szImgCachePath;			// ͼƬ�Ļ����ļ���

	SQLite3DB													m_Sqlite;

};


extern CacheHandle		theCache;				// �������� 