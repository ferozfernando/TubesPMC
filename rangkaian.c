#include <math.h>
#include<stdio.h>
#define T 0.0001

double genSin(double A, double f, double phase, double DC, double time){
    return A*sin(2*M_PI*f*time + phase) + DC;
}

double genSqr(double A, double f, double phase, double DC, double time){
    if(sin(2*M_PI*f*time + phase) < 0){
        return -A+DC;
    }
    else{
        return A + DC;
    }
}

// double genTri(double A, double f, double phase, double DC, double time){
//         //Belum kepikiran caranya//
// }

void rangkaian1(double *v, double R, double C, double src, int i){
	double Ia = C*v[i]/T;
	double Ga = C/T;
  	v[i+1] 	  = (src+Ia*R)/(1+Ga*R);
  	// printf("%lf\n",v[i]);
}

void rangkaian2(double v[], double R, double C, double src, int i){
	double Ia = C*v[i]/T;
	double Ga = C/T;
  	v[i+1]    = (src+Ia)/(Ga+(1/R));
}

void rangkaian3(double v1[],double R, double C1, double C2, double Src[], int i){
	double G1 = C1/T;
	double G2 = C2/T;
	double I1 = C1*(Src[i-1]-v1[i])/T;
	double I2 = C2*(v1[i])/T;
	v1[i+1]   = (I2-I1+Src[i]*(G1+1/R))/(G1+G2+1/R);
}

void rangkaian4(double v2[],double R1, double R2, double C, double Src, int i){
	double Ga = C/T;
	double Ia = C*(Src-v2[i])/T;
	v2[i+1]	  = (Src*(Ga+(1/R1))-Ia)/(Ga+(1/R1)+(1/R2));
}