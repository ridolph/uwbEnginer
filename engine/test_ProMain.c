
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#include"location_4P.h"

#define  M    4  // ���Ƶ㣨��վ����
#define  ErrRan  0.5 // ����Ŷ������
#define  Num  1000 // �Ŷ�����


int main()
{
	int  i, j;
	double  Xi, Yi, Zi;
	double  d0[M] = {0.0};
	double  d[M];
	double  Ran[Num*M]; // 0��1�������
	//double  P_result[Num*3]; // ���¼������ P �����꣨ȫ����
	double  P2[3]; // ���¼������ P �����꣨���Σ�
	
	// 1. ���Ƶ㣨��վ��CtrPoints�͹۲�� P ���궨�� [x,y,z] 
	/*
	A = [0 0 0];
	B = [30 0 0];
	C = [30 50 0];
	D = [0 50 0];
	E = [0 0 20];
	F = [30 0 20];
	G = [30 50 20];
	H = [0 50 20];
	*/
	double CtrPoints[M*3] = { 0.0,  0.0,  20.0,    // E  
                                  30.0, 0.0,  20.0,    // F
                                  30.0, 50.0, 20.0,    // G
                                  0.0,  50.0, 20.0 };  // H
	double P[3] = {28.0, 37.0, 15.0};


	// 3. ���� P �����վ�ľ���
	
	for(i=0; i<M; i++)
	{
	    Xi = CtrPoints[i*3];
	    Yi = CtrPoints[i*3+1];
	    Zi = CtrPoints[i*3+2];

            d0[i] = sqrt((Xi-P[0])*(Xi-P[0])+(Yi-P[1])*(Yi-P[1])+(Zi-P[2])*(Zi-P[2]));;
    	}


	// 4. �� d0 ������������ P_result ������

	srand( (unsigned)time( NULL ) );  // �����������
	for (i =0;i<Num*M;i++)
	{
	    Ran[i] = rand()/(double)RAND_MAX; // RAND_MAX��������ֵ
	}

	for (j=0; j<Num; j++)
	{
	    // Ϊ d ��������Ŷ�
	    for (i=0; i<M; i++)
	    {
	        d[i] = d0[i]+(2*Ran[j*M+i]-1.0)*ErrRan;
	    }

	    // ����4�㶨λ�㷨���� P_result 
	    P2[0] = 0.0;
	    P2[1] = 0.0;
	    P2[2] = 0.0;

	    location_4P (CtrPoints, d, P2); // #############

	//    P_result[j*3]   = P2[0];
	//    P_result[j*3+1] = P2[1];
	//    P_result[j*3+2] = P2[2];

	    printf( "%5d    %5.2f %5.2f %5.2f\n", j+1, P2[0],P2[1],P2[2]);

	}


	return 0;

}
