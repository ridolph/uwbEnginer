#ifndef VEC1_H
#define VEC1_H


typedef struct
{
    double x;
    double y;
}VEC1;


void location_2P(double *pAnc, double *pDst, double *pPos);
void location_2P_ByA(double *pAnc, double *pDst, double *pPos);
void location_2P_ByB(double *pAnc, double *pDst, double *pPos);




#endif // VEC1_H
