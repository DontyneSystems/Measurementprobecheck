//---------------------------------------------------------------------------

#ifndef math_functionsH
#define math_functionsH

void extrapolate_samples(float,float,float,float,float,float,float,float *x3,float *y3,float *z3);
void line_circ_intersect_extrap(int,float,float,float,float,float,float,float,float *,float *);
double Acos(double);
double inv_inverse(double);
double inv(double);
double SQRT(double);
float det2(float,float,float,float);
void two_line_intersect(float,float,float,float,float,float,float,float,float *,float *,int *);
void rad_curvature(double,double,double,double,double,double,double *, double *,double *);
float powC(float,float);
void calc_norm(float,float,float,float,float,float,
float,float,float,float*,float*,float*);
float ATAN(float,float);
int roundinteger(float);
float roundfloat(float,int);
typedef void (*AddFuncv)(int,float,float,float,float,float,float,float,float *,float *,float *);



//---------------------------------------------------------------------------
#endif
