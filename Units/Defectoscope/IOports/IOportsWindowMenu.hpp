#pragma once
#include "WindowsPosition.h"
#include "Dialogs.h"
namespace IOportsWindowMenu
{
	struct MainFile{};
	MENU_TEXT(L"����", TopMenu<MainFile>)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct MainExit{static void Do(HWND h){DestroyWindow(h);}};

	MENU_ITEM(L"�����", MainExit)

	template<>struct TopMenu<MainFile>
	{
		typedef TL::MkTlst<
			MenuItem<MainExit>
		>::Result list;
	};
//-----------------------------------------------------------------------------
	struct MainOptionUnits{};
	MENU_TEXT(L"���������", TopMenu<MainOptionUnits>)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct WindowPosition : WindowPositionDlg<IOportsWindow>{};

	MENU_ITEM(L"��������� ���������� ����", WindowPosition)

	template<>struct TopMenu<MainOptionUnits>
	{
		typedef TL::MkTlst<
			MenuItem<WindowPosition>
		>::Result list;
	};

	typedef TL::MkTlst<
		TopMenu<MainFile>
		, TopMenu<MainOptionUnits>
	>::Result MainMenu;
//..++++++++++++++++++
	struct MainOptionUnits1{};
	MENU_TEXT(L"���������", TopMenu<MainOptionUnits1>)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	struct WindowPosition1 : WindowPositionDlg<IOportsWindow1>{};

	MENU_ITEM(L"��������� ���������� ����", WindowPosition1)

	template<>struct TopMenu<MainOptionUnits1>
	{
		typedef TL::MkTlst<
			MenuItem<WindowPosition1>
		>::Result list;
	};

	typedef TL::MkTlst<
		TopMenu<MainFile>
		, TopMenu<MainOptionUnits1>
	>::Result MainMenu1;
}

