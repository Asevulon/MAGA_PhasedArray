#include "pch.h"
#include "Model.h"
#define pow2(x) ((x) * (x))

void Model::SetLocation(vector<point>& val)
{
	loc = val;
}

void Model::SetL(double val)
{
	L = val;
}

void Model::SetR(double val)
{
	R = val;
}

void Model::SetLambda(double val)
{
	Lambda = val;
}

void Model::SetD(double val)
{
	D = val;
}

void Model::CalcIntensivity()
{
	int size = R + 1;
	size *= 2;
	data = vector<vector<double>>(size, vector<double>(size, 0));

	double l = L * Lambda;
	double d = D * Lambda;
	double r = R * d;
	double x = 0;
	double y = 0;
	double z = 0;
	double xr = 0;
	double yr = 0;
	double mid = size / 2 * d;
	double r0 = mid - 5 * l;
	double ri = 0;
	double k = 8 * atan(1) / Lambda;

	cmplx summ(0, 0);
	cmplx Ai(0, 0);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			x = (j + 0.5) * d;
			y = (i + 0.5) * d;
			if (pow2(mid - x) + pow2(mid - y) > pow2(r))
			{
				data[i][j] = 0;
				continue;
			}
			z = sqrt(pow2(r) - pow2(x- mid) - pow2(y - mid));
			summ = cmplx(0, 0);

			for (auto& p : loc)
			{
				xr = r0 + (p.second + 0.5) * l;
				yr = r0 + (p.first + 0.5) * l;

				ri = sqrt(pow2(x - xr) + pow2(y - yr) + pow2(z));

				Ai.re = cos(k * ri) / ri;
				Ai.im = -sin(k * ri) / ri;

				summ = summ + Ai;
			}
			data[i][j] = summ.Abs();
		}
	}
}

vector<vector<double>> Model::GetData()
{
	return data;
}
