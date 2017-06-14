#include "stdafx.h"
#include "DSHelperRegistry.h"
//#include "afxwin.h"
//#include "comdef.h"

DSHelperRegistry::DSHelperRegistry()
{
	LONG hRes = ::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\Simple DS Helper"), 0, KEY_WRITE, &m_hkeyMain);
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