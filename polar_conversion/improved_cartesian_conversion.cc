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

PolarPoint convertToPolar(CartesianPoint p) {
    return createPolarPoint(sqrt(p.x * p.x + p.y * p.y), atan2f(p.y, p.x));
}

CartesianPoint convertToCartesian(PolarPoint p) {
    return createCartesianPoint(p.r * cos(p.theta), p.r * sin(p.theta));
}

struct BezierCurve { //A set of polar points that describes a bezier curve
    BezierCurve* left;
    BezierCurve* right;
    CartesianPoint start, end;
    int order;
};

/* This function takes the cartesian points defining a Bezier Curve
   and converts them to a data structure that can be used to find
   polar points along the curve.

BezierCurve createBezierCurve(CartesianPoint points[], int length) {
    BezierCurve curve;
    curve.start = points[0];
    curve.end = points[length-1];
    curve.order = length - 1;
    if (length > 1) {
        CartesianPoint leftPoints[length-1];
        CartesianPoint rightPoints[length-1];
        for (int i = 0; i < length - 2; i++) {
            leftPoints[i] = points[i];
            rightPoints[i] = points[i+1];
        }
        BezierCurve left = createBezierCurve(leftPoints, length-1);
        BezierCurve right = createBezierCurve(rightPoints, length-1);
        
        curve.left = &left;
        curve.right = &right;
    }
    return curve;
}

PolarPoint pointOnBezier(BezierCurve curve, float t) { //t must be on [0, 1]
    if (curve.order == 0) {
        return convertToPolar(curve.start);
    }  else {
        CartesianPoint start = convertToCartesian(pointOnBezier(*curve.left, t));
        CartesianPoint end = convertToCartesian(pointOnBezier(*curve.right, t));
        CartesianPoint p;
        
        p.x = t * (end.x - start.x) + start.x;
        p.y = t * (end.y - start.y) + start.y;
        
        return convertToPolar(p);
    }
}
*/

PolarPoint* cartesianToPolar(CartesianPoint cartesian[], int length) {
    PolarPoint* polar = new PolarPoint[length];
    
    for (int i = 0; i < length; i++) { 
        polar[i] = convertToPolar(cartesian[i]);
    }
    
    return polar;
}

struct LinearMovement {
    float dTheta;
    float dR;
    float velocity;
    float roatOfChange;
    PolarPoint start;
    PolarPoint end;
}
/*
LinearMovement createLinearMovement(PolarPoint start, PolarPoint end, velocity) {
    
}*/

int main() {
    int l = 4;
    
    CartesianPoint cPoints[l];
    cPoints[0].x = 0;
    cPoints[0].y = 0;
    cPoints[1].x = 0;
    cPoints[1].y = 5;
    cPoints[2].x = 5;
    cPoints[2].y = 5;
    cPoints[3].x = 5;
    cPoints[3].y = 0;
    
    PolarPoint* pPoints;
    pPoints = cartesianToPolar(cPoints, l);
    
    for (int i = 0; i < l; i++) {
        std::cout << pPoints[i].r;
        std::cout << " ";
        std::cout << pPoints[i].theta;
        std::cout << "\n";
    }
    
    std::cout << std::endl;
}
