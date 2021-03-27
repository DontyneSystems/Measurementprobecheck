//---------------------------------------------------------------------------

#pragma hdrstop

#include "Clash_checks.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "math_functions.h"


//---------------------------------------------------------------------------


#include <math.h>

#include <stdio.h>




extern FILE *diagnosticfile;

/////////////////////////////////////////////////////////////////////////////////


void point_from_2DlineXY(float Ax,float Ay,float Dx,float Dy,float Px,float Py,float *Ix,float *Iy,float *Point_I,
int *online)
{
  //line A to D
  //point P
  //intersect of perpendicular from P onto line AD is point I

	if(Ax==Dx && Ay==Dy)
  {
  *Point_I=1e9;
  *online=0;
  }
  else
  {

  //unit vector AD
  float ADx=(Dx-Ax)/SQRT(pow(1.0*Dx-Ax,2.0)+pow(1.0*Dy-Ay,2.0));
  float ADy=(Dy-Ay)/SQRT(pow(1.0*Dx-Ax,2.0)+pow(1.0*Dy-Ay,2.0));

  //vector AP
  float APx=Px-Ax;
  float APy=Py-Ay;

  //scalar distance A to I along AD is dot product  AP.AD  where AD is a unit vect
  float AIdist=APx*ADx+APy*ADy;

  //point I
  *Ix=Ax+AIdist*ADx;
  *Iy=Ay+AIdist*ADy;

  //distance perpendicular Point_I
  *Point_I=SQRT(pow(1.0*(*Ix)-Px,2.0)+pow(1.0*(*Iy)-Py,2.0));

  //does I lay on line AD
  int onlinex=0;
  int onliney=0;

  if(Dx>=Ax && (*Ix>=Ax && *Ix<=Dx))
  onlinex=1;

  if(Dx<Ax &&  (*Ix>=Dx && *Ix<=Ax))
  onlinex=1;

  if(Dy>=Ay && (*Iy>=Ay && *Iy<=Dy))
  onliney=1;

  if(Dy<Ay &&  (*Iy>=Dy && *Iy<=Ay))
  onliney=1;


  if(onlinex==1 && onliney==1)
  *online=1;
  else
  *online=0;


  }

}


/////////////////////////////////////////////////////////////////////////////////


void point_from_2DlineZY(float Az,float Ay,float Dz,float Dy,float Pz,float Py,float *Iz,float *Iy,float *Point_I,
int *online)
{
  //line A to D
  //point P
  //intersect of perpendicular from P onto line AD is point I
  if(Ay==Dy && Az==Dz)
  {
  *Point_I=1e9;
  *online=0;
  }
  else
  {

  //unit vector AD
  float ADz=(Dz-Az)/SQRT(pow(1.0*Dz-Az,2.0)+pow(1.0*Dy-Ay,2.0));
  float ADy=(Dy-Ay)/SQRT(pow(1.0*Dz-Az,2.0)+pow(1.0*Dy-Ay,2.0));

  //vector AP
  float APz=Pz-Az;
  float APy=Py-Ay;

  //scalar distance A to I along AD is dot product  AP.AD  where AD is a unit vect
  float AIdist=APz*ADz+APy*ADy;

  //point I
  *Iz=Az+AIdist*ADz;
  *Iy=Ay+AIdist*ADy;

  //distance perpendicular Point_I
  *Point_I=SQRT(pow(1.0*(*Iz)-Pz,2.0)+pow(1.0*(*Iy)-Py,2.0));

  //does I lay on line AD
  int onlinez=0;
  int onliney=0;

  if(Dz>=Az && (*Iz>=Az && *Iz<=Dz))
  onlinez=1;

  if(Dz<Az &&  (*Iz>=Dz && *Iz<=Az))
  onlinez=1;

  if(Dy>=Ay && (*Iy>=Ay && *Iy<=Dy))
  onliney=1;

  if(Dy<Ay &&  (*Iy>=Dy && *Iy<=Ay))
  onliney=1;


  if(onlinez==1 && onliney==1)
  *online=1;
  else
  *online=0;

  }

}

/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////


