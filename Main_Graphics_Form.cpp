//---------------------------------------------------------------------------
//© Dontyne Systems Ltd 2021

#include <vcl.h>
#pragma hdrstop

#include "STRFMT.h"


#include <GL/gl.h>
#include <GL/glu.h>

#include "Main_Graphics_Form.h"

#include "progressform.h"

#include "Meshplot2D.h"

#include "Matrix_alloc.h"


#include "math_functions.h"
#include "Clash_checks.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"

FILE *diagnosticfile;
//int diagnoistics=0;


int showonce=0;

int extern z,hand,units_type;

float extern lengthunit;

float extern Mn,alpha,Beta,x1,da,df,rhof,prot_resid,chamfer,chamferang,b,bore;

float extern  d_inv_act,lead,meas_dia_bottom,meas_dia_top,meas_dia_middle;

float extern stemdia,balldia,stemlength,totalspan;

float extern gearxpos,gearypos,gearzpos,geartheta,approachdist;

float extern toothprofile[500][2];

float  extern **X,**Y,**Z,**Xtemp,**Ytemp,**Ztemp,**Xn,**Yn,**Zn,**Xorig,**Yorig,**Zorig;



char extern orig_textbox_val[16],text_number[32];
bool extern changeflag;


void convert_to_3D(void);
void Vector_normal(float,float,float,float,float,float,float[3]);
void Formcalculate_normals(int,int,int,int,float);
int check_clash(float,float,float,int);

int fontsize=8;
int detectclash=0;
int clashoccurred;

int sampx,sampy,Notip,Nop,Nof,Nor;

int profilestep;
int currenttooth;
int currentprobe;






GLfloat  zoomgl;
GLfloat	 xrot;				// X Rotation
GLfloat  yrot;				// Y Rotation
GLfloat	 zrot;				// Z Rotation

//GLfloat	 Trot;				// Z Rotation

GLfloat	LightAmbient[]={0.3f,0.3f,0.3f,1.0f};	    //Ambient Light Values
GLfloat	LightDiffuse[]={0.7f,0.7f,0.7f,1.0f};	    //Diffuse Light Values
GLfloat	LightSpecular[]={0.3f,0.3f,0.3f,0.0};	    //Light Specular


GLfloat	LightPosition[]={0.0f,0.0f,1.0f,0.0};	    //Light Position
GLfloat	Light1Position[]={0.0f,0.0f,-1.0f,0.0f};	    //Light Position

GLfloat shininess[]={128.0};
GLfloat mat_amb[]={0.1,0.1,0.1,1.0 };
GLfloat mat_diff[]={0.9,0.9,0.9,1.0};
GLfloat mat_specular[]={0.6,0.6,0.6,1.0 };

GLfloat mat_ambg[]={0.1,0.1,0.1,1.0 };
GLfloat mat_diffg[]={0.9,0.9,0.9,1.0};
GLfloat mat_specularg[]={0.6,0.6,0.6,1.0 };

GLfloat mat_ambb[]={0.1,0.1,0.1,1.0 };
GLfloat mat_diffb[]={1.0,1.0,1.0,1.0};   //Initial back color of G-code  plot
GLfloat mat_specularb[]={0.6,0.6,0.6,1.0 };


//directional light along z axis


GLfloat LightPosition1[]={ 0.1f, 0.1f,-0.8f,0.0f};
GLfloat LightPosition2[]={ 0.1f, 0.1f,0.8f,0.0f};
GLfloat LightPosition3[]={ 0.1f, 0.1f,-0.8f,0.0f};

GLUquadricObj *qobj;
GLUquadricObj *qobj2;



float xscale,yscale; // graphics variables


int zoomwindow2,initialized;

 //integers to control appearance
int  autolimit;

int showteeth,showgrid,allowlighting;

int sectionX1,sectionY1,sectionX2,sectionY2;

//end these variables are the material and light colors and positions




void  Vector_normal(float,float,float,float,float,float,float[3]);


float  normal_vector1[3],normal_vector2[3],normal_vector3[3],normal_vector4[3],
normal_vector5[3],normal_vector6[3],normal_vector7[3],normal_vector8[3],
normal_vector9[3],normal_vectorave[3];


float  zmin,zmax,ymin,ymax,xmin,xmax,gleft,gright,gtop,gbottom;

float   zoomlevel,xpanlevel,ypanlevel,yrottemp;
float   leftgl,rightgl,bottomgl,topgl,xpanlevelgl,ypanlevelgl;
float	temprrot;


float   zoomlevelgl3D,xpanlevelgl3D,ypanlevelgl3D,xscale3D,yscale3D,
xrotlevelgl3D,yrotlevelgl3D,zrotlevelgl3D; // graphics variables
float borgl;

float  mounting_angle;



float probeX=0,probeY=0,probeZ;





TEquator_Helical_Graphics_Check_form *Equator_Helical_Graphics_Check_form;
//---------------------------------------------------------------------------
__fastcall TEquator_Helical_Graphics_Check_form::TEquator_Helical_Graphics_Check_form(TComponent* Owner)
	: TForm(Owner)
{
//OPenGL Directly
 _control87(MCW_EM, MCW_EM);

}



void __fastcall TEquator_Helical_Graphics_Check_form::Setmaintextboxes(void)
{



if(units_type==0)
{
 lengthunit=1.0;
 Labelunits->Caption="All length units in mm unless stated otherwise";

}
else
{
 lengthunit=25.5;
 Labelunits->Caption="All length units in inch unless stated otherwise";
}




   {
   char labelteethtext[128];
   char labelteethtext2[128];
   strcpy(labelteethtext,"");

   for(int m=0;m<4;++m)
  {
     int ctooth;
	 float ctoothf;
	 ctoothf=z/4.0*m;

	 if(ctoothf-floor(ctoothf)<0.5)
		ctooth=floor(ctoothf)+1;
		else
		ctooth=ceil(ctoothf)+1;

	 sprintf(labelteethtext2,"%-3d",ctooth);
	 strcat(labelteethtext,labelteethtext2);

  }
	 Labelteethn->Caption=labelteethtext;
  }


	sprintf(text_number,"%-0.3f",geartheta); //convert double to a string in correct format
	gearthetaedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",geartheta); //convert double to a string in correct format
	gearthetaedit->Hint=text_number; // assign hint

	sprintf(text_number,"%-0.3f",gearzpos/lengthunit); //convert double to a string in correct format
	gearzposedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",gearzpos/lengthunit); //convert double to a string in correct format
	gearzposedit->Hint=text_number; // assign hint

	sprintf(text_number,"%-0.3f",stemdia/lengthunit); //convert double to a string in correct format
	stemdiaedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",stemdia/lengthunit); //convert double to a string in correct format
	stemdiaedit->Hint=text_number; // assign hint


	sprintf(text_number,"%-0.3f",approachdist/lengthunit); //convert double to a string in correct format
	approachdistedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",approachdist/lengthunit); //convert double to a string in correct format
	approachdistedit->Hint=text_number; // assign hint


	sprintf(text_number,"%-0.3f",balldia/lengthunit); //convert double to a string in correct format
	balldiaedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",balldia/lengthunit); //convert double to a string in correct format
	balldiaedit->Hint=text_number; // assign hint


	sprintf(text_number,"%-0.3f",stemlength/lengthunit); //convert double to a string in correct format
	stemlengthedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",stemlength/lengthunit); //convert double to a string in correct format
	stemlengthedit->Hint=text_number; // assign hint


	sprintf(text_number,"%-0.3f",totalspan/lengthunit); //convert double to a string in correct format
	totalspanedit->Text=text_number; // assign ansi string for box checked string
	sprintf(text_number,"%-0.5f",totalspan/lengthunit); //convert double to a string in correct format
	totalspanedit->Hint=text_number; // assign hint



OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);

Progress_form->Visible=false;

}



//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::FormShow(TObject *Sender)
{

FILE *outfile;


if(showonce==0)
{


Nop=125;
Nor=125;
Notip=25;

if(Beta!=0)
lead=z*M_PI*Mn/sin(Beta*M_PI/180);
else
lead=1e8;

if(Beta>0)
Nof=ceil(b/lead*360)+2;  //minimum 3

if(Beta==0)
Nof=2.5*b/Mn;  //minimum 3


if(ComboBoxwidthdensity->ItemIndex==0) //very low
Nof=Nof*0.25;

if(ComboBoxwidthdensity->ItemIndex==1) //low
Nof=Nof*0.5;

if(ComboBoxwidthdensity->ItemIndex==3) //high
Nof=Nof*2;

if(Nof<3)
Nof=3;

//make sure odd so sample in middle

if(Nof*0.5-floor(Nof*0.5)==0)
Nof=Nof+1;


probeZ=1.25*b+gearzpos;

//calculate 2D Gear plot
meshplothobbedbasic2D(1,z,Mn,alpha,Beta,
df,da,x1,rhof,prot_resid,5,chamferang,chamfer,&d_inv_act,toothprofile);

//convert to 3D Gear Plot
convert_to_3D();

 for(int i=0;i<Nof;++i)
 {
  for(int j=0;j<2*(Nop+Nor);++j)
   {

	 Xorig[i][j]=X[i][j];
	 Yorig[i][j]=Y[i][j];
	 Zorig[i][j]=Z[i][j];
   }
 }


//rotate by theta and angular datum

 for(int i=0;i<Nof;++i)
 {
  for(int j=0;j<2*(Nop+Nor);++j)
   {
	 float temptheta=ATAN(X[i][j],Y[i][j]);
	 float tempr=SQRT(X[i][j]*X[i][j]+Y[i][j]*Y[i][j]);

	 temptheta=temptheta-RadioGroupangulardatum->ItemIndex*0.5*b/lead*(2*M_PI)*hand; //datum

	 temptheta=temptheta-geartheta*M_PI/180.0; //user entered angle

	 X[i][j]=tempr*sin(temptheta);
	 Y[i][j]=tempr*cos(temptheta);
   }
 }

//translate

 for(int i=0;i<Nof;++i)
 {
  for(int j=0;j<2*(Nop+Nor);++j)
   {

	 X[i][j]=X[i][j]+gearxpos;
	 Y[i][j]=Y[i][j]+gearypos;
	 Z[i][j]=Z[i][j]+gearzpos;
   }
 }



//calculate normals
Formcalculate_normals(Nop,Nor,Nof,Notip,chamfer);


  ComboBoxtoothtomeasure->Items->Clear();
 for(int i=1;i<=z;++i)
 {
 char temptext1[64];
 sprintf(temptext1,"%d",i);
 ComboBoxtoothtomeasure->Items->Add(temptext1);
 }
 ComboBoxtoothtomeasure->ItemIndex=0;





//outfile=fopen("test.dat","w");

//for(int i=0;i<2*(Nop+Nor);++i)
//{
//fprintf(outfile,"%8.4f %8.4f\n",toothprofile[i][0],toothprofile[i][1]);
//}


//fclose(outfile);


Setmaintextboxes(); //Reset all text boxe


showonce=1;
}

}
//---------------------------------------------------------------------------



