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
#include "EditPathesDlg.h"
#include "afxdialogex.h"

#include "Crypto.h"

#include "jsoncpp/json.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	afx_msg void OnNMClickSyslinkLicense(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickSyslinkHomepage(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_LICENSE, &CAboutDlg::OnNMClickSyslinkLicense)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_HOMEPAGE, &CAboutDlg::OnNMClickSyslinkHomepage)
END_MESSAGE_MAP()

CDSHelperDlg::CDSHelperDlg(CWnd* pParent /*=NULL*/) : CDialogEx(CDSHelperDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDSHelperDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PATH, m_ComboPath);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_CEditAddress);
	DDX_Control(pDX, IDC_CHECK_STORE, m_StorePassword);
	DDX_Control(pDX, IDC_EDIT_USERNAME, m_CEditUsername);
	DDX_Control(pDX, IDC_EDIT_PASSWORD, m_CEditPassword);
	DDX_Control(pDX, IDC_BUTTON_EDIT_PATHES, m_ButtonEditPathes);
	DDX_Control(pDX, IDC_BUTTON_ADD_TASK, m_ButtonAddATask);
	DDX_Control(pDX, IDC_EDIT_TASK, m_CEditTask);
	DDX_Control(pDX, IDC_BUTTON_OPEN_FILE, m_ButtonOpenFile);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_ComboProtocol);
	DDX_Control(pDX, IDC_EDIT_PORT, m_CEditPort);
	DDX_Control(pDX, IDC_LIST_ACTIVE_TASKS, m_CListActiveTasks);
	DDX_Control(pDX, IDC_CHECK_SHOW_ACTIVE_TASKS, m_CheckBoxShowActiveTasks);
}

BEGIN_MESSAGE_MAP(CDSHelperDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD_TASK, &CDSHelperDlg::OnBnClickedButtonAddTask)
	ON_BN_CLICKED(IDC_CHECK_STORE, &CDSHelperDlg::OnBnClickedCheckStore)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK_OPEN_DS_WEB, &CDSHelperDlg::OnNMClickSyslinkOpenDsWeb)
	ON_EN_KILLFOCUS(IDC_EDIT_ADDRESS, &CDSHelperDlg::OnEnKillfocusEditAddress)
	ON_EN_KILLFOCUS(IDC_EDIT_USERNAME, &CDSHelperDlg::OnEnKillfocusEditUsername)
	ON_EN_KILLFOCUS(IDC_EDIT_PASSWORD, &CDSHelperDlg::OnEnKillfocusEditPassword)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_PATHES, &CDSHelperDlg::OnBnClickedButtonEditPathes)
	ON_BN_CLICKED(IDC_BUTTON_OPEN_FILE, &CDSHelperDlg::OnBnClickedButtonOpenFile)
	ON_EN_KILLFOCUS(IDC_EDIT_PORT, &CDSHelperDlg::OnEnKillfocusEditPort)
	ON_CBN_KILLFOCUS(IDC_COMBO_PROTOCOL, &CDSHelperDlg::OnCbnKillfocusComboProtocol)
	ON_CBN_CLOSEUP(IDC_COMBO_PROTOCOL, &CDSHelperDlg::OnCbnCloseupComboProtocol)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ACTIVE_TASKS, &CDSHelperDlg::OnBnClickedCheckShowActiveTasks)
	//ON_MESSAGE(WM_COMMAND, OnMenuClick)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//ON_NOTIFY(NM_RCLICK, IDC_LIST_ACTIVE_TASKS, &CDSHelperDlg::OnNMRClickListActiveTasks)
END_MESSAGE_MAP()

void CDSHelperDlg::HideCList()
{
	m_CListActiveTasks.ShowWindow(SW_HIDE);
	SetWindowPos(NULL, WinRect.left, WinRect.top, WinRect.Width(), CListRect.top + 12, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CDSHelperDlg::ShowCList()
{
	m_CListActiveTasks.ShowWindow(SW_SHOWNORMAL);
	SetWindowPos(NULL, WinRect.left, WinRect.top, WinRect.Width(), WinRect.Height(), SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

}

BOOL CDSHelperDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	this->GetWindowRect(WinRect);
	m_CListActiveTasks.GetWindowRect(CListRect);

	HideCList();
	
	//Create the ToolTip control
	if (!m_ToolTip.Create(this))
	{
		TRACE0("Unable to create the ToolTip!");
	}
	else
	{
		m_ToolTip.AddTool(&m_ButtonEditPathes, _T("Edit predefined pathes"));
		m_ToolTip.AddTool(&m_ButtonAddATask, _T("Add the task"));
		m_ToolTip.AddTool(&m_StorePassword, _T("Store the password"));
		m_ToolTip.AddTool(&m_ButtonOpenFile, _T("Open a file"));

		m_ToolTip.Activate(TRUE);
	}

	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	
	HICON hIcn = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_FOLDER), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR);
	m_ButtonOpenFile.SetIcon(hIcn);

	m_App = (CDSHelperApp *)AfxGetApp();

	m_DoSaveSettings = false;

	m_ComboProtocol.AddString(L"HTTP");
	m_ComboProtocol.AddString(L"HTTPS");

	m_CListImages.Create(16, 16, ILC_COLOR8 | ILC_COLOR16 | ILC_MASK, 2, 6);
	m_CListImages.Add(m_App->LoadIcon(IDI_ICON_EMPTY)); 
	m_CListImages.Add(m_App->LoadIcon(IDI_ICON_DOWNLOAD));
	m_CListImages.Add(m_App->LoadIcon(IDI_ICON_PAUSE));
	m_CListImages.Add(m_App->LoadIcon(IDI_ICON_COMPLETED));
	m_CListImages.Add(m_App->LoadIcon(IDI_ICON_FILE));
	m_CListImages.Add(m_App->LoadIcon(IDI_ICON_TIME));
	m_CListActiveTasks.SetImageList(&m_CListImages, LVSIL_SMALL);

	m_CListActiveTasks.InsertColumn(0, _T("id"), LVCFMT_LEFT, 0, 0); 
	m_CListActiveTasks.InsertColumn(1, _T("Name"), LVCFMT_LEFT, CListRect.Width() * 5 / 6, 1);
	m_CListActiveTasks.InsertColumn(2, _T("%"), LVCFMT_LEFT, CListRect.Width() / 6, 2);

	m_CListActiveTasks.SetExtendedStyle(m_CListActiveTasks.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_SUBITEMIMAGES);
	
		
	ReadSettings();//read the app settings
	
	byte nLast = m_ComboPath.GetCount() - 1;
	if (nLast >= 0)
		m_ComboPath.SetCurSel(nLast);

	m_DoSaveSettings = true;

	GetTaskFromCommandLine();
	
	return TRUE; 
}