void point_from_2DlineXZ(float Ax,float Az,float Dx,float Dz,float Px,float Pz,float *Ix,float *Iz,float *Point_I,
int *online)
{
  //line A to D
  //point P
  //intersect of perpendicular from P onto line AD is point I
  if(Ax==Dx && Az==Dz)
  {
  *Point_I=1e9;
  *online=0;
  }
  else
  {


  //unit vector AD
  float ADx=(Dx-Ax)/SQRT(pow(1.0*Dx-Ax,2.0)+pow(1.0*Dz-Az,2.0));
  float ADz=(Dz-Az)/SQRT(pow(1.0*Dx-Ax,2.0)+pow(1.0*Dz-Az,2.0));

  //vector AP
  float APx=Px-Ax;
  float APz=Pz-Az;

  //scalar distance A to I along AD is dot product  AP.AD  where AD is a unit vect
  float AIdist=APx*ADx+APz*ADz;

  //point I
  *Ix=Ax+AIdist*ADx;
  *Iz=Az+AIdist*ADz;

  //distance perpendicular Point_I
  *Point_I=SQRT(pow(1.0*(*Ix)-Px,2.0)+pow(1.0*(*Iz)-Pz,2.0));

  //does I laz on line AD
  int onlinex=0;
  int onlinez=0;

  if(Dx>=Ax && (*Ix>=Ax && *Ix<=Dx))
  onlinex=1;

  if(Dx<Ax &&  (*Ix>=Dx && *Ix<=Ax))
  onlinex=1;

  if(Dz>=Az && (*Iz>=Az && *Iz<=Dz))
  onlinez=1;

  if(Dz<Az &&  (*Iz>=Dz && *Iz<=Az))
  onlinez=1;


  if(onlinex==1 && onlinez==1)
  *online=1;
  else
  *online=0;
	}

}


/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
void XYpoints_along_3D_line_givenZ(float X1,float Y1,float Z1,float X2,float Y2,float Z2,float *Xp,float *Yp,float Zp,int *errorZ)
{
//calculates z of a point on a line given x y


//The parametric equations joining (x1,y1,z1) and (x2,y2,z2)
//x=(1-u)x1+ux2
//y=(1-u)y1+uy2
//z=(1-u)z1+uz2
//where taking u=1 gives the point (x2,y2,z2)
//where taking u=0 gives the point (x1,y1,z1)

float u;

*errorZ=0;

if(Z2-Z1!=0)      //Z is constant  means line is along x or y and cannot be used
u=(Zp-Z1)/(Z2-Z1);
else
*errorZ=1;

if(*errorZ!=1)   //Z is constant  means line is along x or y and cannot be used
{
   *Xp=(1-u)*X1+u*X2;
   *Yp=(1-u)*Y1+u*Y2;
}


//if both X Y are indeterminate i.e Zero line is along Z and z cannot be determined

}

/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
void ZYpoints_along_3D_line_givenX(float Z1,float Y1,float X1,float Z2,float Y2,float X2,float *Zp,float *Yp,float Xp,int *errorX)
{
//calculates z of a point on a line given x y


//The parametric equations joining (x1,y1,z1) and (x2,y2,z2)
//x=(1-u)x1+ux2
//y=(1-u)y1+uy2
//z=(1-u)z1+uz2
//where taking u=1 gives the point (x2,y2,z2)
//where taking u=0 gives the point (x1,y1,z1)

float u;

*errorX=0;

if(X2-X1!=0)      //X is constant  means line is along x or y and cannot be used
u=(Xp-X1)/(X2-X1);
else
*errorX=1;

if(*errorX!=1)   //X is constant  means line is along x or y and cannot be used
{
   *Zp=(1-u)*Z1+u*Z2;
   *Yp=(1-u)*Y1+u*Y2;
}


//if both Z Y are indeterminate i.e Xero line is along X and z cannot be determined

}

/////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////
void XZpoints_along_3D_line_givenY(float X1,float Z1,float Y1,float X2,float Z2,float Y2,float *Xp,float *Zp,float Yp,int *errorY)
{
//calculates z of a point on a line given x y


//The parametric equations joining (x1,y1,z1) and (x2,y2,z2)
//x=(1-u)x1+ux2
//y=(1-u)y1+uy2
//z=(1-u)z1+uz2
//where taking u=1 gives the point (x2,y2,z2)
//where taking u=0 gives the point (x1,y1,z1)

float u;

*errorY=0;

if(Y2-Y1!=0)      //Y is constant  means line is along x or y and cannot be used
u=(Yp-Y1)/(Y2-Y1);
else
*errorY=1;

if(*errorY!=1)   //Y is constant  means line is along x or y and cannot be used
{
   *Xp=(1-u)*X1+u*X2;
   *Zp=(1-u)*Z1+u*Z2;
}


//if both X Z are indeterminate i.e Yero line is along Y and z cannot be determined

}

/////////////////////////////////////////////////////////////////////////////////



