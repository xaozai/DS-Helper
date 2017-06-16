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
#pragma once
#ifndef _DS_HELPER_H_
#define _DS_HELPER_H_

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"

#include "DS HelperTypes.h"
#include "WebClient.h"
#include "jsoncpp/json.h"

class CDSHelperApp : public CWinApp
{
public:
	CDSHelperApp();

// Overrides
public:
	virtual BOOL InitInstance();

	bool AuthOnSyno(CString* SessionName, CString* strRet = NULL);
	std::string CString2Std(CString&);

	bool m_ProtectPasswControl;
	
	CString m_AppAddress;
	CString m_AppPort;
	CString m_AppUsername;
	CString m_AppPassword;
	CString m_AppSID;
	
	Protocol m_AppEnumProto;

	WebClient* m_pAppSynoConnect = NULL;
	Json::Reader* m_pJSONreader = NULL;


	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CDSHelperApp theApp;

#endif