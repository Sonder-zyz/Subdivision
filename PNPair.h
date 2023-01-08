#pragma once
#include <iostream>
#include <math.h>
#include <utility>
#include <vector>
#include "Vector.h"

using namespace std;

#ifndef PNPAIR_H
#define PNPAIR_H

//#define omega 0.5

typedef pair<Point, UnitVector> PNPair;

typedef struct Node* PtrToNode;

struct Node {
    PNPair p;
    PtrToNode Next = nullptr;
};

typedef PtrToNode SubCurve;

// 两对点法向对确定的直线的交点（输入须保证有交点）
Point interPoint(PNPair pr1, PNPair pr2);

// 判断两个法向关于两点确定的线段是否在同一半平面内
// 1表示在，-1表示不在，0表示有法向和线段共线
int isOnSameSide(PNPair pr1, PNPair pr2);

// 判断cp1和cp2相对于p1p2是否在同一半平面内
// 1表示在，-1表示不在，0表示有点在分界线上
int isOnSameSide(Point p1, Point p2, Point cp1, Point cp2);

// 由pr1和pr2生成新的点法向对
PNPair newPair(PNPair pr1, PNPair pr2, double omega);

// 输入点和法向
SubCurve Read();

// 打印曲线上的点和法向
void Print(SubCurve c);

// 打印曲线上的点
void printPoint(SubCurve c);

// 进行一步插值细分
void addNewPair(SubCurve c);

SubCurve MLR(SubCurve c, int m);

//void M4Pt(SubCurve c);

vector<PNPair> M4Pt(vector<PNPair>& c, int numSteps);

vector<Point> L4Pt(vector<Point>& p, int numSteps);

vector<PNPair> MCC(vector<PNPair>& c, int numSteps);

vector<Point> Chaikin(vector<Point>& p, int numSteps);

//返回 Z(p1, p2)，但是要求两个数组大小相同
vector<Point> Zigzag(vector<Point>& p1, vector<Point>& p2);

//计算 SF 并返回
vector<Point> SF(vector<Point>& p);

//根据公式 TF = S^k Z(F,SF) 计算并返回 TF
vector<Point> oneStepInGLR(vector<Point>& p, int k);

vector<Point> GLR(vector<Point>& p, int numSteps, int k);

#endif // !PNPAIR_H