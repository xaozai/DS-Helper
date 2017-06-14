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
#include "InputBox.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CInputBox, CDialogEx)

CInputBox::CInputBox(CString* RequestDescription, CString* RetVal, CWnd* pParent) : CDialogEx(CInputBox::IDD, pParent)
{
	m_pParent = pParent;
	m_RetVal = RetVal;

	m_RequestDescription.SetString(RequestDescription->GetString());
}

CInputBox::~CInputBox()
{

}

void CInputBox::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	DDX_Control(pDX, IDC_EDIT_VALUE, m_Value);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_StaticRequestDescription);
}

BEGIN_MESSAGE_MAP(CInputBox, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT_VALUE, &CInputBox::OnEnKillfocusEditValue)
END_MESSAGE_MAP()


void CInputBox::OnEnKillfocusEditValue()
{
	CString strUserInput;
	m_Value.GetWindowText(strUserInput);
	*m_RetVal = strUserInput;
}

BOOL CInputBox::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_StaticRequestDescription.SetWindowText(m_RequestDescription.GetString());

	return TRUE;

}
