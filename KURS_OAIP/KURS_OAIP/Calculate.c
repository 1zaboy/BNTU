
#include <math.h>
#include <stdbool.h>
#include <conio.h>
#include <stdio.h>
#include "Log.h"

double D[25];

struct MyX
{
	double x1;
	double x2;
};


struct MyX GetX(double y, double u)
{
	//The left side of the expression in parentheses
	double ch1 = (9.0 * y + u) * -1.0;
	//The right side of the expression in parentheses
	double ch2 = sqrt(pow(y, 2.0) + 18.0 * y * u + pow(u, 2.0));

	struct MyX s;
	double a = ch1 + ch2;
	if (a < 0)
	{
		a = a * -1;
	}
	s.x1 = (a / 2.0) * -1.0;

	a = ch1 - ch2;
	if (a < 0)
	{
		a = a * -1;
	}
	s.x2 = (a / 2.0) * -1.0;

	return s;
}


double GetP(struct MyX xs, double t)
{
	//The left side of the expression in parentheses
	double ch1 = xs.x2 * exp(xs.x1 * t);
	//The right side of the expression in parentheses
	double ch2 = xs.x1 * exp(xs.x2 * t);

	double ch0 = t / (xs.x2 - xs.x1);

	double a = ch1 - ch2;
	if (a < 0)
	{
		a = a * -1;
	}

	return ch0 * a;
}

double* Calc(double y, double u)
{
	struct MyX s;
	s = GetX(y, u);
	for (int i = 0.0; i <= 240.0; i += 10.0)
	{
		D[i / 10] = GetP(s, i);
		SetStringLogDouble("d", D[i / 10]);
	}
	return &D;
}