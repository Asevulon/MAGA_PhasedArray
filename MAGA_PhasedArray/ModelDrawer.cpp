// ModelDrawer.cpp: файл реализации
//

#include "pch.h"
#include "ModelDrawer.h"


// ModelDrawer

IMPLEMENT_DYNAMIC(ModelDrawer, CStatic)

ModelDrawer::ModelDrawer()
{
	GdiplusStartupInput si;
	GdiplusStartup(&token, &si, NULL);

	data = vector<vector<bool>>(GridLines - 1, vector<bool>(GridLines - 1, false));
}

ModelDrawer::~ModelDrawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(ModelDrawer, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// Обработчики сообщений ModelDrawer




void ModelDrawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics ToWindow(lpDrawItemStruct->hDC);
	int width = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	int height = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
	Bitmap bmp(width, height);
	Graphics gr(&bmp);
	gr.Clear(Color::White);

	gr.SetSmoothingMode(SmoothingModeAntiAlias);
	double actWidth(right - left);
	double actHeight(top - bot);
	double actLP = actWidth * lPadding / 100.;
	double actRP = actWidth * rPadding / 100.;
	double actTP = actHeight * tPadding / 100.;
	double actBP = actHeight * bPadding / 100.;

	double actTop = top + actTP;
	double actBot = bot - actBP;
	double actLeft = left - actLP;
	double actRight = right + actRP;

	actWidth = actRight - actLeft;
	actHeight = actTop - actBot;


	double xScale = width / actWidth;
	double yScale = -height / actHeight;

	Pen BackGroundPen(Color(150, 150, 150));

	Matrix matr;
	matr.Scale(xScale, yScale);
	matr.Translate(actLP - left, -actTop);

	PointF p1;
	PointF p2;

	double GridStep = (right - left) / (GridLines - 1.);
	for (int i = 0; i < GridLines; i++)
	{
		p1.X = i * GridStep;
		p1.Y = 0;

		p2.X = i * GridStep;
		p2.Y = top;

		matr.TransformPoints(&p1);
		matr.TransformPoints(&p2);

		gr.DrawLine(&BackGroundPen, p1, p2);
		
		p1.X = 0;
		p1.Y = i * GridStep;

		p2.X = right;
		p2.Y = i * GridStep;

		matr.TransformPoints(&p1);
		matr.TransformPoints(&p2);

		gr.DrawLine(&BackGroundPen, p1, p2);
	}

	SolidBrush DataBrush(Color(200, 100, 0));
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			if (!data[i][j])continue;

			p1.X = j;
			p1.Y = i;
			
			p2.X = j + 1;
			p2.Y = i + 1;

			matr.TransformPoints(&p1);
			matr.TransformPoints(&p2);

			gr.FillEllipse(&DataBrush, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
		}
	}


	ToWindow.DrawImage(&bmp, 0, 0);

	delete SavedMatrix;
	matr.Invert();
	SavedMatrix = matr.Clone();
}

void ModelDrawer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	LBDownFlag = true;
	SetCapture();
	PointF p(point.x, point.y);
	SavedMatrix->TransformPoints(&p);

	if (p.X < left)
	{
		CStatic::OnLButtonDown(nFlags, point);
		return;
	}
	if (p.Y < bot)
	{
		CStatic::OnLButtonDown(nFlags, point);
		return;
	}
	if (p.X > right)
	{
		CStatic::OnLButtonDown(nFlags, point);
		return;
	}
	if (p.Y > top)
	{
		CStatic::OnLButtonDown(nFlags, point);
		return;
	}

	data[p.Y][p.X] = !data[p.Y][p.X];
	lasti = p.Y;
	lastj = p.X;
	Invalidate();
	CStatic::OnLButtonDown(nFlags, point);
}


void ModelDrawer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	LBDownFlag = false;
	ReleaseCapture();
	CStatic::OnLButtonUp(nFlags, point);
}


void ModelDrawer::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (LBDownFlag)
	{
		PointF p(point.x, point.y);
		SavedMatrix->TransformPoints(&p);

		if (p.X < left)
		{
			CStatic::OnMouseMove(nFlags, point);
			return;
		}
		if (p.Y < bot)
		{
			CStatic::OnMouseMove(nFlags, point);
			return;
		}
		if (p.X > right)
		{
			CStatic::OnMouseMove(nFlags, point);
			return;
		}
		if (p.Y > top)
		{
			CStatic::OnMouseMove(nFlags, point);
			return;
		}

		int tempi = p.Y;
		int tempj = p.X;
		if ((tempi == lasti) && (tempj == lastj))
		{
			CStatic::OnMouseMove(nFlags, point);
			return;
		}
		data[p.Y][p.X] = !data[p.Y][p.X];

		lasti = p.Y;
		lastj = p.X;
		Invalidate();
	}
	CStatic::OnMouseMove(nFlags, point);
}

vector<point> ModelDrawer::GetData()
{
	vector<point>res;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j < data[i].size(); j++)
		{
			if (data[i][j])res.push_back(point(i, j));
		}
	}
	return res;
}

void ModelDrawer::Clear()
{
	data = vector<vector<bool>>(GridLines - 1, vector<bool>(GridLines - 1, false));
	Invalidate();
}
