#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "rangkaian.h"
#include "tampilan.h"
#define T 0.00001

int main(){
    //Deklarasi Variabel
    int current_menu;       //Untuk menentukan menu saat ini
    int srcType;            //Untuk menentukan tipe sumber yang digunakan(1: tegangan, 2: arus)
    int signal;             //Untuk menentukan jenis sinyal masukan
    int current_output = 0; //Untuk menentukan sinyal keluaran yang ingin diplot
    double temp;            //Menyimpan nilai tipe data double untuk sementara
    double A;               //Menyimpan nilai amplituda sinyal input
    double f;               //Menyimpan nilai frekuensi sinyal input
    double phase;           //Menyimpan nilai fasa sinyal input
    double DCoff;           //Menyimpan nilai offset dc sinyal input
    double source;          //Menyimpan nilai sinyal input pada detik ke time + 1
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
            //RANGKAIAN 1(coba dites)
            case 1:

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

            //RANGKAIAN 2(coba dites)
            case 2:
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

            //RANGKAIAN 3(coba dites)
            case 3:
                //Menentukan tipe sumber
                sourceType(&srcType);

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
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            if(srcType == 1){
                                rangkaian3V(vo,v2o,R1,C1,C2,A,i);
                            }
                            else{
                                rangkaian3(vo,v2o,R1,C1,C2,A,i);
                            }
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
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        if(srcType == 1){
                            time = 0;
                            source = genSin(A,f,phase,DCoff,time);
                            v2o[0] = source;                            
                        }
                        time = T;
                        source = genSin(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            if(srcType == 1){
                                rangkaian3V(vo,v2o,R1,C1,C2,source,i);
                                time += T;
                                source = genSin(A,f,phase,DCoff,time);
                            }
                            else{
                                rangkaian3(vo,v2o,R1,C1,C2,source,i);
                                time += T;
                                source = genSin(A,f,phase,DCoff,time);
                            }
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
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        if(srcType == 1){
                            time = 0;
                            source = genSqr(A,f,phase,DCoff,time);
                            v2o[0]=source;
                        }
                        time = T;
                        source = genSqr(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            if(srcType == 1){
                                rangkaian3V(vo,v2o,R1,C1,C2,source,i);
                                time += T;
                                source = genSqr(A,f,phase,DCoff,time);
                            }
                            else{
                                rangkaian3(vo,v2o,R1,C1,C2,source,i);
                                time += T;
                                source = genSqr(A,f,phase,DCoff,time);
                            }
                        }
                    break;
                    

                    default:
                        printf("invalid input!");
                        break;
                }
                }while(signal < 1 || signal >3);
                
                //Menu untuk menampilkan grafik output rangkaian 3
                do {
                    outRCC();
                    scanf("%d", &current_output);
                    switch(current_output){
                        case 1:
                            printV("graph.csv", v2o, vo, n);
                            graph();
                            break;

                        case 2:
                            printV("graph.csv", v2o, vo, n);
                            graph();
                            break;

                        case 3:
                            printV0("graph.csv", vo, n);
                            graph();
                            break;

                        case 4:
                            printIR("graph.csv", v2o, vo, R1, n);
                            graph();
                            break;

                        case 5:
                            printIC("graph.csv", v2o, vo, C1, n);
                            graph();
                            break;

                        case 6:
                            printIC0("graph.csv", vo, C2, n);
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
            
            //RANGKAIAN 4 (Sumber tegangan kotak hasil aneh, sisanya oke)
            case 4:
                sourceType(&srcType); //Menentukan tipe sumber
                signList();
                scanf ("%d", &signal);
                    do{
                        switch(signal){
                            ///KONSTAN
                            case 1: //OK
                                printf("Amplitude value: ");
                                scanf("%lf", &A);
                                menuRRC(&R1,&R2,&C1,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                vsig[0] = A;
                                for (int i=0; i<n-1; i++){
                                    vsig[i+1] = A;
                                    if(srcType == 1){
                                        rangkaian4(v,v2,R1,R2,C1,vsig,i);
                                    }
                                    else{
                                        rangkaian4I(v,v2,R1,R2,C1,vsig,i);
                                    }
                                }
                            break;

                            case 2: //OK
                                InputAC(&A, &f, &phase, &DCoff);
                                menuRRC(&R1,&R2,&C1,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                time = 0;
                                vsig[0] = genSin(A,f,phase,DCoff,time);
                                for (int i = 0; i<n-1; i++){
                                    vsig[i+1] = genSin(A,f,phase,DCoff,time+T);
                                    if(srcType == 1){
                                        rangkaian4(v,v2,R1,R2,C1,vsig,i);
                                    }
                                    else{
                                        rangkaian4I(v,v2,R1,R2,C1,vsig,i);
                                    }
                                    time += T;
                                }
                            break;

                            case 3:
                                InputAC(&A, &f, &phase, &DCoff);
                                menuRRC(&R1,&R2,&C1,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                time = 0;
                                vsig[0] = genSqr(A,f,phase,DCoff,time);
                                for (int i = 0; i<n-1; i++){
                                    vsig[i+1] = genSqr(A,f,phase,DCoff,time+T);
                                    if(srcType == 1){
                                        //Hasil Aneh, keinvert
                                        rangkaian4(v,v2,R1,R2,C1,vsig,i);
                                    }
                                    else{
                                        rangkaian4I(v,v2,R1,R2,C1,vsig,i);
                                    }
                                    time += T;
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
                                printV("graph.csv",v,v2,n);
                                graph();
                            break;

                            case 2: ///VR2
                                printV0("graph.csv",v2,n);
                                graph();
                            break;

                            case 4: ///IR1
                                printIR("graph.csv",v,v2,R1,n);
                                graph();
                            break;

                            case 5: ///IR2
                                printIR0("graph.csv",v2,R2,n);
                                graph();
                            break;

                            case 6: ///IC
                                printIC("graph.csv",v,v2,C1,n);
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
            ///RANGKAIAN 5 (coba dites)
            case 5:
                sourceType(&srcType); //Menentukan tipe sumber
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
                            if(srcType == 1){
                                time = 0;
                                vsig[0] = genSin(A,f,phase,DCoff,time);
                            }
                            else{
                                time = T;
                                source = genSin(A,f,phase,DCoff,time);
                            }
                            for (int i = 0; i<n-1; i++){
                                if(srcType == 1){
                                    rangkaian5(v2,R1,R2,C1,C2,vsig,i);
                                    time += T;
                                    vsig[i+1] = genSin(A,f,phase,DCoff,time);
                                }
                                else{
                                    rangkaian5I(vsig, v2,R1,R2,C1,C2,source,i);
                                    time += T;
                                    source = genSin(A,f,phase,DCoff,time);                                }
                            }
                        break;

                        case 3:
                            InputAC(&A, &f, &phase, &DCoff);
                            menuRRCC(&R1,&R2,&C1,&C2,&t);
                            n = t/T;
                            v2 = (double *)realloc(vo, sizeof(double)*(n));
                            vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                            if(srcType == 1){
                                time = 0;
                                vsig[0] = genSqr(A,f,phase,DCoff,time);
                            }
                            else{
                                time = T;
                                source = genSqr(A,f,phase,DCoff,time);
                            }
                            for (int i = 0; i<n-1; i++){
                                if(srcType == 1){
                                    rangkaian5(v2,R1,R2,C1,C2,vsig,i);
                                    time += T;
                                    vsig[i+1] = genSqr(A,f,phase,DCoff,time);
                                }
                                else{
                                    rangkaian5I(vsig, v2,R1,R2,C1,C2,source,i);
                                    time += T;
                                    source = genSqr(A,f,phase,DCoff,time); 
                                }
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
            ///RANGKAIAN 6 (Sumber tegangan kotak hasil aneh, sisanya oke)
            case 6:
                sourceType(&srcType); //Menentukan tipe sumber
                signList();
                scanf("%d", &signal);
                do{
                    switch(signal){
                        ///KONSTAN
                        case 1: //OK
                                printf("Amplitude value: ");
                                scanf("%lf", &A);
                                menuRRCC(&R1,&R2,&C1,&C2,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                v3 = (double *)realloc(v3o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                vsig[0] = A;
                                for (int i=0; i<n-1; i++){
                                    vsig[i+1] = A;
                                    if(srcType == 1){
                                        rangkaian6(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    else{
                                        rangkaian6I(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                }
                            break;

                            case 2: //OK
                                InputAC(&A, &f, &phase, &DCoff);
                                menuRRCC(&R1,&R2,&C1,&C2,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                v3 = (double *)realloc(v3o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                time = 0;
                                vsig[0] = genSin(A,f,phase,DCoff,time);
                                for (int i = 0; i<n-1; i++){
                                    vsig[i+1] = genSin(A,f,phase,DCoff,time+T);
                                    if(srcType == 1){
                                        rangkaian6(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    else{
                                        rangkaian6I(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    time += T;
                                }
                            break;

                            case 3:
                                InputAC(&A, &f, &phase, &DCoff);
                                menuRRCC(&R1,&R2,&C1,&C2,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                v3 = (double *)realloc(v3o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                time = 0;
                                vsig[0] = genSqr(A,f,phase,DCoff,time);
                                for (int i = 0; i<n-1; i++){
                                    vsig[i+1] = genSqr(A,f,phase,DCoff,time+T);
                                    if(srcType == 1){
                                        //Hasil Aneh kayak keinvert
                                        rangkaian6(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    else{
                                        rangkaian6I(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
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
                            printV("graph.csv",v,v2,n);
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
                            printIC("graph.csv",v,v2,C1,n);
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
                sourceType(&srcType); //Menentukan tipe sumber
                signList();
                scanf("%d", &signal);
                do{
                    switch(signal){
                        ///KONSTAN
                        case 1: //OK
                                printf("Amplitude value: ");
                                scanf("%lf", &A);
                                menuRRCC(&R1,&R2,&C1,&C2,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                v3 = (double *)realloc(v3o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                vsig[0] = A;
                                for (int i=0; i<n-1; i++){
                                    vsig[i+1] = A;
                                    if(srcType == 1){
                                        rangkaian7(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    else{
                                        rangkaian7I(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                }
                            break;

                            case 2: //OK
                                InputAC(&A, &f, &phase, &DCoff);
                                menuRRCC(&R1,&R2,&C1,&C2,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                v3 = (double *)realloc(v3o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                time = 0;
                                vsig[0] = genSin(A,f,phase,DCoff,time);
                                for (int i = 0; i<n-1; i++){
                                    vsig[i+1] = genSin(A,f,phase,DCoff,time+T);
                                    if(srcType == 1){
                                        rangkaian7(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    else{
                                        rangkaian7I(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    time += T;
                                }
                            break;

                            case 3:
                                InputAC(&A, &f, &phase, &DCoff);
                                menuRRCC(&R1,&R2,&C1,&C2,&t);
                                n = t/T;
                                v  = (double *)realloc(vo, sizeof(double)*(n));
                                v2 = (double *)realloc(v2o, sizeof(double)*(n));
                                v3 = (double *)realloc(v3o, sizeof(double)*(n));
                                vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                                time = 0;
                                vsig[0] = genSqr(A,f,phase,DCoff,time);
                                for (int i = 0; i<n-1; i++){
                                    vsig[i+1] = genSqr(A,f,phase,DCoff,time+T);
                                    if(srcType == 1){
                                        //Hasil Aneh kayak keinvert
                                        rangkaian7(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
                                    else{
                                        rangkaian7I(v,v2,v3,R1,R2,C1,C2,vsig,i);
                                    }
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
                            printV("graph.csv",v,v2,n);
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
                            printIR("graph.csv",v,v2,R1,n);
                            graph();
                        break;

                        case 8: ///IC2
                            printIC0("graph.csv",v2,C2,n);
                            graph();
                        break;

                        case 6: ///IR2
                        case 7: ///IC1
                            printIR("graph.csv",v2,v3,R2,n);
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

            //RANGKAIAN 8 (coba dites)
            case 8:

                //Menentukan tipe sumber
                sourceType(&srcType);

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
                        menuRRCC(&R1, &R2, &C1, &C2, &t);
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        v3o = (double *)realloc(v3o, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        for(int i=0; i<n-1; i++){
                            if(srcType == 1){
                                rangkaian8V(vo, v2o, v3o, R1, R2, C1, C2, A, i);    //Sumber tegangan
                                vsig[i] = A;
                            }
                            else{
                                rangkaian8(vo, v2o, v3o, R1, R2, C1, C2, A, i);     //Sumber arus
                                vsig[i] = A;
                            }
                        }
                    break;

                    case 2:
                        InputAC(&A, &f, &phase, &DCoff);
                        menuRRCC(&R1, &R2, &C1, &C2, &t);
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        v3o = (double *)realloc(v3o, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        if(srcType == 1){
                            time = 0;
                            source = genSin(A,f,phase,DCoff,time);
                            vo[0] = source;
                        }
                        time=T;
                        source = genSin(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            if(srcType == 1){
                                rangkaian8V(vo, v2o, v3o, R1, R2, C1, C2, source, i);   //Sumber tegangan
                                vsig[i] = source;
                                time += T;
                                source = genSin(A,f,phase,DCoff,time);
                            }
                            else{
                                rangkaian8(vo, v2o, v3o, R1, R2, C1, C2, source, i);    //Sumber arus
                                vsig[i] = source;
                                time += T;
                                source = genSin(A,f,phase,DCoff,time);
                            }
                        }
                    break;

                    case 3:
                        InputAC(&A, &f, &phase, &DCoff);
                        menuRRCC(&R1, &R2, &C1, &C2, &t);
                        n = t/T;
                        vo = (double *)realloc(vo, sizeof(double)*(n));
                        v2o = (double *)realloc(v2o, sizeof(double)*(n));
                        v3o = (double *)realloc(v3o, sizeof(double)*(n));
                        vsig = (double *)realloc(vsigo, sizeof(double)*(n));
                        if(srcType == 1){
                            time = 0;
                            source = genSqr(A,f,phase,DCoff,time);
                            vo[0] = source;
                        }
                        time+=T;
                        source = genSqr(A,f,phase,DCoff,time);
                        for(int i=0; i<n-1; i++){
                            if(srcType == 1){
                                rangkaian8V(vo, v2o, v3o, R1, R2, C1, C2, source, i);   //Sumber tegangan
                                vsig[i] = source;
                                time += T;
                                source = genSqr(A,f,phase,DCoff,time);
                            }
                            else{
                                rangkaian8(vo, v2o, v3o, R1, R2, C1, C2, source, i);    //Sumber arus
                                vsig[i] = source;
                                time += T;
                                source = genSqr(A,f,phase,DCoff,time);
                            }
                        }
                    break;

                    default:
                        printf("invalid input!\n");
                }
                }while(signal<1 || signal >3);

                                //Menu untuk menampilkan grafik output rangkaian 3
                do {
                    outRRCC();
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

    return 0;
}
