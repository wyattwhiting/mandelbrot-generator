#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Z struct complex_num
#define MAX_ITR 300
#define X_RES 80
#define Y_RES 24
#define X_MIN -1.5
#define X_MAX 1.0
#define Y_MIN -1.0
#define Y_MAX 1.0

struct complex_num
{
	float re;
	float im;
};

void complex_add(Z * z1, Z * z2, Z * res)
{
	res->re = z1->re + z2->re;
	res->im = z1->im + z2->im;
}

void complex_times(Z * z1, Z * z2, Z * res)
{
	float a = z1->re;
	float b = z1->im;
	float c = z2->re;
	float d = z2->im;
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

void mandle_iter(Z * z1, Z * c, Z * res)
{
	complex_pow(z1, 2, res);
	complex_add(res, c, res);
}

float mag(Z * z)
{
	return sqrtf(z->re * z->re + z->im * z->im);
}

int main()
{
	/* declare pointers */
	Z * c;
	Z * z;

	/* assign memory */
	c = malloc(sizeof(Z));
	z = malloc(sizeof(Z));

	float re;
	float im;

	for(im = Y_MAX; im > Y_MIN; im -= (Y_MAX-Y_MIN)/Y_RES)
	{
		for(re = X_MIN; re < X_MAX; re += (X_MAX-X_MIN)/X_RES)
		{
			z->re = 0.0;
			z->im = 0.0;
			c->re = re;
			c->im = im;
			int iter = 0;
			int flag = 1;
			while(iter < MAX_ITR)
			{
				mandle_iter(z, c, z);
				if(mag(z) >= 2)
				{
					flag = 0;
					break;
				}
				iter++;
			}
			if(flag) printf("#");
			else printf(" ");
		}
		printf("\n");
	}

	/* free memory */
	free(z);
	free(c);
	return 0;
}
