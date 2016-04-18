#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"

PARAM_TITLE(TickPerZoneLir0, L"��������� �� ���� ��� 1")
PARAM_TITLE(TickPerZoneLir1, L"��������� �� ���� ��� 2")

DO_NOT_CHECK(TickPerZoneLir0)
DO_NOT_CHECK(TickPerZoneLir1)

void LirParamDlg::Do(HWND h)
{
	if(TemplDialogList<
		LirParamTable
		, TL::MkTlst<TickPerZoneLir0, TickPerZoneLir1>::Result
	>(Singleton<LirParamTable>::Instance()).Do(h, L"��������� �������� ���"))
	{
	}
}

PARAM_TITLE(DescriptorLir, L"���������� ����� 1784")
DO_NOT_CHECK(DescriptorLir)

void LirDescriptorDlg::Do(HWND h)
{
	if(TemplDialogList<
		LirParamTable
		, TL::MkTlst<DescriptorLir>::Result
	>(Singleton<LirParamTable>::Instance()).Do(h, L"���������� ����� ���"))
	{
	}
}



