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
#include "stdafx.h"
#include <codecvt>
#include "WebClient.h"

void WebClient::InitCodesDescr()
{
	 m_CodesDescriptions[100] = L"Continue";
	 m_CodesDescriptions[101] = L"Switching Protocol";
	 m_CodesDescriptions[200] = L"OK";
	 m_CodesDescriptions[201] = L"Created";
	 m_CodesDescriptions[202] = L"Accepted";
	 m_CodesDescriptions[203] = L"Non-Authoritative Information";
	 m_CodesDescriptions[204] = L"No Content";
	 m_CodesDescriptions[205] = L"Reset Content";
	 m_CodesDescriptions[206] = L"Partial Content";
	 m_CodesDescriptions[300] = L"Multiple Choice";
	 m_CodesDescriptions[301] = L"Moved Permanently";
	 m_CodesDescriptions[302] = L"Found";
	 m_CodesDescriptions[303] = L"See Other";
	 m_CodesDescriptions[304] = L"Not Modified";
	 m_CodesDescriptions[305] = L"Use Proxy";
	 m_CodesDescriptions[306] = L"unused";
	 m_CodesDescriptions[307] = L"Temporary Redirect";
	 m_CodesDescriptions[308] = L"Permanent Redirect";
	 m_CodesDescriptions[400] = L"Bad Request";
	 m_CodesDescriptions[401] = L"Unauthorized";
	 m_CodesDescriptions[402] = L"Payment Required";
	 m_CodesDescriptions[403] = L"Forbidden";
	 m_CodesDescriptions[404] = L"Not Found";
	 m_CodesDescriptions[405] = L"Method Not Allowed";
	 m_CodesDescriptions[406] = L"Not Acceptable";
	 m_CodesDescriptions[407] = L"Proxy Authentication Required";
	 m_CodesDescriptions[408] = L"Request Timeout";
	 m_CodesDescriptions[409] = L"Conflict";
	 m_CodesDescriptions[410] = L"Gone";
	 m_CodesDescriptions[411] = L"Length Required";
	 m_CodesDescriptions[412] = L"Precondition Failed";
	 m_CodesDescriptions[413] = L"Request Entity Too Large";
	 m_CodesDescriptions[414] = L"Request-URI Too Long";
	 m_CodesDescriptions[415] = L"Unsupported Media Type";
	 m_CodesDescriptions[416] = L"Requested Range Not Satisfiable";
	 m_CodesDescriptions[417] = L"Expectation Failed";
	 m_CodesDescriptions[429] = L"Too Many Requests";
	 m_CodesDescriptions[451] = L"Unavailable For Legal Reasons";
	 m_CodesDescriptions[500] = L"Internal Server Error";
	 m_CodesDescriptions[501] = L"Not Implemented";
	 m_CodesDescriptions[502] = L"Bad Gateway";
	 m_CodesDescriptions[503] = L"Service Unavailable";
	 m_CodesDescriptions[504] = L"Gateway Timeout";
	 m_CodesDescriptions[505] = L"HTTP Version Not Supported";
	 m_CodesDescriptions[510] = L"Not Extended";
	 m_CodesDescriptions[511] = L"Network Authentication Required";
	 m_CodesDescriptions[599] = L"Network connect timeout error";

	 m_SynoDSCodesDescriptions[100] = L"Unknown error";
	 m_SynoDSCodesDescriptions[101] = L"Invalid parameter";
	 m_SynoDSCodesDescriptions[102] = L"The requested API does not exist";
	 m_SynoDSCodesDescriptions[103] = L"The requested method does not exist";
	 m_SynoDSCodesDescriptions[104] = L"The requested version does not support the functionality";
	 m_SynoDSCodesDescriptions[105] = L"The logged in session does not have permission";
	 m_SynoDSCodesDescriptions[106] = L"Session timeout";
	 m_SynoDSCodesDescriptions[107] = L"Session interrupted by duplicate login"; 
	 m_SynoDSCodesDescriptions[400] = L"File upload failed";
	 m_SynoDSCodesDescriptions[401] = L"Max number of tasks reached";
	 m_SynoDSCodesDescriptions[402] = L"Destination denied";
	 m_SynoDSCodesDescriptions[403] = L"Destination does not exist";
	 m_SynoDSCodesDescriptions[404] = L"Invalid task id";
	 m_SynoDSCodesDescriptions[405] = L"Invalid task action";
	 m_SynoDSCodesDescriptions[406] = L"No default destination";
	 m_SynoDSCodesDescriptions[407] = L"Set destination failed";
	 m_SynoDSCodesDescriptions[408] = L"File does not exist";

	 m_SynoFSCodesDescriptions[100] = L"Unknown error";
	 m_SynoFSCodesDescriptions[101] = L"Invalid parameter";
	 m_SynoFSCodesDescriptions[102] = L"The requested API does not exist";
	 m_SynoFSCodesDescriptions[103] = L"The requested method does not exist";
	 m_SynoFSCodesDescriptions[104] = L"The requested version does not support the functionality";
	 m_SynoFSCodesDescriptions[105] = L"The logged in session does not have permission";
	 m_SynoFSCodesDescriptions[106] = L"Session timeout";
	 m_SynoFSCodesDescriptions[107] = L"Session interrupted by duplicate login";
	 m_SynoFSCodesDescriptions[400] = L"Invalid parameter of file operation";
	 m_SynoFSCodesDescriptions[401] = L"Unknown error of file operation";
	 m_SynoFSCodesDescriptions[402] = L"System is too busy";
	 m_SynoFSCodesDescriptions[403] = L"Invalid user does this file operation";
	 m_SynoFSCodesDescriptions[404] = L"Invalid group does this file operation";
	 m_SynoFSCodesDescriptions[405] = L"Invalid user and group does this file operation";
	 m_SynoFSCodesDescriptions[406] = L"Can’t get user/group information from the account server";
	 m_SynoFSCodesDescriptions[407] = L"Operation not permitted";
	 m_SynoFSCodesDescriptions[408] = L"No such file or directory";
	 m_SynoFSCodesDescriptions[409] = L"Non-supported file system ";
	 m_SynoFSCodesDescriptions[410] = L"Failed to connect internet-based file system (ex: CIFS)";
	 m_SynoFSCodesDescriptions[411] = L"Read-only file system";
	 m_SynoFSCodesDescriptions[412] = L"Filename too long in the non-encrypted file system";
	 m_SynoFSCodesDescriptions[413] = L"Filename too long in the encrypted file system";
	 m_SynoFSCodesDescriptions[414] = L"File already exists";
	 m_SynoFSCodesDescriptions[415] = L"Disk quota exceeded";
	 m_SynoFSCodesDescriptions[416] = L"No space left on device";
	 m_SynoFSCodesDescriptions[417] = L"Input/output error";
	 m_SynoFSCodesDescriptions[418] = L"Illegal name or path";
	 m_SynoFSCodesDescriptions[419] = L"Illegal file name";
	 m_SynoFSCodesDescriptions[420] = L"Illegal file name on FAT filesystem";
	 m_SynoFSCodesDescriptions[421] = L"Device or resource busy";
	 m_SynoFSCodesDescriptions[599] = L"No such task of the file operation";
	 
}

