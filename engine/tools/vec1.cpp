#include <stdio.h>
#include "vec1.h"
#include <math.h>


/**************************************************
 * 功能：根据A、B基站坐标以及tag到两基站距离计算标签坐标
 * 参数：@pAnc：存放AB基站x、y坐标的数组的指针
 *      @pDst：存放tag到AB基站距离的数组的指针
 *      @pPos: 计算出来的tag坐标存放位置
***************************************************/
void location_2P(double *pAnc, double *pDst, double *pPos)
{
    VEC1 A ,B, posByA, posByB ;
    double dx, dy;
    double dstA = 0, dstB = 0, dstAB;

    if((NULL == pAnc)||(NULL == pDst)||(NULL == pPos))
    {
        return;
    }

    A.x = *pAnc;
    A.y = *(pAnc + 1);
    B.x = *(pAnc + 2);
    B.y = *(pAnc + 3);
    dstA = *pDst;
    dstB = *(pDst + 1);

    dstAB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

    if(0 == dstAB)
    {
       *pPos = A.x;
       *(pPos+1) = A.y;

       return;
    }

    if(A.x == B.x)
    {
        posByA.x = A.x;
        posByA.y = (A.y > B.y)?(A.y - dstA):(A.y + dstA);
        posByB.x = B.x;
        posByB.y = (B.y > A.y)?(B.y - dstB):(B.y + dstB);

        *pPos = (posByA.x + posByB.x)/2;
        *(pPos+1) = (posByA.y + posByB.y)/2;

        return;
    }

    if(A.y == B.y)
    {
        posByA.x = (A.x > B.x)?(A.x - dstA):(A.x + dstA);
        posByA.y = A.y;
        posByB.x = (B.x > A.x)?(B.x - dstB):(B.x + dstB);
        posByB.y = B.y;

        *pPos = (posByA.x + posByB.x)/2;
        *(pPos+1) = (posByA.y + posByB.y)/2;

        return;
    }

    //以tag到A基站的距离为基准
    dx = dstA*abs(A.x-B.x)/dstAB;
    dy = dstA*abs(A.y-B.y)/dstAB;
    posByA.x = (B.x > A.x)?(A.x + dx):(A.x - dx);
    posByA.y = (B.y > A.y)?(A.y + dy):(A.y - dy);\

    //以tag到B基站的距离为基准
    dx = dstB*abs(A.x-B.x)/dstAB;
    dy = dstB*abs(A.y-B.y)/dstAB;
    posByB.x = (B.x > A.x)?(B.x - dx):(B.x + dx);
    posByB.y = (B.y > A.y)?(B.y - dy):(B.y + dy);

    //两者求平均值
    *pPos = (posByA.x + posByB.x)/2;
    *(pPos+1) = (posByA.y + posByB.y)/2;
}

//以tag到A基准的距离为基准计算tag坐标
void location_2P_ByA(double *pAnc, double *pDst, double *pPos)
{
    VEC1 A ,B ;
    double dx, dy;
    double dstA = 0, dstB = 0, dstAB;
    A.x = *pAnc;
    A.y = *(pAnc + 1);
    B.x = *(pAnc + 2);
    B.y = *(pAnc + 3);

    dstA = *pDst;
    dstB = *(pDst + 1);

    dstAB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

    if(0 == dstAB)
    {
       *pPos = A.x;
       *(pPos+1) = A.y;

       return;
    }

    if(A.x == B.x)
    {
        *pPos = A.x;
        *(pPos+1) = (A.y > B.y)?(A.y - dstA):(A.y + dstA);

        return;
    }

    if(A.y == B.y)
    {
        *pPos = (A.x > B.x)?(A.x - dstA):(A.x + dstA);
        *(pPos+1) = A.y;

        return;
    }

    dx = dstA*abs(A.x-B.x)/dstAB;
    dy = dstA*abs(A.y-B.y)/dstAB;

    *pPos = (B.x > A.x)?(A.x + dx):(A.x - dx);
    *(pPos+1) = (B.y > A.y)?(A.y + dy):(A.y - dy);
}

//以tag到B基准的距离为基准计算tag坐标
void location_2P_ByB(double *pAnc, double *pDst, double *pPos)
{

    VEC1 A ,B ;
    double dx, dy;
    double dstA = 0, dstB = 0, dstAB;
    A.x = *pAnc;
    A.y = *(pAnc + 1);
    B.x = *(pAnc + 2);
    B.y = *(pAnc + 3);

    dstA = *pDst;
    dstB = *(pDst + 1);

    dstAB = sqrt(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
    if(0 == dstAB)
    {
       *pPos = A.x;
       *(pPos+1) = A.y;

       return;
    }

    if(B.x == A.x)
    {
        *pPos = B.x;
        *(pPos+1) = (B.y > A.y)?(B.y - dstB):(B.y + dstB);

        return;
    }

    if(B.y == A.y)
    {
        *pPos = (B.x > A.x)?(B.x - dstB):(B.x + dstB);
        *(pPos+1) = B.y;

        return;
    }

    dx = dstB*abs(A.x-B.x)/dstAB;
    dy = dstB*abs(A.y-B.y)/dstAB;
    *pPos = (B.x > A.x)?(B.x - dx):(B.x + dx);
    *(pPos+1) = (B.y > A.y)?(B.y - dy):(B.y + dy);
}
