#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <GL/glut.h>
#include "Point.h"
#include "Vector.h"
#include "PNPair.h"

using namespace std;

int winWidth = 400, winHeight = 300;

SubCurve c;
vector<Point> inputPoint;
vector<Point> outputPoint;
vector<Point> outputPoint2;
vector<Point> outputPoint3;
vector<Point> outputPoint4;
vector<PNPair> inputPair;
vector<PNPair> outputPair;

void Initial(void) {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void drawSquare(double x, double y)
{
	double width = 0.004;
	glColor3f(0.0f, 0.0f, 0.0f);//设置颜色
	glBegin(GL_POLYGON);
	glVertex2d(x + width, y + width);
	glVertex2d(x - width, y + width);
	glVertex2d(x - width, y - width);
	glVertex2d(x + width, y - width);
	glEnd();
}

//void Display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	for (int i = 0; i < inputPair.size(); ++i)
//	{
//		drawSquare(inputPair[i].first.x, inputPair[i].first.y);
//		if (i < inputPair.size() - 1)
//		{
//			glBegin(GL_LINES);
//			glVertex2d(inputPair[i].first.x, inputPair[i].first.y);
//			glVertex2d(inputPair[i + 1].first.x, inputPair[i + 1].first.y);
//			glEnd();
//		}
//		glColor3f(0.0f, 0.0f, 1.0f);
//		glBegin(GL_LINES);
//		glVertex2d(inputPair[i].first.x, inputPair[i].first.y);
//		glVertex2d(inputPair[i].first.x + inputPair[i].second.x / 15,
//			inputPair[i].first.y + inputPair[i].second.y / 15);
//		glEnd();
//	}
//
//	glColor3f(1.0f, 0.0f, 0.0f);
//
//	if (c->Next && c->Next->Next)
//	{
//		PtrToNode tmp1 = c->Next;
//		PtrToNode tmp2 = tmp1->Next;
//		while (tmp2 != nullptr) {
//			glBegin(GL_LINES);
//			glVertex2d(tmp1->p.first.x, tmp1->p.first.y);
//			glVertex2d(tmp2->p.first.x, tmp2->p.first.y);
//			glEnd();
//			tmp1 = tmp1->Next;
//			tmp2 = tmp2->Next;
//		}
//	}
//
//	glutSwapBuffers();
//}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//glLineWidth(1.5);

	for (int i = 0; i < inputPair.size(); ++i)
	{
		//绘制输入顶点
		drawSquare(inputPair[i].first.x, inputPair[i].first.y);

		//绘制输入多边形
		glColor3f(0.0f, 0.0f, 0.0f);
		if (i < inputPair.size() - 1)
		{
			glBegin(GL_LINES);
			glVertex2d(inputPair[i].first.x, inputPair[i].first.y);
			glVertex2d(inputPair[i + 1].first.x, inputPair[i + 1].first.y);
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			glVertex2d(inputPair[i].first.x, inputPair[i].first.y);
			glVertex2d(inputPair[0].first.x, inputPair[0].first.y);
			glEnd();
		}

		//绘制顶点法向
		//glColor3f(0.0f, 0.0f, 1.0f);
		//glBegin(GL_LINES);
		//glVertex2d(inputPair[i].first.x, inputPair[i].first.y);
		//glVertex2d(inputPair[i].first.x + inputPair[i].second.x / 15,
		//	inputPair[i].first.y + inputPair[i].second.y / 15);
		//glEnd();
	}

	//绘制基于点法向对的细分方法得到的细分曲线
	//glColor3f(1.0f, 0.0f, 0.0f);
	//for (int i = 0; i < outputPair.size() - 1; ++i)
	//{
	//	glBegin(GL_LINES);
	//	glVertex2d(outputPair[i].first.x, outputPair[i].first.y);
	//	glVertex2d(outputPair[i + 1].first.x, outputPair[i + 1].first.y);
	//	glEnd();
	//}

	//绘制圆平均插值法得到的细分曲线
	//glColor3f(1.0f, 0.0f, 0.0f);
	//if (c->Next && c->Next->Next)
	//{
	//	PtrToNode tmp1 = c->Next;
	//	PtrToNode tmp2 = tmp1->Next;
	//	while (tmp2 != nullptr) {
	//		glBegin(GL_LINES);
	//		glVertex2d(tmp1->p.first.x, tmp1->p.first.y);
	//		glVertex2d(tmp2->p.first.x, tmp2->p.first.y);
	//		glEnd();
	//		tmp1 = tmp1->Next;
	//		tmp2 = tmp2->Next;
	//	}
	//}

	//glColor3f(0.5f, 0.7f, 0.0f);
	
	//k=0
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < outputPoint.size() - 1; ++i)
	{
		glBegin(GL_LINES);
		glVertex2d(outputPoint[i].x, outputPoint[i].y);
		glVertex2d(outputPoint[i + 1].x, outputPoint[i + 1].y);
		glEnd();
	}

	//k=2
	glColor3f(0.5f, 0.7f, 0.0f);
	for (int i = 0; i < outputPoint.size() - 1; ++i)
	{
		glBegin(GL_LINES);
		glVertex2d(outputPoint2[i].x, outputPoint2[i].y);
		glVertex2d(outputPoint2[i + 1].x, outputPoint2[i + 1].y);
		glEnd();
	}

	//k=4
	glColor3f(0.0f, 0.0f, 1.0f);
	for (int i = 0; i < outputPoint.size() - 1; ++i)
	{
		glBegin(GL_LINES);
		glVertex2d(outputPoint3[i].x, outputPoint3[i].y);
		glVertex2d(outputPoint3[i + 1].x, outputPoint3[i + 1].y);
		glEnd();
	}

	//k=8
	glColor3f(1.0f, 0.7f, 0.0f);
	for (int i = 0; i < outputPoint.size() - 1; ++i)
	{
		glBegin(GL_LINES);
		glVertex2d(outputPoint4[i].x, outputPoint4[i].y);
		glVertex2d(outputPoint4[i + 1].x, outputPoint4[i + 1].y);
		glEnd();
	}

	glutSwapBuffers();
}

