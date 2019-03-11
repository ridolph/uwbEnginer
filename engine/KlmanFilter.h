#ifndef KLMANFILTER_H
#define KLMANFILTER_H

class  KlmanFilter
{
public :
    KlmanFilter();
    KlmanFilter(double q, double r);
    ~KlmanFilter();
    void  clear();
    double update(double z_measure);

private:
    double _x_last;//״ֵ̬
    double _p_last;//Э����
    double _Q;//ϵͳ����
    double _R;//��������
    int  _lastMsec;//��һ�ν�������ʱ�̣���λms
    double _x_speed;//״̬�仯�ٶȣ�Ԥ����һ״̬��

    double _initQ;
    double _initR;
};







#endif