WebClient::WebClient()
{
	InitCodesDescr();
}

WebClient::~WebClient()
{
	m_session.Close();
}

CString WebClient::GetCodeDescription(DWORD code)
{
	m_it = m_CodesDescriptions.find(code);
	if (m_it != m_CodesDescriptions.end())
		return m_it->second;
	else
		return L"Look at the description on the Internet";
}

CString WebClient::GetSynoDSCodeDescription(DWORD code)
{
	m_it = m_SynoDSCodesDescriptions.find(code);
	if (m_it != m_SynoDSCodesDescriptions.end())
		return m_it->second;
	else
		return L"unknown";
}

CString WebClient::GetSynoFSCodeDescription(DWORD code)
{
	m_it = m_SynoFSCodesDescriptions.find(code);
	if (m_it != m_SynoDSCodesDescriptions.end())
		return m_it->second;
	else
		return L"unknown";
}

CString WebClient::Urlencode(CString* sIn)
{
	
	CString RetVal(CW2A(sIn->GetString(), CP_UTF8));
	RetVal.Replace(L"%", L"%25");
	RetVal.Replace(L"+", L"%2B");
	RetVal.Replace(L" ", L"%20");
	RetVal.Replace(L"&", L"%26");
	RetVal.Replace(L"=", L"%3D");
	return RetVal;

}

