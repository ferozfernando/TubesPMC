void mainmenu();
void circuitList();
void sourceList();
void signList();
void InputAC(double *A, double *f, double *phase, double *DCoff);
void printV(char filename[], double vpos[], double vneg[], int n);
void printV0(char filename[], double *vpos, int n);
void printIR(char filename[], double vpos[], double vneg[], double R, int n);
void printIR0(char filename[], double vpos[], double R, int n);
void printIC(char filename[], double vpos[], double vneg[], double C, int n);
void printIC0(char filename[], double vpos[], double C, int n);
void menuRC(double *R1, double *C1, double *t);
void menuRRC(double *R1, double *R2, double *C1, double *t);
void menuRCC(double *R1, double *C1, double *C2, double *t);
void menuRRCC(double *R1, double *R2, double *C1, double *C2, double *t);
void outRC();
void outRRC();
void outRCC();
void outRRCC();
void graph ();
