#pragma once
#include <iostream>
#include <math.h>

using namespace std;

#ifndef POINT_H
#define POINT_H

class Point {
public:
    double x;
    double y;

public:
    Point();
    Point(double xx, double yy);

    void setX(double xx);
    void setY(double yy);

    friend ostream& operator<<(ostream& os, const Point& p);
    Point& operator=(const Point& p);
    bool operator==(const Point& p) const;
    friend Point operator+(const Point& p1, const Point& p2);
    // friend Point operator+(const Point& p1, double c);
    friend Point operator-(const Point& p1, const Point& p2);
    // friend Point operator-(const Point& p1, double c);
    Point& operator+=(const Point& p);
    // Point& operator+=(double c);
    Point& operator-=(const Point& p);
    // Point& operator-=(double c);
    friend Point operator*(const Point& p, double c);
    friend Point operator*(double c, const Point& p);
    friend Point operator/(const Point& p, double c);
    Point& operator*=(double c);
    Point& operator/=(double c);

    friend double distance(const Point& p1, const Point& p2);
    friend Point midPoint(const Point& p1, const Point& p2);
private:

};

#endif // !POINT_H