CString WebClient::getInetError(DWORD err)
{
	HANDLE h = ::GetModuleHandle(_T("WinINet.dll"));
	if (h != NULL)
	{ 
		LPTSTR p;
		if (::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE, (LPCVOID)h, err, 0, (LPTSTR)&p, 0, NULL) != 0)
		{ 
			CString s(p);
			s.Replace(_T("\r\n"), _T(""));
			return s;
		} 
	} 

	CString s;
	s.Format(_T("%d"), err);
	return s;
} 

HTTPResponse WebClient::ReadResponse(CHttpFile* HTTPfile, bool convert)
{
	HTTPResponse RetVal;

	DWORD dwStatus;

	m_Response = L"";

	HTTPfile->QueryInfoStatusCode(dwStatus);
	if (dwStatus != 200)
	{
		m_Response.Format(L"The server has returned the code: %u (%s)", dwStatus, GetCodeDescription(dwStatus));
		RetVal.strResponse = m_Response;
		RetVal.code = dwStatus;
		return RetVal;
	}

	char szBuff[1024] = { 0 };
	UINT nRead = HTTPfile->Read(szBuff, 1024);
	while (nRead > 0)
	{

		if (convert)
			m_Response = m_Response + CA2W(CStringA(szBuff, nRead), CP_UTF8);
		else
			m_Response = m_Response + CString(szBuff, nRead);

		nRead = HTTPfile->Read(szBuff, 1024);
	}

	RetVal.strResponse = m_Response;
	RetVal.code = dwStatus;

	return RetVal;
}

HTTPResponse WebClient::GetURL(Protocol Prot, CString* URL, bool Convert)
{
	HTTPResponse RetVal; 
	
	DWORD flags(0);
	if(Prot == HTTPS)
		flags = INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_SECURE | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_PRAGMA_NOCACHE;
	else
		flags = INTERNET_FLAG_TRANSFER_ASCII | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_PRAGMA_NOCACHE;

	CHttpFile* HTTPfile = NULL;

	bool SecondTry = false;

Again:
	try
	{
		HTTPfile = (CHttpFile *)m_session.OpenURL(URL->GetString(), 1, flags);
	}
	catch (CInternetException *e)
	{
		if (e->m_dwError == ERROR_INTERNET_INVALID_CA || e->m_dwError == ERROR_INTERNET_SEC_CERT_DATE_INVALID || e->m_dwError == ERROR_INTERNET_SEC_CERT_CN_INVALID)
		{
			if (!SecondTry)
			{
				if (HTTPfile)
				{
					DWORD dwSecurityFlags;
					HTTPfile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwSecurityFlags);
					dwSecurityFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_REVOCATION | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
					HTTPfile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwSecurityFlags);
				}
				SecondTry = true;
				goto Again;
			}
			else
			{
				RetVal.strResponse = getInetError(e->m_dwError);
				RetVal.code = e->m_dwError;
				e->Delete(); 
				return RetVal;
			}
		}
		else
		{
			RetVal.strResponse = getInetError(e->m_dwError);
			RetVal.code = e->m_dwError;
			e->Delete(); 
			return RetVal;
		}

		e->Delete();
	}
	
	if (!HTTPfile)
		return RetVal;

	RetVal = ReadResponse(HTTPfile, Convert);

	HTTPfile->Close(); delete HTTPfile; HTTPfile = NULL;

	return RetVal;
}

