#include <stdio.h>
#include<stdlib.h>
#define T 0.0001

void mainmenu(){
    printf("  _____   _____    _____ _                 _       _             \n");
    printf(" |  __ \\ / ____|  / ____(_)               | |     | |            \n");
    printf(" | |__) | |      | (___  _ _ __ ___  _   _| | __ _| |_ ___  _ __ \n");
    printf(" |  _  /| |       \\___ \\| | '_ ` _ \\| | | | |/ _` | __/ _ \\| '__|\n");
    printf(" | | \\ \\| |____   ____) | | | | | | | |_| | | (_| | || (_) | |   \n");
    printf(" |_|  \\_\\\\_____| |_____/|_|_| |_| |_|\\__,_|_|\\__,_|\\__\\___/|_|   \n");
    printf("                                                                 \n");
}

void circuitList(){
    printf("Circuit List: \n");
    printf("1. RC Series\n");
    printf("2. RC Parallel\n");
    printf("3. (R1 || C1) -- C2\n");
    printf("4. --Isi Disini--\n");
    printf("5. --Isi Disini--\n");
    printf("0. Exit\n");
    printf("Your Choice: ");
}

void sourceList(){
    printf("Choose Source: \n");
    printf("1. Voltage Source \n");
    printf("2. Current Source \n");
    printf("Your Choice: ");
}

void signList(){
    printf("Choose Source Signal: \n");
    printf("1. Constant \n");
    printf("2. Sinusoid \n");
    printf("3. Square \n");
   // printf("4. Triangle \n");
    printf("Your Choice: ");
}

void sourceType(){
    printf("Choose Source Type: \n");
    printf("1. Voltage Source \n");
    printf("2. Current Source \n");
    printf("Your Choice: ");
}

void InputAC(double *A, double *f, double *phase, double *DCoff){
    printf("Amplitude value: ");
    scanf("%lf", A);
    printf("Frequency value: ");
    scanf("%lf", f);
    printf("Phase value: ");
    scanf("%lf", phase);
    printf("DC Offset value: ");
    scanf("%lf", DCoff);
}

void printV(char filename[], double *vpos, double vneg[], int n){
    FILE *filep = fopen(filename, "w");
    double V;
    double time = 0;
    fprintf (filep, "T,V\n");
    for(int i = 0; i<n; i++){
        V = vpos[i]-vneg[i];
        fprintf(filep, "%lf,%lf\n", time, V);
        time +=T;
    }
    fclose(filep);
}
void printV0(char filename[], double *vpos, int n){
    FILE *filep = fopen(filename, "w");
    double V;
    double time = 0;
    fprintf (filep, "T,V\n");
    for(int i = 0; i<n; i++){
        V = vpos[i];
        fprintf(filep, "%lf,%lf\n", time, V);
        time +=T;
    }
    fclose(filep);
}

void printIR(char filename[], double vpos[], double vneg[], double R, int n){
    FILE *filep = fopen(filename, "w");
    double time = 0;
    double I;
    fprintf (filep, "T,I\n");
    for(int i = 0; i<n; i++){
        I = (vpos[i]-vneg[i])/R;
        fprintf(filep,"%lf,%lf\n", time,I);
        time +=T;
    }
    fclose(filep);
}

void printIR0(char filename[], double vpos[], double R, int n){
    FILE *filep = fopen(filename, "w");
    double time = 0;
    double I;
    fprintf (filep, "T,I\n");
    for(int i = 0; i<n; i++){
        I = vpos[i]/R;
        fprintf(filep,"%lf,%lf\n", time,I);
        time +=T;
    }
    fclose(filep);
}

void printIC(char filename[], double vpos[], double vneg[], double C, int n){
    FILE*filep = fopen(filename, "w");
    double time = 0;
    double I;
    fprintf (filep, "T,I\n");
    for(int i = 0; i<n-1; i++){
        I = (vpos[i+1]-vneg[i+1]-vpos[i]+vneg[i])*C/T;
        fprintf(filep,"%lf,%lf\n", time,I);
        time +=T;
    }
    fclose(filep);
}

void printIC0(char filename[], double vpos[], double C, int n){
    FILE*filep = fopen(filename, "w");
    double time = 0;
    double I;
    fprintf (filep, "T,I\n");
    for(int i = 0; i<n-1; i++){
        I = (vpos[i+1]-vpos[i])*C/T;
        fprintf(filep,"%lf,%lf\n", time,I);
        time +=T;
    }
    fclose(filep);
}

void graph(){                                      ///Fungsi untuk membuat grafik
    system("python graph.py");                    ///Panggil python untuk membuat grafik
}