void convert_to_3D(void)
{
float tempz,helixrot,bw;
int sections=Nof;


	for(int i=0;i<2*(Nop+Nor);++i)
	{
	for(int k=0;k<sections;++k) //each axial profile section
			{

		 if(sections>1)
		 helixrot=hand*(b/lead*2*M_PI/(1.0*sections-1.0))*k; //amount to rotate for helix
		 else
		 helixrot=0;

		 if(sections>1)
		 tempz=b/(1.0*sections-1)*k;
		 else
		 tempz=0*k;


		 float temptheta=ATAN(toothprofile[i][0],toothprofile[i][1])+helixrot;
		 float tempr=SQRT(toothprofile[i][0]*toothprofile[i][0]+toothprofile[i][1]*toothprofile[i][1]);




		//root
		X[k][i]=tempr*sin(temptheta);
		Y[k][i]=tempr*cos(temptheta);
		Z[k][i]=tempz;
		   }
	 }
}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void Formcalculate_normals(int Nop,int Nor,int Nof,int Notip,float dchamfer)
{
int sign1,sign2,itemp1,itemp2,jtemp1,jtemp2;

float tempx,tempy,tempz,nx,ny,nz;

int Notiptemp;
//calculate normals

//calculate normals also for export

 if(dchamfer>0)              //need to consider chamfer also as tip.
 Notiptemp=Notip+1;
 else
 Notiptemp=Notip;


	 for(int i=0;i<(Nor+Nop)*2;++i)
	 {
	 for(int j=0;j<Nof;++j)
	 {


	 if(j<Nof-1)
	 {
	 jtemp1=j;
	 jtemp2=j+1;
	 sign1=1;          //1
	 }
	 else
	 {
	 jtemp1=j;
	 jtemp2=j-1;
	 sign1=-1;     //-1
	 }



	 if((i>=0 && i<Nor+Nop-Notiptemp-1)
	 || i==Nor+Nop+Notiptemp
	 || (i>Nor+Nop-Notiptemp-1 && i<Nop+Nor) ) //forward a samp
	 {
	 itemp1=i+1;
	 itemp2=i;
	 sign2=1;   //1
	 }
	 else

	 if((i>Nor+Nop+Notiptemp)
	 || i==Nor+Nop-Notiptemp-1
	 || (i<Nor+Nop+Notiptemp && i>=Nop+Nor)) //back a sample
	 {
	 itemp1=i-1;
	 itemp2=i;
	 sign2=-1;      //-1
	 }



	 calc_norm(
	 X[j][i],Y[j][i],Z[j][i],
	 X[jtemp1][itemp1],Y[jtemp1][itemp1],Z[jtemp1][itemp1],
	 X[jtemp2][itemp2],Y[jtemp2][itemp2],Z[jtemp2][itemp2],
	 &nx, &ny, &nz);


	 //end calculate normals



	  tempx=nx*sign1*sign2;          //nx
	  tempy=ny*sign1*sign2;          //ny
	  tempz=nz*sign1*sign2;    //-nz


	  Xn[j][i]=tempx;
	  Yn[j][i]=tempy;
	  Zn[j][i]=tempz;

	 }
	 }
	 //end calculate normals

}
////////////////////////////


void __fastcall TEquator_Helical_Graphics_Check_form::FormCreate(TObject *Sender)

{

//oncreate

//OPenGL Directly


   //hdc = GetDC(Handle);

   // Get OpenGL Panel DeviceContext Handle

	hdc = GetDC( this->OpenGLAPPanel->Handle );


	SetPixelFormatDescriptor();
	hrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hrc);
	SetupRC();




	OpenGLAPPanelInit(Equator_Helical_Graphics_Check_form);
//end OPenGL directly
////////////////////







X=matrix_float(0,500,0,500);  //create matrix
Y=matrix_float(0,500,0,500);
Z=matrix_float(0,500,0,500);

Xtemp=matrix_float(0,500,0,500);  //create matrix
Ytemp=matrix_float(0,500,0,500);
Ztemp=matrix_float(0,500,0,500);

Xn=matrix_float(0,500,0,500);  //create matrix
Yn=matrix_float(0,500,0,500);
Zn=matrix_float(0,500,0,500);

Xorig=matrix_float(0,500,0,500);  //create matrix
Yorig=matrix_float(0,500,0,500);
Zorig=matrix_float(0,500,0,500);


		zoomlevel=1;
        xpanlevel=0;
        ypanlevel=0;
        xpanlevelgl=0;
        ypanlevelgl=0;
        zoomgl=1;
		yrot=45;



		zoomwindow2=0;
		initialized=0;
		autolimit=1;

		showteeth=z;
		showgrid=0;
		allowlighting=1;

		mounting_angle=0;


        TrackBarX->Position=-24;
		xrotlevelgl3D=TrackBarX->Position*2.5;
		TrackBarY->Position=0;
		yrotlevelgl3D=TrackBarY->Position*2.5;
		TrackBarZ->Position=0;
		zrotlevelgl3D=TrackBarZ->Position*2.5;




	   // rotang=0;
		//rotang2=0;
		Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::OpenGLAPPanelPaint(TObject *Sender)

