#include <iostream>
#include <math.h>

float PI = 3.14159265359;

struct PolarPoint {
    float r;
    float theta; //theta is in radians
} ;

PolarPoint createPolarPoint(float r, float theta) {
    PolarPoint p;
    p.r = r;
    p.theta = theta;
    return p;
}

struct CartesianPoint {
    float x;
    float y;
};

CartesianPoint createCartesianPoint(float x, float y) {
    CartesianPoint p;
    p.x = x;
    p.y = y;
    return p;
}

//Converts cartesian points to polar
PolarPoint convertToPolar(CartesianPoint p) {
    float theta = atan2f(p.y, p.x);
    if (theta < 0) theta = theta + 2 * PI; //atan returns theta on [-PI, PI] but we want [0, 2*PI];
    return createPolarPoint(sqrt(p.x * p.x + p.y * p.y), theta);
}


//Converts polar points to cartesian
CartesianPoint convertToCartesian(PolarPoint p) {
    return createCartesianPoint(p.r * cos(p.theta), p.r * sin(p.theta));
}


//Converts an array of cartesian points to polar
PolarPoint* cartesianToPolar(CartesianPoint cartesian[], int length) { 
    PolarPoint* polar = new PolarPoint[length];
    
    for (int i = 0; i < length; i++) { 
        polar[i] = convertToPolar(cartesian[i]);
    }
    
    return polar;
}

struct LinearMovement {
    
    //Velocity is measured in unit of cartesian measurement per second
    float velocity;
    
    //Dt is the amount to change the parametric variable 't' per second
    //to maintain the given velocity. t will always be >= 0 and <=1
    float dT; 
    
    //Cartesian points to hold the end points
    CartesianPoint start;
    CartesianPoint end;
};

LinearMovement createLinearMovement(CartesianPoint start, CartesianPoint end, float velocity) {
    LinearMovement m;
    m.velocity = velocity;
    m.start = start;
    m.end = end;
    m.velocity = velocity;
    m.dT = sqrt( pow(end.x - start.x, 2) + pow(end.y - start.y, 2) ) / velocity; //See http://imgur.com/AEDInc3 for where this formula comes from
    return m;
}

//T is a variable that represents time (kinda). Combing t with the dT in the
//Linear movement struct allows user to control the velocity of the movement.
// See http://imgur.com/AEDInc3 for some math behind this.
PolarPoint pointAt(LinearMovement m, float t) {
    PolarPoint p;
    
    p.theta = atan2f( t * ( m.end.x - m.start.x ) + m.start.x, 
                      t * ( m.end.y - m.start.y ) + m.start.y);
    if (p.theta < 0) p.theta = p.theta + 2 * PI; //Atan returns -PI < theta < PI, we want 0 < theta < 2*PI
    p.r = sqrt( pow( t * ( m.end.x - m.start.x ) + m.start.x, 2 ) +
                pow( t * ( m.end.y - m.start.y ) + m.start.y , 2));
    
    return p;
}

int main() {
    CartesianPoint start;
    start.x = 0;
    start.y = 0;
    CartesianPoint end;
    end.x = 5;
    end.y = 2;
    
    LinearMovement move1 = createLinearMovement(start, end, .2);
    
    PolarPoint point = pointAt(move1, .5); //Since t = .5 it will be the point halfway between the two
    
    std::cout << point.r;
    std::cout << " ";
    std::cout << point.y;
    
    std::cout << std::endl;
}
