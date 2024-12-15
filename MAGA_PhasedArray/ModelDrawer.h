#pragma once


// ModelDrawer
#include<gdiplus.h>
#include<vector>
#include<algorithm>
#include"Model.h"
using namespace Gdiplus;
using namespace std;

class ModelDrawer : public CStatic
{
	DECLARE_DYNAMIC(ModelDrawer)
private:

	double lPadding = 1;
	double rPadding = 1;
	double tPadding = 1;
	double bPadding = 1;

	double left = 0;
	double right = 10;
	double bot = 0;
	double top = 10;

	int GridLines = 11;

	ULONG_PTR token;

	vector<vector<bool>>data;

	bool LBDownFlag = false;

	Matrix* SavedMatrix = nullptr;

	int lasti = -1;
	int lastj = -1;
public:
	ModelDrawer();
	virtual ~ModelDrawer();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	vector<point> GetData();
	void Clear();
};


