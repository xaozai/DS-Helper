#pragma once

#ifndef _INTERNETCLIENT_H_
#define _INTERNETCLIENT_H_

#include <map>
#include "afxinet.h"

typedef struct
{
	DWORD code;
	CString strResponse;
} HTTPResponse;

class InternetClient
{

public:
	InternetClient();
	~InternetClient();

	HTTPResponse GetURL(CString*);
	HTTPResponse PostFile(CString, CString, CString*, CStringA*);
	CString GetSynoCodeDescription(DWORD);

private:
	CString GetCodeDescription(DWORD);
	void InitCodesDescr();

	CInternetSession m_session;
	CString m_Response;

	std::map<DWORD, TCHAR*> m_CodesDescriptions, m_SynoCodesDescriptions;
	std::map<DWORD, TCHAR*>::iterator m_it;

};
#endif
