#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"
#include "App.h"

PARAM_TITLE(BKlass2<Long>, L"����� 2 �����")
PARAM_TITLE(BDefect<Long>, L"����� �����")

DO_NOT_CHECK(BKlass2<Long>)
DO_NOT_CHECK(BDefect<Long>)
void LongThresholdsDlg  ::Do(HWND h)
{
	if(TemplDialogList<
		ThresholdsTable
		, TL::MkTlst<BKlass2<Long>, BDefect<Long>>::Result
	>(Singleton<ThresholdsTable>::Instance()).Do(h, L"���������� ������"))
	{
	}
}

PARAM_TITLE(BKlass2<Cross>, L"����� 2 �����")
PARAM_TITLE(BDefect<Cross>, L"����� �����")

DO_NOT_CHECK(BKlass2<Cross>)
DO_NOT_CHECK(BDefect<Cross>)
void CrossThresholdsDlg  ::Do(HWND h)
{
	if(TemplDialogList<
		ThresholdsTable
		, TL::MkTlst<BKlass2<Cross>, BDefect<Cross>>::Result
	>(Singleton<ThresholdsTable>::Instance()).Do(h, L"���������� ������"))
	{
	}
}

PARAM_TITLE(MimimumTubeLength, L"����������� ����� �����(� �����)")

MIN_EQUAL_VALUE(MimimumTubeLength, 20)
MAX_EQUAL_VALUE(MimimumTubeLength, 60)

void MinimumTubeLengthDlg::Do(HWND h)
{
	if(TemplDialogList<
		ThresholdsTable
		, TL::MkTlst<MimimumTubeLength>::Result
	>(Singleton<ThresholdsTable>::Instance()).Do(h, L"����������� ����� �����"))
	{
	}
}