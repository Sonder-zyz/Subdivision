#include "Vector.h"

Vector::Vector() : x(0.0), y(0.0) { }

Vector::Vector(double xx, double yy) : x(xx), y(yy) { }

Vector::Vector(const Point& p) : x(p.x), y(p.y) { }

Vector::Vector(const Point& p1, const Point& p2) : x(p2.x - p1.x), y(p2.y - p1.y) { }

void Vector::setX(double xx) { this->x = xx; }

void Vector::setY(double yy) { this->y = yy; }

double Vector::norm() const { return sqrt(x * x + y * y); }

void Vector::normalize()
{
    if (this->norm() == 0)
        return;
    this->x /= this->norm();
    this->y /= this->norm();
}

ostream& operator<<(ostream& os, const Vector& v)
{
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

Vector& Vector::operator=(const Vector& v)
{
    this->x = v.x;
    this->y = v.y;
    return *this;
}

bool Vector::operator == (const Vector& v) const
{
    return ((this->x == v.x) && (this->y == v.y));
}

Vector operator+(const Vector& v1, const Vector& v2)
{
    return Vector(v1.x + v2.x, v1.y + v2.y);
}

// Vector operator+(const Vector& v1, double c)
// {

// }

Vector operator-(const Vector& v1, const Vector& v2)
{
    return Vector(v1.x - v2.x, v1.y - v2.y);
}

// Vector operator-(const Vector& v1, double c)
// {

// }

Vector& Vector::operator+=(const Vector& v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}

// Vector& operator+=(double c)
// {

// }

Vector& Vector::operator-=(const Vector& v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}

// Vector& operator-=(double c)
// {

// }

Vector operator*(const Vector& v, double c)
{
    return Vector(v.x * c, v.y * c);
}

Vector operator*(double c, const Vector& v)
{
    return v * c;
}

Vector operator/(const Vector& v, double c)
{
    return (v * (1.0 / c));
}

Vector& Vector::operator*=(double c)
{
    this->x *= c;
    this->y *= c;
    return *this;
}

Vector& Vector::operator/=(double c)
{
    this->x /= c;
    this->y /= c;
    return *this;
}

double dotProduct(const Vector& v1, const Vector& v2)
{
    return (v1.x * v2.x + v1.y * v2.y);
}

double angle(const Vector& v1, const Vector& v2)
{
    return acos(dotProduct(v1, v2) / (v1.norm() * v2.norm()));
}

int orientation(const Vector& v1, const Vector& v2)
{
    double det = v1.x * v2.y - v1.y * v2.x;
    if (det < 0)   return -1; //逆时针
    if (det > 0)   return 1; //顺时针
    return 0; //共线
}

UnitVector::UnitVector() : Vector(1.0, 0.0), theta(0.0) { }

UnitVector::UnitVector(double alpha) : Vector(cos(alpha), sin(alpha))
{
    while (alpha < 0)   alpha += 2 * pi;
    while (alpha >= 2 * pi) alpha -= 2 * pi;
    this->theta = alpha;
}

UnitVector::UnitVector(const Vector& v)
{
    if (v.norm() == 0.0)
    {
        this->x = this->y = theta = 0.0;
    }
    else
    {
        this->x = v.x / v.norm();
        this->y = v.y / v.norm();
        theta = acos(this->x);
        if (this->y < 0)    theta = 2 * pi - theta;
    }
}

UnitVector::UnitVector(double xx, double yy)
{
    Vector v(xx, yy);
    *this = UnitVector(v);
}