#ifndef __WIN_DIRECTORY_HPP_INCLUDE_20160125__
#define __WIN_DIRECTORY_HPP_INCLUDE_20160125__

//#include "stdafx.h"
#include <string>

namespace FileFolderHelper
{
	//bool GetDirFormatSize(LPCTSTR sDir, LPTSTR dataBlock, size_t dataSize);
	//�½�Ŀ¼    
	bool CreateDir(const wchar_t* lpDirPath);
	//ɾ��Ŀ¼ �� ����Ŀ¼
	bool DeleteDir(const wchar_t* lpDirPath);
	//�ж��Ƿ� ���ļ���
	bool IsDir(const wchar_t* sDirPath);
	//�����ļ��еĴ�С
	unsigned __int64 CalcFolderSize(const wchar_t* lpFolderPath);

	struct WinFolderData
	{
		unsigned __int64				ulFileSize;
		unsigned int					uFileCount;
		unsigned int					uFolderCount;
		WinFolderData()
		{
			ulFileSize = 0;
			uFileCount = 0;
			uFolderCount = 0;
		}
	};
	//�����ļ��� ����Ϣ
	bool CalcFolderInfo(const wchar_t* lpFolderPath, WinFolderData& info);
	unsigned __int64 CalcFileSize(const wchar_t* lpFilePath) ;
	
	std::wstring FileSizeToStr(unsigned __int64 ulFileSize);
	std::wstring FileSizeToBSize(unsigned __int64 ulFileSize);
	
	
	//bool SlipStringByChar(LPCTSTR lpStr, TCHAR Char);
	std::wstring GetFileExt(const wchar_t* lpFileName);

	// ��ȡ�ļ��ĵ�ǰĿ¼ ·�� ���� ȥ���ļ��� 
	std::wstring GetFileCurDir(const wchar_t* lpFileName);

	//����ļ� ��Ч  ���� ������ */\||֮��� �ַ�
	bool IsFileNameValid(const wchar_t* lpFileName);
}//end namespace

//////////////////////////////////////////////////////////////////////////
#endif // __WIN_DIRECTORY_HPP_INCLUDE_20160125__

