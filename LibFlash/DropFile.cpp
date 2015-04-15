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

HRESULT CDropFile::DragEnter(
	__RPC__in_opt IDataObject *pDataObj,
	DWORD grfKeyState,
	POINTL pt,
	__RPC__inout DWORD *pdwEffect) {
		if (grfKeyState != m_dAcceptKeyState) {
			*pdwEffect = DROPEFFECT_NONE;
			return S_OK;
		}
		STGMEDIUM stgMedium;

		FORMATETC cfmt = {(CLIPFORMAT)CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};
		HRESULT ret = pDataObj->GetData(&cfmt, &stgMedium);
		if (FAILED(ret)) return FALSE;
		if (stgMedium.pUnkForRelease != NULL) return FALSE;

		switch (stgMedium.tymed)
		{
		default:
			break;
		}
}