void Intersect_of_line_with_cylZ(float X1,float Y1,float Z1,float X2,float Y2,float Z2,
float cylX,float cylY,float cylZ,float cylR,float cylL,int *withincyl_)
{

 int online,withincircle1,withincircle2,chordwithincircle,withincyl,linealongZ;
 float IX,IY;
 float Xnew,Ynew;

 online=0;
 withincircle1=0;
 withincircle2=0;
 chordwithincircle=0;
 withincyl=0;

 //first check any of the points within the circle
 if(SQRT(pow(1.0*cylX-X1,2)+pow(1.0*cylY-Y1,2))<=cylR)
 withincircle1=1;

 //if within Z limits then line must be within the cylinder
 if(withincircle1==1)
 {
  if(Z1>=cylZ && Z1<=cylZ+cylL)
  withincyl=1;
 }



 //first check any of the points within the circle
 if(SQRT(pow(1.0*cylX-X2,2)+pow(1.0*cylY-Y2,2))<=cylR)
 withincircle2=1;

  //if within Z limits then line must be within the cylinder
 if(withincircle2==1)
 {
  if(Z2>=cylZ && Z2<=cylZ+cylL)
  withincyl=1;
 }


  //next
 //if one point in circle and not within Z limits  and other not within circle it could clip bottom end circle
 //get the value of Z and y at Zlimit

 if(withincyl==0)
 {

 if((Z1<cylZ && Z2>cylZ))
 {
  XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+0.001,&linealongZ);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

 if((Z2<cylZ && Z1>cylZ))
 {
  XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+0.001,&linealongZ);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

   //next
 //if one point in circle and not within Z limits  and other not within circle it could clip top end circle
 //get the value of Z and y at Zlimit

 if((Z1<cylZ+cylL && Z2>cylZ+cylL))
 {
  XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+cylL-0.001,&linealongZ);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

 if((Z2<cylZ+cylL && Z1>cylZ+cylL))
 {
  XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+cylL-0.001,&linealongZ);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

 }


  if(withincyl==0)
 {

 //if both points outside circle line could cross though circle as a chord

 //check within  circle in case points not withinn circle but chord between is
 if(withincircle1==0 && withincircle2==0)
 {
 float PointI;
  point_from_2DlineXY(X1,Y1,X2,Y2,cylX,cylY,&IX,&IY,&PointI,&online);
  if(PointI<=cylR && online==1)
  chordwithincircle=1;

  if(chordwithincircle==1)
  {
  //if both points within Z limits
  if((Z1>=cylZ && Z1<=cylZ+cylL) && (Z2>=cylZ && Z2<=cylZ+cylL))
  withincyl=1;


		// check this is correct same code as above   ???
		//?????????????????????????????????????
		//if one point in circle and not within Z limits  and other not within circle it could clip top end circle
		//get the value of Z and y at Zlimit


		//next
		//if one point in circle and not within Z limits  and other not within circle it could clip bottom end circle
		//get the value of Z and y at Zlimit

		if(withincyl==0)
		{

		if((Z1<cylZ && Z2>cylZ))
		{
		XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+0.001,&linealongZ);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		if((Z2<cylZ && Z1>cylZ))
		{
		XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+0.001,&linealongZ);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		//next
		//if one point in circle and not within Z limits  and other not within circle it could clip top end circle
		//get the value of Z and y at Zlimit

		if((Z1<cylZ+cylL && Z2>cylZ+cylL))
		{
		XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+cylL-0.001,&linealongZ);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		if((Z2<cylZ+cylL && Z1>cylZ+cylL))
		{
		XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+cylL-0.001,&linealongZ);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		}
		//// check this is correct    ???
        ////?????????????????????????????????????

	}//chord within circle


 }

  }


 *withincyl_=withincyl;




}


/////////////////////////////////////////////////////////////////////////////////



