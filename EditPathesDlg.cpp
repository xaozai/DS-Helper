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
#include "EditPathesDlg.h"
#include "InputBox.h"
#include "DS SynoFSDlg.h"

CEditPathesDlg::CEditPathesDlg() : CDialogEx(CEditPathesDlg::IDD)
{

}

void CEditPathesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATHES, m_ListPathes);
	DDX_Control(pDX, IDC_BUTTON_ADD_PATH, m_ButtonAddPath);
	DDX_Control(pDX, IDC_BUTTON_REMOVE_PATH, m_ButtonRemovePath);
	DDX_Control(pDX, IDC_BUTTON_MOVE_UP, m_ButtonMoveUp);
	DDX_Control(pDX, IDC_BUTTON_MOVE_DOWN, m_ButtonMoveDown);
	DDX_Control(pDX, IDOK, m_ButtonOK);
}

BEGIN_MESSAGE_MAP(CEditPathesDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_PATH, &CEditPathesDlg::OnBnClickedButtonAddPath)
	ON_BN_CLICKED(IDC_BUTTON_REMOVE_PATH, &CEditPathesDlg::OnBnClickedButtonRemovePath)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_UP, &CEditPathesDlg::OnBnClickedButtonMoveUp)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_DOWN, &CEditPathesDlg::OnBnClickedButtonMoveDown)
	ON_BN_CLICKED(IDOK, &CEditPathesDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_VIEW_EDIT_ON_SYNO, &CEditPathesDlg::OnBnClickedButtonViewEditOnSyno)
END_MESSAGE_MAP()

BOOL CEditPathesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//Create the ToolTip control
	if (!m_ToolTip.Create(this))
	{
		TRACE0("Unable to create the ToolTip!");
	}
	else
	{
		m_ToolTip.AddTool(&m_ButtonAddPath, _T("Add a path"));
		m_ToolTip.AddTool(&m_ButtonRemovePath, _T("Remove a path"));
		m_ToolTip.AddTool(&m_ButtonMoveUp, _T("Move Up"));
		m_ToolTip.AddTool(&m_ButtonMoveDown, _T("Move Down"));
		m_ToolTip.AddTool(&m_ButtonOK, _T("Save"));

		m_ToolTip.Activate(TRUE);
	}

	m_ButtonMoveUp.SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_UP), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));
	m_ButtonMoveDown.SetIcon((HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_DOWN), IMAGE_ICON, 0, 0, LR_DEFAULTCOLOR));

	for (byte i = 0; i < m_pParentDlg->m_ComboPath.GetCount(); i++)
	{
		m_pParentDlg->m_ComboPath.GetLBText(i, str_Tmp);
		m_ListPathes.AddString(str_Tmp);
	}

	return TRUE;
}

void CEditPathesDlg::OnBnClickedButtonAddPath()
{
	CInputBox dialog(&CString("Type a path:"), &str_Tmp, this);
	
	if (dialog.DoModal() == IDOK)
	{
		m_ListPathes.AddString(str_Tmp);
		m_ListPathes.SetCurSel(m_ListPathes.GetCount() - 1);
	}
}

void CEditPathesDlg::OnBnClickedButtonRemovePath()
{
	byte ind = m_ListPathes.GetCurSel();
	m_ListPathes.DeleteString(ind);
	byte count = m_ListPathes.GetCount();
	if (count == 1)
		m_ListPathes.SetCurSel(0);
	else if((count - 1)  < ind)
		m_ListPathes.SetCurSel(ind - 1);
	else 
		m_ListPathes.SetCurSel(ind);

}

void CEditPathesDlg::OnBnClickedButtonMoveUp()
{
	byte ind = m_ListPathes.GetCurSel();
	if (ind)
	{
		m_ListPathes.GetText(ind, str_Tmp);
		m_ListPathes.DeleteString(ind);
		m_ListPathes.InsertString(ind - 1, str_Tmp);
		m_ListPathes.SetCurSel(ind - 1);
	}
}

void CEditPathesDlg::OnBnClickedButtonMoveDown()
{
	byte ind = m_ListPathes.GetCurSel();
	if (ind < (m_ListPathes.GetCount() - 1))
	{
		m_ListPathes.GetText(ind, str_Tmp);
		m_ListPathes.DeleteString(ind);
		m_ListPathes.InsertString(ind + 1, str_Tmp);
		m_ListPathes.SetCurSel(ind + 1);
	}
}

void CEditPathesDlg::OnBnClickedOk()
{
	for (byte i = 0; i < m_ListPathes.GetCount(); i++)
	{
		m_ListPathes.GetText(i, str_Tmp);
		m_RetArr.Add(str_Tmp);
	}

	CDialogEx::OnOK();
}

BOOL CEditPathesDlg::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);

	return CDialogEx::PreTranslateMessage(pMsg);
}

void CEditPathesDlg::OnBnClickedButtonViewEditOnSyno()
{
	CString RV;
	CDSSynoFSDlg dlgSynoFS(&RV, this);
	dlgSynoFS.DoModal();
	if (!RV.IsEmpty())
	{
		m_ListPathes.AddString(RV);
		m_ListPathes.SetCurSel(m_ListPathes.GetCount() - 1);
	}
}
