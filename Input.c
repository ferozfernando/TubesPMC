#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rangkaian.h"
#include "tampilan.h"
#define T 0.0001

int main(){
    int current_menu;
    int signal;
    int current_output = 0;
    char filename[100];
    double temp;
    double A;
    double f;
    double phase;
    double DCoff;
    double source;
    double R1;
    double R2;
    double C1;
    double C2;
    double time;
    double t;
    double n;
    double *v2o;
    double *v2;
    double *v3o;
    double *v3;
    double *vo;
    double *v;
    double *vsigo;
    double *vsig;
    
    do {
        mainmenu();
        circuitList();
        system("python3 menu.py");
        scanf("%d", &current_menu);
        vo      = (double *)malloc(sizeof(double));
        vsigo   = (double *)malloc(sizeof(double));
        v2o     = (double *)malloc(sizeof(double));
        v3o     = (double *)malloc(sizeof(double));
        *vo     = 0;
        *v2o    = 0;
        *v3o    = 0;
        *vsigo  = 0;

        switch(current_menu)
        {
            case 1:
                do{
                signList();
                scanf("%d", &signal);
                switch(signal)
                {
                    case 2:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C: ");
                        scanf("%lf", &C1);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        time = 0;
                        source = genSin(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            rangkaian1(v, R1, C1, source, i);
                            vsig[i] = source;
                            time += T;
                            source = genSin(A,f,phase,DCoff,time);
                        }
                    break;

                    case 1:
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C: ");
                        scanf("%lf", &C1);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian1(v, R1, C1, A, i);
                            vsig[i] = A;
                        }
                    break;

                    case 3:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C: ");
                        scanf("%lf", &C1);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        time = 0;
                        source = genSqr(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            rangkaian1(v, R1, C1, source, i);
                            vsig[i] = source;
                            time += T;
                            source = genSqr(A,f,phase,DCoff,time);
                        }
                    break;

                    default:
                        printf("invalid input!\n");
                }
                }while(signal<1 || signal >3);

                do {
                    printf("Choose output: \n");
                    printf("1. V1 \n");
                    printf("2. I(R) \n");
                    printf("3. I(C) \n");
                    printf("0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &current_output);
                    switch(current_output){
                        case 1:
                            printV0("graph.csv", v, n);
                            graph();
                            break;
                        case 2:
                            printIR("graph.csv", vsig, v, R1, n);
                            graph();
                            break;

                        case 3:
                            printIC0("graph.csv", v, C1, n);
                            graph();
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid Input\n");
                            break;
                        }
                } while (current_output != 0);
                break;

            case 2:
                do{
                signList();
                scanf("%d", &signal);
                switch(signal)
                {
                    case 1:
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C: ");
                        scanf("%lf", &C1);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian2(v, R1, C1, A, i);
                            vsig[i] = A;
                        }
                    break;

                    case 2:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C: ");
                        scanf("%lf", &C1);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        time = 0;
                        source = genSin(A,f,phase,DCoff,time);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian2(v, R1, C1, source, i);
                            vsig[i] = source;
                            time += T;
                            source = genSin(A,f,phase,DCoff,time);
                        }
                    break;

                    case 3:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C: ");
                        scanf("%lf", &C1);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        time = 0;
                        source = genSqr(A,f,phase,DCoff,time);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian2(v, R1, C1, source, i);
                            vsig[i] = source;
                            time += T;
                            source = genSqr(A,f,phase,DCoff,time);
                        }
                    break;

                    default:
                        printf("Invalid Input!\n");
                        break;
                }
                }while(signal<1 || signal >3);

                do {
                    printf("Choose output: \n");
                    printf("1. V1 \n");
                    printf("2. I(R) \n");
                    printf("3. I(C) \n");
                    printf("0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &current_output);
                    switch(current_output){
                        case 1:
                            printV0("graph.csv", v, n);
                            graph();
                            break;

                        case 2:
                            printIR("graph.csv", vsig, v, R1, n);
                            graph();
                            break;

                        case 3:
                            printIC0("graph.csv", v, C1, n);
                            graph();
                            break;

                        case 0:
                            break;
                        
                        default:
                            printf("Invalid Input!\n");
                            break;
                    }
                } while (current_output != 0);
                break;

            case 3:
                do{
                signList();
                scanf("%d", &signal);
                switch(signal)
                {
                    case 1:
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C1: ");
                        scanf("%lf", &C1);
                        printf("Input C2: ");
                        scanf("%lf", &C2);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian3(v,R1,C1,C2,vsig,i);
                            vsig[i] = A;
                        }
                    break;

                    case 2:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C1: ");
                        scanf("%lf", &C1);
                        printf("Input C2: ");
                        scanf("%lf", &C2);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        time = 0;
                        vsig[0] = genSin(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            rangkaian3(v,R1,C1,C2,vsig,i);
                            time += T;
                            vsig[i+1] = genSin(A,f,phase,DCoff,time);
                        }
                    break;

                    case 3:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R: ");
                        scanf("%lf", &R1);
                        printf("Input C1: ");
                        scanf("%lf", &C1);
                        printf("Input C2: ");
                        scanf("%lf", &C2);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        time = 0;
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian3(v,R1,C1,C2,vsig,i);
                            time += T;
                            vsig[i+1] = genSqr(A,f,phase,DCoff,time);
                        }
                    break;
                    

                    default:
                        printf("invalid input!");
                        break;
                }
                }while(signal < 1 || signal >3);
                do {
                    printf("Choose output: \n");
                    printf("1. V(C1) \n");
                    printf("2. V(C2) \n");
                    printf("3. I(R) \n");
                    printf("4. I(C1) \n");
                    printf("5. I(C2) \n");
                    printf("0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &current_output);
                    switch(current_output){
                        case 1:
                            printV("graph.csv", vsig, v, n);
                            graph();
                            break;

                        case 2:
                            printV0("graph.csv", v, n);
                            graph();
                            break;

                        case 3:
                            printIR("graph.csv", vsig, v, R1, n);
                            graph();
                            break;

                        case 4:
                            printIC("graph.csv", vsig, v, C1, n);
                            graph();
                            break;

                        case 5:
                            printIC0("graph.csv", v, C2, n);
                            graph();
                            break;

                        case 0:
                            break;

                        default:
                            printf("Invalid Input!\n");
                            break;
                    }
                } while (current_output != 0);
                break;

            case 0:
                break;
                
            default:
                printf("Invalid Input!\n\n");
                break;
        }
    } while (current_menu != 0);
    free(v);
    free(vsig);
    free(v2o);
    free(v3o);
}
