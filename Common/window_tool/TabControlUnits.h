#pragma once

#include "message.h"
#include "DebugMess.h"
#include "ParamDlg.h"
#include "USPCmessages.h"
#if 0
template<class Table, class List>class TabPage
{
public:
	List &owner;
	template<class O, class P>struct __show__
	{
		void operator()(O *o, P *p)
		{
			ShowItem()(o->hWnd, *p);
			if(*p)
			{
				o->Update();
			}
		}
	};
	template<class O, class P>struct __init__
	{
		void operator()(O *o, P *p)
		{
			o->Init(p->h, p->width, p->height);	
		}
	};
	struct __table_data__
	{
		HWND h; 
		int &width; 
		int &height;
		__table_data__(HWND h, int &width, int &height): h(h), width(width), height(height){}
	};
	typedef Table TableParam;
public:
	typedef typename TL::TypeToTypeLst<typename Table::items_list, DlgItem>::Result list;
	TL::Factory<list> items;
	bool create;
	void Show(bool b)
	{
		if(create)
		{
			TL::foreach<list, __show__>()(&items, &b);
		}
		else
		{
			create = true;
		    int width = owner.width - 5;
			int height = 30;
			TL::foreach<list, __init__>()(&items, &__table_data__(owner.hTab, width, height));
		}
	}	
public:
	TabPage(List &l) 
		: owner(l)
		, create(false)
		, items(l.unit.items.get<typename TL::Inner<Table>::Result>().items)
	{}
};
//--------------------------------------------------------------------------------------------------------
#pragma warning(disable: 4355)

template<class T>class TabControlUnit: TEvent
{
	template<class O, class P>struct __tab_name__
	{
		void operator()(O *, P *hTab)
		{
			TCITEM ti = {0};
			ti.mask = TCIF_TEXT;
			ti.pszText = ParamTitle<O>()();
			ti.cchTextMax = wcslen(ti.pszText);
			int iid = TL::IndexOf<typename T::items_list, O>::value;
			int res = SendMessage(*hTab, TCM_INSERTITEM, iid, (LPARAM)&ti);
		}
	};
	struct __select_page_data__
	{
		int id;
		bool show;
		TabControlUnit *self;
	};
	template<class O, class P>struct __items__
	{
		void operator()(O *o, P *p)
		{
			Show(o->hWnd, p->show);
		}
	};
	template<class O, class P>struct __select_page__
	{
		bool operator()(O *, P *p)
		{
			if(p->id == TL::IndexOf<typename T::items_list, O>::value)
			{
				p->self->page.get<TabPage<O, TabControlUnit> >().Show(p->show);
				return false;
			}
			return true;
		}
	};
	template<class O, class P>struct __create__
	{
		void operator()(O *o, P *)
		{
			o->create = false;
		}
	};
	template<class O, class P>struct __item_update__
	{
		void operator()(O *o, P *p)
		{
			typedef typename TL::Inner<O>::Result T;
			o->value.value = p->data.items.get<USCPpageItems<typename TL::Inner<T>::Result> >().get<T>().value;
			o->Update();			
		}
	};
	template<class O, class P>struct __update__
	{
		void operator()(O *o, P *p)
		{
			TL::foreach<typename O::list, __item_update__>()(&o->items, p);
		}
    };
	template<class O, class P>struct __store_item__
	{
		void operator()(O *o, P *p)
		{
			  o->Store();
			  typedef typename TL::Inner<O>::Result T;
			  p->data.items.get<USCPpageItems<typename TL::Inner<T>::Result> >().get<T>().value = o->value.value;
		}
	};
	template<class O, class P>struct __store__
	{
		bool operator()(O *o, P *p)
		{
			if(TL::IndexOf<typename P::page_list, O>::value == p->currentPage)
			{
			 TL::foreach<typename O::list, __store_item__>()(&o->items, p);
			 return false;
			}
			return true;
		}
	};
	template<class O, class P>struct __sub_init__
	{
		void operator()(O *o, P *p)
		{
			o->value = p->get<O>().value;
		}
	};
	template<class O, class P>struct __init__
	{
		void operator()(O *o, P *p)
		{
			TL::foreach<O::items_list, __sub_init__>()(&o->items, &p->items.get<USCPpageItems<O> >());
		}
	};
public:
	void Show(bool b)
	{
		int iPage = TabCtrl_GetCurSel(hTab);
		if(b) currentPage = iPage;  
		__select_page_data__ data = {iPage, b, this};
		TL::find<typename Table::items_list, __select_page__>()((TL::Factory<typename Table::items_list> *)0, &data);
	}
public:
	HWND hTab;
	typedef T Table;
	T &data;
	int x, y, width, height;
	int currentPage;
	Unit<TabControlUnit, 0> unit;
	typedef typename TL::TypeToTypeLstParam1<typename Table::items_list, TabPage, TabControlUnit>::Result page_list;
	TL::Factory<page_list> page;
	TabControlUnit(T &t)
		: data(t)
		, page(*this)
	{} 
	void Create(HWND h)
	{
		currentPage = 0;
		hTab = CreateWindowEx(0, WC_TABCONTROL, 0,   WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, h, (HMENU)NULL, hInstance, 0);
		SetWindowLongPtr(hTab, GWLP_USERDATA, (DWORD)this);

		TL::foreach<typename T::items_list, __tab_name__>()((TL::Factory<typename T::items_list> *)0, (HWND *)&hTab);
		TL::foreach<page_list, __create__>()(&page, (int *)0);
		TL::foreach<Unit<TabControlUnit, 0>::items_list, __init__>()(&unit.items, &data);
	}
	
	void Do(TNotify &l)
	{
		switch (l.pnmh->code)
		{
		case TCN_SELCHANGING:
			{
				Show(false);
			}
			break;

		case TCN_SELCHANGE:
			{ 
				Show(true);
			} 
			break;
		}
	}

	void Size(TSize &l)
	{
		MoveWindow(hTab, x, y, width, height, false);
	}

	void UpdatePage()
	{
		TL::foreach<page_list, __update__>()(&page, this);
		Show(true);
	}

	void StorePage()
	{
		TL::find<page_list, __store__>()(&page, this);
		SetParamToGateItem();
	}	
};
#endif