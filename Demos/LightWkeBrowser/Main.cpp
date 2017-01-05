#include "StdAfx.h"
#include "MainWnd.h"
#include "resource.h"

void InitResource(HINSTANCE hInstance)
{
	CPaintManagerUI::SetInstance(hInstance);

	// ��Դ����
#ifdef _DEBUG
	CPaintManagerUI::SetResourceType(UILIB_FILE);
#else
	CPaintManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
#endif

	// ��Դ·��
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();

	// ������Դ
	switch (CPaintManagerUI::GetResourceType())
	{
	case UILIB_FILE:
	{
		strResourcePath += _T("skin\\LightWkeBrowser\\");
		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());

		// ������Դ����
		//CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL);
	}
	break;

	case UILIB_ZIPRESOURCE:
	{
		//strResourcePath += _T("..\\skin\\Heinote\\");

		HINSTANCE hInst = CPaintManagerUI::GetInstance();
		HRSRC hResource = ::FindResource(hInst, MAKEINTRESOURCE(IDR_ZIPRES), _T("ZIPRES"));
		//DWORD dwErr = GetLastError();
		if (hResource != NULL)
		{
			DWORD dwSize = 0;
			HMODULE hModule = CPaintManagerUI::GetResourceDll();
			HGLOBAL hGlobal = ::LoadResource(hModule, hResource);
			if (hGlobal != NULL)
			{
				dwSize = ::SizeofResource(hModule, hResource);
				if (dwSize > 0)
				{
					CPaintManagerUI::SetResourceZip((LPBYTE)::LockResource(hGlobal), dwSize);

					// ������Դ������
					//CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL);
				}
			}
			::FreeResource(hResource);
		}
	}
	break;

	default:
		break;
	}

	// ע��ؼ�
	REGIST_DUICONTROL(CWkeWebkitUI);
}

// void InitResource()
// {
// 	// ��Դ����
// #ifdef _DEBUG
// 	CPaintManagerUI::SetResourceType(UILIB_FILE);
// #else
// 	CPaintManagerUI::SetResourceType(UILIB_ZIPRESOURCE);
// #endif
// 	// ��Դ·��
// 	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
// 	// ������Դ
// 	switch (CPaintManagerUI::GetResourceType())
// 	{
// 	case UILIB_FILE:
// 	{
// 		strResourcePath += _T("skin\\LightWkeBrowser\\");
// 		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
// 		break;
// 	}
// 	case UILIB_ZIPRESOURCE:
// 	{
// // 		strResourcePath += _T("skin\\LightWkeBrowser\\");
// // 		CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
// 		HRSRC hResource = ::FindResource(CPaintManagerUI::GetInstance(), _T("IDR_ZIPRES"), _T("ZIPRES"));
// 		if (hResource != NULL) {
// 			DWORD dwSize = 0;
// 			HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
// 			if (hGlobal != NULL) {
// 				dwSize = ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource);
// 				if (dwSize > 0) {
// 					CPaintManagerUI::SetResourceZip((LPBYTE)::LockResource(hGlobal), dwSize);
// 				}
// 			}
// 			::FreeResource(hResource);
// 		}
// 	}
// 	break;
// 	}
// 
// 	// ע��ؼ�
// 	REGIST_DUICONTROL(CWkeWebkitUI);
// }

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	// COM
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr)) return 0;
	// OLE
	HRESULT hRes = ::OleInitialize(NULL);
	// ��ʼ��UI������
	CPaintManagerUI::SetInstance(hInstance);
	// ��ʼ����Դ
	InitResource(hInstance);

	// ����������
	CMainWnd MainWnd;
	MainWnd.Create(NULL, _T("LightWkeBrowser"), (UI_WNDSTYLE_FRAME | WS_MINIMIZEBOX) & ~WS_SYSMENU, 0L);
	MainWnd.CenterWindow();
	// ��Ϣѭ��
	CPaintManagerUI::MessageLoop();

	// OLE
	OleUninitialize();
	// COM
	::CoUninitialize();
	return 0;
}