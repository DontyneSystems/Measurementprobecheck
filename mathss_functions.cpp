//additional math functions
   //---------------------------------------------------------------------------
//copyright Dontyne Systems
//---------------------------------------------------------------------------


#include <math.h>


/***************************************************************************/

double Acos(double value)
{
        double valuecos;

        if(value>1.0)
        value=1.0;

		if(value<-1.0)
        value=-1.0;

        valuecos=acos(value);

return valuecos;
}



/***************************************************************************/

double inv_inverse(double involute_)
{
		double value,val,val1,val2;

		val1=0;
		val2=M_PI/2.0*.98;

		while(val2-val1>0.000001)
		{
		val=(val1+val2)/2.0;

		value=tan(val)-val;
		if(value>involute_)
		val2=val;
		else
		val1=val;

		}

return val;
}

/***************************************************************************/


/***************************************************************************/

double inv(double value)
{
		double involute_;

		involute_=tan(value)-value;

return involute_;
}

/***************************************************************************/



/***************************************************************************/

double SQRT(double value)
{
        double valuesqrt;

        if(value<0.0)
        value=0.0;

        valuesqrt=sqrt(value);

return valuesqrt;
}

/***************************************************************************/


/****************************************************************************/
/*function to solve 2 linear simultaneous equations*/

float det2(float a,float b,float c,float d)
{
	float valdet2;
	valdet2=a*d-b*c;
	return(valdet2);
}

double det2double(double a,double b,double c,double d)
{
	double valdet2;
	valdet2=a*d-b*c;
	return(valdet2);
}

/****************************************************************************/

/****************************************************************************/
/*function to solve intersection of 2 lines*/

void two_line_intersect(float x11,float y11,float x12,float y12,float x21,float y21,float x22,float y22,float *x3,float *y3,int *intersect)
{
float EPSILON=0.00001;

float m1,m2,c1,c2,a1,b1,k1,a2,b2,k2,valdet;

if(y12-y11==0)
m1=0;
else
{
if(x12-x11==0)
m1=1e9;
else
m1=(y12-y11)/(x12-x11);
}


c1=-m1*x11+y11;

a1=-m1;
b1=1;
k1=c1;

if(y22-y21==0)
m2=0;
else
{
if(x22-x21==0)
m2=1e9;
else
m2=(y22-y21)/(x22-x21);
}

c2=-m2*x21+y21;

a2=-m2;
b2=1;
k2=c2;


valdet=det2(a1,b1,a2,b2);


if(fabs(valdet)>=EPSILON)
{

*x3=det2(k1,b1,k2,b2)/valdet;
*y3=det2(a1,k1,a2,k2)/valdet;


  if(((*x3<=x12 && *x3>=x11) || (*x3<=x11 && *x3>=x12))
  && ((*y3<=y12 && *y3>=y11) || (*y3<=y11 && *y3>=y12))  )
  {
  *intersect=1;
  }
  else
  *intersect=0;

  if(*intersect==1)
  {
   if(((*x3<=x22 && *x3>=x21) || (*x3<=x21 && *x3>=x22))
   && ((*y3<=y22 && *y3>=y21) || (*y3<=y21 && *y3>=y22))  )
   {
   *intersect=1;
   }
   else
   *intersect=0;
  }

}
else
*intersect=0;

}




//checks that infinity is not number before calculating to power
float powC(float num,float tothe)
{
float valx;

   if(num>1e99 && tothe>0)
   valx=1e99;
   else
   if(num>1e99 && tothe<0)
   valx=0;
   else
   if(num<-1e99 && tothe>0)
   valx=-1e99;
   else
   if(num<-1e99 && tothe<0)
   valx=0;
   else
   if(tothe==0)
   valx=1;
   else
   valx=pow(num,tothe);


return valx;

}
/****************************************************************************/

//fixes error of pow wanting 2 doubles
float POW(double num,double tothe)
{


 double   valx=pow(1.0*num,1.0*tothe);


return valx;

}
/****************************************************************************/

/*function to convert involute dist to diameter*/

float disttodia1(float distv)
{
   float extern db1;

	float diamv;

	diamv=2*SQRT(distv*distv+db1*db1);

	return(diamv);
}

/****************************************************************************/

/****************************************************************************/

/*function to convert involute dist to diameter*/

float disttodia2(float distv)
{
   float extern db2;

	float diamv;

	diamv=2*SQRT(distv*distv+db2*db2);

	return(diamv);
}

/****************************************************************************/

/****************************************************************************/

/*function to convert involute dia  to dist*/

float diatodist1(float diav)
{
   float extern db1;

	float distv;

	distv=SQRT(diav*diav/4.0-db1*db1/4.0);

	return(distv);
}

/****************************************************************************/

/****************************************************************************/

/*function to convert involute dia to dist*/

