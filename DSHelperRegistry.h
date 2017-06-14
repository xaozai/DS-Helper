#pragma once
#ifndef _WINREGISTRY_H_
#define _WINREGISTRY_H_

class DSHelperRegistry
{
public:
	DSHelperRegistry();
	~DSHelperRegistry();
	
	LONG WriteSZ(CEdit* Control, HKEY hKey, TCHAR* ValName);

	HKEY GetMainHKey();

private:
	HKEY m_hkeyMain = NULL;
};

#endif