{



		float  tempx,tempy,tempz,tempx1,tempy1,tempz1,tempx2,tempy2,tempz2,tempx3,tempy3,tempz3,
		tempx4,tempy4,tempz4;

        float alphaval;



			 //each time the openGL picture is repainted the following code applies

	   //ZOOM HERE

		tempx1=OpenGLAPPanel->Width ;
		tempx2=OpenGLAPPanel->Height;

		   glViewport(0,0,tempx1,tempx2);     //red book page 91   //set the viewing area here
		  //x,y, width,height       //this is usually the panel size on the form

			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix


	   //	left= -500/2.0;
	   //	right= 500/2.0;
	   ///	top=500/2.0;
	   //	bottom=-500/2.0;




	   //	if(pin_or_wheel==0)
		{
		tempz=da;
		leftgl=zoomgl*(-(tempz/1.5+tempz/1.8)/2)-xpanlevelgl;
		rightgl=zoomgl*((tempz/1.5+tempz/1.8)/2)-xpanlevelgl;
		bottomgl=zoomgl*(-(tempz/1.5+tempz/1.8)/2)*tempx2/tempx1+ypanlevelgl;
		topgl=zoomgl*((tempz/1.5+tempz/1.8)/2)*tempx2/tempx1+ypanlevelgl;
		}

		 glOrtho(leftgl,rightgl,bottomgl,topgl,-212.133,212.133);  //use orthographic so not distorted.
                                                   //150 squared rooted diagonal




 if(RadioButtonprt->Checked==true)
 {
 mat_diffg[0]=pow((20-TrackBarRed->Position),1/5.0)/1.821;
 mat_ambg[0]=pow((20-TrackBarRed->Position),8.0)/8.15e10+0.09;
 mat_specularg[0]=pow((20-TrackBarRed->Position),1.19)/35.34;

 mat_diffg[2]=pow((20-TrackBarBlue->Position),1/5.0)/1.821;
 mat_ambg[2]=pow((20-TrackBarBlue->Position),8.0)/8.15e10+0.09;
 mat_specularg[2]=pow((20-TrackBarBlue->Position),1.19)/35.34;

 mat_diffg[1]=pow((20-TrackBarGreen->Position),1/5.0)/1.821;
 mat_ambg[1]=pow((20-TrackBarGreen->Position),8.0)/8.15e10+0.09;
 mat_specularg[1]=pow((20-TrackBarGreen->Position),1.19)/35.34;
 }


  if(RadioButtonbk->Checked==true)
 {
 mat_diffb[0]=pow((20-TrackBarRed->Position),1/5.0)/1.821;
 mat_ambb[0]=pow((20-TrackBarRed->Position),8.0)/8.15e10+0.09;
 mat_specularb[0]=pow((20-TrackBarRed->Position),1.19)/35.34;

 mat_diffb[2]=pow((20-TrackBarBlue->Position),1/5.0)/1.821;
 mat_ambb[2]=pow((20-TrackBarBlue->Position),8.0)/8.15e10+0.09;
 mat_specularb[2]=pow((20-TrackBarBlue->Position),1.19)/35.34;

 mat_diffb[1]=pow((20-TrackBarGreen->Position),1/5.0)/1.821;
 mat_ambb[1]=pow((20-TrackBarGreen->Position),8.0)/8.15e10+0.09;
 mat_specularb[1]=pow((20-TrackBarGreen->Position),1.19)/35.34;
 }



 mat_diff[0]= mat_diffg[0];
 mat_amb[0]=mat_ambg[0];
 mat_specular[0]=mat_specularg[0];

 mat_diff[1]= mat_diffg[1];
 mat_amb[1]=mat_ambg[1];
 mat_specular[1]=mat_specularg[1];

  mat_diff[2]= mat_diffg[2];
 mat_amb[2]=mat_ambg[2];
 mat_specular[2]=mat_specularg[2];





		glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Initialize viewing values
		glLoadIdentity();

			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);;
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);


		   //	 glClearColor(9.0f,9.0f,9.0f,0.0); //   glClearColor(R,G,B)  //change background color here

           glClearColor(mat_diffb[0],mat_diffb[1],mat_diffb[2],0.0); //white


			 glClearDepth(1.0f);

			 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear screen and depth buffer
			 								// Reset the current modelview matrix




		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		if(CheckBoxbtransparent->Checked==true)
		alphaval=0.4;
		else
        alphaval=1.0;


			sampx=Nof;//set samples here face
		   //	sampy=Nop*2+1+1;// profile
			sampy=2*(Nor+Nop);



		 zoomlevelgl3D=1.0/(TrackBarZoom->Position/75.000);
		 if(TrackBarZoom->Position>325)
		 zoomlevelgl3D=zoomlevelgl3D/(1+(TrackBarZoom->Position-325)/10.0);

		 zoomgl=zoomlevelgl3D;




		 xrotlevelgl3D=TrackBarX->Position*2.5;
		 yrotlevelgl3D=TrackBarY->Position*2.5;
		 zrotlevelgl3D=TrackBarZ->Position*2.5;

		 xrot=xrotlevelgl3D;
		 yrot=yrotlevelgl3D;
		 zrot=zrotlevelgl3D;






				glLoadIdentity();



			//limits of plot
				autolimit=1;

		    //enter limits here or autocalc below
				if(autolimit==0)
				{
				xmax=20;
				xmin=-20;
				ymin=20;
			    ymax=60;
			    zmax=40;
				zmin=40;
				}

				else
				{

					xmax=-1e9;
					xmin=1e9;
					ymax=-1e9;
					ymin=1e9;
					zmax=-1e9;
					zmin=1e9;

				for(int i=0;i<sampx;++i)
				{
					for(int j=0;j<sampy;++j)
					{
						 if(X[i][j]>xmax)
						 xmax=X[i][j];
						 if(X[i][j]<xmin)
						 xmin=X[i][j];

						  if(Y[i][j]>ymax)
						 ymax=Y[i][j];
						 if(Y[i][j]<ymin)
						 ymin=Y[i][j];

						  if(Z[i][j]>zmax)
						 zmax=Z[i][j];
						 if(Z[i][j]<zmin)
						 zmin=Z[i][j];


					}

				}

					tempy=(ymax-ymin);

					xmax=(xmax+xmin)/2.0+tempy;
					xmin=xmax-2*tempy;

					ymax=(ymax+ymin)/2.0+tempy;
					ymin=ymax-2*tempy;

					zmax=-(ymax+ymin)/2.0;
					zmin=-(ymax+ymin)/2.0;



				}



					   //sectionX1=0;
	   //	sectionx2= (sampx-1);
		sectionY1= 0;
		sectionY2= (sampy-1);


		sectionX2=(sampx-1);
		sectionX1=0;









             showteeth=z;

			 for(int k=0;k<showteeth;++k)  //teeth
				 {

		glLoadIdentity();


		 glRotatef(yrot,0.0f,1.0f,0.0f);
		 glRotatef(xrot,1.0f,0.0f,0.0f);
		 glRotatef(zrot,0.0f,0.0f,1.0f);

					 //Rotate the blank pitch angle
		glRotatef(mounting_angle*180/M_PI,1.0f,0.0f,0.0f);

			 temprrot=360.0/(1.0*z)*k;
		glRotatef(temprrot,0.0f,0.0f,1.0f);

		  //plot surface here




		for(int i=sectionX1;i<sectionX2;++i)  //i section
		{
		for(int j=sectionY1;j<sectionY2;++j)   //j section
		{






	 //	if(Notip!=0 || (Notip==0 &&(j<Nop+Nor-25 || j>Nop+Nor+24 ) ) )
		 {


         //quad to be plotted

		 int tempi=i;
		 int tempj=j;







		 for(int l=9;l>0;--l)       //normal vectors around
         {

         if(l==9)
         {
         i=tempi-1;
         j=tempj-1;
         }
         if(l==8)
         {
         i=tempi;
         j=tempj-1;
         }
         if(l==7)
         {
		 i=tempi+1;
         j=tempj-1;
         }
         if(l==6)
         {
         i=tempi+1;
         j=tempj;
         }
         if(l==5)
         {
         i=tempi+1;
         j=tempj+1;
         }

         if(l==4)
         {
         i=tempi;
         j=tempj+1;
         }
         if(l==3)
         {
         i=tempi-1;
         j=tempj+1;
         }
         if(l==2)
         {
         i=tempi-1;
         j=tempj;
         }
         if(l==1)
		 {
         i=tempi;
         j=tempj;
		 }








         if(i<0)
         i=0;
         if(j<0)
         j=0;
         if(i>=sampx-1)
         i=sampx-2;
		 if(j>=sampy-1)
		 j=sampy-2;




				tempx1=X[i][j];
				tempy1=Y[i][j];
				tempz1=Z[i][j];

				tempx2=X[i][j+1];
				tempy2=Y[i][j+1];
				tempz2=Z[i][j+1];

				tempx3=X[i+1][j+1];
				tempy3=Y[i+1][j+1];
				tempz3=Z[i+1][j+1];

				tempx4=X[i+1][j];
				tempy4=Y[i+1][j];
				tempz4=Z[i+1][j];


					//shadow problem with bottom root sample

		  // if(j!=Nop+Nor-Notip-1 && j!=Nop+Nor+Notip)
		   {

           if(l==1)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
		   tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector1);
           if(l==2)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector2);
           if(l==3)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector3);
           if(l==4)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector4);
           if(l==5)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector5);
           if(l==6)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector6);
           if(l==7)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector7);
           if(l==8)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
           tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector8);
           if(l==9)
           Vector_normal(tempx1-tempx2,tempy1-tempy2,tempz1-tempz2,
		   tempx2-tempx3,tempy2-tempy3,tempz2-tempz3,normal_vector9);

		   }

         } //normal vectors around


         glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);





				{

				glBegin(GL_QUADS);


			  //Colors RGB  up to 1.0
					//Colors RGB  up to 1.0



				 for(int lgl=0;lgl<3;++lgl)
                {
                normal_vectorave[lgl]=(normal_vector1[lgl]+normal_vector2[lgl]
                +normal_vector9[lgl]+normal_vector8[lgl])/4.0;

                }

				glNormal3f(normal_vectorave[0],normal_vectorave[1],normal_vectorave[2]);

				glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],alphaval);




				glVertex3f(tempx1,tempy1,tempz1);


                  for(int lgl=0;lgl<3;++lgl)
                {
                normal_vectorave[lgl]=(normal_vector4[lgl]+normal_vector3[lgl]
                +normal_vector2[lgl]+normal_vector1[lgl])/4.0;

                }

                 glNormal3f(normal_vectorave[0],normal_vectorave[1],normal_vectorave[2]);


       	        glVertex3f(tempx2,tempy2,tempz2);


				  for(int lgl=0;lgl<3;++lgl)
				{
                normal_vectorave[lgl]=(normal_vector5[lgl]+normal_vector4[lgl]
                +normal_vector1[lgl]+normal_vector6[lgl])/4.0;

                }

                 glNormal3f(normal_vectorave[0],normal_vectorave[1],normal_vectorave[2]);



                glVertex3f(tempx3,tempy3,tempz3);


                for(int lgl=0;lgl<3;++lgl)
                {
                normal_vectorave[lgl]=(normal_vector6[lgl]+normal_vector1[lgl]
                +normal_vector8[lgl]+normal_vector7[lgl])/4.0;

                }

                 glNormal3f(normal_vectorave[0],normal_vectorave[1],normal_vectorave[2]);


                glVertex3f(tempx4,tempy4,tempz4);
				glEnd();  //end quads

				}///


				if(showgrid==1)    /////////////start grid
				{
				 glLineWidth(1);


					mat_diff[0]=0.5;
					mat_diff[1]=0.5;
					mat_diff[2]=0.9;


				// glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
				 glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],alphaval);

				// else
				   //	 glColor3f(0.1,0.1,0.9);



				glBegin(GL_LINE_LOOP);
				glVertex3f(tempx1,tempy1,tempz1-0.04);
				glVertex3f(tempx2,tempy2,tempz2-0.04);
				glVertex3f(tempx3,tempy3,tempz3-0.04);
				glVertex3f(tempx4,tempy4,tempz4-0.04);
				glEnd();
				}               ///////////////////end grid









				  }//tipo





					//show normals
				if((CheckBoxnormals->Checked==true ))// && k==0))

				{
				if((j>=Nor && j<Nor+Nop-Notip) || ((j<2*(Nop+Nor)-Nor ) && j>=Nor+Nop+Notip))
			   //	if(j/5.0-floor(j/5.0)==0)
				{


				 glLineWidth(1);


					mat_diff[0]=0.9;
					mat_diff[1]=0.5;
					mat_diff[2]=0.5;


				 //glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
				 glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],alphaval);


				 glBegin(GL_LINE_LOOP);
				 glVertex3f(tempx1,tempy1,tempz1);
				 glVertex3f(tempx1+Xn[i][j]*0.5*balldia,tempy1+Yn[i][j]*0.5*balldia,tempz1+Zn[i][j]*0.5*balldia);
				 glEnd();

				  if(i==Nof-2)    //forward last samp on face
				  {
					glBegin(GL_LINE_LOOP);
				   glVertex3f(tempx4,tempy4,tempz4);
				   glVertex3f(tempx4+Xn[i][j]*0.5*balldia,tempy4+Yn[i][j]*0.5*balldia,tempz4+Zn[i][j]*0.5*balldia);
				   glEnd();

				  }



					mat_diff[0]= mat_diffg[0];
					mat_diff[1]= mat_diffg[1];
					mat_diff[2]= mat_diffg[2];
				   //	glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);

					glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],alphaval);
				}
				}
				//end show normals



				  //gear body
					   if(CheckBoxshowsides->Checked==true)
					   {

					if(i==sectionX2-1)
					{



					 tempx1=0.5*(X[i+1][0]+X[i+1][499]);
					 tempy1=0.5*(Y[i+1][0]+Y[i+1][499]);
					 tempz1=tempz3;
					 tempx2=0.5*(X[i+1][0]+X[i+1][499])+0.01;
					 tempy2=0.5*(Y[i+1][0]+Y[i+1][499])+0.01;
					 tempz2=tempz3;

                     glNormal3f(0.0,0.0,1.0);


				   glBegin(GL_QUADS);
				   glVertex3f(tempx1,tempy1,tempz1);
				   glVertex3f(tempx2,tempy2,tempz2);
				   glVertex3f(tempx3,tempy3,tempz3);
				   glVertex3f(tempx4,tempy4,tempz4);
				   glEnd();
				   }


					if(i==0)
					{



					 tempx3=0.5*(X[i+1][0]+X[i+1][499]);
					 tempy3=0.5*(Y[i+1][0]+Y[i+1][499]);
					 tempz3=tempz1;
					 tempx4=0.5*(X[i+1][0]+X[i+1][499])+0.01;
					 tempy4=0.5*(Y[i+1][0]+Y[i+1][499])+0.01;
					 tempz4=tempz1;

                     glNormal3f(0.0,0.0,1.0);


				   glBegin(GL_QUADS);
				   glVertex3f(tempx1,tempy1,tempz1);
				   glVertex3f(tempx2,tempy2,tempz2);
				   glVertex3f(tempx3,tempy3,tempz3);
				   glVertex3f(tempx4,tempy4,tempz4);
				   glEnd();
				   }




				   if(i==0 && j==0)
				   {
				   glTranslatef(0,0,gearzpos);

				   qobj = gluNewQuadric();
				   gluCylinder(qobj,bore*0.5,bore*0.5,b,50,5);

				   glNormal3f(0.0,0.0,-1.0);

				   gluDisk(qobj,bore*0.5,df*0.5,50,5);

				   glTranslatef(0,0,-gearzpos);  //translate back
				   }

					if(i==sectionX2-1 && j==0)
				   {
				  // qobj = gluNewQuadric();
				   glTranslatef(0,0,gearzpos);

				   glNormal3f(0.0,0.0,1.0);
				   glTranslatef(0,0,b);
				   gluDisk(qobj,bore*0.5,df*0.5,50,5);
				   glTranslatef(0,0,-b);

                   glTranslatef(0,0,-gearzpos);  //translate back


				   }





					   } //end gear body









				}//end i section face

			}//end j section     profile



			  }//end teeth     k








			  ///plot axis


              	  //z
		  glLoadIdentity(); //reset the view
		xrot=0;
		yrot=0;//
		zrot=0;   //if gear rotated 90
		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);



			 //z

			 mat_diff[2]=0.9;
		mat_amb[2]=0.5;
		mat_specular[2]=0.5;

		mat_diff[1]=0.3;
		mat_amb[1]=0.1;
		mat_specular[1]=0.1;

		mat_diff[0]=0.3;
		mat_amb[0]=0.1;
		mat_specular[0]=0.1;

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	   //	glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);

		glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);



		// if(Generic_CNC_form->RadioGroupmounting->ItemIndex==1)
		 glRotatef(0.0,0.0f,1.0f,0.0f);


		// if(bore>Mn)
	   //	 borgl=bore;
	   //	 else
		 borgl=0.75*df;

		 qobj2 = gluNewQuadric();

		 gluSphere(qobj2,(borgl/50.0)*0.3,10,10);



		 gluCylinder(qobj2,1*(borgl/50.0)*0.3,1*(borgl/50.0)*0.3,4*(borgl/50.0),10,5);
		 glTranslatef(0,0,4*(borgl/50.0));
		 gluCylinder(qobj2,2*(borgl/50.0)*0.3,0.001,1.5*(borgl/50.0),10,5);
		 gluDisk(qobj2,0.001,2*(borgl/50.0)*0.3,10,5);
		// glTranslatef(0,0,-10);







		 //x
		 glLoadIdentity(); //reset the view

		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);

			mat_diff[0]=0.9;
		mat_amb[0]=0.5;
		mat_specular[0]=0.5;

		mat_diff[2]=0.3;
		mat_amb[2]=0.1;
		mat_specular[2]=0.1;

		mat_diff[1]=0.3;
		mat_amb[1]=0.1;
		mat_specular[1]=0.1;



		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
        glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);

	   //   if(Generic_CNC_form->RadioGroupmounting->ItemIndex==1)

		glRotatef(90,0.0f,1.0f,0.0f);



		 gluCylinder(qobj2,1*(borgl/50.0)*0.3,1*(borgl/50.0)*0.3,4*(borgl/50.0),5,10);
		  glTranslatef(0,0,4*(borgl/50.0));
		 gluCylinder(qobj2,2*(borgl/50.0)*0.3,0.001,1.5*(borgl/50.0),10,5);
		 gluDisk(qobj2,0.001,2*(borgl/50.0)*0.3,10,5);
		// glTranslatef(0,0,-10);



		 //y
			 glLoadIdentity(); //reset the view

		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);


			mat_diff[1]=0.9;
		mat_amb[1]=0.5;
		mat_specular[1]=0.5;

		mat_diff[2]=0.3;
		mat_amb[2]=0.1;
		mat_specular[2]=0.1;

		mat_diff[0]=0.3;
		mat_amb[0]=0.1;
		mat_specular[0]=0.1;


		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
        glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);


		//datum line

			 glLineWidth(2);

				glTranslatef(0,0,gearzpos+RadioGroupangulardatum->ItemIndex*0.5*b);
				glBegin(GL_LINE_LOOP);
				glVertex3f(0.0,0.55*da,0.01);
				glVertex3f(0.0,0.0,0.05);
				glEnd();
				glTranslatef(0,0,-(gearzpos+RadioGroupangulardatum->ItemIndex*0.5*b));//translate back

	   //	 if(Generic_CNC_form->RadioGroupmounting->ItemIndex==1)
           glRotatef(-90,1.0f,0.0f,0.0f);

		gluCylinder(qobj2,1*(borgl/50.0)*0.3,1*(borgl/50.0)*0.3,4*(borgl/50.0),5,10);
		  glTranslatef(0,0,4*(borgl/50.0));
		 gluCylinder(qobj2,2*(borgl/50.0)*0.3,0.001,1.5*(borgl/50.0),10,5);
		 gluDisk(qobj2,0.001,2*(borgl/50.0)*0.3,10,5);
	  //	glTranslatef(0,0,-4*(borgl/50.0));// glTranslatef(0,0,-10);


			  //end plot axis




			  //plot table

			  if(CheckBoxshowtable->Checked==true)
			  {

						 glLoadIdentity(); //reset the view

		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);


		mat_diff[0]=0.5;
		mat_amb[0]=0.2;
		mat_specular[0]=0.2;

		mat_diff[2]=0.55;
		mat_amb[2]=0.25;
		mat_specular[2]=0.25;

		mat_diff[1]=0.5;
		mat_amb[1]=0.2;
		mat_specular[1]=0.2;



		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);

        glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);

              	glBegin(GL_QUADS);


				glNormal3f(0,0,1);

				//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);



				glVertex3f(-150,-150,0);
				glVertex3f(150,-150,0);
				glVertex3f(150,150,0);
				glVertex3f(-150,150,0);


				glEnd();  //end quads



				//grid

				 glLineWidth(2);

			mat_diff[0]=0.7;
			mat_amb[0]=0.3;
			mat_specular[0]=0.3;

			mat_diff[2]=0.8;
			mat_amb[2]=0.4;
			mat_specular[2]=0.4;

			mat_diff[1]=0.7;
			mat_amb[1]=0.3;
			mat_specular[1]=0.3;



			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		   //	glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);


				// glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);

                glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);

				for(int i=-150;i<=150;i=i+10)
				{
				tempx1=i;
				tempx2=tempx1;
				tempy1=-150;
				tempy2=150;
				glBegin(GL_LINE_LOOP);
				glVertex3f(tempx1,tempy1,0+0.01);
				glVertex3f(tempx2,tempy2,0+0.01);
				glEnd();
				}

                	for(int i=-150;i<=150;i=i+10)
				{
				tempx1=i;
				tempx2=tempx1;
				tempy1=-150;
				tempy2=150;
				glBegin(GL_LINE_LOOP);
				glVertex3f(tempy1,tempx1,0+0.01);
				glVertex3f(tempy2,tempx2,0+0.01);
				glEnd();
				}



				 ///////////////////end grid



              }


				//end plot table






			  //plot Stylus




			if(CheckBoxshowstylus->Checked==true)
			{


				//body

				glLoadIdentity(); //reset the view





		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);

		mat_diff[0]=0.8;
		mat_amb[0]=0.4;
		mat_specular[0]=0.4;

		mat_diff[1]=0.7;
		mat_amb[1]=0.3;
		mat_specular[1]=0.3;

		mat_diff[2]=0.7;
		mat_amb[2]=0.3;
		mat_specular[2]=0.3;

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);

        glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);

        glTranslatef(probeX,probeY,probeZ);

		glTranslatef(0.0,0.0,-stemlength*0.2);
		gluCylinder(qobj2,(totalspan-2*stemlength)*0.5,(totalspan-2*stemlength)*0.5,stemlength,30,4);

		gluDisk(qobj2,0.001,(totalspan-2*stemlength)*0.5,30,4);

		glTranslatef(0.0,0.0,stemlength);
		gluDisk(qobj2,0.001,(totalspan-2*stemlength)*0.5,30,4);




			 glLoadIdentity(); //reset the view

		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);

		mat_diff[0]=0.8;
		mat_amb[0]=0.4;
		mat_specular[0]=0.4;

		mat_diff[1]=0.8;
		mat_amb[1]=0.4;
		mat_specular[1]=0.4;

		mat_diff[2]=0.4;
		mat_amb[2]=0.2;
		mat_specular[2]=0.2;

		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
         glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);


        glTranslatef(probeX,probeY,probeZ);

		glRotatef(-90,1.0f,0.0f,0.0f);          //ydir


		glTranslatef(0.0,0.0,-0.5*totalspan);
		gluCylinder(qobj2,stemdia*0.5,stemdia*0.5,totalspan,15,5);

		mat_diff[0]=0.9;
		mat_amb[0]=0.5;
		mat_specular[0]=0.5;

		mat_diff[1]=0.4;
		mat_amb[1]=0.2;
		mat_specular[1]=0.2;

		mat_diff[2]=0.4;
		mat_amb[2]=0.2;
		mat_specular[2]=0.2;




		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
        glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);

		gluSphere(qobj2,balldia*0.5,15,15);

		glTranslatef(0.0,0.0,totalspan);

		gluSphere(qobj2,balldia*0.5,15,15);



			 glLoadIdentity(); //reset the view

		glRotatef(yrot+yrotlevelgl3D,0.0f,1.0f,0.0f);
		glRotatef(xrot+xrotlevelgl3D,1.0f,0.0f,0.0f);
		glRotatef(zrot+zrotlevelgl3D,0.0f,0.0f,1.0f);


		mat_diff[0]=0.8;
		mat_amb[0]=0.4;
		mat_specular[0]=0.4;

		mat_diff[1]=0.8;
		mat_amb[1]=0.4;
		mat_specular[1]=0.4;

		mat_diff[2]=0.4;
		mat_amb[2]=0.2;
		mat_specular[2]=0.2;


		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
	   //glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);
	   	glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);



		glTranslatef(probeX,probeY,probeZ);


		glRotatef(-90,0.0f,1.0f,0.0f);          //x dir


		glTranslatef(0.0,0.0,-0.5*totalspan);
		gluCylinder(qobj2,stemdia*0.5,stemdia*0.5,totalspan,15,5);




		mat_diff[0]=0.9;
		mat_amb[0]=0.5;
		mat_specular[0]=0.5;

		mat_diff[1]=0.4;
		mat_amb[1]=0.2;
		mat_specular[1]=0.2;

		mat_diff[2]=0.4;
		mat_amb[2]=0.2;
		mat_specular[2]=0.2;


		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb);
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
		glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
		//glColor3f(mat_diff[0],mat_diff[1],mat_diff[2]);
		glColor4f(mat_diff[0],mat_diff[1],mat_diff[2],1.0);

		gluSphere(qobj2,balldia*0.5,15,15);

		glTranslatef(0.0,0.0,totalspan);

		gluSphere(qobj2,balldia*0.5,20,20);


			 } //end plot probe




