#pragma once
#ifndef _CSAFEEDIT_H_
#define _CSAFEEDIT_H_

#include "afxwin.h"

class CSafeCEdit : public CEdit
{

public:

	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnSetPasswordChar(WPARAM, LPARAM);
	afx_msg LRESULT OnGetText(WPARAM, LPARAM);
	
	

private:
	bool m_Disable_WM_GetText = true;
	

public:

	void Disable_WM_GetText();
	void Enable_WM_GetText();
};

#endif