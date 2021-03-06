#pragma once
#include "LongViewer.h"
#include "LineViewer.h"
#include "typelist.hpp"
#include "DataViewer.h"
#include "ConstData.h"
#include "LineChart.hpp"

template<class T>struct ChangeType;

class XLongViewer: public LongViewer
{
public:
	typedef LongViewer Parent;
	void operator()(TRButtonDown &){}													 
};


class LongWindow
{
public:
	typedef Long sub_type;
	int lastZone;
public:
	HWND hWnd;
	bool drawZones;
	
	typedef TL::CreateWapperNumList<Line, LongWindow, 0, 3>::Result line_list;
	typedef TL::AppendList<
		    TL::MkTlst<XLongViewer>::Result
		    , line_list
	    >::Result viewers_list;
	TL::Factory<viewers_list> viewers;
	LongViewer &viewer;
	LongWindow();
	void operator()(TSize &);
	void operator()(TCommand &);
	void operator()(TGetMinMaxInfo &);
	unsigned operator()(TCreate &);
	void operator()(TMouseWell &);
	void operator()(TDestroy &);
	static wchar_t *Title();

	bool DrawCursor(TMouseMove &, VGraphics &);
};