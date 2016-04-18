#pragma once
#include "typelist.hpp"
//#include "ParamDlg.hpp"

#define DEFINE_Bits(z, def_val, txt) struct z\
{\
	typedef unsigned type_value;\
	type_value value;\
	const type_value default_value;\
	const wchar_t *name(){return L#z;}\
	z() : value(def_val), default_value(def_val) {}\
};

DEFINE_Bits(BASE_TS	 	,1 << 4	,L"������ ����"                                      )
DEFINE_Bits(CONTROL	 	,1 << 13	,L"�������� �� �����������"							)
DEFINE_Bits(PCHA	 	,1 << 9	,L"������ � � ���������� ����������� ��������"		)
DEFINE_Bits(PCHB	 	,1 << 8	,L"������ B � ���������� ����������� ��������"		)
DEFINE_Bits(PCHRUN	 	,1 << 10	,L"������ RUN � ���������� ����������� ��������"		)
DEFINE_Bits(READY	 	,1 << 12	,L"���������� �� �����������"						)

DEFINE_Bits(SQfirst	 	, 1 << 7	,L"������ �� ������ ����")

DEFINE_Bits(SQcrossIN	 	,1 << 0	,L"������ �� ����� ������ ����������� ��������"		)
DEFINE_Bits(SQcrossOUT	 	,1 << 1	,L"������ �� ������ ������ ����������� ��������"		)

DEFINE_Bits(SQthickIN	 	,1 << 5	,L"������ �� ����� �����������"		)
DEFINE_Bits(SQthickOUT	 	,1 << 6	,L"������ �� ������ �����������"		)

DEFINE_Bits(SQlongIN	 	,1 << 2	,L"������ �� ����� � ������ ����������� ��������"	)
DEFINE_Bits(SQlongOUT	 	,1 << 3	,L"������ �� ������ ������ ����������� ��������"		)
DEFINE_Bits(ZU	     	,1 << 11	,L"���� ����������"									)
template<int>struct InputsTable;
template<int>struct OutputsTable;
template<>struct InputsTable<0>
{
	typedef TL::MkTlst<	
		BASE_TS
		, CONTROL
		, PCHA	
		, PCHB	
		, PCHRUN	
		, READY	
		, SQcrossIN	
		, SQcrossOUT
		, SQthickIN
		, SQthickOUT
		, SQlongIN	
		, SQlongOUT	
		, SQfirst
		, ZU	   		
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Inputs0Table";}
};

DEFINE_Bits(CYCLE	 	,1 << 8	,L"������ ���� � ����������"							)
DEFINE_Bits(POWPCH	 	,1 << 0	,L"��������� ������� ���������� ����������� ��������")
DEFINE_Bits(POWSU	 	,1 << 5	,L"������� �� ����������� ��������"					)
DEFINE_Bits(RH	     	,1 << 3	,L"������� ��� �������� ����������� ��������"		)
DEFINE_Bits(RL	     	,1 << 1	,L"������� ��� �������� ����������� ��������"		)
DEFINE_Bits(RM	     	,1 << 2	,L"������� ��� �������� ����������� ��������"		)
DEFINE_Bits(STF	     	,1 << 4	,L"���� �������� ����������� ��������"				)

template<>struct OutputsTable<0>
{
	typedef TL::MkTlst<	
		CYCLE
		, POWPCH
		, POWSU
		, RH	  
		, RL	  
		, RM	  
		, STF	  
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Outputs0Table";}
};

DEFINE_Bits(CYCLE_TS 	,1 << 0	,L"�� � ������ �������"								)
DEFINE_Bits(TPP_TS	 	,1 << 4	,L"��� �� ��"										)
DEFINE_Bits(WCROSS	 	,1 << 1	,L"�� ����������� �� ��"								)
DEFINE_Bits(WLINE	 	,1 << 3	,L"�� ����������� �� ��"								)
DEFINE_Bits(WTHICK	 	,1 << 2	,L"�� ����������� �� ��"								)

template<>struct InputsTable<1>
{
	typedef TL::MkTlst<	
		CYCLE_TS 
		, TPP_TS	 
		, WCROSS	 
		, WLINE	 
		, WTHICK	 
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Inputs1Table";}
};

DEFINE_Bits(RCROSS	 	,1 << 8	,L"���������� ����������� � ��"						)
DEFINE_Bits(RESULT	 	,1 << 13	,L"���������"										)
DEFINE_Bits(REVERSE  	,1 << 12	,L"������"											)
DEFINE_Bits(RLINE	 	,1 << 10	,L"���������� ����������� � ��"						)
DEFINE_Bits(RTHICK	 	,1 << 9	,L"���������� ����������� � ��"						)
DEFINE_Bits(START	 	,1 << 11	,L"����"												)

template<>struct OutputsTable<1>
{
	typedef TL::MkTlst<	
		RCROSS	
		, RESULT	
		, REVERSE 
		, RLINE	
		, RTHICK	
		, START	
	>::Result items_list;
	typedef TL::Factory<items_list> TItems;
	TItems items;
	const wchar_t *name(){return L"Outputs1Table";}
};

#undef DEFINE_Bits