//onpaint
//OPenGL Directly
   SwapBuffers(hdc);

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



		void Vector_normal(float a1,float b1,float c1,float a2,float b2,
                float c2,float normal_vector1[3])
		{
        float vectorsize;

		normal_vector1[0]=b1*c2-b2*c1;
		normal_vector1[1]=-(a1*c2-a2*c1);
		normal_vector1[2]=a1*b2-a2*b1;


		vectorsize=     SQRT(normal_vector1[0]*normal_vector1[0]+
						normal_vector1[1]*normal_vector1[1]+
						normal_vector1[2]*normal_vector1[2]);


		if(vectorsize!=0)
		{
		normal_vector1[0]=normal_vector1[0]/vectorsize;
		normal_vector1[1]=normal_vector1[1]/vectorsize;
		normal_vector1[2]=normal_vector1[2]/vectorsize;
		}
		else
		{
		normal_vector1[0]=normal_vector1[0]/1.0;
		normal_vector1[1]=normal_vector1[1]/1.0;
		normal_vector1[2]=normal_vector1[2]/1.0;
		}

		}

//----------------------------------------------------------------------------







void __fastcall TEquator_Helical_Graphics_Check_form::OpenGLAPPanelClick(TObject *Sender)

{
Setmaintextboxes();
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::OpenGLAPPanelInit(TObject *Sender)
{


	 allowlighting=1;

		if(allowlighting>=1)
		{
		glEnable(GL_LIGHTING);

		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		glEnable(GL_LIGHT2);
		glEnable(GL_LIGHT3);
		glEnable(GL_LIGHTING);
		}
		else
		{
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		glDisable(GL_LIGHT2);
		glDisable(GL_LIGHT3);
		}



	   glShadeModel(GL_SMOOTH);
//        glClearColor(0.0,0.0,0.0,0.0); //black
		glClearColor(1.0,1.0,1.0,0.0); //white
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);



		LightPosition[0]= 0.0;	//z up //Light Position  //last zero means directional
	   LightPosition[1]= 0.5656-0.8*sin(M_PI/4.0);
	   LightPosition[2]= 0.8;
	   LightPosition[3]= 0.0;


	   LightPosition1[0]= 0.0;	//z up //Light Position  //last zero means directional
	   LightPosition1[1]=-(0.5656-0.8*sin(M_PI/4.0));
	   LightPosition1[2]= -0.8;
	   LightPosition1[3]= 0.0;


		LightPosition2[0]= 0.8;	//z up //Light Position  //last zero means directional
	   LightPosition2[1]= 0.5656-0.8*sin(M_PI/4.0);;
	   LightPosition2[2]= 0.0;
	   LightPosition2[3]= 0.0;

	   LightPosition3[0]= -0.8;	//z up //Light Position  //last zero means directional
	   LightPosition3[1]=-(0.5656-0.8*sin(M_PI/4.0));
	   LightPosition3[2]= -0.8;
	   LightPosition3[3]= 0.0;








		LightAmbient[0]= 0.1;	//z up //Light Position  //last zero means directional
	   LightAmbient[1]= 0.1;
	   LightAmbient[2]= 0.1;
	   LightAmbient[3]= 1.0;


	   LightDiffuse[0]= 0.5;	//z up //Light Position  //last zero means directional
	   LightDiffuse[1]= 0.5;
	   LightDiffuse[2]= 0.5;
	   LightDiffuse[3]= 1.0;

	   LightSpecular[0]= 0.1;	//z up //Light Position  //last zero means directional
	   LightSpecular[1]= 0.1;
	   LightSpecular[2]= 0.1;
	   LightSpecular[3]= 1.0;


	   mat_amb[0]= 0.1;	//z up //mat_ Position  //last zero means directional
	   mat_amb[1]= 0.1;
	   mat_amb[2]= 0.1;
	   mat_amb[3]= 1.0;


	   mat_diff[0]= 0.9;	//z up //mat_ Position  //last zero means directional
	   mat_diff[1]= 0.9;
	   mat_diff[2]= 0.9;
	   mat_diff[3]= 1.0;

	   mat_specular[0]= 0.6;	//z up //mat_ Position  //last zero means directional
	   mat_specular[1]= 0.6;
	   mat_specular[2]= 0.6;
	   mat_specular[3]= 1.0;


        glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

		glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmbient); //Setup The Ambient Light
		glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiffuse); //Setup The Difuse Light
		glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular); //Setup The Difuse Light
		glLightfv(GL_LIGHT0,GL_POSITION,LightPosition); //Setup The Light Position

		glLightfv(GL_LIGHT1,GL_AMBIENT,LightAmbient); //Setup The Ambient Light
		glLightfv(GL_LIGHT1,GL_DIFFUSE,LightDiffuse); //Setup The Difuse Light
		glLightfv(GL_LIGHT1,GL_SPECULAR,LightSpecular); //Setup The Difuse Light
		glLightfv(GL_LIGHT1,GL_POSITION,LightPosition1); //Setup The Light Position


		glLightfv(GL_LIGHT2,GL_AMBIENT,LightAmbient); //Setup The Ambient Light
		glLightfv(GL_LIGHT2,GL_DIFFUSE,LightDiffuse); //Setup The Difuse Light
		glLightfv(GL_LIGHT2,GL_SPECULAR,LightSpecular); //Setup The Difuse Light
		glLightfv(GL_LIGHT2,GL_POSITION,LightPosition2); //Setup The Light Position



		glLightfv(GL_LIGHT3,GL_AMBIENT,LightAmbient); //Setup The Ambient Light
		glLightfv(GL_LIGHT3,GL_DIFFUSE,LightDiffuse); //Setup The Difuse Light
		glLightfv(GL_LIGHT3,GL_SPECULAR,LightSpecular); //Setup The Difuse Light
		glLightfv(GL_LIGHT3,GL_POSITION,LightPosition3); //Setup The Light Position





        glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

        glEnable(GL_COLOR_MATERIAL);

        glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_amb); //assign the material properties
        glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diff);
        glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
		glMaterialfv(GL_FRONT,GL_SHININESS,shininess);


        if(initialized==0)
		resetButtonClick(Equator_Helical_Graphics_Check_form);

		initialized=1;
}
//---------------------------------------------------------------------------


