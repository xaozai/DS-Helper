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

#ifndef _WebClient_H_
#define _WebClient_H_

#include <map>
#include "afxinet.h"
#include "DS HelperTypes.h"

class WebClient
{

public:
	WebClient();
	~WebClient();

	HTTPResponse GetURL(Protocol, CString* URL, bool Convert = false);
	HTTPResponse GetURL(Protocol, CString* Address, CString* Port, CString* target, CString* URL = NULL);

	CString Urlencode(CString* URL);

	HTTPResponse PostFile(Protocol Prot, CString* PathToFile, CString* Address, CString* Port, CString* Destination, CString* SID);
	
	CString GetSynoDSCodeDescription(DWORD);
	CString GetSynoFSCodeDescription(DWORD);

private:
	CInternetSession m_session;
	CString m_Response;
	
	std::map<DWORD, TCHAR*> m_CodesDescriptions, m_SynoDSCodesDescriptions, m_SynoFSCodesDescriptions;
	std::map<DWORD, TCHAR*>::iterator m_it;
	
	CString GetCodeDescription(DWORD);
	CString getInetError(DWORD err);
	void InitCodesDescr();
	void MakeBoundary(CString*);
	HTTPResponse ReadResponse(CHttpFile*, bool Convert = false);

};
#endif
