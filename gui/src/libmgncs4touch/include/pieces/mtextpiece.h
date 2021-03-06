/*
 * \file 
 * \author FMSoft
 * \date 
 *
 \verbatim

    This file is part of mGNCS4Touch, one of MiniGUI components.

    Copyright (C) 2008-2018 FMSoft (http://www.fmsoft.cn).

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Or,

    As this program is a library, any link to this program must follow
    GNU General Public License version 3 (GPLv3). If you cannot accept
    GPLv3, you need to be licensed from FMSoft.

    If you have got a commercial license of this program, please use it
    under the terms and conditions of the commercial license.

    For more information about the commercial license, please refer to
    <http://www.minigui.com/en/about/licensing-policy/>.

 \endverbatim
*/

#ifndef _MGUI_NCSCTRL_TEXTPIECE_H
#define _MGUI_NCSCTRL_TEXTPIECE_H

#ifdef __cplusplus
extern "C" {
#endif

enum {
    NCSP_TEXTPIECE_LOGFONT= USER_PIECE_PROP_BEGIN + 1,
    NCSP_TEXTPIECE_TEXTCOLOR,
    NCSP_TEXTPIECE_TEXTSHADOWCOLOR,
    NCSP_TEXTPIECE_MAXLEN,
};

typedef struct _mTextPieceClass mTextPieceClass;
typedef struct _mTextPiece mTextPiece;

#define mTextPieceHeader(clss) \
    mLabelPieceHeader(clss) \
    DWORD color; /* ARGB */ \
    DWORD shadow_color; /* ARGB */ \
    BOOL isShadow;  \
    int maxLen;  \
    PLOGFONT font;

#define mTextPieceClassHeader(clss, superCls) \
    mLabelPieceClassHeader(clss, superCls)

struct _mTextPiece
{   
    mTextPieceHeader(mTextPiece)
};

struct _mTextPieceClass
{   
    mTextPieceClassHeader(mTextPiece, mLabelPiece)
};

MGNCS_EXPORT extern mTextPieceClass g_stmTextPieceCls;

#ifdef __cplusplus
}
#endif
#endif /*_MGUI_NCSCTRL_TEXTPIECE_H*/