void __fastcall TEquator_Helical_Graphics_Check_form::OpenGLAPPanelMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
 if(zoomwindow2==0)
		{
		xpanlevel=xpanlevel=X;
		ypanlevel=ypanlevel=Y;
		}

		if(zoomwindow2==4)
		{
		yrottemp=X;
		}
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::OpenGLAPPanelMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y)
{
if(initialized==0)
  OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);

  initialized=1;
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::OpenGLAPPanelMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(Button==mbLeft)
        {


		if(zoomwindow2==1)    // zoom in
        {
		zoomgl=zoomgl*0.8;
		OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
		}

		if(zoomwindow2==2)     //zoom out
        {
		zoomgl=zoomgl/0.8;
		OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
		}


        if(zoomwindow2==0)  //pan
        {
		xpanlevel=(X-xpanlevel)*(rightgl-leftgl)/(OpenGLAPPanel->Width*1.0);
		ypanlevel=(Y-ypanlevel)*(topgl-bottomgl)/(OpenGLAPPanel->Height*1.0);

		xpanlevelgl=xpanlevelgl+xpanlevel;
		ypanlevelgl=ypanlevelgl+ypanlevel;

		OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
		}

		if(zoomwindow2==4)  //rotate
		{

		yrot=yrot+(X-yrottemp)/446.0*180;
		if(yrot>360)
		yrot=yrot-360;

		if(yrot<-360)
		yrot=yrot+360;

		OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
		}

		}//emd left mouse

		else
		{
	 //	if(funct_limit>=2 || funct_limit<=-2)
	  //	PopupMenu1->Popup(Left+G_code_OpenGLform1->Left+X,Top+G_code_OpenGLform1->Top+Y);
		}

		OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
		OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::resetButtonClick(TObject *Sender)

