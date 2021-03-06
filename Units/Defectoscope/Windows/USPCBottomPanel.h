#pragma once
#include "message.h"
#include "TabControlUnits.h"
#include "Button.h"
#include "App.h"
#include "USPCpageItems.hpp"
#include "DebugMess.h"
#if 0
#define PAR(type, name)template<class T>struct ParamTitle<type<T> >\
{wchar_t *operator()(){return name;}};

PAR(position, L"position")
PAR(width, L"width")
PAR(level, L"level")
PAR(nb_alarm_level, L"alarm level")
PAR(offset, L"offset")
PAR(range, L"range")
PAR(velocity, L"velocity")
#undef PAR

class USPCBottomPanel
{
	bool firstSize;
public:
	int &unit;
	int &sens;
public:
	
	struct USPCTabs
	{
		typedef TL::MkTlst<
			USCPpageItems<gateIF>
			, USCPpageItems<gate1>
			, USCPpageItems<gate2>
			, USCPpageItems<scope>
		>::Result items_list;
		
		TL::Factory<items_list> items;
		template<class T>USPCTabs(T &t): items(t){}
	};
	USPCParam uspcParam;
	USPCTabs uspcTabs;
	TabControlUnit<USPCTabs> tabControl;
	Button uspcButtonOk;	
public:
	HWND hWnd;
	USPCBottomPanel(int &, int &);
	unsigned operator()(TCreate &);
	void operator()(TNotify &);
	void operator()(TCommand &);
	void operator()(TSize &);
	void UpdatePage(int);
};
#endif