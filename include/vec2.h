#ifndef _VEC2_
#define _VEC2_ 
#include <math.h>

#include <SDL2/SDL.h>

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
        this->vec.x = x;
        this->vec.y = y;
    }

    /* Add a vector to this vector */
    void add(Vec2 v) {
        this->vec.x += v.getX();
        this->vec.y += v.getY();
    }

    /* Subtract a vector from this vector */
    void sub(Vec2 v) {
        this->vec.x -= v.getX();
        this->vec.y -= v.getY();
    }

    /* Limit this vectors magnitude to the mag passed in */
    void limit(double mag) {
        if (this->magnitude() > mag) {
            this->setMag(mag);
        } 
    }

    int magnitude() {
        return sqrt( pow(vec.x, 2) + pow(vec.y, 2));
    }

    void multiply(double scalar) {
        this->vec.x *= scalar;
        this->vec.y *= scalar;
    }

    void divide(double scalar) {
        this->vec.x /= scalar;
        this->vec.y /= scalar;
    }

    /* https://stackoverflow.com/questions/41317291/setting-the-magnitude-of-a-2d-vector */
    void setMag(double newMag) {
        vec.x = vec.x * newMag / this->magnitude();
        vec.y = vec.y * newMag / this->magnitude();
    }

    SDL_FPoint getVec() { return vec; }

    double getX() { return vec.x; }
    double getY() { return vec.y; }

    void setX(double x) { this->vec.x = x; }
    void setY(double y) { this->vec.y = y; }

    void multX(double scalar) { this->vec.x *= scalar; }
    void multY(double scalar) { this->vec.y *= scalar; }

    void operator = (const Vec2 &v) {
        vec.x = v.vec.x;
        vec.y = v.vec.y;
    }

    /* Just your friendly Pythagorean Theorem */
    double Distance (Vec2 point) {
        double distX = this->getX() - point.getX();
        double distY = this->getY() - point.getY();
        return sqrt((distX * distX) + (distY * distY));
    }
};

#endif