void Intersect_of_line_with_cylX(float Z1,float Y1,float X1,float Z2,float Y2,float X2,
float cylZ,float cylY,float cylX,float cylR,float cylL,int *withincyl_)
{

 int online,withincircle1,withincircle2,chordwithincircle,withincyl,linealongX;
 float IZ,IY;
 float Znew,Ynew;

 online=0;
 withincircle1=0;
 withincircle2=0;
 chordwithincircle=0;
 withincyl=0;

 //first check any of the points within the circle
 if(SQRT(pow(1.0*cylZ-Z1,2)+pow(1.0*cylY-Y1,2))<=cylR)
 withincircle1=1;

 //if within X limits then line must be within the cylinder
 if(withincircle1==1)
 {
  if(X1>=cylX && X1<=cylX+cylL)
  withincyl=1;
 }



 //first check any of the points within the circle
 if(SQRT(pow(1.0*cylZ-Z2,2)+pow(1.0*cylY-Y2,2))<=cylR)
 withincircle2=1;

  //if within X limits then line must be within the cylinder
 if(withincircle2==1)
 {
  if(X2>=cylX && X2<=cylX+cylL)
  withincyl=1;
 }


  //next
 //if one point in circle and not within X limits  and other not within circle it could clip bottom end circle
 //get the value of X and y at Xlimit

 if(withincyl==0)
 {

 if((X1<cylX && X2>cylX))
 {
  ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+0.001,&linealongX);
   if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

 if((X2<cylX && X1>cylX))
 {
  ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+0.001,&linealongX);
   if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

   //next
 //if one point in circle and not within X limits  and other not within circle it could clip top end circle
 //get the value of X and y at Xlimit

 if((X1<cylX+cylL && X2>cylX+cylL))
 {
  ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+cylL-0.001,&linealongX);
   if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

 if((X2<cylX+cylL && X1>cylX+cylL))
 {
  ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+cylL-0.001,&linealongX);
   if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
   withincyl=1;
 }

 }


  if(withincyl==0)
 {

 //if both points outside circle line could cross though circle as a chord

 //check within  circle in case points not withinn circle but chord between is
 if(withincircle1==0 && withincircle2==0)
 {
 float PointI;
  point_from_2DlineZY(Z1,Y1,Z2,Y2,cylZ,cylY,&IZ,&IY,&PointI,&online);
  if(PointI<=cylR && online==1)
  chordwithincircle=1;

  if(chordwithincircle==1)
  {
  //if both points within X limits
  if((X1>=cylX && X1<=cylX+cylL) && (X2>=cylX && X2<=cylX+cylL))
  withincyl=1;


		// check this is correct same code as above   ???
		//?????????????????????????????????????
		//if one point in circle and not within X limits  and other not within circle it could clip top end circle
		//get the value of X and y at Xlimit


		//next
		//if one point in circle and not within X limits  and other not within circle it could clip bottom end circle
		//get the value of X and y at Xlimit

		if(withincyl==0)
		{

		if((X1<cylX && X2>cylX))
		{
		ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+0.001,&linealongX);
		if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		if((X2<cylX && X1>cylX))
		{
		ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+0.001,&linealongX);
		if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		//next
		//if one point in circle and not within X limits  and other not within circle it could clip top end circle
		//get the value of X and y at Xlimit

		if((X1<cylX+cylL && X2>cylX+cylL))
		{
		ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+cylL-0.001,&linealongX);
		if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		if((X2<cylX+cylL && X1>cylX+cylL))
		{
		ZYpoints_along_3D_line_givenX(Z1,Y1,X1,Z2,Y2,X2,&Znew,&Ynew,cylX+cylL-0.001,&linealongX);
		if(SQRT(pow(1.0*cylZ-Znew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		}
		//// check this is correct    ???
        ////?????????????????????????????????????

	}//chord within circle


 }

  }


 *withincyl_=withincyl;



}







void Intersect_of_line_with_cylY(float X1,float Z1,float Y1,float X2,float Z2,float Y2,
float cylX,float cylZ,float cylY,float cylR,float cylL,int *withincyl_)
{

 int online,withincircle1,withincircle2,chordwithincircle,withincyl,linealongY;
 float IX,IZ;
 float Xnew,Znew;

 online=0;
 withincircle1=0;
 withincircle2=0;
 chordwithincircle=0;
 withincyl=0;

 //first check any of the points within the circle
 if(SQRT(pow(1.0*cylX-X1,2)+pow(1.0*cylZ-Z1,2))<=cylR)
 withincircle1=1;

 //if within Y limits then line must be within the cylinder
 if(withincircle1==1)
 {
  if(Y1>=cylY && Y1<=cylY+cylL)
  withincyl=1;



 }



 //first check any of the points within the circle
 if(SQRT(pow(1.0*cylX-X2,2)+pow(1.0*cylZ-Z2,2))<=cylR)
 withincircle2=1;

  //if within Y limits then line must be within the cylinder
 if(withincircle2==1)
 {
  if(Y2>=cylY && Y2<=cylY+cylL)
  withincyl=1;


 }


  //next
 //if one point in circle and not within Y limits  and other not within circle it could clip bottom end circle
 //get the value of Y and y at Ylimit

 if(withincyl==0)
 {

 if((Y1<cylY && Y2>cylY))
 {
  XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+0.001,&linealongY);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
   withincyl=1;


 }

 if((Y2<cylY && Y1>cylY))
 {
  XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+0.001,&linealongY);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
   withincyl=1;


 }

   //next
 //if one point in circle and not within Y limits  and other not within circle it could clip top end circle
 //get the value of Y and y at Ylimit

 if((Y1<cylY+cylL && Y2>cylY+cylL))
 {
  XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+cylL-0.001,&linealongY);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
   withincyl=1;

 }

 if((Y2<cylY+cylL && Y1>cylY+cylL))
 {
  XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+cylL-0.001,&linealongY);
   if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
   withincyl=1;


 }

 }


  if(withincyl==0)
 {

 //if both points outside circle line could cross though circle as a chord

 //check within  circle in case points not withinn circle but chord between is
 if(withincircle1==0 && withincircle2==0)
 {
 float PointI;
  point_from_2DlineXZ(X1,Z1,X2,Z2,cylX,cylZ,&IX,&IZ,&PointI,&online);
  if(PointI<=cylR && online==1)
  chordwithincircle=1;

  if(chordwithincircle==1)
  {
  //if both points within Y limits
  if((Y1>=cylY && Y1<=cylY+cylL) && (Y2>=cylY && Y2<=cylY+cylL))
  withincyl=1;






		// check this is correct same code as above   ???
		//?????????????????????????????????????
		//if one point in circle and not within Y limits  and other not within circle it could clip top end circle
		//get the value of Y and y at Ylimit


		//next
		//if one point in circle and not within Y limits  and other not within circle it could clip bottom end circle
		//get the value of Y and y at Ylimit

		if(withincyl==0)
		{

		if((Y1<cylY && Y2>cylY))
		{
		XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+0.001,&linealongY);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
		withincyl=1;


		}

		if((Y2<cylY && Y1>cylY))
		{
		XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+0.001,&linealongY);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
		withincyl=1;


		}

		//next
		//if one point in circle and not within Y limits  and other not within circle it could clip top end circle
		//get the value of Y and y at Ylimit

		if((Y1<cylY+cylL && Y2>cylY+cylL))
		{
		XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+cylL-0.001,&linealongY);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
		withincyl=1;


		}

		if((Y2<cylY+cylL && Y1>cylY+cylL))
		{
		XZpoints_along_3D_line_givenY(X1,Z1,Y1,X2,Z2,Y2,&Xnew,&Znew,cylY+cylL-0.001,&linealongY);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylZ-Znew,2))<=cylR)
		withincyl=1;


		}

		}
		//// check this is correct    ???
        ////?????????????????????????????????????

	}//chord within circle


 }

  }


 *withincyl_=withincyl;



}







