#include "stdafx.h"
#include "CrossViewer.h"
#include "EmptyWindow.h"
#include "DebugMess.h"
#include "ConstData.h"
#include "MenuApi.h"
#include "ViewersMenu.hpp"
#include "CrossWindow.h"
#include "Common.h"
#include "LabelMessage.h"

using namespace Gdiplus;
//-----------------------------------------------------------------------------------------
CrossViewer::CrossViewer()
	: backScreen(NULL)
	, chart(backScreen)
	, cursor(chart)
	, viewerData(Singleton<ItemData<Cross> >::Instance())
{
	chart.minAxesY = 1;
	chart.maxAxesY = 1 + App::cross_count_sensors;
	chart.minAxesX = 0;
	chart.maxAxesX = App::zonesCount;
	chart.rect.top = 17;
	mouseMove = true;
	label.fontHeight = 12;
	label.top = 0;
	chart.items.get<FixedGridSeries>().SetColorCellHandler(this, &CrossViewer::GetColorBar);
	cursor.SetMouseMoveHandler(this, &CrossViewer::Draw);	
	chart.items.get<FixedGridSeries>().sensorCount = App::cross_count_sensors;
}
//--------------------------------------------------------------------------
bool CrossViewer::Draw(TMouseMove &l, VGraphics &g)
{
	int x, y;
	chart.CoordCell(l.x, l.y, x, y);
	//dprint("cross %d \n", x);
	bool drawZones =  x < viewerData.currentOffsetZones;
	if(drawZones)
	{
		int color;
		bool b;
		char *s = StatusText()(viewerData.status[y][x], color, b);
		wchar_t buf[128];
		if(b)
		{
			wsprintf(buf, L"<ff>�������� <ff0000>%s", Wchar_from<double, 3>(viewerData.buffer[y][x])());
		}
		else
		{
			buf[0] = 0;
		}
		wsprintf(label.buffer, L"<ff>���������� ���� %d  ������ %d   <%6x>%S %s"
			, 1 + x
			, 1 + y
			, color
			, s
			, buf
			);
		label.Draw(g());
	}
	return drawZones;
}
bool CrossViewer::GetColorBar(unsigned sensor, int zone, double &data, unsigned &color)
{
	--sensor;
	data = viewerData.buffer[sensor][zone];
	color = ConstData::ZoneColor(viewerData.status[sensor][zone]);
	return zone < viewerData.currentOffsetZones;
}
/////////////////////////////////////////////////////////////////////////////////////////////
void CrossViewer::operator()(TSize &l)
{
	if(l.resizing == SIZE_MINIMIZED || 0 == l.Width || 0 == l.Height) return;	
	
	if(NULL != backScreen)
	{
		if(backScreen->GetWidth() < l.Width || backScreen->GetHeight() < l.Height)
		{
			delete backScreen;
		    backScreen = new Bitmap(l.Width, l.Height);
		}
	}
	else if(l.Width > 0 && l.Height > 0)
	{
		backScreen = new Bitmap(l.Width, l.Height);
	}
	else
	{
		return;
	}
    Graphics g(backScreen);
	SolidBrush solidBrush(Color(0xffaaaaaa));
	g.FillRectangle(&solidBrush, 0, 0, 10, l.Height);   
	g.FillRectangle(&solidBrush, 0, 0, l.Width, 29);  
	
	
	chart.rect.right = l.Width;
	chart.rect.bottom = l.Height;
	chart.Draw(g);
}
//-----------------------------------------------------------------------
void CrossViewer::operator()(TPaint &l)
{
	if(NULL == backScreen) return;
	PAINTSTRUCT p;
	HDC hdc = BeginPaint(l.hwnd, &p);
	{		
		Graphics g(hdc);		
		g.DrawCachedBitmap(&CachedBitmap(backScreen, &g), 0, 0);
		cursor.CrossCursor(storedMouseMove, PaintGraphics(g));
	}
	EndPaint(l.hwnd, &p);
}
//------------------------------------------------------------------------
void CrossViewer::operator()(TMouseMove &l)
{
	if(mouseMove)
	{
		if(cursor.CrossCursor(l, HDCGraphics(l.hwnd, backScreen)))
		{
			storedMouseMove = l;
		}
	}
}
//------------------------------------------------------------------------------
void CrossViewer::operator()(TLButtonDbClk &l)
{
	 mouseMove = true;
	if(cursor.CrossCursor(*(TMouseMove *)&l, HDCGraphics(l.hwnd, backScreen)))
	{
		storedMouseMove.x = l.x;
	}
}
//--------------------------------------------------------------------------------
void CrossViewer::operator()(TMouseWell &l)
{
		mouseMove = false;
	
		chart.items.get<FixedGridSeries>().OffsetToPixel(
			storedMouseMove.x
			, storedMouseMove.y
			, l.delta / 120
			, 0 == l.flags.lButton 
			);
		cursor.CrossCursor(storedMouseMove, HDCGraphics(storedMouseMove.hwnd, backScreen));		
}
//--------------------------------------------------------------------------------------
void CrossViewer::operator()(TLButtonDown &)
{
		mouseMove = false;
}
//------------------------------------------------------------------
unsigned CrossViewer::operator()(TCreate &l)
{
	storedMouseMove.hwnd = l.hwnd;
	storedMouseMove.x = 0;	
	storedMouseMove.y = WORD(chart.rect.top + 1);
	return 0;
}
//------------------------------------------------------------------------------------------
CONTEXT_MENU(CrossWindow)
void CrossViewer::operator()(TRButtonDown &l)
{
	PopupMenu<ContextMenuCrossWindow::items_list>::Do(l.hwnd, l.hwnd);
}
//--------------------------------------------------------------------------------
