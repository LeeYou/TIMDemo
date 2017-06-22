#pragma once
#include "stdafx.h"

class SharkWinHandle
{
public:
	SharkWinHandle(void)
		: m_nIndex(0)
	{

	}

	virtual ~SharkWinHandle(void)
	{

	}
	
	// ��ʼ�� 
	void Init(HWND hWnd)
	{
		m_hWnd = hWnd;
		
	}
	 void UpdateSize(const CRect& rc)
	 {
		 m_rcWnd = rc;
	 }
	//  ��ʼ 
	void OnTimeSharkWin()
	{
		int ty = 2;
		
		int nLeft = m_rcWnd.left;
		int nTop = m_rcWnd.top;

		int nType = m_nIndex % 7;
		switch (nType)
		{
		case 0:					// �� ��
			nLeft -= ty;
			nTop += ty;
			break;
		case 1:					// ��
			nLeft -= ty;
			//nTop += ty;
			break;
		case 2:					// �� ����
			nLeft -= ty;
			nTop -= 2 * ty;
			break;
		case 3:					// �� ��
			//nLeft -= ty;
			nTop -= 2 * ty;
			break;
		case 4:					// �� �� �� ��
			nLeft += 2 * ty;
			nTop -= 2 * ty;
			break;
		case 5:					// �� �� ��
			nLeft += 2 * ty;
			nTop -= ty;
			break;
		case 6:					// �� �� �� 
			nLeft += 2 * ty;
			nTop += ty;
			break;
		default:
			break;
		}
		
		::SetWindowPos(m_hWnd, NULL, nLeft, nTop, 0, 0, SWP_NOSIZE|SWP_SHOWWINDOW );

		++m_nIndex;
	}
	bool IsSharkDone()
	{
		if(35 == m_nIndex)
		{
			m_nIndex = 0;
			return true;
		}

		return false;
	}
protected:
	HWND				m_hWnd;
	CRect					m_rcWnd;
	UINT					m_nIndex;
};