void CDSHelperDlg::GetTaskFromCommandLine()
{
	m_CEditTask.SetWindowText(AfxGetApp()->m_lpCmdLine);

	return;
}

void CDSHelperDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CDSHelperDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CDSHelperDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CDSHelperDlg::ReadPathesToCombo()
{
	HKEY hKey(0);
	CString cKeyName = _T("");
	LONG hRes;

	if (::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\DS Helper\\Pathes"), 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{
		TCHAR szData[256];
		ZeroMemory(szData, 1);
		DWORD dwKeyDataType;
		DWORD dwDataBufSize = 256;

		for (byte i = 1; i < 254; i++)
		{
			cKeyName.Format(_T("P%u"), i);

			hRes = ::RegQueryValueEx(hKey, cKeyName, NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
			if (hRes == ERROR_SUCCESS)
			{
				switch (dwKeyDataType)
				{
				case REG_SZ:
					m_ComboPath.AddString(szData);
					ZeroMemory(szData, 1);
					dwDataBufSize = 256;
					dwKeyDataType = 0;
					break;
				}
			}
			else
			{
				break;
			}

		}
		::RegCloseKey(hKey);
	}
	else
	{
		//not found, create
		hRes = ::RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\DS Helper", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		if (hRes != ERROR_SUCCESS)
		{
			_com_error error(hRes);
			MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
		}
		else
			::RegCloseKey(hKey);

		::RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\DS Helper\\Pathes", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		::RegCloseKey(hKey);
	}

	return true;
}

void CDSHelperDlg::OnBnClickedCheckStore()
{
	HKEY hKey = m_Registry.GetMainHKey();
	DWORD val(0);
	LONG hRes(0);

	if (hKey)
	{
		if (m_StorePassword.GetCheck())
		{
			val = 1;
			hRes = ::RegSetValueEx(hKey, L"StorePassword", NULL, REG_DWORD, (const BYTE*)&val, sizeof(val));
			if (hRes != ERROR_SUCCESS)
			{
				_com_error error(hRes);
				MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
			}
			else
				OnEnKillfocusEditPassword();//save the password
		}
		else
		{
			val = 0;
			hRes = ::RegSetValueEx(hKey, L"StorePassword", NULL, REG_DWORD, (const BYTE*)&val, sizeof(val));
			if (hRes != ERROR_SUCCESS)
			{
				_com_error error(hRes);
				MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
			}
			hRes = ::RegDeleteValue(hKey, L"Password");
			if (hRes != ERROR_SUCCESS)
			{
				_com_error error(hRes);
				MessageBox(error.ErrorMessage(), L"Delete the registry key error!", MB_ICONEXCLAMATION);
			}
		}
	}
}

void CDSHelperDlg::OnNMClickSyslinkOpenDsWeb(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString URL;
	m_CEditAddress.GetWindowText(URL);
	
	if (URL.Find(L"http") == -1)
		URL = L"http://" + URL + L"/index.cgi?launchApp=SYNO.SDS.DownloadStation.Application";
	else
		URL = URL + L"/index.cgi?launchApp=SYNO.SDS.DownloadStation.Application";
	
	ShellExecute(this->GetSafeHwnd(), L"open", URL, NULL, NULL, SW_SHOWNORMAL);
	
	*pResult = 0;
}

void CDSHelperDlg::OnEnKillfocusEditAddress()
{
	if (!m_DoSaveSettings)
		return; 

	LONG hRes = m_Registry.WriteSZ(&m_CEditAddress, m_Registry.GetMainHKey(), L"Address");
	if (hRes != ERROR_SUCCESS)
	{
		_com_error error(hRes);
		MessageBox(error.ErrorMessage(), L"Write the registry key error!", MB_ICONEXCLAMATION);
	}
}

void CDSHelperDlg::OnEnKillfocusEditUsername()
{
	if (!m_DoSaveSettings)
		return; 
	
	LONG hRes = m_Registry.WriteSZ(&m_CEditUsername, m_Registry.GetMainHKey(), L"Username");
	if (hRes != ERROR_SUCCESS)
	{
		_com_error error(hRes);
		MessageBox(error.ErrorMessage(), L"Write the registry key error!", MB_ICONEXCLAMATION);
	}
}

void CDSHelperDlg::ReadSettings()
{
	HKEY hKey(0);

	TCHAR szData[256]; ZeroMemory(szData, 1);
	DWORD dwKeyDataType;
	DWORD dwDataBufSize = 256;

	if (::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\DS Helper"), 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
	{
		LONG hRes = ::RegQueryValueEx(hKey, L"StorePassword", NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
		if (hRes == ERROR_SUCCESS)
		{
			switch (dwKeyDataType)
			{
			case REG_DWORD:
				if (szData[0] == 1)
					m_StorePassword.SetCheck(BST_CHECKED);

				dwDataBufSize = 256;
				dwKeyDataType = 0;
				ZeroMemory(szData, 1);

				break;
			}
		}

		hRes = ::RegQueryValueEx(hKey, L"Protocol", NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
		if (hRes == ERROR_SUCCESS)
		{
			switch (dwKeyDataType)
			{
			case REG_DWORD:
				if (szData[0] == 1)
				{
					m_ComboProtocol.SetCurSel(1);//https
					m_App->m_AppEnumProto = HTTPS;
				}
				else
				{
					m_ComboProtocol.SetCurSel(0);//http
					m_App->m_AppEnumProto = HTTP;
				}

				dwDataBufSize = 256;
				dwKeyDataType = 0;
				ZeroMemory(szData, 1);

				break;
			}
		}

		hRes = ::RegQueryValueEx(hKey, L"Address", NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
		if (hRes == ERROR_SUCCESS)
		{
			switch (dwKeyDataType)
			{
			case REG_SZ:

				m_CEditAddress.SetWindowText(szData);

				dwDataBufSize = 256;
				dwKeyDataType = 0;
				ZeroMemory(szData, 1);

				break;
			}
		}

		hRes = ::RegQueryValueEx(hKey, L"Port", NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
		if (hRes == ERROR_SUCCESS)
		{
			switch (dwKeyDataType)
			{
			case REG_SZ:

				m_CEditPort.SetWindowText(szData);

				dwDataBufSize = 256;
				dwKeyDataType = 0;
				ZeroMemory(szData, 1);

				break;
			}
		}

		hRes = ::RegQueryValueEx(hKey, L"Username", NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
		if (hRes == ERROR_SUCCESS)
		{
			switch (dwKeyDataType)
			{
			case REG_SZ:

				m_CEditUsername.SetWindowText(szData);
				dwDataBufSize = 256;
				dwKeyDataType = 0;
				ZeroMemory(szData, 1);

				break;
			}
		}

		hRes = ::RegQueryValueEx(hKey, L"Password", NULL, &dwKeyDataType, (LPBYTE)&szData, &dwDataBufSize);
		if (hRes == ERROR_SUCCESS)
		{
			switch (dwKeyDataType)
			{
			case REG_BINARY:

				CCrypto crypto;
				crypto.DeriveKey(m_App->m_pszAppName);

				CByteArray arBytes;
				CString strDecrypred;
			
				arBytes.SetSize(dwDataBufSize);
				CopyMemory(arBytes.GetData(), szData, dwDataBufSize);

				if (crypto.Decrypt(arBytes, strDecrypred) == true)
				{
					m_CEditPassword.SetWindowText(strDecrypred);
				}

				break;
			}
		}

		::RegCloseKey(hKey);
	}

	ReadPathesToCombo();//read pathes to combo
}

void CDSHelperDlg::OnEnKillfocusEditPassword()
{
	
	if (!m_DoSaveSettings)
		return;

	if (!m_StorePassword.GetCheck())
		return;

	HKEY hKey = m_Registry.GetMainHKey();
	CString val;
	LONG hRes(0);

	m_CEditPassword.Enable_WM_GetText();
	m_CEditPassword.GetWindowText(val);
	m_CEditPassword.Disable_WM_GetText();

	if (val.IsEmpty())
		return;
	
	CCrypto crypto;
	crypto.DeriveKey(m_App->m_pszAppName);
	CByteArray arBytes;//arr to store encr pass
	if (crypto.Encrypt(val, arBytes) == true)
	{
		if (hKey)
		{
			hRes = ::RegSetValueEx(hKey, L"Password", NULL, REG_BINARY, (const BYTE*)arBytes.GetData(), arBytes.GetSize());
			if (hRes != ERROR_SUCCESS)
			{
				_com_error error(hRes);
				MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
			}
		}
	}
}

void CDSHelperDlg::OnCbnKillfocusComboProtocol()
{
	HKEY hKey = m_Registry.GetMainHKey();
	LONG hRes(0);
	DWORD val(0);

	if (m_Registry.GetMainHKey())
	{
		if (m_App->m_AppEnumProto == HTTPS)
		{
			val = 1;
			hRes = ::RegSetValueEx(hKey, L"Protocol", NULL, REG_DWORD, (const BYTE*)&val, sizeof(val));
			if (hRes != ERROR_SUCCESS)
			{
				_com_error error(hRes);
				MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
			}
		}
		else
		{
			val = 0;
			hRes = ::RegSetValueEx(hKey, L"Protocol", NULL, REG_DWORD, (const BYTE*)&val, sizeof(val));
			if (hRes != ERROR_SUCCESS)
			{
				_com_error error(hRes);
				MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
			}
		}
	}
}

void CDSHelperDlg::OnEnKillfocusEditPort()
{
	if (!m_DoSaveSettings)
		return;
	LONG hRes = m_Registry.WriteSZ(&m_CEditPort, m_Registry.GetMainHKey(), L"Port");
	if (hRes != ERROR_SUCCESS)
	{
		_com_error error(hRes);
		MessageBox(error.ErrorMessage(), L"Write the registry key error!", MB_ICONEXCLAMATION);
	}
}

void CDSHelperDlg::OnBnClickedButtonEditPathes()
{
	CEditPathesDlg dlgEditPathes;
	dlgEditPathes.m_pParentDlg = this;
	if (dlgEditPathes.DoModal() == IDOK)
	{
		m_ComboPath.ResetContent();
		
		for (byte i = 0; i < dlgEditPathes.m_RetArr.GetCount(); i++)
		{
			m_ComboPath.AddString(dlgEditPathes.m_RetArr.GetAt(i));
		}

		byte nLast = m_ComboPath.GetCount() - 1;
		if (nLast >= 0)
			m_ComboPath.SetCurSel(nLast);
	}
	SavePathes();
}

bool CDSHelperDlg::SavePathes(bool Param)
{
	HKEY hKey(0);
	CString cKeyName = _T("");
	CString s;
	bool RetVal = Param;

	LONG hRes(0);

	if (::RegOpenKeyEx(HKEY_CURRENT_USER, _T("Software\\DS Helper\\Pathes"), 0, KEY_WRITE, &hKey) == ERROR_SUCCESS)
	{
		//delete existing
		for (byte i = 1; i < 254; i++)
		{
			cKeyName.Format(_T("P%u"), i);
			hRes = ::RegDeleteValue(hKey, cKeyName);
			if (hRes != ERROR_SUCCESS)
			{
				break;
			}
		}

		//create
		byte count = m_ComboPath.GetCount();
		if(count)
		{
			for (byte i = 1; i <= count; i++)
			{
				cKeyName.Format(_T("P%u"), i);

				m_ComboPath.GetLBText(i - 1, s);
				hRes = ::RegSetValueEx(hKey, cKeyName, NULL, REG_SZ, (const BYTE*)s.GetString(), s.GetLength() * sizeof(TCHAR));
				if (hRes != ERROR_SUCCESS)
				{
					_com_error error(hRes);
					MessageBox(error.ErrorMessage(), L"Create the registry key error!", MB_ICONEXCLAMATION);
				}

			}
		}
		
		::RegCloseKey(hKey);

		RetVal = true;
	}
	else
	{
		//not found, create
		::RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\DS Helper", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		::RegCloseKey(hKey);
		::RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\DS Helper\\Pathes", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
		::RegCloseKey(hKey);

		SavePathes(false);
	}

	return RetVal;
}

BOOL CDSHelperDlg::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	//CList Menu
	if (pMsg->message == WM_COMMAND)
	{
		switch (LOWORD(pMsg->wParam))
		{
			case ID_MENU_PAUSE:
			{
								  PauseTask();
								  break;
			}
			case ID_MENU_RESUME:
			{
								   ResumeTask();
								   break;
			}
			case ID_MENU_DELETE:
			{
								   DeleteTask();
								   break;
			}
		};
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CDSHelperDlg::OnBnClickedButtonOpenFile()
{
	CFileDialog OpenFileDialog(true);
	OpenFileDialog.m_pOFN->lpstrFilter = L"BitTorrent files (*.torrent)\0*.torrent\0All files (*.*)\0*.*";

	if (OpenFileDialog.DoModal() == IDOK)
	{
		m_CEditTask.SetWindowText(OpenFileDialog.GetPathName());
	}
}

void CDSHelperDlg::OnCbnCloseupComboProtocol()
{
	if (!m_DoSaveSettings)
		return;

	CString val;
	m_ComboProtocol.GetWindowText(val);
	
	if (val.IsEmpty())
		return;

	int val_len = val.GetLength() + 1;

	if (val == "HTTPS")
		m_App->m_AppEnumProto = HTTPS;
	else
		m_App->m_AppEnumProto = HTTP;
}

void CDSHelperDlg::OnBnClickedButtonAddTask()
{
	
	CString Task;
	m_CEditTask.GetWindowText(Task);
	if (Task.IsEmpty())
	{
		MessageBox(L"The task is empty!", L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	Json::Value root;//will contains the root value after parsing.
	
	// --- Auth
	m_CEditUsername.GetWindowText(m_App->m_AppUsername);
	m_CEditAddress.GetWindowText(m_App->m_AppAddress);
	m_CEditPort.GetWindowText(m_App->m_AppPort);
	m_CEditPassword.Enable_WM_GetText();
	m_CEditPassword.GetWindowText(m_App->m_AppPassword);
	m_CEditPassword.Disable_WM_GetText();

	if (!(m_App->AuthOnSyno(&(CString(L"DownloadStation")))))
		return;

	// --- create task
	CString Destination;
	
	m_ComboPath.GetWindowText(Destination);
	
	if (Destination.Left(1) == L"/")
	{
		Destination = Destination.Right(Destination.GetLength() - 1);
	}

	CString URL;
	HTTPResponse Response;

	if ((Task.Find(L"magnet:?") == -1)
		&& (Task.Find(L"ftp://") == -1)
		&& (Task.Find(L"ftps://") == -1)
		&& (Task.Find(L"sftp://") == -1)
		&& (Task.Find(L"http://") == -1)
		&& (Task.Find(L"https://") == -1)
		&& (Task.Find(L"thunder://") == -1)
		&& (Task.Find(L"flashget://") == -1)
		&& (Task.Find(L"qqdl://") == -1))
	{//file (*.torrent may be)
		
		URL = L"/webapi/DownloadStation/task.cgi";

		Response = m_App->m_pAppSynoConnect->PostFile(m_App->m_AppEnumProto, &Task, &(m_App->m_AppAddress), &(m_App->m_AppPort), &Destination, &(m_App->m_AppSID));
		if (Response.code != 200)
		{
			if(!Response.strResponse.IsEmpty())
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			return;
		}
	}
	else
	{//magnet, http, ftp

		if (m_App->m_AppEnumProto == HTTPS)
		{
			URL = L"/webapi/DownloadStation/task.cgi?api=SYNO.DownloadStation.Task&version=1&method=create&destination=" + Destination + L"&sid=" + m_App->m_AppSID + L"&uri=" + Task;
			Response = m_App->m_pAppSynoConnect->GetURL(m_App->m_AppEnumProto, &(m_App->m_AppAddress), &(m_App->m_AppPort), &URL, NULL);
		}
		else
		{
			URL = CString(L"http://") + m_App->m_AppAddress + L":" + m_App->m_AppPort + +L"/webapi/DownloadStation/task.cgi?api=SYNO.DownloadStation.Task&version=1&method=create&destination=" + Destination + L"&sid=" + m_App->m_AppSID + L"&uri=" + Task;
			Response = m_App->m_pAppSynoConnect->GetURL(m_App->m_AppEnumProto, &URL);
		}
		
		if (Response.code != 200)
		{
			if (!Response.strResponse.IsEmpty())
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			return;
		}
	}

	bool parsingSuccessful = m_App->m_pJSONreader->parse(m_App->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", m_App->m_pJSONreader->getFormattedErrorMessages());
		MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, m_App->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
	}
	else
		MessageBox(L"The task was created successfully.", L"Success", MB_ICONINFORMATION);
	
	return;
}

void CAboutDlg::OnNMClickSyslinkLicense(NMHDR *pNMHDR, LRESULT *pResult)
{
	CString Path;
	::GetModuleFileName(NULL, CStrBuf(Path, MAX_PATH), MAX_PATH);
	Path.Replace(L"DS Helper.exe", L"LICENSE.txt");
	
	ShellExecute(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), _T("open"), Path, _T(""), _T(""), SW_SHOWNORMAL);

	*pResult = 0;
}

void CAboutDlg::OnNMClickSyslinkHomepage(NMHDR *pNMHDR, LRESULT *pResult)
{
	ShellExecute(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), _T("open"), _T("https://github.com/xaozai/DS-Helper/"), _T(""), _T(""), SW_SHOWNORMAL);

	*pResult = 0;
}

void CDSHelperDlg::OnBnClickedCheckShowActiveTasks()
{
	if (m_CheckBoxShowActiveTasks.GetCheck())
	{
		m_CheckBoxShowActiveTasks.EnableWindow(false);
		if (RefreshTaskThreadRunning || RefreshThread)
		{
			::WaitForSingleObject(RefreshThread->m_hThread, INFINITE);//wait for thread ends
			delete RefreshThread; RefreshThread = NULL;
		}
		if (!m_ThreadSynoConnect)
		{
			m_ThreadSynoConnect = new WebClient;
		}
		m_CListActiveTasks.EnableWindow(true);
		RefreshThread = AfxBeginThread(RefreshActiveTasksLoop, (LPVOID)this, 0, CREATE_SUSPENDED);
		RefreshThread->m_bAutoDelete = false;
		RefreshThread->ResumeThread();
		m_CheckBoxShowActiveTasks.EnableWindow(true);
		ShowCList();
	}
	else
	{
		m_CheckBoxShowActiveTasks.EnableWindow(false);
		RefreshTaskThreadRunning = false;

		::WaitForSingleObject(RefreshThread->m_hThread, INFINITE);//wait for thread ends
		delete RefreshThread; RefreshThread = NULL;
		if (m_ThreadSynoConnect)
		{
			delete m_ThreadSynoConnect; m_ThreadSynoConnect = NULL;
		}
		m_CListActiveTasks.DeleteAllItems();
		m_CListActiveTasks.EnableWindow(false);
		m_CheckBoxShowActiveTasks.EnableWindow(true);
		HideCList();
	}
}

UINT __cdecl CDSHelperDlg::RefreshActiveTasksLoop(LPVOID pParam)
{
	
	CDSHelperDlg* Dlg = (CDSHelperDlg*)pParam;

	Dlg->RefreshTaskThreadRunning = true;
	
	bool NeedAuth = true;

	while (Dlg->RefreshTaskThreadRunning)
	{
		if(Dlg->RefreshActiveTasks(NeedAuth) != -1)
			NeedAuth = false;
		
		if (!Dlg->RefreshTaskThreadRunning)
			break;
		
		UINT i = 0;
		while (i < 50 && Dlg->RefreshTaskThreadRunning)//~5 sec
		{
			
			if (!Dlg->RefreshTaskThreadRunning)
				break;

			Sleep(100); i++;
		}
				
	}

	return 0;
}

void CDSHelperDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	RefreshTaskThreadRunning = false;

	if (RefreshThread)
	{
		::WaitForSingleObject(RefreshThread->m_hThread, INFINITE);//wait for thread ends
		
		delete RefreshThread; RefreshThread = NULL;
	}
	
	if (m_ThreadSynoConnect)
	{
		delete m_ThreadSynoConnect; m_ThreadSynoConnect = NULL;
	}
}

void CDSHelperDlg::OnClose()
{
	//theApp.SynoLogout(L"DownloadStation");
	//theApp.SynoLogout(L"FileStation");
	CDialogEx::OnClose();
}

int CDSHelperDlg::RefreshActiveTasks(bool NeedAuth)
{

	CString StatusQuery(L"The query is executed...");

	LVITEM item;
	item.state = 0;
	item.stateMask = 0;
	item.iImage = 0;
	item.lParam = 0;

	if (!m_CListActiveTasks.GetItemCount())
	{
		item.mask = LVIF_TEXT;
		item.iItem = 0;
		item.iSubItem = 0;
		item.pszText = (LPWSTR)StatusQuery.GetString();

		m_CListActiveTasks.InsertItem(&item);

		item.iSubItem = 1;

		m_CListActiveTasks.SetItem(&item);
	}
		

	Json::Value root;//will contains the root value after parsing.

	if (NeedAuth)
	{
		// --- Auth
		m_CEditUsername.GetWindowText(m_App->m_AppUsername);
		m_CEditAddress.GetWindowText(m_App->m_AppAddress);
		m_CEditPort.GetWindowText(m_App->m_AppPort);
		m_CEditPassword.Enable_WM_GetText();
		m_CEditPassword.GetWindowText(m_App->m_AppPassword);
		m_CEditPassword.Disable_WM_GetText();

		CString strAuthRet;

		if (!(m_App->AuthOnSyno(&(CString(L"DownloadStation")), &strAuthRet)))
		{
			if (RefreshTaskThreadRunning)
			{
				m_CListActiveTasks.DeleteAllItems();
				
				item.mask = LVIF_TEXT;
				item.iItem = 0;
				item.iSubItem = 0;
				item.pszText = (LPWSTR)strAuthRet.GetString();

				m_CListActiveTasks.InsertItem(&item);

				item.iSubItem = 1;

				m_CListActiveTasks.SetItem(&item);

			}
			return -1;
		}
	}
	
	CString URL;
	HTTPResponse Response;

	URL = (m_App->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + m_App->m_AppAddress + L":" + m_App->m_AppPort + L"/webapi/DownloadStation/task.cgi?api=SYNO.DownloadStation.Task&version=1&method=list&additional=transfer&sid=" + m_App->m_AppSID;
	Response = m_ThreadSynoConnect->GetURL(m_App->m_AppEnumProto, &URL, true);

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
		{
			if (RefreshTaskThreadRunning)
			{
				m_CListActiveTasks.DeleteAllItems();
				
				item.mask = LVIF_TEXT;
				item.iItem = 0;
				item.iSubItem = 0;
				item.pszText = (LPWSTR)Response.strResponse.GetString();

				m_CListActiveTasks.InsertItem(&item);

				item.iSubItem = 1;

				m_CListActiveTasks.SetItem(&item);
			}
		}
		return 0;
	}

	bool parsingSuccessful = m_App->m_pJSONreader->parse(m_App->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		if (RefreshTaskThreadRunning)
		{
			m_CListActiveTasks.DeleteAllItems();
			
			item.mask = LVIF_TEXT;
			item.iItem = 0;
			item.iSubItem = 0;
			item.pszText = (LPWSTR)Response.strResponse.GetString();

			m_CListActiveTasks.InsertItem(&item);

			item.iSubItem = 1;

			m_CListActiveTasks.SetItem(&item);
		}
		return 0;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, m_App->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			if (RefreshTaskThreadRunning)
			{
				m_CListActiveTasks.DeleteAllItems();
				
				item.mask = LVIF_TEXT;
				item.iItem = 0;
				item.iSubItem = 0;
				item.pszText = (LPWSTR)Response.strResponse.GetString();

				m_CListActiveTasks.InsertItem(&item);

				item.iSubItem = 1;

				m_CListActiveTasks.SetItem(&item);
			}
			
		}
	}
	else
	{
		UINT LastInserted = 0;
		double SizeDownloaded = 0;
		double FullSize = 0;

		bool ThereIsInserted = false;

		if (!root.isMember("data"))
		{
			if (RefreshTaskThreadRunning)
			{
				m_CListActiveTasks.DeleteAllItems();
			}
			return 0;
		}
		else
			root = root.get("data", NULL);

		if (!root.isMember("tasks"))
		{
			if (RefreshTaskThreadRunning)
			{
				m_CListActiveTasks.DeleteAllItems();
			}
			return 0;
		}
		else
			root = root.get("tasks", NULL);
				
		CArray<CString, CString> NeedInListArray;
		CString title;
		CString id;

		for (Json::ArrayIndex index = 0; index < root.size(); index++)
		{

			bool NeedInList = false;
			byte ImageIndex(0);
			
			CString strStatus(root[index]["status"].asCString());
			
			LVFINDINFO info;

			int ListItemIndex(-1);
			
			if (strStatus == L"downloading" || strStatus == L"finishing")
			{
				NeedInList = true;
				ImageIndex = 1;
			}
			else
			{
				if (strStatus == L"paused")
				{
					NeedInList = true;
					ImageIndex = 2;
				}
				else
				{
					if (strStatus == L"finished")
					{
						NeedInList = true;
						ImageIndex = 3;
					}
					else
					{
						if (strStatus == L"hash_checking")
						{
							NeedInList = true;
							ImageIndex = 4;
						}
						else
						if (strStatus == L"waiting")
						{
							NeedInList = true;
							ImageIndex = 5;
						}
					}
				}
			}

			if (NeedInList)
			{
				if (RefreshTaskThreadRunning)
				{
					info.flags = LVFI_STRING;
					info.psz = StatusQuery.GetString();
					ListItemIndex = m_CListActiveTasks.FindItem(&info);
					if (ListItemIndex != -1)
						m_CListActiveTasks.DeleteItem(ListItemIndex);
					ListItemIndex = -1;
				}

				ThereIsInserted = true;

				if (root[index].isMember("id"))
				{
					id = root[index]["id"].asCString();

					NeedInListArray.Add(id);

					if (RefreshTaskThreadRunning)
					{
						
						info.flags = LVFI_STRING;
						info.psz = id.GetString();
						ListItemIndex = m_CListActiveTasks.FindItem(&info);


						if (ListItemIndex == -1)
						{
							item.mask =  LVIF_TEXT;
							item.iItem = LastInserted;
							item.iSubItem = 0;
							item.pszText = (LPWSTR)info.psz;

							m_CListActiveTasks.InsertItem(&item);

							if (root[index].isMember("title"))
							{
								title = root[index]["title"].asCString();
								
								item.iItem = LastInserted;
								item.mask = LVIF_IMAGE | LVIF_TEXT;
								item.pszText = (LPWSTR)title.GetString();
								item.iSubItem = 1;
								item.iImage = ImageIndex;
								m_CListActiveTasks.SetItem(&item);
							}

							ListItemIndex = LastInserted;

							LastInserted++;
						}
						else
						{
							item.iItem = ListItemIndex;
							item.mask = LVIF_IMAGE;
							item.iSubItem = 1;
							item.iImage = ImageIndex;
							m_CListActiveTasks.SetItem(&item);
						}
						
					}
				}//root[index].isMember("id")
				
				if (root[index].isMember("size"))
				{
					FullSize = (double)(root[index].get("size", 0).asDouble());
				}
				
				CString percent;
				
				if (ImageIndex == 4)
				{
					percent.SetString(L"Checking...");
				}
				else
				{
					if (FullSize)
					{
						SizeDownloaded = 0;

						if (root[index].isMember("additional"))
						{
							if (root[index]["additional"].isMember("transfer"))
							{
								SizeDownloaded = (double)(root[index]["additional"]["transfer"]["size_downloaded"].asDouble());

								if (SizeDownloaded == FullSize)
								{
									item.iItem = ListItemIndex;
									item.mask = LVIF_IMAGE;
									item.iSubItem = 1;
									item.iImage = 3;
									m_CListActiveTasks.SetItem(&item);
								}
							}
						}

						percent.Format(L"%.2f", (100.0 * (SizeDownloaded / FullSize)));
						
					}
				}

				if (RefreshTaskThreadRunning)
				{
					m_CListActiveTasks.SetItemText(ListItemIndex, 2, percent);
				}

			}
			else//no need in list
			{
				if (RefreshTaskThreadRunning)
				{
					if (root[index].isMember("id"))
					{
						id = root[index]["id"].asCString();
						info.flags = LVFI_STRING;
						info.psz = id.GetString();
						ListItemIndex = m_CListActiveTasks.FindItem(&info);

						if (ListItemIndex != -1)
							m_CListActiveTasks.DeleteItem(ListItemIndex);
					}
				}
			}

		}//for
		
		if (!ThereIsInserted)
		{
			if (RefreshTaskThreadRunning)
			{
				m_CListActiveTasks.DeleteAllItems();
			}
		}
		else
		{
			if (RefreshTaskThreadRunning)
			{
				for (int _i = 0; _i < m_CListActiveTasks.GetItemCount(); _i++)
				{

					bool InArray = false;
					if (RefreshTaskThreadRunning)
					{
						id = m_CListActiveTasks.GetItemText(_i, 0);


						for (int _j = 0; _j < NeedInListArray.GetCount(); _j++)
						{
							if (NeedInListArray.GetAt(_j) == id)
							{
								InArray = true;
								break;
							}

						}
					}

					if (!InArray)
					{
						if (RefreshTaskThreadRunning)
						{
							m_CListActiveTasks.DeleteItem(_i);
						}
					}

				}
			}
		}
	
	}//root.get("success", false).asBool()

	return 0;
}

void CDSHelperDlg::DeleteTask()
{
	int SelectedIndex = m_CListActiveTasks.GetSelectionMark();
	if (SelectedIndex == -1)
		return;

	// --- Auth
	m_CEditUsername.GetWindowText(m_App->m_AppUsername);
	m_CEditAddress.GetWindowText(m_App->m_AppAddress);
	m_CEditPort.GetWindowText(m_App->m_AppPort);
	m_CEditPassword.Enable_WM_GetText();
	m_CEditPassword.GetWindowText(m_App->m_AppPassword);
	m_CEditPassword.Disable_WM_GetText();

	if (!(m_App->AuthOnSyno(&(CString(L"DownloadStation")))))
		return;

	Json::Value root;//will contains the root value after parsing.

	CString URL;
	HTTPResponse Response;

	LVITEM item;
	item.state = 0;
	item.stateMask = 0;
	item.iImage = 0;
	item.lParam = 0;

	CString id = m_CListActiveTasks.GetItemText(SelectedIndex, 0);

	URL = (m_App->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + m_App->m_AppAddress + L":" + m_App->m_AppPort + L"/webapi/DownloadStation/task.cgi?api=SYNO.DownloadStation.Task&version=1&method=delete&id=" + id + "&sid=" + m_App->m_AppSID;
	Response = m_ThreadSynoConnect->GetURL(m_App->m_AppEnumProto, &URL, true);

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);

		return;
	}

	bool parsingSuccessful = m_App->m_pJSONreader->parse(m_App->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", m_App->m_pJSONreader->getFormattedErrorMessages());
		MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, m_App->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
	}
	else
	{

		if (root.isMember("data"))
		{
			int RetCode = root["data"][0].get("error", -1).asInt();
			if (RetCode == 0)
			{
				item.mask = LVIF_IMAGE;
				item.iImage = 1;
				item.iSubItem = 1;
				m_CListActiveTasks.SetItem(&item);
			}
			else
			{
				Response.strResponse.Format(L"The server has returned the code: %u", RetCode);
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			}
		}
	}
}

void CDSHelperDlg::PauseTask()
{
	int SelectedIndex = m_CListActiveTasks.GetSelectionMark();
	if (SelectedIndex == -1)
		return;

	// --- Auth
	m_CEditUsername.GetWindowText(m_App->m_AppUsername);
	m_CEditAddress.GetWindowText(m_App->m_AppAddress);
	m_CEditPort.GetWindowText(m_App->m_AppPort);
	m_CEditPassword.Enable_WM_GetText();
	m_CEditPassword.GetWindowText(m_App->m_AppPassword);
	m_CEditPassword.Disable_WM_GetText();

	if (!(m_App->AuthOnSyno(&(CString(L"DownloadStation")))))
		return;

	Json::Value root;//will contains the root value after parsing.

	CString URL;
	HTTPResponse Response;

	LVITEM item;
	item.state = 0;
	item.stateMask = 0;
	item.iImage = 0;
	item.lParam = 0;

	CString id = m_CListActiveTasks.GetItemText(SelectedIndex, 0);

	URL = (m_App->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + m_App->m_AppAddress + L":" + m_App->m_AppPort + L"/webapi/DownloadStation/task.cgi?api=SYNO.DownloadStation.Task&version=1&method=pause&id=" + id + "&sid=" + m_App->m_AppSID;
	Response = m_ThreadSynoConnect->GetURL(m_App->m_AppEnumProto, &URL, true);

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);

		return;
	}

	bool parsingSuccessful = m_App->m_pJSONreader->parse(m_App->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", m_App->m_pJSONreader->getFormattedErrorMessages());
		MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, m_App->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
	}
	else
	{

		if (root.isMember("data"))
		{
			int RetCode = root["data"][0].get("error", -1).asInt();
			if (RetCode == 0)
			{
				item.mask = LVIF_IMAGE;
				item.iImage = 2;
				item.iSubItem = 1;
				m_CListActiveTasks.SetItem(&item);
			}
			else
			{
				Response.strResponse.Format(L"The server has returned the code: %u", RetCode);
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			}
		}
	}
}

void CDSHelperDlg::ResumeTask()
{
	int SelectedIndex = m_CListActiveTasks.GetSelectionMark();
	if (SelectedIndex == -1)
		return;
	
	// --- Auth
	m_CEditUsername.GetWindowText(m_App->m_AppUsername);
	m_CEditAddress.GetWindowText(m_App->m_AppAddress);
	m_CEditPort.GetWindowText(m_App->m_AppPort);
	m_CEditPassword.Enable_WM_GetText();
	m_CEditPassword.GetWindowText(m_App->m_AppPassword);
	m_CEditPassword.Disable_WM_GetText();

	if (!(m_App->AuthOnSyno(&(CString(L"DownloadStation")))))
		return;
	
	Json::Value root;//will contains the root value after parsing.

	CString URL;
	HTTPResponse Response;

	LVITEM item;
	item.state = 0;
	item.stateMask = 0;
	item.iImage = 0;
	item.lParam = 0;

	CString id = m_CListActiveTasks.GetItemText(SelectedIndex, 0);

	URL = (m_App->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + m_App->m_AppAddress + L":" + m_App->m_AppPort + L"/webapi/DownloadStation/task.cgi?api=SYNO.DownloadStation.Task&version=1&method=resume&id=" + id + "&sid=" + m_App->m_AppSID;
	Response = m_ThreadSynoConnect->GetURL(m_App->m_AppEnumProto, &URL, true);

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		
		return;
	}

	bool parsingSuccessful = m_App->m_pJSONreader->parse(m_App->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", m_App->m_pJSONreader->getFormattedErrorMessages());
		MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, m_App->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
	}
	else
	{

		if (root.isMember("data"))
		{
			int RetCode = root["data"][0].get("error", -1).asInt();
			if (RetCode == 0)
			{
				item.mask = LVIF_IMAGE;
				item.iImage = 1;
				item.iSubItem = 1;
				m_CListActiveTasks.SetItem(&item);
			}
			else
			{
				Response.strResponse.Format(L"The server has returned the code: %u", RetCode);
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			}
		}
	}
}