//void reshape(int w, int h)
//{
//	winWidth = w;
//	winHeight = h;
//	glViewport(0, 0, w, h);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	gluOrtho2D(0.0, winWidth, 0.0, winHeight);
//}

int main(int argc, char* argv[]) {
	c = Read();
	PtrToNode head = c->Next;
	PtrToNode temp = c->Next;
	while (temp != nullptr)
	{
		inputPair.push_back(temp->p);
		inputPoint.push_back(temp->p.first);
		temp = temp->Next;
		if (temp->p.first == head->p.first && temp->p.second == head->p.second)
		{
			temp = temp->Next;
		}
	}
	//for (int i = 0; i < 15; ++i)
	//{
	//	addNewPair(c);
	//}
	//outputPair = M4Pt(inputPair, 15);
	//outputPoint = L4Pt(inputPoint, 15);
	//outputPair = MCC(inputPair, 15);
	//outputPoint = Chaikin(inputPoint, 15);
	//outputPoint = oneStepInGLR(inputPoint, 2);
	outputPoint = GLR(inputPoint, 15, 0);
	outputPoint2 = GLR(inputPoint, 15, 2);
	outputPoint3 = GLR(inputPoint, 15, 4);
	outputPoint4 = GLR(inputPoint, 15, 8);

	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("test");
	glutDisplayFunc(Display);

	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glutReshapeFunc(reshape);//若屏幕窗口大小改变则调用reshape函数
	//glutReshapeFunc(ChangeSize);//回调函数
	//glutMouseFunc(MousePlot);//指定鼠标点击响应函数
	//glutPassiveMotionFunc(PassiveMouseMove);//指定鼠标移动响应函数
	Initial();
	glutMainLoop();
	return 0;
}