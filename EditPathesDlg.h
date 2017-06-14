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
#ifndef _EDIT_PATHES_DLG_H_
#define _EDIT_PATHES_DLG_H_

#include "DS HelperDlg.h"
#include "afxwin.h"

class CEditPathesDlg : public CDialogEx
{
	enum { IDD = IDD_DIALOG_EDIT_PATHES };

public:
	CEditPathesDlg();
	CDSHelperDlg* m_pParentDlg;
	
	virtual BOOL OnInitDialog();
	CListBox m_ListPathes;

	typedef  CArray  < CString, CString > SArray;
	SArray  m_RetArr;

private:
	afx_msg void OnBnClickedButtonAddPath();
	afx_msg void OnBnClickedButtonRemovePath();
	afx_msg void OnBnClickedButtonMoveUp();
	afx_msg void OnBnClickedButtonMoveDown();
	afx_msg void OnBnClickedOk();
	
	CString str_Tmp;

protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX); 
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CToolTipCtrl m_ToolTip;
	CButton m_ButtonAddPath;
	CButton m_ButtonRemovePath;
	CButton m_ButtonMoveUp;
	CButton m_ButtonMoveDown;
	CButton m_ButtonOK;
public:
	afx_msg void OnBnClickedButtonViewEditOnSyno();
};

#endif