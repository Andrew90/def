#include "stdafx.h"
#include "ParamDlg.h"
#include "ParamDlg.hpp"
#include "Dialogs.h"
#include "AppBase.h"
#include "App.h"
#include "Device1730.h"

template<class O, class P>struct __set__
{
	typedef typename TL::Inner<O>::Result T;
	void operator()(O *o, P *p)
	{
		wchar_t buf[128];
		GetWindowText(o->hWnd, buf, dimention_of(buf));
		o->value.value = p->Set<O>(Wchar_to<typename T::type_value>()(buf));
	}
};
template<class List>struct __data__
{
	typedef List list;
	unsigned buf[TL::Length<List>::value];
	template<class T>unsigned Set(unsigned val)
	{
		buf[TL::IndexOf<list, T>::value] = val;
		return 1 << val;
	}
};
template<class O, class P>struct __compress_bits__
{
	void operator()(O *o, P *p)
	{
		unsigned t = p->get<O>().value;
		unsigned i = 0;
		while(t >>= 1) ++i;
		o->value = i;
	}
};
struct putsDlg_OkBtn
{
	static const int width = 120;
	static const int height = 30;
	static const int ID = IDOK;
	wchar_t *Title(){return L"���������";}
	template<class Owner>void BtnHandler(Owner &owner, HWND h)
	{
		if(TestPassword<Owner::Table>()(h))
		{
			if(!TL::find<Owner::list, __test__>()(&owner.items, &h))return;
			__data__<Owner::list> d;
			TL::foreach<Owner::list, __set__>()(&owner.items, &d);
			for(int i = 0; i < dimention_of(d.buf) - 1; ++i)
			{
				unsigned value = d.buf[i];
				for(int j = i + 1; j < dimention_of(d.buf); ++j)
				{
					if(value == d.buf[j])
					{
						MessageBox(h, L"��������� ������ ��������� �� ���� ���", L"������!!!", MB_ICONERROR);
						return;
					}
				}
			}
			CBase base(ParametersBase().name());
			if(base.IsOpen())
			{
				CopyFactory::Do(Singleton<Owner::Table>::Instance().items, owner.table.items);
				UpdateWhere<Owner::Table>(owner.table, base).ID(1).Execute();
			}
			EndDialog(h, TRUE);
		}
	}
};


struct DefaultBtn
{
	static const int width = 160;
	static const int height = 30;
	static const int ID = IDRETRY;
	wchar_t *Title(){return L"���������� ���������";}
	template<class Owner>void BtnHandler(Owner &o, HWND h)
	{
		if(TestPassword<Owner::Table>()(h))
		{
			CBase base(ParametersBase().name());
			if(base.IsOpen())
			{
				Owner::Table t;
				CopyFactory::Do(Singleton<Owner::Table>::Instance().items, t.items);
				UpdateWhere<Owner::Table>(t, base).ID(1).Execute();
			}
			EndDialog(h, TRUE);
		}
	}
};
//----------------------------------------------------------------------------
/*
MIN_EQUAL_VALUE(SQ0, 0 )
MAX_EQUAL_VALUE(SQ0, 31)
MIN_EQUAL_VALUE(SQ1, 0 )
MAX_EQUAL_VALUE(SQ1, 31)
MIN_EQUAL_VALUE(SQ2, 0 )
MAX_EQUAL_VALUE(SQ2, 31)
MIN_EQUAL_VALUE(SQ3, 0 )
MAX_EQUAL_VALUE(SQ3, 31)
MIN_EQUAL_VALUE(SQ4, 0 )
MAX_EQUAL_VALUE(SQ4, 31)

PARAM_TITLE(SQ0, L"����� �� ������� SQ1(����)")
PARAM_TITLE(SQ1, L"����� �� ������� SQ2(�����)")
PARAM_TITLE(SQ2, L"��������� ��������")
PARAM_TITLE(SQ3, L"SQ3");
PARAM_TITLE(SQ4, L"SQ4");

template<>struct DlgSubItems<SQ0, unsigned >: UpDownSubItem<SQ0>{};
template<>struct DlgSubItems<SQ1, unsigned >: UpDownSubItem<SQ1>{};
template<>struct DlgSubItems<SQ2, unsigned >: UpDownSubItem<SQ2>{};
template<>struct DlgSubItems<SQ3, unsigned >: UpDownSubItem<SQ3>{};
template<>struct DlgSubItems<SQ4, unsigned >: UpDownSubItem<SQ4>{};
*/

