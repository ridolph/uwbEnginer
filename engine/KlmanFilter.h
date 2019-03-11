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
    double _x_last;//状态值
    double _p_last;//协方差
    double _Q;//系统噪声
    double _R;//测量噪声
    int  _lastMsec;//上一次接收数据时刻，单位ms
    double _x_speed;//状态变化速度，预估下一状态。

    double _initQ;
    double _initR;
};







#endif
