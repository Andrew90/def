#include "stdafx.h"
#include "Dialogs.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "AppBase.h"

PARAM_TITLE(IPPort, L"IP ����")
PARAM_TITLE(IPName, L"��� ����������")

DO_NOT_CHECK(IPPort)
DO_NOT_CHECK(IPName)
void TcpDlg::Do(HWND h)
{
   if(TemplDialog<IPAddressTable>(Singleton<IPAddressTable>::Instance()).Do(h, L"��������� TCP"))
	{
	}
}