//---------------------------------------------------------------------------
//© Dontyne Systems Ltd 2021

#include <vcl.h>
#include <windows.h>

#pragma hdrstop
#pragma argsused

#include "Main_Graphics_Form.h"


#include "progressform.h"


int z,hand,units_type;

float Mn,alpha,Beta,x1,da,df,rhof,prot_resid,chamfer,chamferang,b,bore;

float d_inv_act,lead,meas_dia_bottom,meas_dia_top,meas_dia_middle;

float lengthunit;

float toothprofile[500][2];

float **X,**Y,**Z,**Xtemp,**Ytemp,**Ztemp,**Xn,**Yn,**Zn,**Xorig,**Yorig,**Zorig;

char orig_textbox_val[16],text_number[32];
bool changeflag;

float stemdia,balldia,stemlength,totalspan;
float gearxpos,gearypos,gearzpos,geartheta,approachdist;


void __export equator_helical_check(int,int,float,float,float,float,float,float,float,float,float,float,float,float,
float *,float *,float *,float *);




void equator_helical_check(int z_,int hand_,float Mn_,float alpha_,float beta_,float x1_,float da_,float df_,float rhof_,float prot_resid_,float chamfer_,
float chamferang_,float b_,float bore_,float *stemdia_,float *balldia_,float *stemlength_,float *totalspan_)

{

z=z_;
hand=hand_;
Mn=Mn_;
alpha=alpha_;
Beta=beta_;
x1=x1_;
da=da_;
df=df_;
rhof=rhof_;
prot_resid=prot_resid_;
chamfer=chamfer_;
chamferang=chamferang_;
b=b_;
bore=bore_;

stemdia=*stemdia_;
balldia=*balldia_;
stemlength=*stemlength_;
totalspan=*totalspan_;



//if(chamfer<0.05*Mn)
//chamfer=0.05*Mn;


 //make data transverse
//Mn=Mn/cos(Beta*M_PI/180.0);

//Beta=45;



units_type=0;


//b=100;




gearxpos=0; //these must be zero
gearypos=0; //these must be zero
gearzpos=10;
geartheta=0;  //these must be zero

approachdist=0.25;




//
 Application->CreateForm(__classid(TProgress_form), &Progress_form);

 Application->CreateForm(__classid(TEquator_Helical_Graphics_Check_form), &Equator_Helical_Graphics_Check_form);



 Equator_Helical_Graphics_Check_form->ShowModal();





  *stemdia_=stemdia;
  *balldia_=balldia;
  *stemlength_=stemlength;
  *totalspan_=totalspan;

}



int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
	return 1;
}