HTTPResponse WebClient::GetURL(Protocol Prot, CString* Address, CString* Port, CString* Target, CString* URL)
{
	HTTPResponse RetVal; 
	
	DWORD flags(0);
	if (Prot == HTTPS)
		flags = INTERNET_FLAG_SECURE;
	else
		flags = INTERNET_FLAG_TRANSFER_ASCII;

	CHttpConnection* connection = m_session.GetHttpConnection(Address->GetString(), (INTERNET_PORT)_wtoi(Port->GetString()));
	CHttpFile* HTTPfile = connection->OpenRequest(CHttpConnection::HTTP_VERB_GET, Target->GetString(), NULL, 1, 0, 0, flags);

	bool SecondTry = false;

Again:
	try
	{
		HTTPfile->SendRequest();
	}
	catch (CInternetException *e)
	{
		if (e->m_dwError == ERROR_INTERNET_INVALID_CA || e->m_dwError == ERROR_INTERNET_SEC_CERT_DATE_INVALID || e->m_dwError == ERROR_INTERNET_SEC_CERT_CN_INVALID)
		{
			if (!SecondTry)
			{
				DWORD dwSecurityFlags;
				HTTPfile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwSecurityFlags);
				dwSecurityFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_REVOCATION | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
				HTTPfile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwSecurityFlags);
				SecondTry = true;
				goto Again;
			}
			else
			{
				RetVal.strResponse = getInetError(e->m_dwError);
				RetVal.code = e->m_dwError;
				e->Delete();
				return RetVal;
			}
		}
		else
		{
			RetVal.strResponse = getInetError(e->m_dwError);
			RetVal.code = e->m_dwError;
			e->Delete();
			return RetVal;
		}
		
		e->Delete();
	}

	

	if (!HTTPfile)
		return RetVal;

	RetVal = ReadResponse(HTTPfile);
	
	HTTPfile->Close(); delete HTTPfile; HTTPfile = NULL;

	return RetVal;
}

void WebClient::MakeBoundary(CString* Str)
{
	GUID guid; CoCreateGuid(&guid);
	wchar_t szGuidW[40] = { 0 };
	StringFromGUID2(guid, szGuidW, 40);
	
	CString tmp(szGuidW);
	tmp.Replace(L"{", L""); 
	tmp.Replace(L"-", L"");
	tmp.Replace(L"}", L"");

	Str->Append(L"--------------------");
	Str->Append(tmp);
}

