//---------------------------------------------------------------------------

#ifndef Clash_checksH
#define Clash_checksH
void point_from_2DlineXY(float,float,float,float,float,float,float *,float *,float *,int *);
void point_from_2DlineZY(float,float,float,float,float,float,float *,float *,float *,int *);
void point_from_2DlineZX(float,float,float,float,float,float,float *,float *,float *,int *);
void XYpoints_along_3D_line_givenZ(float,float,float,float,float,float,float *,float *,float ,int *);
void XYpoints_along_3D_line_givenY(float,float,float,float,float,float,float *,float *,float ,int *);
void XYpoints_along_3D_line_givenX(float,float,float,float,float,float,float *,float *,float ,int *);
void  Intersect_of_line_with_cylZ(float,float,float,float,float,float,float,float,float,float,float,int *);
void  Intersect_of_line_with_cylY(float,float,float,float,float,float,float,float,float,float,float,int *);
void  Intersect_of_line_with_cylX(float,float,float,float,float,float,float,float,float,float,float,int *);


void Intersect_of_line_with_circ_innerZ(float,float,float,float,float,float,float,float,float,float,int *);
void Intersect_of_line_with_sphere(float X1,float Y1,float Z1,float X2,float Y2,float Z2,
float,float,float,float,int,int *);
//---------------------------------------------------------------------------
#endif
