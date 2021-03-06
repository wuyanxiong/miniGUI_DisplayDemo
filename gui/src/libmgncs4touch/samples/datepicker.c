/*
 * \file datepicker.c
 * \author FMSoft
 * \date 2010/10/09
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>

#include <mgncs/mgncs.h>
#include <mgeff/mgeff.h>

#include <mgncs4touch/mgncs4touch.h>
// #define NDEBUG	1
#include <mgncs4touch/mtouchdebug.h>

#define ID_DPICKER1    101
#define ID_DPICKER2    102
#define ID_DPICKER3    103
#define ID_DPICKER4    104


static BOOL mymain_onCreate(mWidget* self, DWORD add_data)
{
	mDatePicker* pick = NULL;
/*
    if (NULL != (pick = (mDatePicker*)ncsGetChildObj(self->hwnd, ID_DPICKER1))) {
	    _M(pick, setDate, 2010, 3, 18);
	} else {
	    LOGE("---- Get mDatePicker Error. \n");
	}
*/
    if (NULL != (pick = (mDatePicker*)ncsGetChildObj(self->hwnd, ID_DPICKER2))) {
	    _M(pick, setProperty, NCSP_DPCK_YEAR,  2018);
	    _M(pick, setProperty, NCSP_DPCK_MONTH, 3);
	    _M(pick, setProperty, NCSP_DPCK_DAY,   28);
	} else {
	    LOGE("---- Get mDatePicker Error. \n");
	}

    if (NULL != (pick = (mDatePicker*)ncsGetChildObj(self->hwnd, ID_DPICKER3))) {
	    _M(pick, setDate, 2010, 3, 18);
	} else {
	    LOGE("---- Get mDatePicker Error. \n");
	}

    if (NULL != (pick = (mDatePicker*)ncsGetChildObj(self->hwnd, ID_DPICKER4))) {
	    _M(pick, setDate, 2010, 3, 18);
	} else {
	    LOGE("---- Get mDatePicker Error. \n");
	}

	return TRUE;
}


static void mymain_onClose(mWidget* self, int message)
{
	DestroyMainWindow(self->hwnd);
	PostQuitMessage(0);
}

static void datechanged_notify(mWidget *self, int id, int nc, DWORD add_data)
{
    int y, m, d;
    _M((mDatePicker *)self, getDate, &y, &m, &d);
	LOGE("NCSN_DPCK_DATECHANGED: %d, %d, %d\n", y, m, d);
}

static NCS_EVENT_HANDLER multi_handlers [] = {
    NCS_MAP_NOTIFY(NCSN_DPCK_DATECHANGED, datechanged_notify),
	{0, NULL}
};

static NCS_PROP_ENTRY _props [] = {
	{NCSP_CMBPCK_HMARGIN, 10},
	{NCSP_CMBPCK_VMARGIN, 10},
	{0, 0}
};

//Controls
static NCS_WND_TEMPLATE _ctrl_templ[] = {
	{
		NCSCTRL_DATEPICKER,
		ID_DPICKER1,
		5, 10, 280, 200,
		WS_VISIBLE | NCSS_DPCK_YYYYMMDD | NCSS_NOTIFY,
		WS_EX_NONE,
		"datepicker",
		_props,
		NULL, //rdr_info
		multi_handlers, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_DATEPICKER,
		ID_DPICKER2,
		320, 10, 280, 200,
		WS_VISIBLE | NCSS_DPCK_MMDDYYYY | NCSS_NOTIFY,
		WS_EX_NONE,
		"datepicker",
		_props,
		NULL, //rdr_info
		multi_handlers, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_DATEPICKER,
		ID_DPICKER3,
		5, 260, 280, 200,
		WS_VISIBLE | NCSS_DPCK_YYMMDD | NCSS_NOTIFY,
		WS_EX_NONE,
		"datepicker",
		_props,
		NULL, //rdr_info
		multi_handlers, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
	{
		NCSCTRL_DATEPICKER,
		ID_DPICKER4,
		320, 260, 280, 200,
		WS_VISIBLE | NCSS_DPCK_MMDDYY | NCSS_NOTIFY,
		WS_EX_NONE,
		"datepicker",
		_props,
		NULL, //rdr_info
		multi_handlers, //handlers,
		NULL, //controls
		0,
		0 //add data
	},
};


static NCS_EVENT_HANDLER mymain_handlers[] = {
	{MSG_CREATE, mymain_onCreate},
	{MSG_CLOSE, mymain_onClose},
	{0, NULL}
};


//define the main window template
static NCS_MNWND_TEMPLATE mymain_templ = {
	NCSCTRL_MAINWND,
	1,
	0, 0, 625, 500,
	WS_CAPTION | WS_BORDER | WS_VISIBLE,
	WS_EX_NONE,
	"mDatePicker Test ...",
	NULL,
	NULL,
	mymain_handlers,
	_ctrl_templ,
	sizeof(_ctrl_templ) / sizeof(NCS_WND_TEMPLATE),
	0,
	0,
	0,
};


int MiniGUIMain(int argc, const char* argv[])
{
#ifdef _MGRM_PROCESSES
	JoinLayer (NAME_DEF_LAYER, NULL, 0, 0);
#endif

	ncsInitialize();
	ncs4TouchInitialize();

	mDialogBox* mydlg = (mDialogBox*)ncsCreateMainWindowIndirect
									(&mymain_templ, HWND_DESKTOP);
	_c(mydlg)->doModal(mydlg, TRUE);

	ncs4TouchUninitialize();
	ncsUninitialize();
	return 0;
}
#ifdef _USE_MINIGUIENTRY
int main(int argc, const char* argv[])
{
    main_entry(argc, argv);
    return 0;
}
#endif
#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

