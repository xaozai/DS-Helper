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
#include "DS Helper.h"
#include "DS SynoFSDlg.h"
#include "afxdialogex.h"
#include "InputBox.h"

IMPLEMENT_DYNAMIC(CDSSynoFSDlg, CDialogEx)

CDSSynoFSDlg::CDSSynoFSDlg(CString* RetVal, CEditPathesDlg* pParent) : CDialogEx(CDSSynoFSDlg::IDD, pParent)
{
	m_pParent = pParent;
	m_RetVal = RetVal;
}

void CDSSynoFSDlg::FreeTree(HTREEITEM hTreeItem)
{
	if (hTreeItem)
	{
		CString* ItemData = (CString*)m_Tree.GetItemData(hTreeItem);
		if (ItemData)
		{
			delete ItemData;
		}

		if (m_Tree.ItemHasChildren(hTreeItem))
		{
			for (HTREEITEM hSubItem = m_Tree.GetChildItem(hTreeItem); hSubItem != 0; hSubItem = m_Tree.GetNextItem(hSubItem, TVGN_NEXT))
			{
				FreeTree(hSubItem);
			}
		}
	}
}

CDSSynoFSDlg::~CDSSynoFSDlg()
{
	
}

void CDSSynoFSDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	HTREEITEM hTreeItem = m_Tree.GetRootItem();
	while (hTreeItem)
	{
		FreeTree(hTreeItem);
		hTreeItem = m_Tree.GetNextSiblingItem(hTreeItem);
	}
}

void CDSSynoFSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_TREE_SYNO, m_Tree);
}

BEGIN_MESSAGE_MAP(CDSSynoFSDlg, CDialogEx)
	
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE_SYNO, &CDSSynoFSDlg::OnTvnItemexpandingTreeSyno)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CREATE_FOLDER_ON_SYNO, &CDSSynoFSDlg::OnBnClickedButtonCreateFolderOnSyno)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CURRENT_TO_PREDEF, &CDSSynoFSDlg::OnBnClickedButtonAddCurrentToPredef)
END_MESSAGE_MAP()

BOOL CDSSynoFSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_TreeImages.Create(16, 16, ILC_COLOR8 | ILC_MASK, 2, 1);
	m_TreeImages.Add(AfxGetApp()->LoadIcon(IDI_ICON_FOLDER));
	m_Tree.SetImageList(&m_TreeImages, TVSIL_NORMAL);

	ShowSynoFSTree();

	return TRUE; 
}

