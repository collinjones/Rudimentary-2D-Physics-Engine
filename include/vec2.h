#ifndef _VEC2_
#define _VEC2_ 
#include <math.h>

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Vec2 {

private:
    SDL_FPoint vec;

public:

    Vec2() {
        vec.x = 0;
        vec.y = 0;
    }

    Vec2(double x, double y) {
        vec.x = x;
        vec.y = y;
    }

    void setVec(double x, double y) {
        vec.x = x;
        vec.y = y;
    }

    /* Add a vector to this vector */
    void add(Vec2 v) {
        vec.x += v.getX();
        vec.y += v.getY();
    }

    /* Subtract a vector from this vector */
    void sub(Vec2 v) {
        vec.x -= v.getX();
        vec.y -= v.getY();
    }

    /* Limit this vectors magnitude to the mag passed in */
    void limit(double mag) {
        if (magnitude() > mag) {
            setMag(mag);
        } 
    }

    double magnitude() {
        return sqrt( pow(vec.x, 2) + pow(vec.y, 2));
    }

    void multiply(double scalar) {
        vec.x *= scalar;
        vec.y *= scalar;
    }

    void divide(double scalar) {
        vec.x /= scalar;
        vec.y /= scalar;
    }

    /* https://stackoverflow.com/questions/41317291/setting-the-magnitude-of-a-2d-vector */
    void setMag(double newMag) {
        vec.x = vec.x * newMag / magnitude();
        vec.y = vec.y * newMag / magnitude();
    }

    SDL_FPoint getVec() { return vec; }

    double getX() { return vec.x; }
    double getY() { return vec.y; }

    void setX(double x) { vec.x = x; }
    void setY(double y) { vec.y = y; }

    void multX(double scalar) { vec.x *= scalar; }
    void multY(double scalar) { vec.y *= scalar; }

    void operator = (const Vec2 &v) {
        vec.x = v.vec.x;
        vec.y = v.vec.y;
    }

    /* Just your friendly Pythagorean Theorem */
    double Distance (Vec2 other) {
        double distX = vec.x - other.getX();
        double distY = vec.y - other.getY();
        return sqrt((distX * distX) + (distY * distY));  
    }

    double Dot(Vec2 other) {
        return (vec.x * other.getX()) + (vec.y * other.getY());
    }

    friend ostream& operator<<(ostream& os, const Vec2& v)
    {
        os << "(" << v.vec.x << ", " << v.vec.y << ")";
        return os;
    }

    void Normalize() {
        setVec(vec.x / magnitude(), vec.y / magnitude());
    }

    bool IntersectCircle(Vec2 pos, double rad) {
        double dist = Distance(pos);
        if(dist <= rad) {
            return true;
        }
        return false;
    }
};

#endif