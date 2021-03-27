//---------------------------------------------------------------------------

#pragma hdrstop

#include "STRFMT.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
//copyright Dontyne Systems
//---------------------------------------------------------------------------
#include<stdio.h>
#include<string.h>
#include<ctype.h>

void float_format(char *cp)
	{
        int i,j,temp;


        if(strlen(cp)!=0) // check string is not empty (if true skip all)
        {


	// format should be  +##.##e+##

	// first digit
	j=0;
	while(!isdigit(cp[0]) && (cp[0]!='.' && (cp[0]!='-' && (cp[0]!='+' && (cp[0]!='\0')))))
	{


		i=0;
		while(cp[i]!='\x0')
		{
		cp[i]=cp[i+1];
		i=i+1;
		}

	}

        if(cp[0]=='0' && (cp[1]=='-' || cp[1]=='+'))
        {
        	i=0;
		while(cp[i]!='\x0')
		{
		cp[i]=cp[i+1];
		i=i+1;
		}
        }

        if(cp[0]=='.' && (!isdigit(cp[1]) && cp[1]!='\0'  ))
        {
        	i=0;
		while(cp[i]!='\x0')
		{
		cp[i]=cp[i+1];
		i=i+1;
		}
        }


	// end if first digit
	j=j+1;


      //  if(cp[1]=='-' || cp[1]=='+')
        //&& (cp[1]=='+' || cp[1]=='-')




	//	  up to first . or e or E
		while(cp[j]!='.' && (cp[j]!='E' && (cp[j]!='e' && cp[j]!='\0')))
		{
			if(!isdigit(cp[j]))
			{
				i=j;
				while(cp[i]!='\0')
				{
				cp[i]=cp[i+1];
				i=i+1;
				}
			}
			else j=j+1;
		}
		//	end  up to first . or e

	// if is a decimal point
		if(cp[j]=='.')
								{
		j=j+1;
		while(cp[j]!='E' && (cp[j]!='e' && cp[j]!='\0'))
		{
			if(!isdigit(cp[j]))
			{
				i=j;
				while(cp[i]!='\0')
				{
				cp[i]=cp[i+1];
				i=i+1;
				}
			}
			else j=j+1;
		}

		if(cp[j]=='e' || cp[j]=='E')
		{
		j=j+1;

		while(cp[j]!='\0')
		{
			if(cp[j-1]=='e' || cp[j-1]=='E')
			{
			if(!isdigit(cp[j]) && (cp[j]!='+' && cp[j]!='-'))
			{
				i=j;
				while(cp[i]!='\0')
				{
				cp[i]=cp[i+1];
				i=i+1;
				}
			}
			else j=j+1;
			}
			else
			{
			if(!isdigit(cp[j]))
			{
				i=j;
				while(cp[i]!='\0')
				{
				cp[i]=cp[i+1];
				i=i+1;
				}
			}
			else j=j+1;
			}
		}
		}
								} 	// end if is a decimal point
								else
								{
		if(cp[j]=='e' || cp[j]=='E')
		{
		j=j+1;

		while(cp[j]!='\0')
		{
			if(cp[j-1]=='e' || cp[j-1]=='E')
			{
			if(!isdigit(cp[j]) && (cp[j]!='+' && cp[j]!='-'))
			{
				i=j;
				while(cp[i]!='\0')
				{
				cp[i]=cp[i+1];
				i=i+1;
				}
			}
			else j=j+1;
			}
			else
			{
			if(!isdigit(cp[j]))
			{
				i=j;
				while(cp[i]!='\0')
				{
				cp[i]=cp[i+1];
				i=i+1;
				}
			}
			else j=j+1;
			}
		}
		}
								}
        }  //end if string is empty

}
