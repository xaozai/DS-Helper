#include "stdafx.h"//precompiled headers
#include "CSafeCEdit.h"

BEGIN_MESSAGE_MAP(CSafeCEdit, CEdit)
	ON_MESSAGE(EM_SETPASSWORDCHAR, OnSetPasswordChar)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
END_MESSAGE_MAP()

LRESULT CSafeCEdit::OnSetPasswordChar(WPARAM, LPARAM)
{
	return 0;
}

LRESULT CSafeCEdit::OnGetText(WPARAM wParam, LPARAM lParam)
{
	if (m_Disable_WM_GetText)
		return 0;
	else
		return DefWindowProc(WM_GETTEXT, wParam, lParam);
}

void CSafeCEdit::Disable_WM_GetText()
{
	m_Disable_WM_GetText = true;
}

void CSafeCEdit::Enable_WM_GetText()
{
	m_Disable_WM_GetText = false;
}