#define DEFINE_Bits(z, def_val, txt)\
MIN_EQUAL_VALUE(z, 0 )\
MAX_EQUAL_VALUE(z, 31)\
PARAM_TITLE(z, txt)\
template<>struct DlgSubItems<z, unsigned >: UpDownSubItem<z>{};

DEFINE_Bits(BASE_TS	 	,4	,L"������ ����"                                      )
DEFINE_Bits(CONTROL	 	,13	,L"�������� �� �����������"							)
DEFINE_Bits(PCHA	 	,9	,L"������ � � ���������� ����������� ��������"		)
DEFINE_Bits(PCHB	 	,8	,L"������ B � ���������� ����������� ��������"		)
DEFINE_Bits(PCHRUN	 	,10	,L"������ RUN � ���������� ����������� ��������"		)
DEFINE_Bits(READY	 	,12	,L"���������� �� �����������"						)

DEFINE_Bits(SQfirst	 	,8	,L"������ �� ������ ����")

DEFINE_Bits(SQcrossIN	 	,0	,L"������ �� ����� ������ ����������� ��������"		)
DEFINE_Bits(SQcrossOUT	 	,1	,L"������ �� ������ ������ ����������� ��������"		)

DEFINE_Bits(SQthickIN	 	,5	,L"������ �� ����� �����������"		)
DEFINE_Bits(SQthickOUT	 	,6	,L"������ �� ������ �����������"		)

DEFINE_Bits(SQlongIN	 	,2	,L"������ �� ����� � ������ ����������� ��������"	)
DEFINE_Bits(SQlongOUT	 	,3	,L"������ �� ������ ������ ����������� ��������"		)
DEFINE_Bits(ZU	     	,11	,L"���� ����������"									)

DEFINE_Bits(CYCLE	 	,9	,L"������ ���� � ����������"							)
DEFINE_Bits(POWPCH	 	,0	,L"��������� ������� ���������� ����������� ��������")
DEFINE_Bits(POWSU	 	,5	,L"������� �� ����������� ��������"					)
DEFINE_Bits(RH	     	,3	,L"������� ��� �������� ����������� ��������"		)
DEFINE_Bits(RL	     	,1	,L"������� ��� �������� ����������� ��������"		)
DEFINE_Bits(RM	     	,2	,L"������� ��� �������� ����������� ��������"		)
DEFINE_Bits(STF	     	,4	,L"���� �������� ����������� ��������"				)



DEFINE_Bits(CYCLE_TS 	,0	,L"�� � ������ �������"								)
DEFINE_Bits(TPP_TS	 	,4	,L"��� �� ��"										)
DEFINE_Bits(WCROSS	 	,1	,L"�� ����������� �� ��"								)
DEFINE_Bits(WLINE	 	,3	,L"�� ����������� �� ��"								)
DEFINE_Bits(WTHICK	 	,2	,L"�� ����������� �� ��"								)



DEFINE_Bits(RCROSS	 	,8	,L"���������� ����������� � ��"						)
DEFINE_Bits(RESULT	 	,13	,L"���������"										)
DEFINE_Bits(REVERSE  	,12	,L"������"											)
DEFINE_Bits(RLINE	 	,10	,L"���������� ����������� � ��"						)
DEFINE_Bits(RTHICK	 	,9	,L"���������� ������������ � ��"						)
DEFINE_Bits(START	 	,11	,L"����"												)



