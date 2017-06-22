#ifndef __WINFILE_ICON_SKIN_HPP_
#define __WINFILE_ICON_SKIN_HPP_

#include "core/SSkinObjBase.h"
#include <commoncontrols.h>
//************************************
// ����� ϵͳ�ļ�ͼ�� ��Ƥ���ؼ��� ʹ��SHGetFileInfo ����ȡͼ������  
// ʹ��֮ǰ�� ע�� theApp->RegisterSkinFactory(TplSkinFactory<SSkinSystemIconList>());		//ע��Skin
// Ȼ����skin.xml �� ��� ��Դ  <sysiconlist name="sysiconlist" flag="1" />  flag ��ʾͼ���С���� �������Ҫ��
// 
//************************************
class SSkinSystemIconList: public SSkinObjBase
{
	SOUI_CLASS_NAME(SSkinSystemIconList, L"sysiconlist")

public:
	SSkinSystemIconList()
		: m_hIconList(NULL)
		, m_nImageCount(1)
	{			
		
	}
	virtual ~SSkinSystemIconList()
	{
		if(NULL != m_hIconList)
		{
			((IImageList*)m_hIconList)->Release();
			m_hIconList = NULL;
		}
	}

	virtual SIZE GetSkinSize()
	{
		return m_szSimpleIcon;
	}
	virtual int GetStates()
	{
		return m_nImageCount;
	}
protected:
	virtual void _Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha)
	{
		if(NULL == m_hIconList)
			return ;

		HICON hIcon = NULL;
		((IImageList*)m_hIconList)->GetIcon(dwState, ILD_NORMAL, &hIcon);
		if(NULL != hIcon)
		{
			pRT->DrawIconEx(rcDraw->left, rcDraw->top, hIcon, rcDraw->right-rcDraw->left, rcDraw->bottom-rcDraw->top, DI_NORMAL);
			DestroyIcon(hIcon);
			hIcon = NULL;
		}
	}
private:
	HIMAGELIST*		m_hIconList;
	SIZE					m_szSimpleIcon;
	int						m_nImageCount;
	SOUI_ATTRS_BEGIN()
		ATTR_CUSTOM(L"flag", OnAttrFlag)   //XML�ļ���ָ����ͼƬ��Դ��,(type:name) flag ��ʾͼ������ ��small large 
	SOUI_ATTRS_END()
protected:
	LRESULT OnAttrFlag(const SStringW &strValue,BOOL bLoading)
	{
		int nRet=0;   
		::StrToIntExW(strValue, STIF_SUPPORT_HEX, &nRet);

		//#define SHIL_LARGE          0   // normally 32x32
		//#define SHIL_SMALL          1   // normally 16x16
		//SHIL_EXTRALARGE��ȡ48 * 48��ͼ�꣬ SHIL_JUMBO ��ȡ256 * 256��ͼ�ꡣ
		HRESULT hResult = ::SHGetImageList(nRet , IID_IImageList, (void**)&m_hIconList);
		if(S_OK != hResult)
			return S_FALSE;

		//����ͼ���С 
		int nX = 0;
		int nY = 0;
		((IImageList*)m_hIconList)->GetIconSize(&nX, &nY);
		m_szSimpleIcon.cx = nX;
		m_szSimpleIcon.cy = nY;

		((IImageList*)m_hIconList)->GetImageCount(&m_nImageCount);

		return S_OK;
	}
};
//////////////////////////////////////////////////////////////////////////
#endif // __WINFILE_ICON_SKIN_HPP_

