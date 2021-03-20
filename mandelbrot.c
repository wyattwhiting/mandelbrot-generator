#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Z struct complex_num
#define flt float
#define MAX_ITR 500
#define X_RES 80
#define Y_RES 31
#define X_MIN -1.5
#define X_MAX 0.5
#define Y_MIN -1.0
#define Y_MAX 1.0

struct complex_num
{
	/* complex numbers have real and imaginary component */
	flt re;
	flt im;
};

void complex_add(Z * z1, Z * z2, Z * res)
{
	/* addition is component-wise */
	res->re = z1->re + z2->re;
	res->im = z1->im + z2->im;
}

void complex_times(Z * z1, Z * z2, Z * res)
{
	flt a = z1->re;
	flt b = z1->im;
	flt c = z2->re;
	flt d = z2->im;
	res->re = a*c - b*d;
	res->im = a*d + b*c;
}

void complex_pow(Z * z1, int n, Z * res)
{
	/* copy z1 to res */
	res->re = z1->re;
	res->im = z1->im;
	
	/* multiply result by original (n - 1) times */
	int i;
	for(i = 0; i < (n - 1); i++)
		complex_times(z1, res, res);
}

void complex_print(Z * z1, int flag)
{
	printf("%f + %f i ", z1->re, z1->im);
	if(flag) printf("\n");
}

void mandel_iter(Z * z1, Z * c, Z * res)
{
	complex_pow(z1, 2, res);
	complex_add(res, c, res);
}

flt mag(Z * z)
{
	return sqrtf(z->re * z->re + z->im * z->im);
}

void draw_set(flt x_min, flt x_max, flt x_res, flt y_min, flt y_max, flt y_res, flt max_iter)
{
	Z * c = malloc(sizeof(Z));
	Z * z = malloc(sizeof(Z));

	/* loop variables */
	flt re;
	flt im;

	for(im = y_max; im >= y_min; im -= (y_max-y_min)/(y_res - 1))
	{
		for(re = x_min; re <= x_max; re += (x_max-x_min)/(x_res - 1))
		{
			z->re = 0.0;
			z->im = 0.0;
			c->re = re;
			c->im = im;
			int iter = 0;
			while(iter < max_iter && mag(z) < 2)
			{
				mandel_iter(z, c, z);
				iter++;
			}
			(iter == max_iter) ? printf("#") : printf(" ");
		}
		printf("\n");
	}
	free(z);
	free(c);
}

int main()
{
	draw_set(X_MIN, X_MAX, X_RES, Y_MIN, Y_MAX, Y_RES, MAX_ITR);

	return 0;
}
