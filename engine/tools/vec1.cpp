#include <stdio.h>
#include "vec1.h"
#include <math.h>


/**************************************************
 * ���ܣ�����A��B��վ�����Լ�tag������վ��������ǩ����
 * ������@pAnc�����AB��վx��y����������ָ��
 *      @pDst�����tag��AB��վ����������ָ��
 *      @pPos: ���������tag������λ��
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

    //��tag��A��վ�ľ���Ϊ��׼
    dx = dstA*abs(A.x-B.x)/dstAB;
    dy = dstA*abs(A.y-B.y)/dstAB;
    posByA.x = (B.x > A.x)?(A.x + dx):(A.x - dx);
    posByA.y = (B.y > A.y)?(A.y + dy):(A.y - dy);\

    //��tag��B��վ�ľ���Ϊ��׼
    dx = dstB*abs(A.x-B.x)/dstAB;
    dy = dstB*abs(A.y-B.y)/dstAB;
    posByB.x = (B.x > A.x)?(B.x - dx):(B.x + dx);
    posByB.y = (B.y > A.y)?(B.y - dy):(B.y + dy);

    //������ƽ��ֵ
    *pPos = (posByA.x + posByB.x)/2;
    *(pPos+1) = (posByA.y + posByB.y)/2;
}

//��tag��A��׼�ľ���Ϊ��׼����tag����
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

//��tag��B��׼�ľ���Ϊ��׼����tag����
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
