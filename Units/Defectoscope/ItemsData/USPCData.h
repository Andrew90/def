#pragma once
#include "App.h"
#include "AppBase.h"

struct CommonItemData
{
	//int currentOffsetFrames;
	int currentOffsetZones;
	int offsets[App::zonesCount + 2];
};

template<class T>struct ItemData;

template<>struct ItemData<Cross>: CommonItemData
{
	double buffer[App::cross_count_sensors][App::zonesCount];	///<����������� ������ �������� �� �������� � �����
	char status[App::cross_count_sensors][App::zonesCount];	///< ������ ������ �� �������� � �����	
};

template<>struct ItemData<Long>: CommonItemData
{
	double buffer[App::long_count_sensors][App::zonesCount];	///<����������� ������ �������� �� �������� � �����
	char status[App::long_count_sensors][App::zonesCount];	///< ������ ������ �� �������� � �����	
};

template<>struct ItemData<Thickness>//: CommonItemData 
{
	int currentOffsetZones;
	double buffer[2][App::zonesCount];	///<����������� ������ �������� �� �������� � �����
	char status[App::zonesCount];	///< ������ ������ �� �������� � �����	
	void Clear()
	{
		memset(this, 0, sizeof(*this));
	}
};

struct RowData
{
	int currentOffset;//������� ������
	int currentFrames;//������� ������� ������
	unsigned timeFrames[1024 * 4];//�����
	int offsets[1024 * 4];//�������� ������
	short data[App::total_count_sensors][App::count_frames];
	void Clear();
	void SetData(ULONG *d, int count);
};