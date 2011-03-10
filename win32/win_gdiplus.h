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

#ifndef WIN_GDIPLUS_H
#define WIN_GDIPLUS_H

#include "win_main.h"

// =============================================================================

class CGdiPlus {
public:
  CGdiPlus();
  ~CGdiPlus();

  HBITMAP LoadImage(const wstring& file);

private:
  ULONG_PTR m_Token;
};

#endif // WIN_GDIPLUS_H