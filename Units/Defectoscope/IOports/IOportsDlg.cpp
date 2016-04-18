#pragma once
#include "stdafx.h"
#include "Dialogs.h"
#include "IOportsWindow.h"
#include "EmptyWindow.h"
#include "AppBase.h"
#include "mainwindow.h"
#include "Pass.h"
#include <CommCtrl.h>
#include <WindowsX.h>
#include "WindowsPosition.h"

void IOportsDlg::Do(HWND h)
{
	HWND hh = FindWindow(L"IOportsWindow", 0);
	if(NULL != hh)
	{
		SendMessage(hh, WM_SYSCOMMAND, SC_RESTORE, 0);
		SetForegroundWindow(hh);
	}
	else
	{
		RECT r;
		WindowPosition::Get<IOportsWindow>(r);
		h = WindowTemplate(
			&IOportsWindow::Instance()
			,  L"�������� ���������� ������-������� (����� 0)"
			, r.left, r.top
			, IOportsWindow::width, IOportsWindow::height
			);
		ShowWindow(h, SW_SHOWNORMAL);
	}
}

void IOports1Dlg::Do(HWND h)
{
	HWND hh = FindWindow(L"IOportsWindow1", 0);
	if(NULL != hh)
	{
		SendMessage(hh, WM_SYSCOMMAND, SC_RESTORE, 0);
		SetForegroundWindow(hh);
	}
	else
	{
		RECT r;
		WindowPosition::Get<IOportsWindow1>(r);
		const int height = IOportsWindow1::height;
		h = WindowTemplate(
			&IOportsWindow1::Instance()
			,  L"�������� ���������� ������-������� (����� 1)"
			, r.left, r.top
			, IOportsWindow1::width, height
			);
		ShowWindow(h, SW_SHOWNORMAL);
	}
}

