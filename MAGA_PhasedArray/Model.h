#pragma once
#include<vector>
#include"cmplx.h"
using namespace std;

typedef pair<double, double> point;
class Model
{
private:
	double L = 0;
	double R = 0;
	double Lambda = 0;
	double D = 0;
	vector<point> loc;
	
	vector<vector<double>>data;
protected:

public:
	void SetLocation(vector<point>& val);
	void SetL(double val);
	void SetR(double val);
	void SetLambda(double val);
	void SetD(double val);
	void CalcIntensivity();
	vector<vector<double>>GetData();
};

