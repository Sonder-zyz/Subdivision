#pragma once
#include <iostream>
#include <math.h>
#include "Point.h"

using namespace std;

#ifndef VECTOR_H
#define VECTOR_H

#define pi 3.141592653

class Vector {
public:
    double x;
    double y;

public:
    Vector();
    Vector(double xx, double yy);
    Vector(const Point& p);
    Vector(const Point& p1, const Point& p2);

    void setX(double xx);
    void setY(double yy);
    double norm() const;
    void normalize();

    friend ostream& operator<<(ostream& os, const Vector& v);
    Vector& operator=(const Vector& v);
    bool operator==(const Vector& v) const;
    friend Vector operator+(const Vector& v1, const Vector& v2);
    // friend Vector operator+(const Vector& v1, double c);
    friend Vector operator-(const Vector& v1, const Vector& v2);
    // friend Vector operator-(const Vector& v1, double c);
    Vector& operator+=(const Vector& v);
    // Vector& operator+=(double c);
    Vector& operator-=(const Vector& v);
    // Vector& operator-=(double c);
    friend Vector operator*(const Vector& v, double c);
    friend Vector operator*(double c, const Vector& v);
    friend Vector operator/(const Vector& v, double c);
    Vector& operator*=(double c);
    Vector& operator/=(double c);

    friend double dotProduct(const Vector& v1, const Vector& v2);
    friend double angle(const Vector& v1, const Vector& v2);
    friend int orientation(const Vector& v1, const Vector& v2); //返回1,0,-1，分别表示v1->v2：顺时针、共线、逆时针
private:

};

class UnitVector : public Vector {
public:
    double theta; // theta \in [0, 2pi)

public:
    UnitVector();
    UnitVector(double alpha);
    UnitVector(const Vector& v);
    UnitVector(double xx, double yy);

private:

};

#endif // !VECTOR_H