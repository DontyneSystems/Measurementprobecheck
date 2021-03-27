//---------------------------------------------------------------------------
//copyright Dontyne Systems
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


#pragma hdrstop

#include "Matrix_alloc.h"

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define NR_END 1
#define FREE_ARG char*

//---------------------------------------------------------------------------

#pragma package(smart_init)

void free_matrix_float(float **m, long nrl, long nrh, long ncl, long nch)
/* free a float matrix allocated by matrix() */
{
free((FREE_ARG) (m[nrl]+ncl-NR_END));
free((FREE_ARG) (m+nrl-NR_END));
}







//this is written so an array of floats is created not doubles.
//only used for main matrix but doubles are used in gauss jordan
//saves space in memory

float **matrix_float(long nrl, long nrh, long ncl, long nch)
/* allocate a float matrix with subscript range m[nrl..nrh][ncl..nch] */
{
long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
float **m;
/* allocate pointers to rows */
m=(float **) malloc((size_t)((nrow+NR_END)*sizeof(float*)));


if (!m) //nrerror("allocation failure 1 in matrix()");
m += NR_END;
m -= nrl;
/* allocate rows and set pointers to them */
m[nrl]=(float *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(float)));
if (!m[nrl]) //nrerror("allocation failure 2 in matrix()");
m[nrl] += NR_END;
m[nrl] -= ncl;
for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;
/* return pointer to array of pointers to rows */
return m;
}


