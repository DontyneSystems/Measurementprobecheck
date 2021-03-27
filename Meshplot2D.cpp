//---------------------------------------------------------------------------

#pragma hdrstop

#include "Meshplot2D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//copyright Dontyne Systems
//---------------------------------------------------------------------------
#include<stdio.h>
#include<math.h>

#include "Math_functions.h"



void meshplothobbedbasic2D(int pinorwheel,int z,float Mn,float phi_n,float psi,
float R_root,float R_a,float X_g,float rho_ao,float delta_o,float phi_n_Q,
float chamang,float y_cham,float *d_inv_act,
float toothprofile1[500][2])

{


	float 	toothprofiletemp[500][2];


	double R_b,r_i,phi_i,theta_i,inv_phi_i,inv_phi_p,t_b,t_i,zi_i,
	eta_i,rho_i,rho_n_i,phi,psi_b,t_n_i,psi_i,phi_n_i,r_F,alpha_n_limit,
	r_F_at_phi_n,h_ao,h_fo;

	double zi_s_no,S_no,eta_s_no,zi_no,alpha_n,eta_no,zi_o,eta_o,alpha,
		kappa_F,theta,R,Beta,zi_F,eta_F,r_F_limit,st_ref_temp;
	//float (*pin_involute_coords)[2],(*pin_fillet_coords)[2];
		double pin_involute_coords[100][2],pin_fillet_coords[100][2];


	double y_prot,limit,limit2,r_y_prot_fin,actual_form_radius;

	int i,j,hh;
	double zi_F_old,zi_i_old,temp,eta_F_old,eta_i_old;
	float tempf,tempf2,tempf3,tempf4;

	float d_dashc,rhotip,phitemp,d_cinva;

	double st_ref_fin=Mn*(X_g*2.0*tan(phi_n*M_PI/180)+M_PI/2.0)/cos(psi*M_PI/180);

	double st_ref=st_ref_fin;

	//initial calcs

		R_root=R_root/2.0;
        R_a=R_a/2.0;
	R=z*Mn/cos(psi*M_PI/180)/2.0;

		h_ao=R+X_g*Mn-R_root;
		h_fo=R_a-R-X_g*Mn;
		h_fo=h_fo;

	phi=180/M_PI*atan(tan(phi_n*M_PI/180)/cos(psi*M_PI/180));     	//transverse pressure angle
	R_b=z*Mn/cos(psi*M_PI/180)*
	cos( atan(tan(phi_n*M_PI/180)/cos(psi*M_PI/180)) )/2;

	S_no=M_PI*Mn/2;		 	//normal reference tool thickness

		if(st_ref_fin<st_ref && delta_o==0)  //Increase hob thickness for thinning
        {                                //when no protuberance
        S_no=S_no+(st_ref-st_ref_fin)*cos(psi*M_PI/180);
        }


	st_ref_temp=st_ref;

	//end initial calcs


       //  phi_n_Q=10;


		//if no protuberance set phi_n_Q to phi_n
		if(delta_o==0)
		{
		phi_n_Q=phi_n;
		limit=phi_n/4.0;
		}
		else
		limit=phi_n_Q/4.0;  /*limit on range for finding form dia
												 this should be phi_n_Q but with protuberance
												 it seems to not be low enough*/


		//basic details of hob cutter
		//protuberance start
		if(delta_o!=0)
		y_prot=delta_o*cos(phi_n_Q*M_PI/180)/tan((phi_n-phi_n_Q)*M_PI/180)+
			rho_ao*(1-sin(phi_n_Q*M_PI/180));
		r_y_prot_fin=R_b;





		//Fillet calculation**************************************
		//**************************************************************************
	//if undercut initially find form dia

	int rerun=0;

	r_F_limit=R_b;  // initially set form dia to base diameter
	alpha_n_limit=phi_n;  // initially set alpha_n_limit to phi_n

	zi_i_old=0.0;
	zi_F_old=0.0;
	for(j=0;j<10000;++j)
	{

	alpha_n=90/(pow(pow((90/(limit)),1/9999.0),j));


	if(rerun==1)
	alpha_n=limit+(limit2-limit)/9999.0*j;

	//alpha_n=limit/9999.0*j;
	//use GP spacing for samps
	//limit should be between 90 and phi_n_Q but needs extending for prot

	zi_s_no=(Mn*M_PI-S_no)/2+(h_ao-rho_ao)*tan(phi_n*M_PI/180)+
					(rho_ao-delta_o)/cos(phi_n*M_PI/180);
	eta_s_no=Mn*X_g-(h_ao-rho_ao);

		if(zi_s_no>M_PI*Mn/2)  //fillet radius too large to fit in
		{
		zi_s_no=S_no;
		limit=phi_n_Q/4.0;
		}

	zi_no=zi_s_no-rho_ao*cos(alpha_n*M_PI/180);
	eta_no=eta_s_no-rho_ao*sin(alpha_n*M_PI/180);

	zi_o=zi_no/cos(psi*M_PI/180);
	eta_o=eta_no;
	alpha=180/M_PI*atan(tan(alpha_n*M_PI/180)/cos(psi*M_PI/180));

	kappa_F=eta_o/sin(alpha*M_PI/180);
	theta=180/M_PI*1/R*(zi_o-kappa_F*cos(alpha*M_PI/180));
	Beta=alpha-theta;

	zi_F=R*sin(theta*M_PI/180)+kappa_F*cos(Beta*M_PI/180);
	eta_F=R*cos(theta*M_PI/180)+kappa_F*sin(Beta*M_PI/180);

	r_F=SQRT((zi_F*zi_F+eta_F*eta_F));



		if(r_F<R_b)
		{
		alpha_n_limit=alpha_n;
		}

		if(r_F>R_b)
		{
		//calculate involute at interface to find r_F_limit
		r_i=r_F;

		//changed so ignores above and protuberance ramp
		st_ref_temp=st_ref_fin;


     		phi_i=Acos(R_b/r_i);
		inv_phi_i=tan(phi_i)-phi_i;
		t_b=2*R_b*(st_ref_temp/2/R+(tan(Acos(R_b/R))-Acos(R_b/R)));
		inv_phi_p=t_b/2/R_b;
		theta_i=inv_phi_p-inv_phi_i;
		t_i=2*r_i*theta_i;
		zi_i=r_i*sin(theta_i);
		eta_i=r_i*cos(theta_i);

			if(!( ((zi_i-zi_F)<(zi_i_old-zi_F_old)) && ((zi_i-zi_F)<0.0 )) )
			{
			r_F_limit=r_F;
			alpha_n_limit=alpha_n;

			}

				if( ((zi_i-zi_F)<(zi_i_old-zi_F_old)) && ((zi_i-zi_F)<0.0 ) )
				{
					if(zi_i_old>0.0)
					{
					if(rerun==1)
					j=10000;
					else
					j=0;
					limit=alpha_n_limit;
					limit2=alpha_n;
					rerun=1;
					}
				}




						if((j>0 && r_F>R_b) && j!=10000)
			{
			zi_F_old=zi_F;
			zi_i_old=zi_i;




			}


		}       //end calculate involute at interface to find r_F_limit



	}


		//if thinning is greater than protuberance
		if(alpha_n_limit==phi_n &&
			(st_ref-st_ref_fin>2*delta_o/cos(phi_n*M_PI/180)/cos(psi*M_PI/180) ))
		{
		r_F_limit=r_F_at_phi_n;
		}

	//recalculate fillet coords with 100 samples
	for(j=0;j<100;++j)
	{

	alpha_n=90/(pow(pow((90/alpha_n_limit),1/99.0),j));

	zi_s_no=(Mn*M_PI-S_no)/2+(h_ao-rho_ao)*tan(phi_n*M_PI/180)+
					(rho_ao-delta_o)/cos(phi_n*M_PI/180);
	eta_s_no=Mn*X_g-(h_ao-rho_ao);

		if(zi_s_no>M_PI*Mn/2)  //fillet radius too large to fit in
		{
		zi_s_no=S_no;
		}

	zi_no=zi_s_no-rho_ao*cos(alpha_n*M_PI/180);
	eta_no=eta_s_no-rho_ao*sin(alpha_n*M_PI/180);

	zi_o=zi_no/cos(psi*M_PI/180);
	eta_o=eta_no;
	alpha=180/M_PI*atan(tan(alpha_n*M_PI/180)/cos(psi*M_PI/180));

	kappa_F=eta_o/sin(alpha*M_PI/180);
	theta=180/M_PI*1/R*(zi_o-kappa_F*cos(alpha*M_PI/180));
	Beta=alpha-theta;

	zi_F=R*sin(theta*M_PI/180)+kappa_F*cos(Beta*M_PI/180);
	eta_F=R*cos(theta*M_PI/180)+kappa_F*sin(Beta*M_PI/180);

	pin_fillet_coords[j][0]=zi_F;
	pin_fillet_coords[j][1]=eta_F;

	}


	//Involute calculation**************************************
	//first perform accurate to get breakout point

		if(r_F_limit<y_prot+R_root && delta_o!=0)
	for(i=0;i<1000;++i)
	{
	r_i=r_F_limit+((y_prot+R_root)-r_F_limit)/999.0*i;

	   //	st_ref_temp=st_ref-2*((R_root+y_prot-r_i)*
		//(tan(phi_n*M_PI/180)-tan(phi_n_Q*M_PI/180))/cos(psi*M_PI/180));

		//changed so ignores above and protuberance ramp
		st_ref_temp=st_ref_fin;

		if(st_ref_fin>st_ref_temp) //if thinned thickness is less than protuberance
		r_y_prot_fin=r_i;	//straight bit (sets break out dia on prot straight)

	}
	//End Involute calculation**************************************



	//if tip round not chamfer then start of tip round needs calculating

   //	if(tipround==0)
	d_cinva=R_a*2-y_cham*2;



		//Involute calculation**************************************
	//resample involute with 100 points
	//note top of fillet is same as this first point so to prevent overlap ass small amount.
	 //0.0001

	//note top of involute is same as first point of tip round so reduce a small amount
    //0.0001

	for(i=0;i<100;++i)
	{


   	if(y_cham>0.0001)
	r_i=(r_F_limit+0.0001)+((d_cinva-0.0001)/2.0-(r_F_limit+0.0001))/(98.0)*i;
	else
	r_i=(r_F_limit+0.0001)+((d_cinva-0.0001)/2.0-(r_F_limit+0.0001))/(99.0)*i;




		//changed so ignores above and protuberance ramp
		st_ref_temp=st_ref_fin;


		if(st_ref_fin<st_ref_temp) //if thinned thickness is less than protuberance
		st_ref_temp=st_ref_fin;		 //straight or st_ref


	phi_i=Acos(R_b/r_i);
	inv_phi_i=tan(phi_i)-phi_i;
	t_b=2*R_b*(st_ref_temp/2/R+(tan(Acos(R_b/R))-Acos(R_b/R)));
	inv_phi_p=t_b/2/R_b;
	theta_i=inv_phi_p-inv_phi_i;
	t_i=2*r_i*theta_i;
        eta_i=r_i*cos(theta_i); //y coord
	zi_i=r_i*sin(theta_i);  //x coord

		//chamfer defined in normal plane
		//converted to transverse by dividing reduction in thickness
		//divided by cos of helix angle at tip
		//the transverse chamfer angle will be shown on plot




	   if((i==99 ) && y_cham>0.0001) //if in chamfer region apply chamfer to x
		{


		float tempang=chamang;

		 for(int ij=0;ij<5;++ij)
		 {

		 temp=(pin_involute_coords[i-1][0]-y_cham*tan(tempang*M_PI/180.0))/R_a;

		 pin_involute_coords[i][0]=R_a*sin(temp);
		 pin_involute_coords[i][1]=R_a*cos(temp);

		 float tempang2=-180.0/M_PI*ATAN(pin_involute_coords[i][0]-pin_involute_coords[i-1][0],pin_involute_coords[i][1]-pin_involute_coords[i-1][1]);

		 tempang=tempang+(chamang-tempang2);
		 }

		}

                else
                {
        	pin_involute_coords[i][0]=zi_i;
        	pin_involute_coords[i][1]=eta_i;
                }

        }
	//End Involute calculation**************************************


	//definition of form radius
	if(delta_o>0)
	{
		if(st_ref-st_ref_fin>2*delta_o/cos(phi_n*M_PI/180)/cos(psi*M_PI/180) )
		{
		actual_form_radius=r_F_limit;
		}
		else
		{
			if(r_F_limit>r_y_prot_fin)
			actual_form_radius=r_F_limit;
			else
			actual_form_radius=r_y_prot_fin;
		}
	}
	else
	{
	actual_form_radius=r_F_limit;
	}

	//end definition of form radius


	//*********************
//  curvature in root and tip part


	for(i=0;i<25;++i)
		{
		theta=360/(2.0*z)*M_PI/180-(360/(2.0*z)*M_PI/180-
		atan(pin_fillet_coords[0][0]/pin_fillet_coords[0][1]))
		/24.2*i;
		///24.2*(i+0.1);

		toothprofiletemp[i][0]=R_root*sin(theta);
		toothprofiletemp[i][1]=R_root*cos(theta);
		}

		for(i=25;i<125;++i)
		{
		toothprofiletemp[i][0]=pin_fillet_coords[i-25][0];
		toothprofiletemp[i][1]=pin_fillet_coords[i-25][1];
		}



		for(i=125;i<225;++i)
		{
		toothprofiletemp[i][0]=pin_involute_coords[i-125][0];
		toothprofiletemp[i][1]=pin_involute_coords[i-125][1];
		}

	   //	if(tipround==0)
		{

		for(i=225;i<250;++i)
		{
		//theta=(249-i)/24.0*atan(pin_involute_coords[99][0]/
	   //	theta=(249-i+0.1)/24.2*atan(pin_involute_coords[99][0]/
		theta=(249-i+1)/26.0*atan(pin_involute_coords[99][0]/
		pin_involute_coords[99][1]);
		toothprofiletemp[i][0]=R_a*sin(theta);
		toothprofiletemp[i][1]=R_a*cos(theta);
		}

		}








		for(i=250;i<500;++i)
		{
		toothprofiletemp[i][0]=-1*toothprofiletemp[499-i][0];
		toothprofiletemp[i][1]=toothprofiletemp[499-i][1];
		}


	//**********************
//end   curvature in root part




   for(i=0;i<500;++i)
   {
   toothprofile1[i][0]=toothprofiletemp[i][0];
   toothprofile1[i][1]=toothprofiletemp[i][1];
   }




    *d_inv_act=actual_form_radius*2; //set form diameter
    t_i=t_i;               // stop warnings



}

//---------------------------------------------------------------------------



