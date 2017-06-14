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
#ifndef _DSSYNOFS_H_
#define _DSSYNOFS_H_

#include "afxwin.h"
#include "EditPathesDlg.h"
#include "afxcmn.h"

class CDSSynoFSDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDSSynoFSDlg)

public:
	CDSSynoFSDlg(CString* RetVal, CEditPathesDlg* pParent = NULL);  

	virtual ~CDSSynoFSDlg();
	virtual BOOL OnInitDialog();

	
	enum { IDD = IDD_DIALOG_VIEW_EDIT_ON_SYNO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()

	CEditPathesDlg* m_pParent;
	CString* m_RetVal;

private:
	void ShowSynoFSTree();
	void FreeTree(HTREEITEM hTreeItem);

	CImageList m_TreeImages;

	CTreeCtrl m_Tree;
public:
	afx_msg void OnTvnItemexpandingTreeSyno(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonCreateFolderOnSyno();
	afx_msg void OnBnClickedButtonAddCurrentToPredef();
};

#endif