/////////////////////////////////////////////////////////////////////////////////

void Intersect_of_line_with_circ_innerZ(float X1,float Y1,float Z1,float X2,float Y2,float Z2,
float cylX,float cylY,float cylZ,float cylR,int *withincyl_)
{

 int withincyl,linealongz;
 float Ix,Iy;
 float Xnew,Ynew;


 withincyl=0;


 //if both points in z plane
 if(Z1==cylZ && Z2==cylZ)
 {
	Z1=Z1+0.0001;
	Z2=Z2-0.0001;
 }


		if(withincyl==0)
		{

		if((Z1<cylZ && Z2>cylZ))
		{
		XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+0.001,&linealongz);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		if((Z2<cylZ && Z1>cylZ))
		{
		XYpoints_along_3D_line_givenZ(X1,Y1,Z1,X2,Y2,Z2,&Xnew,&Ynew,cylZ+0.001,&linealongz);
		if(SQRT(pow(1.0*cylX-Xnew,2)+pow(1.0*cylY-Ynew,2))<=cylR)
		withincyl=1;
		}

		}




 *withincyl_=withincyl;

}

/////////////////////////////////////////////////////////////////////////////////





void Intersect_of_line_with_sphere(float X1,float Y1,float Z1,float X2,float Y2,float Z2,
float sphX_,float sphY,float sphZ_,float sphR_,int resolut,int *withinsph_)
{

int intersect;
int withinsph=0;
float sphR,sphZ;

//min resolution 100 recommended

 //Z axis
 for(int i=1;i<resolut-1;++i)
 {
  sphR=sphR_*cos(-M_PI/2.0+M_PI*i/(resolut-1.0));
  sphZ=sphZ_+sphR_*sin(-M_PI/2.0+M_PI*i/(resolut-1.0));
  Intersect_of_line_with_circ_innerZ(X1,Y1,Z1,X2,Y2,Z2,sphX_,sphY,sphZ,sphR,&intersect);

   if(intersect==1)
   {
   withinsph=1;
   i=10000;
   }
 }




*withinsph_=withinsph;
}

/////////////////////////////////////////////////////////////////////////////////




