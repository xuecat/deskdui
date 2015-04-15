#pragma once
#include "oleidl.h"
class CDropFile :
	public IDropTarget
{
public:
	CDropFile(void);
	~CDropFile(void);

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void **ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, __RPC__inout DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragEnter(__RPC__in_opt IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, __RPC__inout DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragLeave();
	HRESULT STDMETHODCALLTYPE Drop(__RPC__in_opt IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, __RPC__inout DWORD *pdwEffect);
	BOOL DrapDropRegister(HWND hWnd, DWORD AcceptKeyState = MK_LBUTTON);//默认接受鼠标左键

private:
	HWND m_hTargetWnd;
	DWORD m_dAcceptKeyState;
	ULONG m_ulRefCount;
};