float diatodist2(float diav)
{
   float extern db2;

	float distv;

	distv=SQRT(diav*diav/4.0-db2*db2/4.0);

	return(distv);
}

/****************************************************************************/


//---------------------------------------------------------------------------
//Function to calculate normals


void calc_normMF(float Px, float Py, float Pz,float Pjx, float Pjy, float Pjz,
float Pix, float Piy, float Piz, float *nx, float *ny, float *nz)
{

float size;
//P  - reference point (Px, Py, Pz) coordinates input
//Pj - point in j direction (Pjx, Pjy, Pjz) coordinates input
//Pi - Point in i direction  (Pjx, Pjy, Pjz) coordinates input
float vjx= Pjx- Px;
float vjy= Pjy- Py;
float vjz= Pjz- Pz;

float vix= Pix- Px;
float viy= Piy- Py;
float viz= Piz- Pz;

*nx = vjy*viz - vjz*viy;
*ny = vjz*vix - vjx*viz;
*nz = vjx*viy - vjy*vix;

size = sqrt(*nx**nx + *ny**ny + *nz**nz);

if(size!=0)
{
*nx = *nx/size;
*ny = *ny/size;
*nz = *nz/size;
}


}



//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
//Function to calculate normals


void calc_norm(float Px, float Py, float Pz,float Pjx, float Pjy, float Pjz,
float Pix, float Piy, float Piz, float *nx, float *ny, float *nz)
{

float size;
//P  - reference point (Px, Py, Pz) coordinates input
//Pj - point in j direction (Pjx, Pjy, Pjz) coordinates input
//Pi - Point in i direction  (Pjx, Pjy, Pjz) coordinates input
float vjx= Pjx- Px;
float vjy= Pjy- Py;
float vjz= Pjz- Pz;

float vix= Pix- Px;
float viy= Piy- Py;
float viz= Piz- Pz;

*nx = vjy*viz - vjz*viy;
*ny = vjz*vix - vjx*viz;
*nz = vjx*viy - vjy*vix;

size = sqrt(*nx**nx + *ny**ny + *nz**nz);

if(size!=0)
{
*nx = *nx/size;
*ny = *ny/size;
*nz = *nz/size;
}


}



//---------------------------------------------------------------------------





float dia_to_manuf(float dia,float db, int lengthUnitR)
{
float value_converted;

		if(lengthUnitR==0)
		value_converted=dia;
		if(lengthUnitR==1)
		{
		 if(dia*dia/4.0-db*db/4.0>0)
		 value_converted=sqrt(dia*dia/4.0-db*db/4.0);
		 else
		 value_converted=0;
		}
		if(lengthUnitR==2)
		{
		if(dia*dia/4.0-db*db/4.0>0)
		value_converted= (sqrt(dia*dia/4.0-db*db/4.0))/(db/2.0)*180/M_PI;
		else
        value_converted=0;
		}

return(value_converted);
}
//---------------------------------------------------------------------------

float dia_from_manuf(float value_converted,float db,int lengthUnitR)
{
float dia;
float dist;

        if(lengthUnitR==1)
        dia=value_converted;
        if(lengthUnitR==2)
        dia=2*sqrt(value_converted*value_converted+db*db/4.0);
        if(lengthUnitR==3)
        {
        dist=value_converted*M_PI/180*(db/2.0);
        dia=2*sqrt(dist*dist+db*db/4.0);
        }
return(dia);
}
//---------------------------------------------------------------------------
/***********************************************************************************************/
//Function to aTAN and check divide zero and which quadrant

float ATAN(float invaluey,float invaluex)
{
 float outvalue;

   if(invaluey==0)
   {
	 if(invaluex>=0)
	 outvalue=0;
	 else
	 outvalue=M_PI;
   }
   else
   if(invaluex==0)
   {
	 if(invaluey>=0)
	 outvalue=0.5*M_PI;
	 else
	 outvalue=-0.5*M_PI;
   }
   else
   if(invaluex>0 && invaluey>0)     //1st quadrant
   outvalue=atan(invaluey/invaluex);
   else
   if(invaluex<0 && invaluey>0)    // 2nd quadrant
   outvalue=M_PI+atan(invaluey/invaluex);
   else
   if(invaluex<0 && invaluey<0)        //3rd quadrant
   outvalue=-M_PI+atan(invaluey/invaluex);
   else
   if(invaluex>0 && invaluey<0)        //4th quadrant
   outvalue=atan(invaluey/invaluex);


   return outvalue;
}
/***********************************************************************************************/


 //*******************************************************************************************/

 int roundinteger(float numberin)
 {
 int numberout;

	 if(numberin-floor(numberin)>=0.5)
	 numberout=ceil(numberin);
	 else
	 numberout=floor(numberin);

 return numberout;

 }



 //*******************************************************************************************/

 //*******************************************************************************************/

