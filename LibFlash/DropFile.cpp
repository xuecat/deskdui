#include "stdafx.h"
#include "DropFile.h"


CDropFile::CDropFile(void)
{
}


CDropFile::~CDropFile(void)
{
}

BOOL CDropFile::DrapDropRegister(HWND hWnd, DWORD AcceptKeyState /* = MK_LBUTTON */) {
	if (!IsWindow(hWnd)) return false;
	HRESULT hr = ::RegisterDragDrop(hWnd, this);
	if (SUCCEEDED(hr)) {
		m_hTargetWnd = hWnd;
		m_dAcceptKeyState = AcceptKeyState;
		return true;
	} else return false;
}

HRESULT STDMETHODCALLTYPE CDropFile::DragEnter(
	__RPC__in_opt IDataObject *pDataObj,
	DWORD grfKeyState,
	POINTL pt,
	__RPC__inout DWORD *pdwEffect) {
		if( grfKeyState != m_AcceptKeyState )
	{
		*pdwEffect = DROPEFFECT_NONE;
		return S_OK;
	}
	
	FORMATETC cFmt = {(CLIPFORMAT) CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
	GetDragData(pDataObject, cFmt);

	*pdwEffect = DROPEFFECT_COPY;

	if ( m_bUseDnDHelper )
	{
		m_piDropHelper->DragEnter ( m_hTargetWnd, pDataObject, (LPPOINT)&pt, *pdwEffect );
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDropFile::DragOver(DWORD grfKeyState,POINTL pt,	DWORD *pdwEffect)
{
	ScreenToClient(m_hTargetWnd, (LPPOINT)&pt);
	/////修改需要
	if( grfKeyState != m_AcceptKeyState || pt.x < m_rcList.left || pt.x > m_rcList.right || pt.y < m_rcList.top || pt.y > m_rcList.bottom)
	{
		*pdwEffect = DROPEFFECT_NONE;	
	}
	else
	{
		*pdwEffect = DROPEFFECT_COPY ;
	}
	if ( m_bUseDnDHelper )
	{
		m_piDropHelper->DragOver((LPPOINT)&pt, *pdwEffect);
	}
	
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDropFile::DragLeave(void)
{
	int temp = m_Array.size();
	for(UINT i = 0;i < m_Array.size(); i++)
	{
		LPDRAGDATA pData = m_Array[i];
		::ReleaseStgMedium(&pData->stgMedium);
		delete pData;
		m_Array.clear();
	}

	if ( m_bUseDnDHelper )
	{
		m_piDropHelper->DragLeave();
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CDropFile::Drop(IDataObject *pDataObj,DWORD grfKeyState,	POINTL pt,	DWORD __RPC_FAR *pdwEffect)
{

	int temp = m_Array.size();
	for(UINT i = 0; i < m_Array.size(); i++)
	{
		LPDRAGDATA pData = m_Array[i];

		//ÎÒÕâÀïÖ»»ñÈ¡ÁËHDROPÀàÐÍµÄÊý¾Ý£¬ËùÒÔÖ±½Ó¿ªÊ¼´¦Àí
		ProcessDrop(pData);
		::ReleaseStgMedium(&pData->stgMedium);
		delete pData;
		m_Array.clear();
	}
	
	if ( m_bUseDnDHelper )
	{
		m_piDropHelper->Drop ( pDataObj,  (LPPOINT)&pt, *pdwEffect );
	}

	return S_OK;
}

BOOL CDropFile::GetDragData(IDataObject *pDataObject,FORMATETC cFmt)
{
	HRESULT ret=S_OK;
	STGMEDIUM stgMedium;

	ret = pDataObject->GetData(&cFmt, &stgMedium);

	if (FAILED(ret))
		return FALSE;

	if (stgMedium.pUnkForRelease != NULL)
		return FALSE;


	switch (stgMedium.tymed)
	{
	//¿ÉÒÔÀ©³äÕâ¿é´úÂë£¬ÅäºÏEnumDragDataº¯ÊýÀ´±£´æ¸ü¶àÀàÐÍµÄÊý¾Ý
	case TYMED_HGLOBAL:
		{

			LPDRAGDATA pData = new DRAGDATA;

			pData->cfFormat = cFmt.cfFormat ;
			memcpy(&pData->stgMedium,&stgMedium,sizeof(STGMEDIUM));

			m_Array.push_back(pData);

			return true;
			break;

		}
	default:
		// type not supported, so return error
		{
			::ReleaseStgMedium(&stgMedium);
		}
		break;
	}

	return false;

}

void CDropFile::ProcessDrop(LPDRAGDATA pDropData/*HDROP hDrop*/)
{
	switch(pDropData->cfFormat)
	{
	case CF_TEXT:
		{
			//m_pTextCallBack((HDROP)pDropData->stgMedium.hGlobal);
			break;
		}
	case CF_HDROP:
		{
			m_pDropCallBack(m_pMainWnd, (HDROP)pDropData->stgMedium.hGlobal);
			break;
		}
	default:
		break;
	}

}