{


xpanlevelgl=0;
//ypanlevelgl=Mn*8.0;


ypanlevelgl=b*0.85;


if(TrackBarZoom->Position!=58)
TrackBarZoom->Position=58;

zoomlevelgl3D=1.0/(TrackBarZoom->Position/75.000);
zoomgl=zoomlevelgl3D;




 //if(Generic_CNC_form->RadioGroupmounting->ItemIndex==1)
 {
TrackBarX->Position=-20;
xrotlevelgl3D=TrackBarX->Position*2.5;
TrackBarY->Position=0;
yrotlevelgl3D=TrackBarY->Position*2.5;
TrackBarZ->Position=-56;
zrotlevelgl3D=TrackBarZ->Position*2.5;
}






ComboBoxline->ItemIndex=Memo1->Lines->Count-1;

ComboBoxline->ItemIndex=Memo1->Lines->Count*0.5-1;


OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::Button4Click(TObject *Sender)

{
 OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::TrackBarBlueChange(TObject *Sender)

{
OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::fontbutton2MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
fontsize=fontsize-1;
Memo1->Font->Size=fontsize;
 OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::fontbutton1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
fontsize=fontsize+1;
Memo1->Font->Size=fontsize;
 OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::LabelrotxMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
TrackBarX->Position=0;
xrotlevelgl3D=TrackBarX->Position*2.5;




OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::LabelrotyMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{


{
TrackBarY->Position=0;
yrotlevelgl3D=TrackBarY->Position*2.5;
}



OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::LabelrotzMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
{
TrackBarZ->Position=0;
zrotlevelgl3D=TrackBarZ->Position*2.5;
}



OpenGLAPPanel->Repaint() ;
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::FormResize(TObject *Sender)

{
if(initialized==1)
{
 Equator_Helical_Graphics_Check_form->AutoSize=false;

 Panel1->Height=Equator_Helical_Graphics_Check_form->ClientHeight-Panel1->Top-5;
 Memo1->Height=Panel1->Height-Memo1->Top-30;

 Labelunits->Top=Panel1->Height-18;
  Labelcopyright->Top=Panel1->Height-18;

 OpenGLAPPanel->Width=Equator_Helical_Graphics_Check_form->ClientWidth-OpenGLAPPanel->Left-10;

 OpenGLAPPanel->Height=Equator_Helical_Graphics_Check_form->ClientHeight-OpenGLAPPanel->Top-10;



 //OpenGL Directly

 Equator_Helical_Graphics_Check_form->Repaint();

OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);


}

}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::CheckBoxshowstylusMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------


void __fastcall TEquator_Helical_Graphics_Check_form::ButtonupdateClick(TObject *Sender)

{

char temptext[512];

int meas_samp_bottom,meas_samp_top,meas_samp_middle;

		float stylusorientY13;
	float stylusorientX24;




	diagnosticfile=fopen("interferelog.txt","w");




	//
	Memo1->Font->Size=fontsize;
    Memo1->Font->Name="Lucida Console" ;

	Memo1->Lines->Clear();








    if(Beta!=0)
lead=z*M_PI*Mn/sin(Beta*M_PI/180);
else
lead=1e8;

if(Beta>0)
Nof=ceil(b/lead*360)+2;  //minimum 3

if(Beta==0)
Nof=2.5*b/Mn;  //minimum 3



if(ComboBoxwidthdensity->ItemIndex==0) //very low
Nof=Nof*0.25;

if(ComboBoxwidthdensity->ItemIndex==1) //low
Nof=Nof*0.5;

if(ComboBoxwidthdensity->ItemIndex==3) //high
Nof=Nof*2;

if(Nof<3)
Nof=3;

//make sure odd so sample in middle

if(Nof*0.5-floor(Nof*0.5)==0)
Nof=Nof+1;








  int sampline=0;

	ComboBoxline->Items->Clear();


  //v	Equator_Helical_Graphics_Check_form->Visible=false;










  //repeat for 4 teeth
 for(int m=0;m<4;++m)
  {


	if(CheckBox4teeth->Checked==false)
	{
	currenttooth=ComboBoxtoothtomeasure->ItemIndex+1;
	m=4;
	}
	else
	{

	 float currenttoothf;
	 currenttoothf=z/4.0*m;

	 if(currenttoothf-floor(currenttoothf)<0.5)
		currenttooth=floor(currenttoothf)+1;
		else
		currenttooth=ceil(currenttoothf)+1;
	}




//which probe to use

//current tooth angle from datum
float currenttooth_ang_dat=geartheta*M_PI/180.0+(currenttooth-1)*(2*M_PI/(1.0*z));

if(currenttooth_ang_dat*180/M_PI<=45)
currentprobe=1;
else
if(currenttooth_ang_dat*180/M_PI<=135)
currentprobe=2;
else
if(currenttooth_ang_dat*180/M_PI<=225)
currentprobe=3;
else
if(currenttooth_ang_dat*180/M_PI>225)
currentprobe=4;


	if(currentprobe==1)
	{
	stylusorientY13=0.5*totalspan;
	stylusorientX24=0;
	}
	if(currentprobe==3)
	{
	stylusorientY13=-0.5*totalspan;
	stylusorientX24=0;
	}


	if(currentprobe==2)
	{
	stylusorientY13=0;
	stylusorientX24=-0.5*totalspan;
	}
	if(currentprobe==4)
	{
	stylusorientY13=0;
	stylusorientX24=0.5*totalspan;
	}




//calculate 2D Gear plot
meshplothobbedbasic2D(1,z,Mn,alpha,Beta,
df,da,x1,rhof,prot_resid,5,chamferang,chamfer,&d_inv_act,toothprofile);

//convert to 3D Gear Plot
convert_to_3D();

//rotate by theta

 for(int i=0;i<Nof;++i)
 {
  for(int j=0;j<2*(Nop+Nor);++j)
   {
	 float temptheta=ATAN(X[i][j],Y[i][j]);
	 float tempr=SQRT(X[i][j]*X[i][j]+Y[i][j]*Y[i][j]);

	 temptheta=temptheta-RadioGroupangulardatum->ItemIndex*0.5*b/lead*(2*M_PI)*hand; //datum

	 temptheta=temptheta-geartheta*M_PI/180.0; //user entered angle
	 temptheta=temptheta-(currenttooth-1)*(2*M_PI/(1.0*z));

	 X[i][j]=tempr*sin(temptheta);
	 Y[i][j]=tempr*cos(temptheta);
   }
 }

//translate

 for(int i=0;i<Nof;++i)
 {
  for(int j=0;j<2*(Nop+Nor);++j)
   {

	 X[i][j]=X[i][j]+gearxpos;
	 Y[i][j]=Y[i][j]+gearypos;
	 Z[i][j]=Z[i][j]+gearzpos;
   }
 }

  //calculate normals
  Formcalculate_normals(Nop,Nor,Nof,Notip,chamfer);


	   meas_dia_bottom=d_inv_act+0.001;
	   meas_dia_top=da-2*chamfer-0.001;


	   meas_dia_middle=0.5*(meas_dia_top+meas_dia_bottom);




    //get sample to use
	{
	int i=Nor+Nop*0.5-Notip; //



	  //middle

	  {
	   int i=0;
	   while(sqrt(X[0][i]*X[0][i]+Y[0][i]*Y[0][i])<0.5*meas_dia_middle)
	   {
	   meas_samp_middle=i;
	   i=i+1;
	   }
	  }

	  //bottom

	  {
	   int i=0;
	   while(sqrt(X[0][i]*X[0][i]+Y[0][i]*Y[0][i])<=0.5*meas_dia_bottom)
	   {
	   meas_samp_bottom=i;
	   i=i+1;
	   }
	  }

	   //top

	  {
	   int i=0;
	   while(sqrt(X[0][i]*X[0][i]+Y[0][i]*Y[0][i])<0.5*meas_dia_top)
	   {
	   meas_samp_top=i;
	   i=i+1;
	   }
       meas_samp_top=meas_samp_top-1; //back one
	  }

	 }
	  //end get sample to use



	 if(RadioGroupfinish->ItemIndex>=1) //lead
	 {


	 if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int i=meas_samp_bottom;
	  for(int j=0;j<Nof;++j)
	  {


		char tempclashtext[64];


		  if(approachdist>0 && j==0)
		  {
		  sampline=sampline+1;
		  strcpy(tempclashtext,"");
		  if(detectclash==1)
		  if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		  strcpy(tempclashtext,"INTERFERENCE");

		  sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		  Memo1->Lines->Add(temptext);
		  ComboBoxline->Items->Add(temptext);
		  }

		  sampline=sampline+1;
		strcpy(tempclashtext,"");
		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);




		  if(approachdist>0 && j==Nof-1)
		  {
		  sampline=sampline+1;
		  strcpy(tempclashtext,"");
		  if(detectclash==1)
		  if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		  strcpy(tempclashtext,"INTERFERENCE");

		  sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		  Memo1->Lines->Add(temptext);
		  ComboBoxline->Items->Add(temptext);
		  }


	  }
	 }

	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }

	  if(ComboBoxFlankcut->ItemIndex>=0)
	 {
	   int i=meas_samp_middle;
	  for(int j=0;j<Nof;++j)
	  {


		 char tempclashtext[64];


		if(approachdist>0 && j==0)
		{
        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

	   sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
	   Memo1->Lines->Add(temptext);
	   ComboBoxline->Items->Add(temptext);

		 }


	   sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

	   sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
	   Memo1->Lines->Add(temptext);
	   ComboBoxline->Items->Add(temptext);


		if(approachdist>0 && j==Nof-1)
		{
        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

	   sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
	   Memo1->Lines->Add(temptext);
	   ComboBoxline->Items->Add(temptext);

		 }





	  }
	 }

	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }

	  if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int i=meas_samp_top;
	  for(int j=0;j<Nof;++j)
	  {


	  char tempclashtext[64];

		if(approachdist>0 && j==0)
		{
      	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);

		}


		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);


		if(approachdist>0 && j==Nof-1)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


	  }
	 }


