#include "filters.h"
#include "Include/Dsp.h"

//! @brief ��� ��� ������� ���������� �� ��������
//! @param data - ������ � ��������
//! @param N - ������ �������
//! @param order - ������� �������
//! @param sampleRate - ������� �����
//! @param cutoffFrequency - ������� �����
//! @param centerFrequency ������� ������ �������
//! @param widthFrequency ������ �������
//! @param rippleDb ��������� � ������ �����������
//! @param type - ��� ������� 0 - LowPass,1 - HighPass,2 - BandPass,3 - BandStop
void ChebyshevI::Do(double *data,int N,
                                       int order,
                                       double sampleRate,
                                       double cutoffFrequency,
                                       double centerFrequency,
                                       double widthFrequency,
                                       double rippleDb,
                                       int type)
{
    switch(type)
    {
        case 0:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::LowPass<20>,1> filter;
            filter.setup(order,                 //�������
                         sampleRate,            //������� �������������
                         cutoffFrequency,       //������� �����
                         rippleDb);             //���������
            filter.process(N,&data);
            break;
        }
        case 1:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::HighPass<20>,1> filter;
            filter.setup(order,                 //�������
                         sampleRate,            //������� �������������
                         cutoffFrequency,       //������� �����
                         rippleDb);             //���������
            filter.process(N,&data);
            break;

        }
        case 2:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::BandPass<20>,1> filter;
            filter.setup(order,                 //�������
                         sampleRate,            //������� �����
                         centerFrequency,       //������� ������ ����������
                         widthFrequency,        //������ �������
                         rippleDb);             //���������
            filter.process(N,&data);
            break;
        }
        case 3:
        {
            Dsp::SimpleFilter<Dsp::ChebyshevI::BandStop<20>,1> filter;
            filter.setup(order,                 //�������
                         sampleRate,            //������� �����
                         centerFrequency,       //������� ������ ����������
                         widthFrequency,        //������ �������
                         rippleDb);             //���������
            filter.process(N,&data);
            break;
        }
    }
}

//! @brief ��� ��� ������� ���������� �� �����������
//! @param data - ������ � ��������
//! @param N - ������ �������
//! @param order - ������� �������
//! @param sampleRate - ������� �����
//! @param cutoffFrequency - ������� �����
//! @param centerFrequency - ������� ������ �������
//! @param widthFrequency - ������ �������
//! @param type - ��� ������� 0 - LowPass,1 - HighPass,2 - BandPass,3 - BandStop
void Butterworth::Do(double *data,int N,
                                     int order,
                                     double sampleRate,
                                     double cutoffFrequency,
                                     double centerFrequency,
                                     double widthFrequency,
                                     int type)
{
    switch(type)
    {

        case 0:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::LowPass<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         cutoffFrequency);  //������� �����

            filter.process(N,&data);
        }
        case 1:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::HighPass<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         cutoffFrequency);  //������� �����

            filter.process(N,&data);
        }
        case 2:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::BandPass<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         centerFrequency,   //������� ������
                         widthFrequency);   //������ �������

            filter.process(N,&data);
        }

        case 3:
        {
            Dsp::SimpleFilter <Dsp::Butterworth::BandStop<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         centerFrequency,   //������� ������
                         widthFrequency);   //������ �������

            filter.process(N,&data);
        }

    }
}
//! @brief ��� ��� ������� ���������� �� �����������
//! @param data - ������ � ��������
//! @param N - ������ �������
//! @param order - ������� �������
//! @param sampleRate - ������� �����
//! @param cutoffFrequency - ������� �����
//! @param centerFrequency - ������� ������ �������
//! @param widthFrequency - ������ �������
//! @param rippleDb - ��������� � ������ �����������
//! @param rolloff - ��������� � ������ ����������
//! @param type - ��� ������� 0 - LowPass,1 - HighPass,2 - BandPass,3 - BandStop
void Elliptic::Do(double *data,int N,
                                              int order,
                                              double sampleRate,
                                              double cutoffFrequency,
                                              double centerFrequency,
                                              double widthFrequency,
                                              double rippleDb,
                                              double rolloff,
                                              int type)
{
    switch(type)
    {
        case 0:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::LowPass<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         cutoffFrequency,   //������� �����
                         rippleDb,          //��������� � ������ �����������
                         rolloff);          //��������� � ������ ����������
            filter.process(N,&data);
            break;
        }

        case 1:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::HighPass<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         cutoffFrequency,   //������� �����
                         rippleDb,          //��������� � ������ �����������
                         rolloff);          //��������� � ������ ����������
            filter.process(N,&data);
            break;
        }

        case 2:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::BandPass<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         centerFrequency,   //������� ������
                         widthFrequency,    //������ �������
                         rippleDb,          //��������� � ������ �����������
                         rolloff);          //��������� � ������ ����������

            filter.process(N,&data);
            break;
        }
        case 3:
        {
            Dsp::SimpleFilter < Dsp::Elliptic::BandStop<20>,1> filter;
            filter.setup(order,             //�������
                         sampleRate,        //������� �����
                         centerFrequency,   //������� ������
                         widthFrequency,    //������ �������
                         rippleDb,          //��������� � ������ �����������
                         rolloff);          //��������� � ������ ����������

            filter.process(N,&data);
            break;
        }
    }
}
