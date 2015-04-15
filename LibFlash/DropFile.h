#pragma once
#include "oleidl.h"
typedef void (*DROPCALLBACK)(HWND, HDROP);
//继承修改
class CDropFile :
	public IDropTarget
{
public:
	CDropFile(void);
	~CDropFile(void);

	typedef struct _DRAGDATA {
		int cfFormat;
		STGMEDIUM stgMedium;
	} DRAGDATA,*LPDRAGDATA;

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, _COM_Outptr_ void **ppvObject);
	ULONG STDMETHODCALLTYPE AddRef();
	ULONG STDMETHODCALLTYPE Release();
	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, __RPC__inout DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragEnter(__RPC__in_opt IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, __RPC__inout DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragLeave();
	HRESULT STDMETHODCALLTYPE Drop(__RPC__in_opt IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, __RPC__inout DWORD *pdwEffect);
	BOOL DrapDropRegister(HWND hWnd, DWORD AcceptKeyState = MK_LBUTTON);//Ä¬ÈÏ½ÓÊÜÊó±ê×ó¼ü
	BOOL GetDragData(IDataObject *pDataObject,FORMATETC cFmt);
	void ProcessDrop(LPDRAGDATA pDropData/*HDROP hDrop*/);

private:
	bool	m_bUseDnDHelper;
	IDropTargetHelper* m_piDropHelper;
	HWND m_hTargetWnd;
	DWORD m_dAcceptKeyState;
	ULONG m_ulRefCount;
	vector<LPDRAGDATA> m_Array;
};