//----------------------------------------------------------------------------------
void Inputs0Dlg::Do(HWND h)
{
	InputsTable<0> t;
	TL::foreach<InputsTable<0>::items_list, __compress_bits__>()(&t.items, &Singleton<InputsTable<0>>::Instance().items);
	if(TemplDialog<InputsTable<0>, TL::MkTlst<putsDlg_OkBtn, CancelBtn>::Result>(t).Do(h, L"�������� ��� �������� �����"))
	{
	}
}
void Inputs1Dlg::Do(HWND h)
{
	InputsTable<1> t;
	TL::foreach<InputsTable<1>::items_list, __compress_bits__>()(&t.items, &Singleton<InputsTable<1>>::Instance().items);
	if(TemplDialog<InputsTable<1>, TL::MkTlst<putsDlg_OkBtn, CancelBtn>::Result>(t).Do(h, L"�������� ��� �������� �����"))
	{
	}
}
//-----------------------------------------------------------------------------
/*
MIN_EQUAL_VALUE(Y0, 0 )
MAX_EQUAL_VALUE(Y0, 31)
MIN_EQUAL_VALUE(Y1, 0 )
MAX_EQUAL_VALUE(Y1, 31)
MIN_EQUAL_VALUE(Y2, 0 )
MAX_EQUAL_VALUE(Y2, 31)
MIN_EQUAL_VALUE(Y3, 0 )
MAX_EQUAL_VALUE(Y3, 31)
MIN_EQUAL_VALUE(Y4, 0 )
MAX_EQUAL_VALUE(Y4, 31) 

PARAM_TITLE(Y0, L"����� �� ������� Y0(����)")
PARAM_TITLE(Y1, L"����� �� ������� Y1(�����)")
PARAM_TITLE(Y2, L"��������� ��������")
PARAM_TITLE(Y3, L"Y3");
PARAM_TITLE(Y4, L"Y4");

template<>struct DlgSubItems<Y0, unsigned >: UpDownSubItem<Y0>{};
template<>struct DlgSubItems<Y1, unsigned >: UpDownSubItem<Y1>{};
template<>struct DlgSubItems<Y2, unsigned >: UpDownSubItem<Y2>{};
template<>struct DlgSubItems<Y3, unsigned >: UpDownSubItem<Y3>{};
template<>struct DlgSubItems<Y4, unsigned >: UpDownSubItem<Y4>{};
*/

void Outputs0Dlg::Do(HWND h)
{
	OutputsTable<0> t;
	TL::foreach<OutputsTable<0>::items_list, __compress_bits__>()(&t.items, &Singleton<OutputsTable<0>>::Instance().items);
	if(TemplDialog<OutputsTable<0>, TL::MkTlst<putsDlg_OkBtn, CancelBtn>::Result>(t).Do(h, L"�������� ��� ��������� �����"))
	{
	}
}
void Outputs1Dlg::Do(HWND h)
{
	OutputsTable<1> t;
	TL::foreach<OutputsTable<1>::items_list, __compress_bits__>()(&t.items, &Singleton<OutputsTable<1>>::Instance().items);
	if(TemplDialog<OutputsTable<1>, TL::MkTlst<putsDlg_OkBtn, CancelBtn>::Result>(t).Do(h, L"�������� ��� ��������� �����"))
	{
	}
}
//----------------------------------------------------------------------------
DO_NOT_CHECK(Descriptor1730_0)
PARAM_TITLE(Descriptor1730_0, L"���������� 0 ����� 1730")
DO_NOT_CHECK(Descriptor1730_1)
PARAM_TITLE(Descriptor1730_1, L"���������� 1 ����� 1730")
void Descriptor1730Dlg::Do(HWND h)
{
	Descriptor1730Table &t = Singleton<Descriptor1730Table>::Instance();
	if(TemplDialog<Descriptor1730Table>(t).Do(h, L"���������� ����� 1730"))
	{
		device1730_0.Destroy();
		device1730_1.Destroy();
		Sleep(500);
		if(!device1730_0.Init(t.items.get<Descriptor1730_0>().value))
		{
			MessageBox(h, L"�� ���� ������������ ����� 0 1730", L"������ !!!", MB_ICONERROR);
		}
		if(!device1730_1.Init(t.items.get<Descriptor1730_1>().value))
		{
			MessageBox(h, L"�� ���� ������������ ����� 0 1730", L"������ !!!", MB_ICONERROR);
		}
	}
}