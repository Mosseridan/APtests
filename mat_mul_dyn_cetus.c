/*
Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it andor
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http:www.gnu.org/licenses/>. 
*/
/*
This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it. 
*/
/* We do support the IEC 559 math functionality, real and complex.  */
/*
wchar_t uses ISOIEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0. 
*/
/* We do not support C11 <threads.h>.  */
#include <stdio.h>
#include <stdlib.h>
#include <mat_mul_dyn.h>
void mat_mul(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	#pragma cetus private(i, j, k) 
	#pragma loop name mat_mul#0 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<(((1L+(3L*n))+((4L*n)*n))+(((3L*n)*n)*n)))) private(i, j, k)
	for (i=0; i<n; i ++ )
	{
		#pragma cetus private(j, k) 
		#pragma loop name mat_mul#0#0 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<((1L+(4L*n))+((3L*n)*n)))) private(j, k)
		for (j=0; j<n; j ++ )
		{
			c[i][j]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul#0#0#0 
			#pragma cetus reduction(+: c[i][j]) 
			#pragma cetus parallel 
			#pragma omp parallel for if((10000<(1L+(3L*n)))) private(k) reduction(+: c[i][j])
			for (k=0; k<n; k ++ )
			{
				c[i][j]+=(a[i][k]*b[k][j]);
			}
		}
	}
	return ;
}

int compute_cijk(int i, int j, int k, int * * a, int * * b)
{
	return (a[i][k]*b[k][j]);
}

void mat_mul_function_calls(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	#pragma cetus firstprivate(c) 
	#pragma cetus private(i, j, k) 
	#pragma cetus lastprivate(c) 
	#pragma loop name mat_mul_function_calls#0 
	for (i=0; i<n; i ++ )
	{
		#pragma cetus firstprivate(c) 
		#pragma cetus private(j, k) 
		#pragma cetus lastprivate(c) 
		#pragma loop name mat_mul_function_calls#0#0 
		for (j=0; j<n; j ++ )
		{
			c[i][j]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_function_calls#0#0#0 
			#pragma cetus reduction(+: c[i][j]) 
			for (k=0; k<n; k ++ )
			{
				c[i][j]+=compute_cijk(i, j, k, a, b);
			}
		}
	}
	return ;
}

void compute_cijk2(int i, int j, int k, int * * a, int * * b, int * * c)
{
	c[i][j]+=(a[i][k]*b[k][j]);
}

void mat_mul_function_calls2(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	#pragma cetus private(i, j, k) 
	#pragma loop name mat_mul_function_calls2#0 
	for (i=0; i<n; i ++ )
	{
		#pragma cetus private(j, k) 
		#pragma loop name mat_mul_function_calls2#0#0 
		for (j=0; j<n; j ++ )
		{
			c[i][j]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_function_calls2#0#0#0 
			for (k=0; k<n; k ++ )
			{
				compute_cijk2(i, j, k, a, b, c);
			}
		}
	}
	return ;
}

void compute_cij(int i, int j, int n, int * * a, int * * b, int * * c)
{
	int k;
	c[i][j]=0;
	#pragma cetus private(k) 
	#pragma loop name compute_cij#0 
	#pragma cetus reduction(+: c[i][j]) 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<(1L+(3L*n)))) private(k) reduction(+: c[i][j])
	for (k=0; k<n; k ++ )
	{
		c[i][j]+=(a[i][k]*b[k][j]);
	}
}

void mat_mul_function_calls3(int n, int * * a, int * * b, int * * c)
{
	int i, j;
	#pragma cetus private(i, j) 
	#pragma loop name mat_mul_function_calls3#0 
	for (i=0; i<n; i ++ )
	{
		#pragma cetus private(j) 
		#pragma loop name mat_mul_function_calls3#0#0 
		for (j=0; j<n; j ++ )
		{
			compute_cij(i, j, n, a, b, c);
		}
	}
	return ;
}

