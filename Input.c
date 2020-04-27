#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rangkaian.h"
#include "tampilan.h"
#define T 0.0001

int main(){
    //Deklarasi Variabel
    int current_menu;       //Untuk menentukan menu saat ini
    int signal;             //Untuk menentukan jenis sinyal masukan
    int current_output = 0; //Untuk menentukan sinyal keluaran yang ingin diplot
    char filename[100];     //
    double temp;            //Menyimpan nilai tipe data double untuk sementara
    double A;               //Menyimpan nilai amplituda sinyal input
    double f;               //Menyimpan nilai frekuensi sinyal input
    double phase;           //Menyimpan nilai fasa sinyal input
    double DCoff;           //Menyimpan nilai offset dc sinyal input
    double source;          //Menyimpan nilai sinyal input pada detik ke time
    double R1;              //Menyimpan nilai resistor
    double R2;              //Menyimpan nilai resistor
    double C1;              //Menyimpan nilai kapasitor
    double C2;              //Menyimpan nilai kapasitor
    double time;            //Menyimpan nilai waktu untuk simulasi
    double t;               //Menyimpan nilai lama rentang waktu simulasi
    double n;               //Menyimpan nilai banyaknya iterasi
    double *v2o;
    double *v2;
    double *v3o;
    double *v3;
    double *vo;
    double *v;
    double *vsigo;
    double *vsig;
    
    do {
        mainmenu();             //Menampilkan menu utama
        circuitList();          //Menampilkan daftar rangkaian yang tersedia
        system("python menu.py");  // Menampilkan gambar rangkaian yang ada di circuitList()
        scanf("%d", &current_menu);

        //Inisialisasi
        vo      = (double *)malloc(sizeof(double));
        vsigo   = (double *)malloc(sizeof(double));
        v2o     = (double *)malloc(sizeof(double));
        v3o     = (double *)malloc(sizeof(double));
        *vo     = 0;
        *v2o    = 0;
        *v3o    = 0;
        *vsigo  = 0;

        switch(current_menu) //Switch case jenis rangkaian berdasarkan input yang dimasukkan user
        {
            case 1:     //Rangkaian 1

                //Menentukan jenis sinyal masukan (1: constant, 2: sinusoid, 3: square)
                do{
                signList();
                scanf("%d", &signal);
                
                //Switch case untuk memproses sinyal output berdasarkan jenis sinyal masukan
                switch(signal){
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

                //Menu menampilkan grafik output rangkaian 1
                do {
                    printf("Choose output: \n");
                    printf("1. V1 \n");
                    printf("2. I(R) \n");
                    printf("3. I(C) \n");
                    printf("0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &current_output);
                    
                    //Switch case jenis output yang ingin diplot
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

            case 2:     //Rangkaian 2
                
                //Menentukan jenis sinyal masukan (1: constant, 2: sinusoid, 3: square)
                do{
                signList();
                scanf("%d", &signal);
                
                //Switch case untuk memproses sinyal output berdasarkan jenis sinyal masukan
                switch(signal){
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

                //Menu untuk menampilkan grafik output rangkaian 2
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

            case 3:     //Rangkaian 3
                
                //Menentukan jenis sinyal masukan (1: constant, 2: sinusoid, 3: square)
                do{
                signList();
                scanf("%d", &signal);

                //Switch case untuk memproses sinyal output berdasarkan jenis sinyal masukan
                switch(signal){
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
                
                //Menu untuk menampilkan grafik output rangkaian 3
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

            case 8:     //Rangkaian 8
                //Menentukan jenis sinyal masukan (1: constant, 2: sinusoid, 3: square)
                do{
                signList();
                scanf("%d", &signal);

                //Switch case untuk memproses sinyal output berdasarkan jenis sinyal masukan
                switch(signal){
                    case 1:
                        printf("Amplitude value: ");
                        scanf("%lf", &A);
                        printf("Input R1: ");
                        scanf("%lf", &R1);
                        printf("Input R2: ");
                        scanf("%lf", &R2);
                        printf("Input C1: ");
                        scanf("%lf", &C1);
                        printf("Input C2: ");
                        scanf("%lf", &C2);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        v3o = (double *)realloc(v3o, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            rangkaian8(vo, v2o, v3o, R1, R2, C1, C2, A, i);
                            vsig[i] = A;
                        }
                    break;

                    case 2:
                        InputAC(&A, &f, &phase, &DCoff);
                        printf("Input R1: ");
                        scanf("%lf", &R1);
                        printf("Input R2: ");
                        scanf("%lf", &R2);
                        printf("Input C1: ");
                        scanf("%lf", &C1);
                        printf("Input C2: ");
                        scanf("%lf", &C2);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        v3o = (double *)realloc(v3o, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        time = 0;
                        source = genSin(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            rangkaian8(vo, v2o, v3o, R1, R2, C1, C2, source, i);
                            vsig[i] = source;
                            time += T;
                            source = genSin(A,f,phase,DCoff,time);
                        }
                    break;

                    case 3:
                        InputAC(&A, &f, &phase, &DCoff);
                        scanf("%lf", &R1);
                        printf("Input R2: ");
                        scanf("%lf", &R2);
                        printf("Input C1: ");
                        scanf("%lf", &C1);
                        printf("Input C2: ");
                        scanf("%lf", &C2);
                        printf("\nInput duration (in s): ");
                        scanf("%lf", &t);
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        v3o = (double *)realloc(v3o, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        time = 0;
                        source = genSqr(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            rangkaian8(vo, v2o, v3o, R1, R2, C1, C2, source, i);
                            vsig[i] = source;
                            time += T;
                            source = genSqr(A,f,phase,DCoff,time);
                        }
                    break;

                    default:
                        printf("invalid input!\n");
                }
                }while(signal<1 || signal >3);

                                //Menu untuk menampilkan grafik output rangkaian 3
                do {
                    printf("Choose output: \n");
                    printf("1. V(R1) \n");
                    printf("2. V(R2) \n");
                    printf("3. V(C1) \n");
                    printf("4. V(C2) \n");
                    printf("5. I(R1) \n");
                    printf("6. I(R2) \n");
                    printf("7. I(C1) \n");
                    printf("8. I(C2) \n");
                    printf("0. Back\n");
                    printf("Your choice: ");
                    scanf("%d", &current_output);
                    switch(current_output){
                        case 1:
                            printV("graph.csv", vo, v2o, n);
                            graph();
                            break;

                        case 2:
                            printV0("graph.csv", v3o, n);
                            graph();
                            break;

                        case 3:
                            printV("graph.csv", v2o, v3o, n);
                            graph();
                            break;

                        case 4:
                            printV0("graph.csv", v3o, n);
                            graph();
                            break;

                        case 5:
                            printIR("graph.csv", vo, v2o, R1, n);
                            graph();
                            break;

                        case 6:
                            printIR0("graph.csv", v3o, R2, n);
                            graph();
                            break;

                        case 7:
                            printIC("graph.csv", v2o, v3o, C1, n);
                            graph();
                            break;

                        case 8:
                            printIC0("graph.csv", v3o, C2, n);
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
