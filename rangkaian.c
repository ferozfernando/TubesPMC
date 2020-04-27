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

void rangkaian3(double v1[], double v2[], double R, double C1, double C2, double Src, int i){
	double G1 = C1/T;
	double G2 = C2/T;
	double I1 = C1*(v2[i]-v1[i])/T;
	double I2 = C2*(v1[i])/T;
	v1[i+1]   = (Src+I2)/G2;
	v2[i+1]	  = (Src + I1 + (1/R+G1)*v1[i+1])/(1/R + G1);
}

void rangkaian3V(double v1[], double v2[], double R, double C1, double C2, double Src, int i){
	double G1 = C1/T;
	double G2 = C2/T;
	double I1 = C1*(v2[i]-v1[i])/T;
	double I2 = C2*(v1[i])/T;
	v2[i+1]	  = Src;
	v1[i+1]	  = (I2-I1+(1/R+G1)*v2[i+1])/(1/R+G1+G2);
}

void rangkaian4(double v2[],double R1, double R2, double C, double Src, int i){
	double Ga = C/T;
	double Ia = C*(Src-v2[i])/T;
	v2[i+1]	  = (Src*(Ga+(1/R1))-Ia)/(Ga+(1/R1)+(1/R2));
}

void rangkaian8(double v1[], double v2[], double v3[], double R1, double R2, double C1, double C2, double src, int i){
	double g1 = C1/T;
	double g2 = C2/T;
	double i1 = C1*(v2[i]-v3[i])/T;
	double i2 = C2*(v3[i])/T;
	v3[i+1] = (src+i2)/(g2+1/R2);
	v2[i+1] = (src+i1+g1*v3[i+1])/g1;
	v1[i+1] = (src+v2[i+1]/R1)*R1;
}

void rangkaian8V(double v1[], double v2[], double v3[], double R1, double R2, double C1, double C2, double src, int i){
	double g1 = C1/T;
	double g2 = C2/T;
	double i1 = C1*(v2[i]-v3[i])/T;
	double i2 = C2*(v3[i])/T;
	double temp = g1/(g1+g2+1/R1);
	v1[i+1] = src;
	v2[i+1] = (temp*(i2-i1)+i1+(v1[i+1]/R1))/(g1+(1/R1)-g1*temp);
	v3[i+1] = (i1+(v1[i+1]/R1)-(v2[i+1]*(1/R1+g1)))/(-g1);
	printf("%lf\n", v1[i+1]);
}