void compute_ci(int i, int n, int * * a, int * * b, int * * c)
{
	int j, k;
	#pragma cetus private(j, k) 
	#pragma loop name compute_ci#0 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<((1L+(4L*n))+((3L*n)*n)))) private(j, k)
	for (j=0; j<n; j ++ )
	{
		c[i][j]=0;
		#pragma cetus private(k) 
		#pragma loop name compute_ci#0#0 
		#pragma cetus reduction(+: c[i][j]) 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<(1L+(3L*n)))) private(k) reduction(+: c[i][j])
		for (k=0; k<n; k ++ )
		{
			c[i][j]+=(a[i][k]*b[k][j]);
		}
	}
}

void mat_mul_function_calls4(int n, int * * a, int * * b, int * * c)
{
	int i;
	#pragma cetus private(i) 
	#pragma loop name mat_mul_function_calls4#0 
	for (i=0; i<n; i ++ )
	{
		compute_ci(i, n, a, b, c);
	}
	return ;
}

void mat_mul_loop_unroll(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	#pragma cetus firstprivate(c) 
	#pragma cetus private(i, j, k) 
	#pragma cetus lastprivate(c) 
	#pragma loop name mat_mul_loop_unroll#0 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<(((1L+(3L*n))+((4L*n)*n))+(((3L*n)*n)*((-2L+n)/2L))))) private(i, j, k) firstprivate(c) lastprivate(c)
	for (i=0; i<n; i ++ )
	{
		#pragma cetus firstprivate(c) 
		#pragma cetus private(j, k) 
		#pragma cetus lastprivate(c) 
		#pragma loop name mat_mul_loop_unroll#0#0 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<((1L+(4L*n))+((3L*n)*((-2L+n)/2L))))) private(j, k) firstprivate(c) lastprivate(c)
		for (j=0; j<n; j ++ )
		{
			c[i][j]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_loop_unroll#0#0#0 
			#pragma cetus reduction(+: c[i][j]) 
			#pragma cetus parallel 
			#pragma omp parallel for if((10000<(1L+(3L*((-2L+n)/2L))))) private(k) reduction(+: c[i][j])
			for (k=0; k<(n-1); k+=2)
			{
				/* we asume that n is even */
				c[i][j]+=((a[i][k]*b[k][j])+(a[i][k+1]*b[k+1][j]));
			}
		}
	}
	return ;
}

void mat_mul_loop_unroll2(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	#pragma cetus private(i, j, k) 
	#pragma loop name mat_mul_loop_unroll2#0 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<(((1L+(3L*n))+((5L*n)*((-2L+n)/2L)))+(((4L*n)*((-2L+n)/2L))*((-2L+n)/2L))))) private(i, j, k)
	for (i=0; i<n; i ++ )
	{
		#pragma cetus private(j, k) 
		#pragma loop name mat_mul_loop_unroll2#0#0 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<((1L+(5L*((-2L+n)/2L)))+((4L*((-2L+n)/2L))*((-2L+n)/2L))))) private(j, k)
		for (j=0; j<(n-1); j+=2)
		{
			/* we asume that n is even */
			c[i][j]=0;
			c[i][j+1]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_loop_unroll2#0#0#0 
			#pragma cetus reduction(+: c[i][j+1], c[i][j]) 
			#pragma cetus parallel 
			#pragma omp parallel for if((10000<(1L+(4L*((-2L+n)/2L))))) private(k) reduction(+: c[i][j+1], c[i][j])
			for (k=0; k<(n-1); k+=2)
			{
				c[i][j]+=((a[i][k]*b[k][j])+(a[i][k+1]*b[k+1][j]));
				c[i][j+1]+=((a[i][k]*b[k][j+1])+(a[i][k+1]*b[k+1][j+1]));
			}
		}
	}
	return ;
}

