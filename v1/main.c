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
        //system("python3 menu.py");
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
            ///RANGKAIAN 1
            case 1:
                do{
                signList();
                scanf("%d", &signal);
                switch(signal)
                {
                    case 1:
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        menuRC(&R1, &C1, &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian1(v, R1, C1, A, i);
                            vsig[i] = A;
                        }
                    break;

                    case 2:
                        InputAC(&A, &f, &phase, &DCoff);
                        menuRC(&R1, &C1, &t);
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

                    case 3:
                        InputAC(&A, &f, &phase, &DCoff);
                        menuRC(&R1, &C1, &t);
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
                    outRC();
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

            ///RANGKAIAN 2
            case 2:
                do{
                signList();
                scanf("%d", &signal);
                switch(signal)
                {
                    case 1:
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        menuRC(&R1, &C1, &t);
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
                        menuRC(&R1, &C1, &t);
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
                        menuRC(&R1, &C1, &t);
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
                    outRC();
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

            ///RANGKAIAN 3
            case 3:
                do{
                signList();
                scanf("%d", &signal);
                switch(signal)
                {
                    case 1: ///KONSTAN
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        menuRCC(&R1, &C1, &C2, &t);
                        n = t/T;
                        v = (double *)realloc(vo, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian3(v,R1,C1,C2,vsig,i);
                            vsig[i] = A;
                        }
                    break;

                    case 2: ///SINUSOID
                        InputAC(&A, &f, &phase, &DCoff);
                        menuRCC(&R1, &C1, &C2, &t);
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

                    case 3: ///KOTAK
                        InputAC(&A, &f, &phase, &DCoff);
                        menuRCC(&R1, &C1, &C2, &t);
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
                    outRCC();
                    scanf("%d", &current_output);
                    switch(current_output){
                        case 1: ///VR
                        case 2: ///VC1
                            printV("graph.csv", vsig, v, n);
                            graph();
                            break;
                        case 3: ///VC2
                            printV0("graph.csv", v, n);
                            graph();
                            break;

                        case 4: ///IR
                            printIR("graph.csv", vsig, v, R1, n);
                            graph();
                            break;

                        case 5: ///IC1
                            printIC("graph.csv", vsig, v, C1, n);
                            graph();
                            break;

                        case 6: ///IC2
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

            ///RANGKAIAN 4
            case 4:
            signList();
            scanf ("%d", &signal);
                do{
                    switch(signal){
                        ///KONSTAN
                        case 1:
                            printf("Amplitude value: ");
                            scanf("%lf", &A);
                            menuRRC(&R1,&R2,&C1,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            for (int i=0; i<n-1; i++){
                                rangkaian4(v2,R1,R2,C1,vsig,i);
                                vsig[i] = A;
                            }
                        break;

                        case 2:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRC(&R1,&R2,&C1,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSin(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                rangkaian4(v2,R1,R2,C1,vsig,i);
                                time += T;
                                vsig[i+1] = genSin(A,f,phase,DCoff,time);
                            }
                        break;

                        case 3:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRC(&R1,&R2,&C1,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSqr(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                rangkaian4(v2,R1,R2,C1,vsig,i);
                                time += T;
                                vsig[i+1] = genSqr(A,f,phase,DCoff,time);
                            }
                        break;

                        default:
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(signal < 1 || signal >3);

                do{
                    outRRC();
                    scanf("%d", &current_output);
                    switch (current_output){
                        case 1: ///VR1
                        case 3: ///VC
                            printV("graph.csv",vsig,v2,n);
                            graph();
                        break;

                        case 2: ///VR2
                            printV0("graph.csv",v2,n);
                            graph();
                        break;

                        case 4: ///IR1
                            printIR("graph.csv",vsig,v2,R1,n);
                            graph();
                        break;

                        case 5: ///IR2
                            printIR0("graph.csv",v2,R2,n);
                            graph();
                        break;

                        case 6: ///IC
                            printIC("graph.csv",vsig,v2,C1,n);
                            graph();
                        break;

                        case 0: ///EXIT
                        break;

                        default : ///KASUS KESALAHAN
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(current_output != 0);

            break;
            ///RANGKAIAN 5
            case 5:
                signList();
                scanf("%d", &signal);
                do{
                    switch(signal){
                        ///KONSTAN
                        case 1:
                            printf("Amplitude value: ");
                            scanf("%lf", &A);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            for (int i=0; i<n-1; i++){
                                rangkaian5(v2,R1,R2,C1,C2,vsig,i);
                                vsig[i] = A;
                            }
                        break;

                        case 2:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSin(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                rangkaian5(v2,R1,R2,C1,C2,vsig,i);
                                time += T;
                                vsig[i+1] = genSin(A,f,phase,DCoff,time);
                            }
                        break;

                        case 3:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSqr(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                rangkaian5(v2,R1,R2,C1,C2,vsig,i);
                                time += T;
                                vsig[i+1] = genSqr(A,f,phase,DCoff,time);
                            }
                        break;

                        default:
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(signal < 1 || signal >3);

                do{
                    outRRCC();
                    scanf("%d", &current_output);
                    switch (current_output){
                        case 1: ///VR1
                        case 3: ///VC1
                            printV("graph.csv",vsig,v2,n);
                            graph();
                        break;

                        case 2: ///VR2
                        case 4: ///VC2
                            printV0("graph.csv",v2,n);
                            graph();
                        break;

                        case 5: ///IR1
                            printIR("graph.csv",vsig,v2,R1,n);
                            graph();
                        break;

                        case 6: ///IR2
                            printIR0("graph.csv",v2,R2,n);
                            graph();
                        break;

                        case 7: ///IC1
                            printIC("graph.csv",vsig,v2,C1,n);
                            graph();
                        break;

                        case 8: ///IC2
                            printIC0("graph.csv",v2,C2,n);
                            graph();
                        break;

                        case 0: ///EXIT
                        break;

                        default : ///KASUS KESALAHAN
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(current_output != 0);
            break;
            ///RANGKAIAN 6
            case 6:
                signList();
                scanf("%d", &signal);
                do{
                    switch(signal){
                        ///KONSTAN
                        case 1:
                            printf("Amplitude value: ");
                            scanf("%lf", &A);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            v3 = (double *)realloc(v2o, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            for (int i=0; i<n-1; i++){
                                rangkaian6(v2,v3,R1,R2,C1,C2,vsig,i);
                                vsig[i] = A;
                            }
                        break;

                        case 2:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            v3 = (double *)realloc(v2o, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSin(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                vsig[i+1] = genSin(A,f,phase,DCoff,time);
                                rangkaian6(v2,v3,R1,R2,C1,C2,vsig,i);
                                time += T;
                            }
                        break;

                        case 3:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            v3 = (double *)realloc(v2o, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSqr(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                vsig[i+1] = genSqr(A,f,phase,DCoff,time);
                                rangkaian6(v2,v3,R1,R2,C1,C2,vsig,i);
                                time += T;
                            }
                        break;

                        default:
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(signal < 1 || signal >3);

                do{
                    outRRCC();
                    scanf("%d", &current_output);
                    switch (current_output){
                        case 1: ///VR1
                            printV("graph.csv",v2,v3,n);
                            graph();
                        break;

                        case 2: ///VR2
                            printV0("graph.csv",v2,n);
                            graph();
                        break;

                        case 3: ///VC1
                            printV("graph.csv",vsig,v2,n);
                            graph();
                        break;

                        case 4: ///VC2
                            printV0("graph.csv",v3,n);
                            graph();
                        break;

                        case 5: ///IR1
                        case 8: ///IC2
                            printIR("graph.csv",v2,v3,R1,n);
                            graph();
                        break;

                        case 6: ///IR2
                            printIR0("graph.csv",v2,R2,n);
                            graph();
                        break;

                        case 7: ///IC1
                            printIC("graph.csv",vsig,v2,C1,n);
                            graph();
                        break;

                        case 0: ///EXIT
                        break;

                        default : ///KASUS KESALAHAN
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(current_output != 0);
            break;
            ///RANGKAIAN 7
            case 7:
                signList();
                scanf("%d", &signal);
                do{
                    switch(signal){
                        ///KONSTAN
                        case 1:
                            printf("Amplitude value: ");
                            scanf("%lf", &A);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            v3 = (double *)realloc(v2o, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            for (int i=0; i<n-1; i++){
                                rangkaian7(v2,v3,R1,R2,C1,C2,vsig,i);
                                vsig[i] = A;
                            }
                        break;

                        ///SINUSOID
                        case 2:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            v3 = (double *)realloc(v2o, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSin(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                rangkaian7(v2,v3,R1,R2,C1,C2,vsig,i);
                                time += T;
                                vsig[i+1] = genSin(A,f,phase,DCoff,time);
                            }
                        break;

                        ///KOTAK
                        case 3:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            v3 = (double *)realloc(v2o, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            time = 0;
                            vsig[0] = genSqr(A,f,phase,DCoff,time);
                            for (int i = 0; i<n-1; i++){
                                rangkaian7(v2,v3,R1,R2,C1,C2,vsig,i);
                                time += T;
                                vsig[i+1] = genSqr(A,f,phase,DCoff,time);
                            }
                        break;

                        default:
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(signal < 1 || signal >3);

                do{
                    outRRCC();
                    scanf("%d", &current_output);
                    switch (current_output){
                        case 1: ///VR1
                            printV("graph.csv",vsig,v2,n);
                            graph();
                        break;

                        case 2: ///VR2
                            printV("graph.csv",v2,v3,n);
                            graph();
                        break;

                        case 3: ///VC1
                            printV0("graph.csv",v3,n);
                            graph();
                        break;

                        case 4: ///VC2
                            printV0("graph.csv",v2,n);
                            graph();
                        break;

                        case 5: ///IR1
                            printIR("graph.csv",vsig,v2,R1,n);
                            graph();
                        break;

                        case 7: ///IC1
                        case 6: ///IR2
                            printIR("graph.csv",v2,v3,R2,n);
                            graph();
                        break;

                        case 8: ///IC2
                            printIC0("graph.csv",v2,C1,n);
                            graph();
                        break;

                        case 0: ///EXIT
                        break;

                        default : ///KASUS KESALAHAN
                            printf("Invalid Input!\n");
                        break;
                    }
                }while(current_output != 0);
            break;
            ///RANGKAIAN 8
            case 8:

            break;

            case 0:
            break;

            default:
                printf("Invalid Input!\n\n");
            break;
        }
    } while (current_menu != 0);
    free(v);
    free(v2);
    free(v3);
    free(vsig);
    free(v2o);
    free(v3o);
}
