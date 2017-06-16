/*
// Synology DownloadStation Helper
//
// The application is designed to simplify adding your download tasks to DownloadStation on your Synology DiskStation.
//
// MIT License
//
// Copyright (c) 2017 xaozai
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/
#include "stdafx.h"//precompiled headers
#include "DS Helper.h"
#include "DS HelperDlg.h"
#include "WebClient.h"
#include "jsoncpp/json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//---hyperlink
// Enable Visual Style
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
//---hyperlink

BEGIN_MESSAGE_MAP(CDSHelperApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CDSHelperApp::CDSHelperApp()
{
	
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

}

CDSHelperApp theApp;

BOOL CDSHelperApp::InitInstance()
{
	CWinApp::InitInstance();

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	m_pAppSynoConnect = new WebClient;
	m_pJSONreader = new Json::Reader;

	CDSHelperDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	if (m_pAppSynoConnect)
		delete m_pAppSynoConnect;

	if (m_pJSONreader)
		delete m_pJSONreader;

	
	return FALSE;
}

bool CDSHelperApp::AuthOnSyno(CString* SessionName, CString* strRet)
{
	CString URL;
	HTTPResponse Response;
	
	m_AppSID = L"";

	Json::Value root;//will contains the root value after parsing.

	if (m_AppEnumProto == HTTPS)
	{
		URL = L"/webapi/auth.cgi?api=SYNO.API.Auth&version=2&method=login&account=" + m_AppUsername + L"&passwd=" + m_AppPassword + L"&session=" + SessionName->GetString() + L"&format=sid";
		Response = m_pAppSynoConnect->GetURL(m_AppEnumProto, &m_AppAddress, &m_AppPort, &URL, NULL);
	}
	else
	{
		URL = L"http://" + m_AppAddress + L":" + m_AppPort + L"/webapi/auth.cgi?api=SYNO.API.Auth&version=2&method=login&account=" + m_AppUsername + L"&passwd=" + m_AppPassword + L"&session=" + SessionName->GetString() + L"&format=sid";
		Response = m_pAppSynoConnect->GetURL(m_AppEnumProto, &URL);
	}

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
		{
			if (strRet)
				strRet->SetString(Response.strResponse);
			else
				theApp.GetMainWnd()->MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
		
		return false;
	}

	bool parsingSuccessful = m_pJSONreader->parse(CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", m_pJSONreader->getFormattedErrorMessages());
		
		if (strRet)
			strRet->SetString(Response.strResponse);
		else
			theApp.GetMainWnd()->MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);

		return false;
	}

	if ((root.get("success", "false").asString()) == "false")
	{
		if (strRet)
			strRet->SetString(L"The server returned \"success\": false");
		else
			theApp.GetMainWnd()->MessageBox(L"The server returned \"success\": false", L"DS Helper - Authentication error", MB_ICONEXCLAMATION);
		return false;
	}
	else
	{
		if (root.isMember("data"))
		{
			if (root["data"].isMember("sid"))
				m_AppSID=((root["data"]["sid"]).asCString());
		}
	}
		
	return true;
}

std::string CDSHelperApp::CString2Std(CString &str)
{
	//CT2CA pszConvertedAnsiString(str);
	CW2A pszConvertedAnsiString(str);
	std::string strStd(pszConvertedAnsiString);

	return strStd;
}

int CDSHelperApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
