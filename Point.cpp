#include "Point.h"

Point::Point() : x(0.0), y(0.0) { }

Point::Point(double xx, double yy) : x(xx), y(yy) { }

void Point::setX(double xx) { this->x = xx; }

void Point::setY(double yy) { this->y = yy; }

ostream& operator<<(ostream& os, const Point& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

Point& Point::operator=(const Point& p)
{
    this->x = p.x;
    this->y = p.y;
    return *this;
}

bool Point::operator==(const Point& p) const
{
    return ((this->x == p.x) && (this->y == p.y));
}

Point operator+(const Point& p1, const Point& p2)
{
    return Point(p1.x + p2.x, p1.y + p2.y);
}

// Point operator+(const Point& p1, double c)
// {

// }

Point operator-(const Point& p1, const Point& p2)
{
    return Point(p1.x - p2.x, p1.y - p2.y);
}

// Point operator-(const Point& p1, double c)
// {

// }

Point& Point::operator+=(const Point& p)
{
    this->x += p.x;
    this->y += p.y;
    return *this;
}

// Point& operator+=(double c)
// {

// }

Point& Point::operator-=(const Point& p)
{
    this->x -= p.x;
    this->y -= p.y;
    return *this;
}

// Point& operator-=(double c)
// {

// }

Point operator*(const Point& p, double c)
{
    return Point(p.x * c, p.y * c);
}

Point operator*(double c, const Point& p)
{
    return p * c;
}

Point operator/(const Point& p, double c)
{
    return (p * (1.0 / c));
}

Point& Point::operator*=(double c)
{
    this->x *= c;
    this->y *= c;
    return *this;
}

Point& Point::operator/=(double c)
{
    this->x /= c;
    this->y /= c;
    return *this;
}

double distance(const Point& p1, const Point& p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

Point midPoint(const Point& p1, const Point& p2)
{
    return (p1 + p2) / 2;
}