void CDSSynoFSDlg::ShowSynoFSTree()
{
	Json::Value root;//will contains the root value after parsing.
	
	// --- Auth
	CDSHelperApp* DSHelperApp = (CDSHelperApp *)AfxGetApp();

	m_pParent->m_pParentDlg->m_CEditAddress.GetWindowText(DSHelperApp->m_AppAddress);
	m_pParent->m_pParentDlg->m_CEditPort.GetWindowText(DSHelperApp->m_AppPort);
	m_pParent->m_pParentDlg->m_CEditUsername.GetWindowText(DSHelperApp->m_AppUsername);
	m_pParent->m_pParentDlg->m_CEditPassword.GetWindowText(DSHelperApp->m_AppPassword);

	
	if (!(DSHelperApp->AuthOnSyno(&(CString(L"FileStation")))))
		return;


	// --- Get Folders
	CString URL;
	HTTPResponse Response;

	//http://myds.com:port/webapi/FileStation/file_share.cgi?api=SYNO.FileStation.List&version=1&method=list_share
	//403 Forbidden issue: forum.synology.com/enu/viewtopic.php?t=109631
  
	URL = (DSHelperApp->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + DSHelperApp->m_AppAddress + L":" + DSHelperApp->m_AppPort + L"/webapi/entry.cgi?api=SYNO.FileStation.List&version=1&method=list_share&sid=" + DSHelperApp->m_AppSID;
	Response = DSHelperApp->m_pAppSynoConnect->GetURL(DSHelperApp->m_AppEnumProto, &URL, true);

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	bool parsingSuccessful = DSHelperApp->m_pJSONreader->parse(DSHelperApp->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", DSHelperApp->m_pJSONreader->getFormattedErrorMessages());
		MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, DSHelperApp->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
	}
	else
	{
		HTREEITEM Item;
		
		if (root.isMember("data"))
		{
			root = root.get("data", NULL);
			if (root.isMember("shares"))
			{
				root = root.get("shares", NULL);
				for (Json::ArrayIndex index = 0; index < root.size(); index++)
				{
					Item = m_Tree.InsertItem(CString(root[index]["name"].asCString()), 0, 0, TVI_ROOT, TVI_LAST);
					
					CString* ItemData = new CString;
					ItemData->SetString(CString(root[index]["path"].asCString()));
					m_Tree.SetItemData(Item, (DWORD_PTR)ItemData);

					m_Tree.InsertItem(L"0", Item, Item);
				}
			}
		}
	}

}

void CDSSynoFSDlg::OnTvnItemexpandingTreeSyno(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	if (pNMTreeView->action != 2)//expanded 2; collapsed 1
	{
		*pResult = 0; return;
	}

	HTREEITEM hTreeItem = pNMTreeView->itemNew.hItem;
	if (hTreeItem == NULL)
	{
		*pResult = 0; return;
	}

	if (m_Tree.ItemHasChildren(hTreeItem))
	{
		HTREEITEM hTreeItemC = m_Tree.GetChildItem(hTreeItem);
		if(m_Tree.GetItemData(hTreeItemC) == NULL)
			m_Tree.DeleteItem(hTreeItemC);
		else
		{
			*pResult = 0; return;
		}
			

		// --- Get Folders
		HTTPResponse Response;
		CDSHelperApp* DSHelperApp = (CDSHelperApp *)AfxGetApp();

		CString URL = (DSHelperApp->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + DSHelperApp->m_AppAddress + L":" + DSHelperApp->m_AppPort \
			+ L"/webapi/entry.cgi?api=SYNO.FileStation.List&version=2&method=list&folder_path=%22" \
			+ DSHelperApp->m_pAppSynoConnect->Urlencode((CString*)m_Tree.GetItemData(hTreeItem)).GetString() \
			+ L"%22&filetype=dir&sid=" + DSHelperApp->m_AppSID;
		
		Response = DSHelperApp->m_pAppSynoConnect->GetURL(DSHelperApp->m_AppEnumProto, &URL, true);

		if (Response.code != 200)
		{
			if (!Response.strResponse.IsEmpty())
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			*pResult = 0; return;
		}

		Json::Value root;//will contains the root value after parsing.
		
		bool parsingSuccessful = DSHelperApp->m_pJSONreader->parse(DSHelperApp->CString2Std(Response.strResponse), root);
		if (!parsingSuccessful)
		{
			Response.strResponse.Format(L"Failed to parse the string:\n%s", DSHelperApp->m_pJSONreader->getFormattedErrorMessages());
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			*pResult = 0; return;
		}

		if (root.get("success", false).asBool() == false)
		{
			root = root.get("error", NULL);
			if (root != NULL)
			{
				DWORD code = root.get("code", 0).asUInt();
				Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, DSHelperApp->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
				MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
			}
		}
		else
		{
			HTREEITEM Item;

			if (root.isMember("data"))
			{
				root = root.get("data", NULL);
				if (root.isMember("files"))
				{
					root = root.get("files", NULL);
					for (Json::ArrayIndex index = 0; index < root.size(); index++)
					{
						Item = m_Tree.InsertItem(CString(root[index]["name"].asCString()), 0, 0, hTreeItem, hTreeItem);

						CString* ItemData = new CString;
						ItemData->SetString(CString(root[index]["path"].asCString()));
						m_Tree.SetItemData(Item, (DWORD_PTR)ItemData);

						m_Tree.InsertItem(L"0", Item, Item);
					}
				}
			}
		}
		
	}
	else
	{
		*pResult = 0; return;
	}

	*pResult = 0;
}

void CDSSynoFSDlg::OnBnClickedButtonCreateFolderOnSyno()
{
	HTREEITEM hTreeItem = m_Tree.GetSelectedItem();
	if (!hTreeItem)
	{
		return;
	}
	
	CString NewFolderName;
	
	CInputBox dialog(&CString(L"A new folder name:"), &NewFolderName, this);

	if (dialog.DoModal() != IDOK || NewFolderName.IsEmpty())
	{
		return;
	}

	CDSHelperApp* DSHelperApp = (CDSHelperApp *)AfxGetApp();

	HTTPResponse Response;

	CString URL = (DSHelperApp->m_AppEnumProto == HTTPS ? L"https://" : L"http://") + DSHelperApp->m_AppAddress + L":" + DSHelperApp->m_AppPort \
		+ L"/webapi/entry.cgi?api=SYNO.FileStation.CreateFolder&version=2&method=create&folder_path=%22" \
		+ DSHelperApp->m_pAppSynoConnect->Urlencode((CString*)m_Tree.GetItemData(hTreeItem)).GetString() \
		+ L"%22&name=%5B%22" + DSHelperApp->m_pAppSynoConnect->Urlencode(&NewFolderName).GetString() + "%22%5D&sid=" + DSHelperApp->m_AppSID;

	Response = DSHelperApp->m_pAppSynoConnect->GetURL(DSHelperApp->m_AppEnumProto, &URL, true);

	if (Response.code != 200)
	{
		if (!Response.strResponse.IsEmpty())
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	Json::Value root;//will contains the root value after parsing.
	
	bool parsingSuccessful = DSHelperApp->m_pJSONreader->parse(DSHelperApp->CString2Std(Response.strResponse), root);
	if (!parsingSuccessful)
	{
		Response.strResponse.Format(L"Failed to parse the string:\n%s", DSHelperApp->m_pJSONreader->getFormattedErrorMessages());
		MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		return;
	}

	if (root.get("success", false).asBool() == false)
	{
		root = root.get("error", NULL);
		if (root != NULL)
		{
			DWORD code = root.get("code", 0).asUInt();
			Response.strResponse.Format(L"The server has returned the code: %u (%s)", code, DSHelperApp->m_pAppSynoConnect->GetSynoDSCodeDescription(code));
			MessageBox(Response.strResponse, L"DS Helper - Error", MB_ICONEXCLAMATION);
		}
	}
	else
	{
		HTREEITEM Item;

		if (root.isMember("data"))
		{
			root = root.get("data", NULL);
			if (root.isMember("folders"))
			{
				root = root.get("folders", NULL);
				for (Json::ArrayIndex index = 0; index < root.size(); index++)
				{
					Item = m_Tree.InsertItem(CString(root[index]["name"].asCString()), hTreeItem, TVI_SORT);

					CString* ItemData = new CString;
					ItemData->SetString(CString(root[index]["path"].asCString()));
					m_Tree.SetItemData(Item, (DWORD_PTR)ItemData);

					m_Tree.Invalidate();
					m_Tree.UpdateWindow();
				}
			}
		}
	}
}

void CDSSynoFSDlg::OnBnClickedButtonAddCurrentToPredef()
{
	HTREEITEM hTreeItem = m_Tree.GetSelectedItem();
	if (!hTreeItem)
	{
		return;
	}

	*m_RetVal = CString(((CString*)m_Tree.GetItemData(hTreeItem))->GetString());

	::PostMessage(this->GetSafeHwnd(), WM_COMMAND, IDOK, 0);
	
}