float roundfloat(float numberin,int decimalplaces)
 {
 float numberout;

	 numberin=numberin*pow(10.0,decimalplaces);

	 if(numberin-floor(numberin)>=0.5)
	 numberout=ceil(numberin);
	 else
	 numberout=floor(numberin);

	 numberout=numberout*pow(10.0,-decimalplaces);

 return numberout;

 }



 //*******************************************************************************************/



//----------------------------------------------------------------------------



void extrapolate_samples(float dist,float x1,float y1,float z1,float x2,float y2,float z2,float *x3,float *y3,float *z3)
{

//calculates vector to extend the surface tangentially.

   float v1[3],v_;

   v1[0]=x2-x1;
   v1[1]=y2-y1;
   v1[2]=z2-z1;

   v_=sqrt(v1[0]*v1[0]+v1[1]*v1[1]+v1[2]*v1[2]);
   if(v_==0)
   v_=1.0;

   v1[0]=v1[0]/v_;
   v1[1]=v1[1]/v_;
   v1[2]=v1[2]/v_;

   *x3=x2+dist*v1[0];
   *y3=y2+dist*v1[1];
   *z3=z2+dist*v1[2];



}

//-------------------------------------------------------------------------------------

/****************************************************************************/

//function to calculate radii of curvature of 3 points

void rad_curvature(double x1,double y1,double x2,double y2,double x3,double y3,
double *r, double *xa,double *xb)
{
double a1,b1,a2,b2,a3,b3,k1,k2,a,b;

double valdet;


//makesure points not same  by checking distance between them
if(sqrt((y1-y2)*(y1-y2)+(x1-x2)*(x1-x2))>0.005 &&

sqrt((y3-y2)*(y3-y2)+(x3-x2)*(x3-x2))>0.005)
{



a1=2*x3-2*x1;
b1=2*y3-2*y1;
k1=-(x1*x1-x3*x3+y1*y1-y3*y3);

a2=2*x3-2*x2;
b2=2*y3-2*y2;
k2=-(x2*x2-x3*x3+y2*y2-y3*y3);



valdet=det2double(a1,b1,a2,b2);

if(fabs(valdet)>=0.00000001)
{
a=det2double(k1,b1,k2,b2)/valdet;
b=det2double(a1,k1,a2,k2)/valdet;





*r=sqrt((x1-a)*(x1-a)+(y1-b)*(y1-b));
*xa=a;
*xb=b;

}
else
{
*r=0;
*xa=0;
*xb=0;
}

}
else
{
*r=0;
*xa=0;
*xb=0;
}


}

/****************************************************************************/

void line_circ_intersect_extrap(int leftright,float x1,float y1,float x2,float y2,float ra,float a,float b,float *x,float *y)
{
 double e1,e2,mid,ytemp1,ytemp2;
 int iloop;

		 /*

 //e vals y val
 e1=ra*0.8;
 e2=ra-0.000001;

 iloop=0;
 while(fabs(e1-e2)>0.000001 && iloop<20)
 {
 mid=(e1+e2)*0.5;

 //line
 xtemp1=x1+(mid-y1)/(y2-y1)*(x2-x1);

 xtemp2=sqrt(ra*ra-pow(mid-b,2))+a;  //+ve x

 if(leftright==2 && x1<0)
 xtemp2=-(sqrt(ra*ra-pow(mid-b,2))+a);  //-ve x

 if(leftright==1) //right
 {
 if(xtemp1<xtemp2)
 e1=mid;
 else
 e2=mid;
 }
 else
  if(leftright==2) //left
 {
 if(xtemp1<xtemp2)
 e1=mid;
 else
 e2=mid;
 }

 }

 *x=xtemp1;
 *y=mid;

 */


 //e vals x val
 e1=0.5*ra;
 e2=-0.5*ra;

 iloop=0;
 while(fabs(e1-e2)>0.000001 && iloop<20)
 {
 mid=(e1+e2)*0.5;
 if(mid==0)
 mid=0.00001;

 //line
 ytemp1=y1+(mid-x1)/(x2-x1)*(y2-y1);

 ytemp2=sqrt(ra*ra-pow(mid-a,2))+b;  //y


 if(leftright==2)
 {
 if(mid<0) //right
 {
 if(ytemp1>ytemp2)
 e1=mid;
 else
 e2=mid;
 }
 else
 if(mid>0) //left
 {
 if(ytemp1>ytemp2)
 e1=mid;
 else
 e2=mid;
 }
 }
 else
 if(leftright==1)
 {
 if(mid<0) //right
 {
 if(ytemp1<ytemp2)
 e1=mid;
 else
 e2=mid;
 }
 else
 if(mid>0) //left
 {
 if(ytemp1<ytemp2)
 e1=mid;
 else
 e2=mid;
 }
 }





 }

 *x=mid;
 *y=ytemp1;


}

/////////////////////////////////////////////////////////////////////////////////






