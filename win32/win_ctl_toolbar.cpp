/*
** Taiga, a lightweight client for MyAnimeList
** Copyright (C) 2010-2011, Eren Okka
** 
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "win_control.h"

// =============================================================================

void CToolbar::PreCreate(CREATESTRUCT &cs) {
  cs.dwExStyle = NULL;
  cs.lpszClass = TOOLBARCLASSNAME;
  cs.style     = WS_CHILD | WS_VISIBLE | WS_TABSTOP | CCS_NODIVIDER | CCS_NOPARENTALIGN | 
                 TBSTYLE_FLAT | TBSTYLE_LIST | TBSTYLE_TOOLTIPS | TBSTYLE_TRANSPARENT;
}

void CToolbar::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
  ::SendMessage(m_hWindow, TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
  ::SendMessage(m_hWindow, TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_DRAWDDARROWS | TBSTYLE_EX_MIXEDBUTTONS);
  SetImageList(NULL, 0, 0);
  CWindow::OnCreate(hwnd, lpCreateStruct);
}

// =============================================================================

BOOL CToolbar::EnableButton(int nIndex, bool bEnabled) {
  TBBUTTONINFO tbbi = {0};
  tbbi.cbSize  = sizeof(TBBUTTONINFO);
  tbbi.dwMask  = TBIF_BYINDEX | TBIF_STATE;
  tbbi.fsState = bEnabled ? TBSTATE_ENABLED : TBSTATE_INDETERMINATE;
  return ::SendMessage(m_hWindow, TB_SETBUTTONINFO, nIndex, reinterpret_cast<LPARAM>(&tbbi));
}

int CToolbar::GetHeight() {
  RECT rect;
  ::SendMessage(m_hWindow, TB_GETITEMRECT, 1, (LPARAM)&rect);
  return rect.bottom;
}

DWORD CToolbar::GetButtonSize() {
  return ::SendMessage(m_hWindow, TB_GETBUTTONSIZE, 0, 0);
}

LPCWSTR CToolbar::GetButtonTooltip(int nIndex) {
  return nIndex < static_cast<int>(m_TooltipText.size()) ? m_TooltipText[nIndex] : L"";
}

DWORD CToolbar::GetPadding() {
  return ::SendMessage(m_hWindow, TB_GETPADDING, 0, 0);
}

BOOL CToolbar::InsertButton(int iIndex, int iBitmap, int idCommand, bool bEnabled, 
                            BYTE fsStyle, DWORD_PTR dwData, LPCWSTR lpText, LPCWSTR lpTooltip) {
  TBBUTTON tbb  = {0};
  tbb.iBitmap   = iBitmap;
  tbb.idCommand = idCommand;
  tbb.iString   = reinterpret_cast<INT_PTR>(lpText);
  tbb.fsState   = bEnabled ? TBSTATE_ENABLED : TBSTATE_INDETERMINATE;
  tbb.fsStyle   = fsStyle;
  tbb.dwData    = dwData;

  m_TooltipText.push_back(lpTooltip);
  return ::SendMessage(m_hWindow, TB_INSERTBUTTON, iIndex, reinterpret_cast<LPARAM>(&tbb));
}

BOOL CToolbar::SetButtonImage(int nIndex, int iImage) {
  TBBUTTONINFO tbbi = {0};
  tbbi.cbSize = sizeof(TBBUTTONINFO);
  tbbi.dwMask = TBIF_BYINDEX | TBIF_IMAGE;
  tbbi.iImage = iImage;
  return ::SendMessage(m_hWindow, TB_SETBUTTONINFO, nIndex, reinterpret_cast<LPARAM>(&tbbi));
}

BOOL CToolbar::SetButtonText(int nIndex, LPCWSTR lpText) {
  TBBUTTONINFO tbbi = {0};
  tbbi.cbSize  = sizeof(TBBUTTONINFO);
  tbbi.dwMask  = TBIF_BYINDEX | TBIF_TEXT;
  tbbi.pszText = const_cast<LPWSTR>(lpText);
  return ::SendMessage(m_hWindow, TB_SETBUTTONINFO, nIndex, reinterpret_cast<LPARAM>(&tbbi));
}

BOOL CToolbar::SetButtonTooltip(int nIndex, LPCWSTR lpTooltip) {
  if (nIndex > static_cast<int>(m_TooltipText.size())) {
    return FALSE;
  } else {
    m_TooltipText[nIndex] = lpTooltip;
    return TRUE;
  }
}

void CToolbar::SetImageList(HIMAGELIST hImageList, int dxBitmap, int dyBitmap) {
  ::SendMessage(m_hWindow, TB_SETBITMAPSIZE, 0, (LPARAM)MAKELONG(dxBitmap, dyBitmap));
  ::SendMessage(m_hWindow, TB_SETIMAGELIST, 0, (LPARAM)hImageList);
}