void mat_mul_loop_unroll3(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	#pragma cetus private(i, j, k) 
	#pragma loop name mat_mul_loop_unroll3#0 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<(((1L+(3L*((-2L+n)/2L)))+((7L*((-2L+n)/2L))*((-2L+n)/2L)))+(((6L*((-2L+n)/2L))*((-2L+n)/2L))*((-2L+n)/2L))))) private(i, j, k)
	for (i=0; i<(n-1); i+=2)
	{
		/* we asume that n is even */
		#pragma cetus private(j, k) 
		#pragma loop name mat_mul_loop_unroll3#0#0 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<((1L+(7L*((-2L+n)/2L)))+((6L*((-2L+n)/2L))*((-2L+n)/2L))))) private(j, k)
		for (j=0; j<(n-1); j+=2)
		{
			c[i][j]=0;
			c[i][j+1]=0;
			c[i+1][j]=0;
			c[i+1][j+1]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_loop_unroll3#0#0#0 
			#pragma cetus reduction(+: c[i+1][j+1], c[i+1][j], c[i][j+1], c[i][j]) 
			#pragma cetus parallel 
			#pragma omp parallel for if((10000<(1L+(6L*((-2L+n)/2L))))) private(k) reduction(+: c[i+1][j+1], c[i+1][j], c[i][j+1], c[i][j])
			for (k=0; k<(n-1); k+=2)
			{
				c[i][j]+=((a[i][k]*b[k][j])+(a[i][k+1]*b[k+1][j]));
				c[i][j+1]+=((a[i][k]*b[k][j+1])+(a[i][k+1]*b[k+1][j+1]));
				c[i+1][j]+=((a[i+1][k]*b[k][j])+(a[i+1][k+1]*b[k+1][j]));
				c[i+1][j+1]+=((a[i+1][k]*b[k][j+1])+(a[i+1][k+1]*b[k+1][j+1]));
			}
		}
	}
	return ;
}

void mat_mul_arr_priv(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	int * d = malloc(sizeof (int)*n);
	#pragma cetus firstprivate(d) 
	#pragma cetus private(i, j, k) 
	#pragma cetus lastprivate(d) 
	#pragma loop name mat_mul_arr_priv#0 
	for (i=0; i<n; i ++ )
	{
		d[i]=0;
		#pragma cetus firstprivate(d) 
		#pragma cetus private(j, k) 
		#pragma cetus lastprivate(d) 
		#pragma loop name mat_mul_arr_priv#0#0 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<((1L+(5L*n))+((3L*n)*n)))) private(j, k) firstprivate(d) lastprivate(d)
		for (j=0; j<n; j ++ )
		{
			d[i]=i;
			c[d[i]][j]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_arr_priv#0#0#0 
			#pragma cetus reduction(+: c[i][j]) 
			#pragma cetus parallel 
			#pragma omp parallel for if((10000<(1L+(3L*n)))) private(k) reduction(+: c[i][j])
			for (k=0; k<n; k ++ )
			{
				c[i][j]+=(a[i][k]*b[k][j]);
			}
		}
	}
	return ;
}

void mat_mul_arr_priv2(int n, int * * a, int * * b, int * * c)
{
	int i, j, k;
	int * d = malloc(sizeof (int)*n);
	#pragma cetus firstprivate(d) 
	#pragma cetus private(i, j, k) 
	#pragma cetus lastprivate(d) 
	#pragma loop name mat_mul_arr_priv2#0 
	#pragma cetus parallel 
	#pragma omp parallel for if((10000<(((1L+(3L*n))+((5L*n)*n))+(((3L*n)*n)*n)))) private(i, j, k) firstprivate(d) lastprivate(d)
	for (i=0; i<n; i ++ )
	{
		#pragma cetus firstprivate(d) 
		#pragma cetus private(j, k) 
		#pragma cetus lastprivate(d) 
		#pragma loop name mat_mul_arr_priv2#0#0 
		#pragma cetus parallel 
		#pragma omp parallel for if((10000<((1L+(5L*n))+((3L*n)*n)))) private(j, k) firstprivate(d) lastprivate(d)
		for (j=0; j<n; j ++ )
		{
			d[i]=0;
			#pragma cetus private(k) 
			#pragma loop name mat_mul_arr_priv2#0#0#0 
			#pragma cetus reduction(+: d[i]) 
			#pragma cetus parallel 
			#pragma omp parallel for if((10000<(1L+(3L*n)))) private(k) reduction(+: d[i])
			for (k=0; k<n; k ++ )
			{
				d[i]+=(a[i][k]*b[k][j]);
			}
			c[i][j]=d[i];
		}
	}
	return ;
}

/* void mat_mul_pointer_alias(int n, int a, int** b, int** c) { */
	int i, j, k;
