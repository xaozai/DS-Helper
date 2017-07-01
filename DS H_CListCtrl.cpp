#include "stdafx.h"//precompiled headers
#include "DS H_CListCtrl.h"
#include "Resource.h"
//#include <VersionHelpers.h>//doesn't work for XP

#define SendMessageTimeoutMSEC 5000

#pragma comment(lib, "gdiplus.lib")
#include <gdiplus.h>

BEGIN_MESSAGE_MAP(CDSHListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CDSHListCtrl::OnNMRClick)
END_MESSAGE_MAP()

void CDSHListCtrl::MakeBitmapFromICO(CBitmap* pBitMapObj, int ICO_ID)
{
	BITMAPV5HEADER bi;
	void *lpBits;
	ZeroMemory(&bi, sizeof(BITMAPV5HEADER));
	bi.bV5Size = sizeof(BITMAPV5HEADER);
	bi.bV5Width = 16;
	bi.bV5Height = 16;
	bi.bV5Planes = 1;
	bi.bV5BitCount = 32;
	bi.bV5Compression = BI_BITFIELDS;
	bi.bV5RedMask = 0x00FF0000;
	bi.bV5GreenMask = 0x0000FF00;
	bi.bV5BlueMask = 0x000000FF;
	bi.bV5AlphaMask = 0xFF000000;

	HDC hDC = ::GetDC(NULL);
	HBITMAP hbm = CreateDIBSection(hDC, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&lpBits, NULL, (DWORD)0);
	HDC hMemDC = CreateCompatibleDC(hDC);
	::ReleaseDC(NULL, hDC);

	HBITMAP hOldb = (HBITMAP)SelectObject(hMemDC, hbm);
	PatBlt(hMemDC, 0, 0, 16, 16, WHITENESS);

	DWORD *lpdwPixel;
	lpdwPixel = (DWORD *)lpBits;
	DWORD x, y;
	for (x = 0; x < 16; x++)
	for (y = 0; y < 16; y++)
	{
		// Clear the alpha bits
		*lpdwPixel &= 0x00FFFFFF;
		// Set the alpha bits to 0x9F (semi-transparent)
		//*lpdwPixel |= 0x9F000000;
		lpdwPixel++;
	}
	DrawIconEx(hMemDC, 0, 0, AfxGetApp()->LoadIcon(ICO_ID), 16, 16, 0, NULL, DI_NORMAL);
	SelectObject(hMemDC, hOldb);
	Gdiplus::Bitmap TranspBitmap(16, 16, 16 * 4, PixelFormat32bppARGB, (BYTE*)lpBits);
	TranspBitmap.RotateFlip(Gdiplus::Rotate180FlipX);

	HBITMAP hB = NULL;
	TranspBitmap.GetHBITMAP(0, &hB);
	
	pBitMapObj->Attach(hB);

	DeleteDC(hMemDC);
	DeleteObject(hOldb);
	DeleteObject(hbm);
}

CDSHListCtrl::CDSHListCtrl()
{

	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_GDIplusToken, &gdiplusStartupInput, NULL);
	
	m_Menu.CreatePopupMenu();

	m_Menu.AppendMenu(MF_STRING , ID_MENU_PAUSE, L"Pause");
	m_Menu.AppendMenu(MF_STRING, ID_MENU_RESUME, L"Resume");
	m_Menu.AppendMenu(MF_STRING, ID_MENU_DELETE, L"Remove");

	OSVERSIONINFO   vi;
	memset(&vi, 0, sizeof vi);
	vi.dwOSVersionInfoSize = sizeof vi;
	GetVersionEx(&vi);

	if (vi.dwMajorVersion >= 6)//if (IsWindowsVistaOrGreater())//icons are ugly in XP
	{
		MakeBitmapFromICO(&m_BitmapDelete, IDI_ICON_DELETE);
		m_Menu.SetMenuItemBitmaps(ID_MENU_DELETE, MF_BYCOMMAND, &m_BitmapDelete, NULL);

		MakeBitmapFromICO(&m_BitmapResume, IDI_ICON_PLAY);
		m_Menu.SetMenuItemBitmaps(ID_MENU_RESUME, MF_BYCOMMAND, &m_BitmapResume, NULL);

		MakeBitmapFromICO(&m_BitmapPause, IDI_ICON_PAUSE);
		m_Menu.SetMenuItemBitmaps(ID_MENU_PAUSE, MF_BYCOMMAND, &m_BitmapPause, NULL);
	}

}

CDSHListCtrl::~CDSHListCtrl()
{
	if (m_BitmapPause.m_hObject)
		m_BitmapPause.DeleteObject();

	if (m_BitmapResume.m_hObject)
		m_BitmapResume.DeleteObject();

	if (m_BitmapDelete.m_hObject)
		m_BitmapDelete.DeleteObject();
	
	m_Menu.DestroyMenu();
	
	Gdiplus::GdiplusShutdown(m_GDIplusToken);

}

void CDSHListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	if (this->GetSelectionMark() == -1)
	{
		*pResult = 0; return;
	}

	POINT current_point;
	GetCursorPos(&current_point);

	m_Menu.EnableMenuItem(ID_MENU_RESUME, MF_BYCOMMAND | MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_PAUSE, MF_BYCOMMAND | MF_ENABLED);
	m_Menu.EnableMenuItem(ID_MENU_DELETE, MF_BYCOMMAND | MF_ENABLED);

	LVITEM item;
	item.iItem = this->GetSelectionMark();
	item.iSubItem = 1;
	item.mask = LVIF_IMAGE;
	if (item.iItem != -1)
	{
		if (this->GetItem(&item))
		{
			if (item.iImage == 1)
				m_Menu.EnableMenuItem(ID_MENU_RESUME, MF_BYCOMMAND | MF_GRAYED);
			else
			{
				if (item.iImage == 2)
					m_Menu.EnableMenuItem(ID_MENU_PAUSE, MF_BYCOMMAND | MF_GRAYED);
				else
				{
					if (item.iImage == 3)
					{
					}
					else
					{
						if (item.iImage == 4)
						{
							m_Menu.EnableMenuItem(ID_MENU_RESUME, MF_BYCOMMAND | MF_GRAYED);
						}
						else
						{
							if (item.iImage == 6)
							{
								m_Menu.EnableMenuItem(ID_MENU_PAUSE, MF_BYCOMMAND | MF_GRAYED);
							}
							else
							{
								m_Menu.EnableMenuItem(ID_MENU_RESUME, MF_BYCOMMAND | MF_GRAYED);
								m_Menu.EnableMenuItem(ID_MENU_PAUSE, MF_BYCOMMAND | MF_GRAYED);
								m_Menu.EnableMenuItem(ID_MENU_DELETE, MF_BYCOMMAND | MF_GRAYED);
							}
						}
					}
				}
			}
		}
	}

	m_Menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, current_point.x, current_point.y, this);

	*pResult = 0;
}

BOOL CDSHListCtrl::DeleteItem(_In_ int nItem)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	BOOL bRetVal;

	::SendMessageTimeout(m_hWnd, LVM_DELETEITEM, nItem, 0L, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&bRetVal);

	return bRetVal;
}

int CDSHListCtrl::GetItemCount() const
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	int iRetVal;

	::SendMessageTimeout(m_hWnd, LVM_GETITEMCOUNT, 0, 0L, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&iRetVal);

	return iRetVal;
}

int CDSHListCtrl::InsertItem(_In_ const LVITEM* pItem)
{
	ASSERT(::IsWindow(m_hWnd));

	int iRetVal;

	::SendMessageTimeout(m_hWnd, LVM_INSERTITEM, 0, (LPARAM)pItem, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&iRetVal);

	return iRetVal;
}

BOOL CDSHListCtrl::SetItem(_In_ const LVITEM* pItem)
{
	ASSERT(::IsWindow(m_hWnd)); 
	
	BOOL bRetVal;
	
	::SendMessageTimeout(m_hWnd, LVM_SETITEM, 0, (LPARAM)pItem, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&bRetVal);

	return bRetVal;
	
}

BOOL CDSHListCtrl::DeleteAllItems()
{
	ASSERT(::IsWindow(m_hWnd));
	
	BOOL bRetVal; 
	
	::SendMessageTimeout(m_hWnd, LVM_DELETEALLITEMS, 0, 0L, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&bRetVal);

	return bRetVal;
}

BOOL CDSHListCtrl::GetItem(_Out_ LVITEM* pItem) const
{
	ASSERT(::IsWindow(m_hWnd));
	
	BOOL bRetVal;

	::SendMessageTimeout(m_hWnd, LVM_GETITEM, 0, (LPARAM)pItem, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&bRetVal);

	return bRetVal;
}

int CDSHListCtrl::FindItem(_In_ LVFINDINFO* pFindInfo, _In_ int nStart) const
{
	ASSERT(::IsWindow(m_hWnd));
	
	int iRetVal; 
	
	::SendMessageTimeout(m_hWnd, LVM_FINDITEM, nStart, (LPARAM)pFindInfo, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&iRetVal);

	return iRetVal;
}

CString CDSHListCtrl::GetItemText(int nItem, int nSubItem) const
{
	ASSERT(::IsWindow(m_hWnd));

	LVITEM lvi;
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.iSubItem = nSubItem;
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		lvi.cchTextMax = nLen;
		lvi.pszText = str.GetBufferSetLength(nLen);
		::SendMessageTimeout(m_hWnd, LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&nRes);
	} while (nRes >= nLen - 1);
	str.ReleaseBuffer();

	return str;
}

BOOL CDSHListCtrl::SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
{
	ASSERT(::IsWindow(m_hWnd));
	ASSERT((GetStyle() & LVS_OWNERDATA) == 0);

	LVITEM lvi;
	lvi.iSubItem = nSubItem;
	lvi.pszText = (LPTSTR)lpszText;
	
	BOOL bRetVal;
	
	::SendMessageTimeout(m_hWnd, LVM_SETITEMTEXT, nItem, (LPARAM)&lvi, SMTO_NORMAL, SendMessageTimeoutMSEC, (PDWORD_PTR)&bRetVal);

	return bRetVal;
}