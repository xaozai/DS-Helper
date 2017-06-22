#pragma once
#ifndef _DS_H_CLISTCTRL_H_
#define _DS_H_CLISTCTRL_H_

#define ID_MENU_PAUSE 10001
#define ID_MENU_RESUME 10002
#define ID_MENU_DELETE 10003

#include "afxwin.h"

class CDSHListCtrl : public CListCtrl
{

public:

	DECLARE_MESSAGE_MAP()

public:
	CDSHListCtrl(void);
	~CDSHListCtrl(void);
	
	void MakeBitmapFromICO(CBitmap* pBitMapObj, int ICO_ID);

	CMenu m_Menu;
	ULONG_PTR m_GDIplusToken;
	CBitmap m_BitmapPause;
	CBitmap m_BitmapResume;
	CBitmap m_BitmapDelete;

	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
	
	BOOL DeleteItem(_In_ int nItem);
	int GetItemCount() const;
	int InsertItem(_In_ const LVITEM* pItem);
	BOOL SetItem(_In_ const LVITEM* pItem);
	BOOL DeleteAllItems();
	int FindItem(_In_ LVFINDINFO* pFindInfo, _In_ int nStart = -1) const;
	CString GetItemText(int nItem, int nSubItem) const;
	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText);
	BOOL GetItem(_Out_ LVITEM* pItem) const;

};

#endif