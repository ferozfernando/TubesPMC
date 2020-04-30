#include <stdio.h>
#include<stdlib.h>
#define T 0.00001

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
    printf("4. (R1 || C1) -- R2\n");
    printf("5. (R1 || C1) -- (R2 || C2)\n");
    printf("6. C1 -- ( (R1 -- C2) || R2 )\n");
    printf("7. R1 -- ( (R1 -- C2) || C2 )\n");
    printf("8. R1 -- C1 -- ( R1 || C2)\n");
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

void sourceType(int *srcType){
    printf("Choose Source Type: \n");
    printf("1. Voltage Source \n");
    printf("2. Current Source \n");
    printf("Your Choice: ");
    scanf("%d", srcType);
    while(!(*srcType == 1 || *srcType == 2)){
        printf("Invalid input!");
        sourceType(srcType);
        scanf("%d", srcType);
    }
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

void menuRC(double *R1, double *C1, double *t){
    printf("Input R: ");
    scanf("%lf", R1);
    printf("Input C: ");
    scanf("%lf", C1);
    printf("\nInput duration (in s): ");
    scanf("%lf", t);
}

void menuRRC(double *R1, double *R2, double *C1, double *t){
    printf("Input R1: ");
    scanf("%lf", R1);
    printf("Input R2: ");
    scanf("%lf", R2);
    printf("Input C1: ");
    scanf("%lf", C1);
    printf("\nInput duration (in s): ");
    scanf("%lf", t);
}

void menuRCC(double *R1, double *C1, double *C2, double *t){
    printf("Input R: ");
    scanf("%lf", R1);
    printf("Input C1: ");
    scanf("%lf", C1);
    printf("Input C2: ");
    scanf("%lf", C2);
    printf("\nInput duration (in s): ");
    scanf("%lf", t);
}

void menuRRCC(double *R1, double *R2, double *C1, double *C2, double *t){
    printf("Input R1: ");
    scanf("%lf", R1);
    printf("Input R2: ");
    scanf("%lf", R2);
    printf("Input C1: ");
    scanf("%lf", C1);
    printf("Input C2: ");
    scanf("%lf", C2);
    printf("\nInput duration (in s): ");
    scanf("%lf", t);
}

void outRC(){
    printf("Choose output: \n");
    printf("1. V1 \n");
    printf("2. I(R) \n");
    printf("3. I(C) \n");
    printf("0. Back\n");
    printf("Your choice: ");
}

void outRRC(){
    printf("Choose output: \n");
    printf("1. V(R1) \n");
    printf("2. V(R2) \n");
    printf("3. V(C)  \n");
    printf("4. I(R1) \n");
    printf("5. I(R2) \n");
    printf("6. I(C)  \n");
    printf("0. Back\n");
    printf("Your choice: ");
}

void outRCC(){
    printf("Choose output: \n");
    printf("1. V(R)  \n");
    printf("2. V(C1) \n");
    printf("3. V(C2) \n");
    printf("4. I(R)  \n");
    printf("5. I(C1) \n");
    printf("6. I(C2) \n");
    printf("0. Back\n");
    printf("Your choice: ");
}

void outRRCC(){
    printf("Choose output: \n");
    printf("1. V(R1)  \n");
    printf("2. V(R2) \n");
    printf("3. V(C1) \n");
    printf("4. V(C2)  \n");
    printf("5. I(R1) \n");
    printf("6. I(R2) \n");
    printf("7. I(C1) \n");
    printf("8. I(C2) \n");
    printf("0. Back\n");
    printf("Your choice: ");
}

void graph(){                                      ///Fungsi untuk membuat grafik
    system("python3 graph.py");                    ///Panggil python untuk membuat grafik
}