HTTPResponse WebClient::PostFile(Protocol Prot, CString* PathToFile, CString* Address, CString* Port, CString* Destination, CString* SID)
{
	HTTPResponse RetVal;

	DWORD dwStatus(0);
	
	m_Response = "";

	DWORD flags(0);

	if (Prot == HTTPS)
		flags = INTERNET_FLAG_KEEP_CONNECTION | INTERNET_FLAG_SECURE;
	else
		flags = INTERNET_FLAG_KEEP_CONNECTION;

	CFile file;
	if (!file.Open(PathToFile->GetString(), CFile::modeRead | CFile::typeBinary))
	{
		_com_error error(::GetLastError());
		AfxGetApp()->GetMainWnd()->MessageBox(error.ErrorMessage(), L"Can't open the file", MB_ICONEXCLAMATION);
		return RetVal;
	}

	CHttpConnection* connection = m_session.GetHttpConnection(Address->GetString(), (INTERNET_PORT)_wtoi(Port->GetString()));

	CHttpFile* HTTPfile = connection->OpenRequest(CHttpConnection::HTTP_VERB_POST, L"/webapi/DownloadStation/task.cgi", NULL, 1, 0, 0, flags);

	//DWORD dwTimeout = 1200000;/*defines the connection timeout in ms*/
	//InternetSetOption(*HTTPfile, INTERNET_OPTION_CONTROL_RECEIVE_TIMEOUT, &dwTimeout, sizeof(DWORD));
	//InternetSetOption(*HTTPfile, INTERNET_OPTION_CONTROL_SEND_TIMEOUT, &dwTimeout, sizeof(DWORD));

	CString Boundary;
	MakeBoundary(&Boundary);

	HTTPfile->AddRequestHeaders(L"Content-Type: multipart/form-data; boundary=" + Boundary + "\r\n", HTTP_ADDREQ_FLAG_ADD_IF_NEW | HTTP_ADDREQ_FLAG_REPLACE);//HTTP_ADDREQ_FLAG_ADD
	
	CStringA BoundaryA = CW2A(Boundary, CP_ACP);

	CStringA BODYpre = "--" + BoundaryA + "\r\n";
	BODYpre += "Content-Disposition: form-data; name=\"api\"\r\n\r\n";
	BODYpre += "SYNO.DownloadStation.Task\r\n";
	BODYpre += "--" + BoundaryA + "\r\n";
	BODYpre += "Content-Disposition: form-data; name=\"version\"\r\n\r\n";
	BODYpre += "1\r\n"; 
	BODYpre += "--" + BoundaryA + "\r\n";
	BODYpre += "Content-Disposition: form-data; name=\"method\"\r\n\r\n";
	BODYpre += "create\r\n";
	BODYpre += "--" + BoundaryA + "\r\n";
	BODYpre += "Content-Disposition: form-data; name=\"destination\"\r\n\r\n";
	BODYpre += CStringA(Destination->GetString()) + "\r\n";
	BODYpre += "--" + BoundaryA + "\r\n";
	BODYpre += "Content-Disposition: form-data; name=\"file\"; filename=\"" + CStringA(file.GetFileName()) + "\"\r\n";
	BODYpre += "Content-Type: application/octet-stream\r\n\r\n";
	
	CStringA BODYpost = "\r\n" + BoundaryA + "--\r\n\r\n";//the last "\r\n" just for correct the length
	
	HTTPfile->SendRequestEx(DWORD(BODYpre.GetLength() + file.GetLength() + BODYpost.GetLength()), HSR_SYNC | HSR_INITIATE);

	HTTPfile->Write(BODYpre, BODYpre.GetLength());
	
	char szBuff[2048];
	UINT nRead = file.Read(&szBuff, 2048);
	while (nRead > 0)
	{
		HTTPfile->Write(&szBuff, nRead);
		nRead = file.Read(&szBuff, 2048);
	}
	file.Close(); 

	HTTPfile->Write(BODYpost, BODYpost.GetLength());

	bool SecondTry = false;
	
Again:
	try
	{
		HTTPfile->EndRequest(HSR_SYNC);
	}
	catch (CInternetException *e)
	{
		if (e->m_dwError == ERROR_INTERNET_INVALID_CA || e->m_dwError == ERROR_INTERNET_SEC_CERT_DATE_INVALID || e->m_dwError == ERROR_INTERNET_SEC_CERT_CN_INVALID)
		{
			if (!SecondTry)
			{
				if (HTTPfile)
				{
					DWORD dwSecurityFlags;
					HTTPfile->QueryOption(INTERNET_OPTION_SECURITY_FLAGS, dwSecurityFlags);
					dwSecurityFlags |= SECURITY_FLAG_IGNORE_UNKNOWN_CA | SECURITY_FLAG_IGNORE_REVOCATION | INTERNET_FLAG_IGNORE_CERT_CN_INVALID | INTERNET_FLAG_IGNORE_CERT_DATE_INVALID;
					HTTPfile->SetOption(INTERNET_OPTION_SECURITY_FLAGS, dwSecurityFlags);
					SecondTry = true;
				}
				
				goto Again;
			}
			else
			{
				RetVal.strResponse = getInetError(e->m_dwError);
				RetVal.code = e->m_dwError;
				e->Delete();
				return RetVal;
			}
		}
		else
		{
			RetVal.strResponse = getInetError(e->m_dwError);
			RetVal.code = e->m_dwError;
			e->Delete();
			return RetVal;
		}

		e->Delete();
	}

	if (!HTTPfile)
		return RetVal;

	RetVal = ReadResponse(HTTPfile);

	HTTPfile->Close(); delete HTTPfile; HTTPfile = NULL;

	return RetVal;
}