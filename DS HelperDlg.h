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
#ifndef _DS_HELPER_DLG_H_
#define _DS_HELPER_DLG_H_

#include "afxwin.h"
#include "DS HelperTypes.h"
#include "DS HelperRegistry.h"
#include "afxcmn.h"
#include "CSafeCEdit.h"
#include "DS H_CListCtrl.h"


class CDSHelperDlg : public CDialogEx
{

public:
	CDSHelperDlg(CWnd* pParent = NULL);
	
	CComboBox m_ComboPath;
	CComboBox m_ComboProtocol;

	CEdit m_CEditAddress;
	CEdit m_CEditPort;
	CEdit m_CEditUsername;
	CSafeCEdit m_CEditPassword;
	
	bool RefreshTaskThreadRunning = false;

	CDSHelperApp* m_App;
		
	enum { IDD = IDD_DSHELPER_DIALOG };

private:
	bool ReadPathesToCombo();
	void ReadSettings();
	bool SavePathes(bool Param = true);
	void GetTaskFromCommandLine();
	
	bool m_DoSaveSettings;

	CButton m_ButtonEditPathes;
	CButton m_ButtonAddATask;
	CButton m_StorePassword;
	CButton m_ButtonOpenFile;
	CEdit m_CEditTask;

	CDSHListCtrl m_CListActiveTasks;//CListCtrl

	HICON m_hIcon;

	DSHelperRegistry m_Registry;
	
	afx_msg void OnBnClickedButtonAddTask();
	afx_msg void OnBnClickedCheckStore();
	afx_msg void OnNMClickSyslinkOpenDsWeb(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnKillfocusEditAddress();
	afx_msg void OnEnKillfocusEditUsername();
	afx_msg void OnEnKillfocusEditPassword();
	afx_msg void OnBnClickedButtonEditPathes();
	afx_msg void OnBnClickedButtonOpenFile();
	afx_msg void OnEnKillfocusEditPort();
	afx_msg void OnCbnKillfocusComboProtocol();
	afx_msg void OnCbnCloseupComboProtocol();
	afx_msg void OnBnClickedCheckShowActiveTasks();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//afx_msg LRESULT OnMenuClick(WPARAM, LPARAM);
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	
	static UINT __cdecl RefreshActiveTasksLoop(LPVOID pParam);
	int RefreshActiveTasks(bool NeedAuth);
	CWinThread* RefreshThread = NULL;
	WebClient* m_ThreadSynoConnect = NULL;
	
	void DeleteTask();
	void PauseTask();
	void ResumeTask();
	

protected:
	CToolTipCtrl m_ToolTip;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
	
private:
	CButton m_CheckBoxShowActiveTasks;
	CImageList m_CListImages;

	void HideCList();
	void ShowCList();
	CRect CListRect;
	CRect WinRect;
	
//public:
	//afx_msg void OnNMRClickListActiveTasks(NMHDR *pNMHDR, LRESULT *pResult);
};

#endif