if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }





	 if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int i=2*(Nop+Nor)-1-meas_samp_bottom;
	  for(int j=0;j<Nof;++j)
	  {


      char tempclashtext[64];




		if(approachdist>0 && j==0)
		{

        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}

        sampline=sampline+1;
		strcpy(tempclashtext,"");

			if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);



		if(approachdist>0 && j==Nof-1)
		{
        sampline=sampline+1;
		strcpy(tempclashtext,"");

			if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);

		}

	  }
	 }


	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }


	  if(ComboBoxFlankcut->ItemIndex>=0)
	 {
	   int i=2*(Nop+Nor)-1-meas_samp_middle;
	  for(int j=0;j<Nof;++j)
	  {


      char tempclashtext[64];


		if(approachdist>0 && j==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);



		if(approachdist>0 && j==Nof-1)
		{
        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


	  }
	 }

if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }



	  if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int i=2*(Nop+Nor)-1-meas_samp_top;
	  for(int j=0;j<Nof;++j)
	  {


	  char tempclashtext[64];

      if(approachdist>0 && j==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);


		if(approachdist>0 && j==Nof-1)
		{
			sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}

	  }
	 }

	}   //end lead


   //	}//end lead


   ////////////////////////////////profile



   if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }



	if(ComboBoxwidthdensity->ItemIndex==0)
	profilestep=10;

	if(ComboBoxwidthdensity->ItemIndex==1)
	profilestep=20;

	if(ComboBoxwidthdensity->ItemIndex==2)
	profilestep=40;




	if(RadioGroupfinish->ItemIndex==0 || RadioGroupfinish->ItemIndex==2) //profile
	{

	 if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int j=0;

	   for(int ii=0;ii<profilestep;++ii)
	  {


	  int i=meas_samp_bottom+(meas_samp_top-meas_samp_bottom)/(1.0*profilestep-1)*ii;


	  char tempclashtext[64];



		if(ii==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);


        if(ii==profilestep-1)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}

	  }
	 }

	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }


	 if(ComboBoxFlankcut->ItemIndex>=0)
	 {
	   int j=0.5*(Nof);

	  for(int ii=0;ii<profilestep;++ii)
	  {


	  int i=meas_samp_bottom+(meas_samp_top-meas_samp_bottom)/(1.0*profilestep-1)*ii;


	  char tempclashtext[64];

		if(ii==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");
		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");
		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);



		if(ii==profilestep-1)
		{
        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");
		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


	  }
	 }

	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }


	  if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int j=Nof-1;

	   for(int ii=0;ii<profilestep;++ii)
	  {


	  int i=meas_samp_bottom+(meas_samp_top-meas_samp_bottom)/(1.0*profilestep-1)*ii;


	  char tempclashtext[64];

	  if(ii==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");
		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");
		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);



	   if(ii==profilestep-1)
		{
        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");
		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


	  }
	 }


	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }



	 //next flank
      if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int j=0;

	   for(int ii=0;ii<profilestep;++ii)
	  {


	  int i=meas_samp_bottom+(meas_samp_top-meas_samp_bottom)/(1.0*profilestep-1)*ii;
	  i=2*(Nop+Nor)-1-i;

	  char tempclashtext[64];

	  if(ii==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
	  }



        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);


	   if(ii==profilestep-1)
		{
        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
	   }

	  }
	 }

	 if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }


	 if(ComboBoxFlankcut->ItemIndex>=0)
	 {
	   int j=0.5*(Nof);

	  for(int ii=0;ii<profilestep;++ii)
	  {


	  int i=meas_samp_bottom+(meas_samp_top-meas_samp_bottom)/(1.0*profilestep-1)*ii;
	  i=2*(Nop+Nor)-1-i;

	  char tempclashtext[64];


	  if(ii==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);



		if(ii==profilestep-1)
		{
        sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		 }


	  }
	 }

	if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }


	  if(ComboBoxFlankcut->ItemIndex==1)
	 {
	   int j=Nof-1;

	   for(int ii=0;ii<profilestep;++ii)
	  {


	  int i=meas_samp_bottom+(meas_samp_top-meas_samp_bottom)/(1.0*profilestep-1)*ii;
	  i=2*(Nop+Nor)-1-i;

	  char tempclashtext[64];

      if(ii==0)
		{
		sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}


        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*0.5*balldia,Y[j][i]+Yn[j][i]*0.5*balldia,Z[j][i]+Zn[j][i]*0.5*balldia,j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*0.5*balldia)/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*0.5*balldia)/lengthunit,(Z[j][i]+Zn[j][i]*0.5*balldia)/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);


		if(ii==profilestep-1)
		{
        	sampline=sampline+1;
		strcpy(tempclashtext,"");

		if(detectclash==1)
		if(check_clash(X[j][i]+Xn[j][i]*(0.5*balldia+approachdist),Y[j][i]+Yn[j][i]*(0.5*balldia+approachdist),Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist),j)==1)
		strcpy(tempclashtext,"INTERFERENCE");

		sprintf(temptext,"N%-4d %-9.4f %-9.4f %-9.4f %s",sampline,(X[j][i]+stylusorientX24+Xn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Y[j][i]+stylusorientY13+Yn[j][i]*(0.5*balldia+approachdist))/lengthunit,(Z[j][i]+Zn[j][i]*(0.5*balldia+approachdist))/lengthunit,tempclashtext);
		Memo1->Lines->Add(temptext);
		ComboBoxline->Items->Add(temptext);
		}

	  }
	 }
	  if(detectclash==1)
	 {
	 Equator_Helical_Graphics_Check_form->Hide(); Equator_Helical_Graphics_Check_form->Show();
	 }


    }//end profile


  }//end m teeth





    ComboBoxline->ItemIndex=Nof;
    ButtonleftClick(Equator_Helical_Graphics_Check_form);

   // probeZ=1.5*b;





	OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);

	fclose(diagnosticfile);


    detectclash=0;
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::Memo1Exit(TObject *Sender)
{

int tempindex=ComboBoxline->ItemIndex;

ComboBoxline->Items->Clear();

  for(int j=0;j<Memo1->Lines->Count;++j)
	  {

	  ComboBoxline->Items->Add(Memo1->Lines->Strings[j]);
	  }



	ComboBoxline->ItemIndex=tempindex;

	OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------


void __fastcall TEquator_Helical_Graphics_Check_form::ComboBoxlineChange(TObject *Sender)

{
char temptext[512];
int currentlinenum;

strcpy(temptext,AnsiString(Memo1->Lines->Strings[ComboBoxline->ItemIndex]).c_str());


for(int n=0;n<strlen(temptext);++n)
temptext[n]=temptext[n+1];

sscanf(temptext,"%d %f %f %f",&currentlinenum,&probeX,&probeY,&probeZ);

probeX=probeX*lengthunit;
probeY=probeY*lengthunit;
probeZ=probeZ*lengthunit;



OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::ButtonrightMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{



ComboBoxline->ItemIndex=ComboBoxline->ItemIndex+1;

ComboBoxlineChange(Equator_Helical_Graphics_Check_form);

OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::ButtonleftClick(TObject *Sender)

{
ComboBoxline->ItemIndex=ComboBoxline->ItemIndex-1;

if(ComboBoxline->ItemIndex<0)
ComboBoxline->ItemIndex=0;

ComboBoxlineChange(Equator_Helical_Graphics_Check_form);

OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------


void __fastcall TEquator_Helical_Graphics_Check_form::CheckBoxunitsMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
if(CheckBoxunits->Checked==true)
{
units_type=1;
}
else
{
units_type=0;
}

	Setmaintextboxes(); //Reset all text boxe

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::gearthetaeditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(gearthetaedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::gearthetaeditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[gearthetaedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(gearthetaedit->Text).c_str() ); // copy text from box to new char
        y=gearthetaedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        gearthetaedit->Text=cp; // assign ansi string for box checked string
        if(gearthetaedit->SelStart==0) //if an illegal character
        gearthetaedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::gearthetaeditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[gearthetaedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(gearthetaedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp); //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=geartheta;
		geartheta=atof(text_number); //Assign value



				if(geartheta<-360/(1.0*z) || geartheta>360/(1.0*z))
				{
				ShowMessage("Value is out of range");

				geartheta=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::gearzposeditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(gearzposedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::gearzposeditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[gearzposedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(gearzposedit->Text).c_str() ); // copy text from box to new char
        y=gearzposedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        gearzposedit->Text=cp; // assign ansi string for box checked string
        if(gearzposedit->SelStart==0) //if an illegal character
        gearzposedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::gearzposeditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[gearzposedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(gearzposedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp)*lengthunit; //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=gearzpos;
		gearzpos=atof(text_number); //Assign value



				if(gearzpos<-300|| gearzpos>300)
				{
				ShowMessage("Value is out of range");

				gearzpos=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::stemdiaeditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(stemdiaedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::stemdiaeditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[stemdiaedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(stemdiaedit->Text).c_str() ); // copy text from box to new char
        y=stemdiaedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        stemdiaedit->Text=cp; // assign ansi string for box checked string
        if(stemdiaedit->SelStart==0) //if an illegal character
        stemdiaedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::stemdiaeditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[stemdiaedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(stemdiaedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp)*lengthunit; //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=stemdia;
		stemdia=atof(text_number); //Assign value



				if(stemdia<0.00001 || stemdia>10)
				{
				ShowMessage("Value is out of range");

				stemdia=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::approachdisteditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(approachdistedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::approachdisteditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[approachdistedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(approachdistedit->Text).c_str() ); // copy text from box to new char
        y=approachdistedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        approachdistedit->Text=cp; // assign ansi string for box checked string
        if(approachdistedit->SelStart==0) //if an illegal character
        approachdistedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::approachdisteditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[approachdistedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(approachdistedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp)*lengthunit; //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=approachdist;
		approachdist=atof(text_number); //Assign value



				if(approachdist<0.00000 || approachdist>1)
				{
				ShowMessage("Value is out of range");

				approachdist=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::balldiaeditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(balldiaedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::balldiaeditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[balldiaedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(balldiaedit->Text).c_str() ); // copy text from box to new char
        y=balldiaedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        balldiaedit->Text=cp; // assign ansi string for box checked string
        if(balldiaedit->SelStart==0) //if an illegal character
        balldiaedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::balldiaeditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[balldiaedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(balldiaedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp)*lengthunit; //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=balldia;
		balldia=atof(text_number); //Assign value



				if(balldia<0.00001 || balldia>20)
				{
				ShowMessage("Value is out of range");

				balldia=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::stemlengtheditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(stemlengthedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::stemlengtheditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[stemlengthedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(stemlengthedit->Text).c_str() ); // copy text from box to new char
        y=stemlengthedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        stemlengthedit->Text=cp; // assign ansi string for box checked string
        if(stemlengthedit->SelStart==0) //if an illegal character
		stemlengthedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::stemlengtheditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[stemlengthedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(stemlengthedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp)*lengthunit; //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=stemlength;
		stemlength=atof(text_number); //Assign value



				if(stemlength<0.00001 || stemlength>100)
				{
				ShowMessage("Value is out of range");

				stemlength=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::totalspaneditEnter(TObject * /*Sender*/  )
{
		strcpy(orig_textbox_val,AnsiString(totalspanedit->Text).c_str() ); // copy original text from box to new char

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::totalspaneditChange(TObject * /*Sender*/  )
{

int y;
        char* cp = new char[totalspanedit->Text.Length() + 1 ]; // create new char
        strcpy( cp,AnsiString(totalspanedit->Text).c_str() ); // copy text from box to new char
        y=totalspanedit->SelStart; //get current position of cursor
        float_format(cp); //check string is float using custom written function
        totalspanedit->Text=cp; // assign ansi string for box checked string
        if(totalspanedit->SelStart==0) //if an illegal character
        totalspanedit->SelStart=y-1;   //keep current cursor position
        if(strcmp(cp,orig_textbox_val)!=0) //compare original text box data
		changeflag=true;   // if changed set change flag to true


}

//---------------------------------------------------------------------------




//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::totalspaneditExit(TObject * /*Sender*/  )
{
double number;
float temp;

		char* cp = new char[totalspanedit->Text.Length() + 1 ]; // create new char
		strcpy( cp,AnsiString(totalspanedit->Text).c_str() ); // copy text from box to new char

		number=atof(cp)*lengthunit; //convert string cp to a double
		sprintf(text_number,"%f",number); //convert double to a string in correct format
        if(changeflag==1)//if a change occurred
		{
		temp=totalspan;
		totalspan=atof(text_number); //Assign value



				if(totalspan<0.00001 || totalspan>300)
				{
				ShowMessage("Value is out of range");

				totalspan=temp;
				}





		 //Calculate all other geometry
		}

Setmaintextboxes(); //Reset all text boxe
}
//---------------------------------------------------------------------------


void __fastcall TEquator_Helical_Graphics_Check_form::Button2Click(TObject *Sender)

{
detectclash=1;

ButtonupdateClick(Equator_Helical_Graphics_Check_form);





}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::LabelzoomMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{

if(TrackBarZoom->Position!=58)
TrackBarZoom->Position=58;

OpenGLAPPanel->Repaint() ;
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::ComboBoxprobeSelect(TObject *Sender)

{
	char temptextw[128];


		if(ComboBoxprobe->ItemIndex>0)
		{

		strcpy(temptextw,AnsiString(ComboBoxprobe->Items->Strings[ComboBoxprobe->ItemIndex]).c_str());

		sscanf(temptextw,"%f %f %f %f",&balldia,&stemdia,&stemlength,&totalspan);

		balldiaedit->Enabled=false;
		stemdiaedit->Enabled=false;
		stemlengthedit->Enabled=false;
		totalspanedit->Enabled=false;
		}
		else
		{
		balldiaedit->Enabled=true;
		stemdiaedit->Enabled=true;
		stemlengthedit->Enabled=true;
		totalspanedit->Enabled=true;
		}


       Setmaintextboxes(); //Reset all text boxe

}
//---------------------------------------------------------------------------


int check_clash(float tempXc1, float tempYc1,float tempZc1, int icurrent)
{

int intersect1,intersect2,intersect3,intersect4,intersect5,intersect6;
int intersecttrue=0;

int Nofmin,Nofmax;

float Xspindle,Yspindle,Zspindle;






	   // speed up by only checking ball width equivalent axially each side


	   if(balldia<=b/(Nof-1.0))
	   {
	   Nofmax=icurrent+1;
	   Nofmin=icurrent-1;
	   }
	   else
	   if(balldia<=b/(Nof-1.0)*2)
	   {
	   Nofmin=icurrent-2;
	   Nofmax=icurrent+2;
	   }
	   else
	   if(balldia<=b/(Nof-1.0)*3)
	   {
	   Nofmin=icurrent-3;
	   Nofmax=icurrent+3;
	   }
	   else
	   if(balldia<=b/(Nof-1.0)*4)
	   {
	   Nofmin=icurrent-4;
	   Nofmax=icurrent+4;
	   }
	   else
	   {
	   Nofmin=0;
	   Nofmax=Nof-1;
	   }







	   if(Nofmax>Nof)
	   Nofmax=Nof;

	   if(Nofmin>Nof-1)
	   Nofmin=Nof-1;

	   if(Nofmin<0)
	   Nofmin=0;


	  // Nofmin=0;
	  // Nofmax=Nof;



       Nofmin=Nofmin;
//repeat for one tooth each side
 //rot around Z

 for(int kk=-1;kk<=1;++kk)
 {
	for(int jj=0;jj<Nof;++jj)
	{
	for(int ii=0;ii<2*(Nop+Nor);++ii)
	{
	float temprr=SQRT(X[jj][ii]*X[jj][ii]+Y[jj][ii]*Y[jj][ii]);
	float tempttheta=ATAN(X[jj][ii],Y[jj][ii])+kk*2*M_PI/(1.0*z);

	 Xtemp[jj][ii]=temprr*sin(tempttheta);
	 Ytemp[jj][ii]=temprr*cos(tempttheta);
	 Ztemp[jj][ii]=Z[jj][ii];
	}
	}







	for(int jj=Nofmin;jj<Nofmax;++jj)
	{
	for(int ii=0;ii<2*(Nop+Nor);++ii)
	{
	float tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2;

	if(ii<2*(Nop+Nor)-1)
	{
	tempX1=Xtemp[jj][ii];
	tempY1=Ytemp[jj][ii];
	tempZ1=Ztemp[jj][ii];

	tempX2=Xtemp[jj][ii+1];
	tempY2=Ytemp[jj][ii+1];
	tempZ2=Ztemp[jj][ii+1];


	if(currentprobe==1)
	{                                                                                                         //was stemlength
	Intersect_of_line_with_cylY(tempX1,tempZ1,tempY1,tempX2,tempZ2,tempY2,tempXc1,tempZc1,tempYc1,0.5*stemdia,totalspan,&intersect1);
	//check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1+totalspan/2.0,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempX1;
	Yspindle=tempY1+0.5*totalspan;
	Zspindle=tempZ1;



	}

	if(currentprobe==3)
	{
	Intersect_of_line_with_cylY(tempX1,tempZ1,tempY1,tempX2,tempZ2,tempY2,tempXc1,tempZc1,tempYc1-totalspan,0.5*stemdia,totalspan,&intersect1);
		//check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1-totalspan/2.0,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);


    Xspindle=tempXc1;
	Yspindle=tempYc1-0.5*totalspan;
	Zspindle=tempZc1;
	}

	if(currentprobe==4)
	{
	Intersect_of_line_with_cylX(tempZ1,tempY1,tempX1,tempZ2,tempY2,tempX2,tempZc1,tempYc1,tempXc1,0.5*stemdia,totalspan,&intersect1);
	 //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1+totalspan/2.0,tempYc1,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1+0.5*totalspan;
	Yspindle=tempYc1;
	Zspindle=tempZc1;
	}

	if(currentprobe==2)
	{
	Intersect_of_line_with_cylX(tempZ1,tempY1,tempX1,tempZ2,tempY2,tempX2,tempZc1,tempYc1,tempXc1-totalspan,0.5*stemdia,totalspan,&intersect1);
	 //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1-totalspan/2.0,tempYc1,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1-0.5*totalspan;
	Yspindle=tempYc1;
	Zspindle=tempZc1;
	}

	//Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1,tempZc1,0.495*balldia,50,&intersect3);

	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle,Yspindle+0.5*totalspan,Zspindle,0.495*balldia,50,&intersect3);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle,Yspindle-0.5*totalspan,Zspindle,0.495*balldia,50,&intersect4);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle+0.5*totalspan,Yspindle,Zspindle,0.495*balldia,50,&intersect5);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle-0.5*totalspan,Yspindle,Zspindle,0.495*balldia,50,&intersect6);



	if(intersect1==1 || intersect2==1 || intersect3==1 || intersect4==1 || intersect5==1 || intersect6==1)
	{
	intersecttrue=1;

	}

	}




	if(jj<Nof-1 && intersecttrue==0)
	{
	tempX1=Xtemp[jj][ii];
	tempY1=Ytemp[jj][ii];
	tempZ1=Ztemp[jj][ii];

	tempX2=Xtemp[jj+1][ii];
	tempY2=Ytemp[jj+1][ii];
	tempZ2=Ztemp[jj+1][ii];


	if(currentprobe==1)
	{
	Intersect_of_line_with_cylY(tempX1,tempZ1,tempY1,tempX2,tempZ2,tempY2,tempXc1,tempZc1,tempYc1,0.5*stemdia,totalspan,&intersect1);
	//check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1+totalspan/2.0,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1;
	Yspindle=tempYc1+0.5*totalspan;
	Zspindle=tempZc1;
	}

	if(currentprobe==3)
	{
	Intersect_of_line_with_cylY(tempX1,tempZ1,tempY1,tempX2,tempZ2,tempY2,tempXc1,tempZc1,tempYc1-totalspan,0.5*stemdia,totalspan,&intersect1);
    //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1-totalspan/2.0,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1;
	Yspindle=tempYc1-0.5*totalspan;
	Zspindle=tempZc1;
	}

	if(currentprobe==4)
	{
	Intersect_of_line_with_cylX(tempZ1,tempY1,tempX1,tempZ2,tempY2,tempX2,tempZc1,tempYc1,tempXc1,0.5*stemdia,totalspan,&intersect1);
     //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1+totalspan/2.0,tempYc1,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1+0.5*totalspan;
	Yspindle=tempYc1;
	Zspindle=tempZc1;
	}

	if(currentprobe==2)
	{
	Intersect_of_line_with_cylX(tempZ1,tempY1,tempX1,tempZ2,tempY2,tempX2,tempZc1,tempYc1,tempXc1-totalspan,0.5*stemdia,totalspan,&intersect1);
    //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1-totalspan/2.0,tempYc1,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

    Xspindle=tempXc1-0.5*totalspan;
	Yspindle=tempYc1;
	Zspindle=tempZc1;
	}

	//Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1,tempZc1,0.495*balldia,50,&intersect3);

	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle,Yspindle+0.5*totalspan,Zspindle,0.495*balldia,50,&intersect3);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle,Yspindle-0.5*totalspan,Zspindle,0.495*balldia,50,&intersect4);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle+0.5*totalspan,Yspindle,Zspindle,0.495*balldia,50,&intersect5);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle-0.5*totalspan,Yspindle,Zspindle,0.495*balldia,50,&intersect6);



	if(intersect1==1 || intersect2==1 || intersect3==1 || intersect4==1 || intersect5==1 || intersect6==1)
	{
	intersecttrue=1;

	
	}

	}







	if((jj!=Nof-1 && ii!=2*(Nop+Nor)-1)   && intersecttrue==0) //diagonal
	{
	tempX1=Xtemp[jj][ii];
	tempY1=Ytemp[jj][ii];
	tempZ1=Ztemp[jj][ii];

	tempX2=Xtemp[jj+1][ii+1];
	tempY2=Ytemp[jj+1][ii+1];
	tempZ2=Ztemp[jj+1][ii+1];


	if(currentprobe==1)
	{
	Intersect_of_line_with_cylY(tempX1,tempZ1,tempY1,tempX2,tempZ2,tempY2,tempXc1,tempZc1,tempYc1,0.5*stemdia,totalspan,&intersect1);
    //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1+totalspan/2.0,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1;
	Yspindle=tempYc1+0.5*totalspan;
	Zspindle=tempZc1;
	}

	if(currentprobe==3)
	{
	Intersect_of_line_with_cylY(tempX1,tempZ1,tempY1,tempX2,tempZ2,tempY2,tempXc1,tempZc1,tempYc1-totalspan,0.5*stemdia,totalspan,&intersect1);
     //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1-totalspan/2.0,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

	Xspindle=tempXc1;
	Yspindle=tempYc1-0.5*totalspan;
	Zspindle=tempZc1;
	}

	if(currentprobe==4)
	{
	Intersect_of_line_with_cylX(tempZ1,tempY1,tempX1,tempZ2,tempY2,tempX2,tempZc1,tempYc1,tempXc1,0.5*stemdia,totalspan,&intersect1);
	 //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1+totalspan/2.0,tempYc1,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

    Xspindle=tempXc1+0.5*totalspan;
	Yspindle=tempYc1;
	Zspindle=tempZc1;
	}

	if(currentprobe==2)
	{
	Intersect_of_line_with_cylX(tempZ1,tempY1,tempX1,tempZ2,tempY2,tempX2,tempZc1,tempYc1,tempXc1-totalspan,0.5*stemdia,totalspan,&intersect1);
    //check body holder
	Intersect_of_line_with_cylZ(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1-totalspan/2.0,tempYc1,tempZc1-stemlength*0.2,0.5*(totalspan-2*stemlength),stemlength,&intersect2);

    Xspindle=tempXc1-0.5*totalspan;
	Yspindle=tempYc1;
	Zspindle=tempZc1;
	}

	//Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,tempXc1,tempYc1,tempZc1,0.495*balldia,50,&intersect3);


	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle,Yspindle+0.5*totalspan,Zspindle,0.495*balldia,50,&intersect3);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle,Yspindle-0.5*totalspan,Zspindle,0.495*balldia,50,&intersect4);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle+0.5*totalspan,Yspindle,Zspindle,0.495*balldia,50,&intersect5);
	Intersect_of_line_with_sphere(tempX1,tempY1,tempZ1,tempX2,tempY2,tempZ2,Xspindle-0.5*totalspan,Yspindle,Zspindle,0.495*balldia,50,&intersect6);



	if(intersect1==1 || intersect2==1 || intersect3==1 || intersect4==1 || intersect5==1 || intersect6==1)
	{
	intersecttrue=1;

	}



	if(intersecttrue==1)
	{
	ii=1000;
	jj=1000;
	kk=1000;
	}
	}  //diagonal

	}//ii

	}//jj


 }//kk




   return(intersecttrue);



}

void __fastcall TEquator_Helical_Graphics_Check_form::CheckBoxbtransparentMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y)
{
OpenGLAPPanelPaint(Equator_Helical_Graphics_Check_form);
}
//---------------------------------------------------------------------------











//OPenGL Directly

//---------------------------------------------------------------------------
void __fastcall TEquator_Helical_Graphics_Check_form::SetPixelFormatDescriptor()
{
    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,0,
        0,0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
        };
    PixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, PixelFormat, &pfd);
}
//---------------------------------------------------------------------------

void __fastcall TEquator_Helical_Graphics_Check_form::SetupRC()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//---------------------------------------------------------------------------



//End OPenGL Directly


void __fastcall TEquator_Helical_Graphics_Check_form::FormDestroy(TObject *Sender)

{
	   //
		wglMakeCurrent(hdc, NULL);
	wglDeleteContext(hrc);

	ReleaseDC(Handle,hdc);
   //	ReleaseDC(hdc);
}
//---------------------------------------------------------------------------

