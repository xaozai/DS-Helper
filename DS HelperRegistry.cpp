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
#include "DS HelperRegistry.h"

DSHelperRegistry::DSHelperRegistry()
{
	LONG hRes = ::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\DS Helper"), 0, KEY_WRITE, &m_hkeyMain);
	if (hRes != ERROR_SUCCESS)
	{
		_com_error error(hRes);
		AfxGetApp()->GetMainWnd()->MessageBox(error.ErrorMessage(), L"Open the registry key error!", MB_ICONEXCLAMATION);
	}
}

DSHelperRegistry::~DSHelperRegistry()
{
	::RegCloseKey(m_hkeyMain);
}

HKEY DSHelperRegistry::GetMainHKey()
{
	return m_hkeyMain;
}

LONG DSHelperRegistry::WriteSZ(CEdit* Control, HKEY hKey, TCHAR* ValName)
{
	if (!hKey)
		return ERROR_INVALID_HANDLE;

	CString val;
	LONG hRes(0);

	Control->GetWindowText(val);

	if (val.IsEmpty())
		return ERROR_INVALID_DATA;

	return ::RegSetValueEx(hKey, ValName, NULL, REG_SZ, (const BYTE*)val.GetString(), (val.GetLength() + 1) * sizeof(TCHAR));
}