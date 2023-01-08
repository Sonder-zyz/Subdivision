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

// ���Ե㷨���ȷ����ֱ�ߵĽ��㣨�����뱣֤�н��㣩
Point interPoint(PNPair pr1, PNPair pr2);

// �ж����������������ȷ�����߶��Ƿ���ͬһ��ƽ����
// 1��ʾ�ڣ�-1��ʾ���ڣ�0��ʾ�з�����߶ι���
int isOnSameSide(PNPair pr1, PNPair pr2);

// �ж�cp1��cp2�����p1p2�Ƿ���ͬһ��ƽ����
// 1��ʾ�ڣ�-1��ʾ���ڣ�0��ʾ�е��ڷֽ�����
int isOnSameSide(Point p1, Point p2, Point cp1, Point cp2);

// ��pr1��pr2�����µĵ㷨���
PNPair newPair(PNPair pr1, PNPair pr2, double omega);

// �����ͷ���
SubCurve Read();

// ��ӡ�����ϵĵ�ͷ���
void Print(SubCurve c);

// ��ӡ�����ϵĵ�
void printPoint(SubCurve c);

// ����һ����ֵϸ��
void addNewPair(SubCurve c);

SubCurve MLR(SubCurve c, int m);

//void M4Pt(SubCurve c);

vector<PNPair> M4Pt(vector<PNPair>& c, int numSteps);

vector<Point> L4Pt(vector<Point>& p, int numSteps);

vector<PNPair> MCC(vector<PNPair>& c, int numSteps);

vector<Point> Chaikin(vector<Point>& p, int numSteps);

//���� Z(p1, p2)������Ҫ�����������С��ͬ
vector<Point> Zigzag(vector<Point>& p1, vector<Point>& p2);

//���� SF ������
vector<Point> SF(vector<Point>& p);

//���ݹ�ʽ TF = S^k Z(F,SF) ���㲢���� TF
vector<Point> oneStepInGLR(vector<Point>& p, int k);

vector<Point> GLR(vector<Point>& p, int numSteps, int k);

#endif // !PNPAIR_H