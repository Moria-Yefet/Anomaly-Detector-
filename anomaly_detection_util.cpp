/*
 * animaly_detection_util.cpp
 *
 * Author: Moria Yefet 318802790
 */

#include "anomaly_detection_util.h"
#include <cmath>


// returns the average of an array of numbers x
float avg(float* x, int size){
    float sum = 0;
	for(int i = 0; i < size; i++) {
		sum += x[i];
	}
	return sum / size;
}

// returns the variance of X and Y
float var(float* x, int size){
	float sum = 0;
	for(int i = 0; i < size; i++) {		
		sum += pow(x[i], 2);
	}
	return (sum / size) - (pow(avg(x, size), 2));
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	float sum = 0;
	for(int i = 0; i < size; i++) {
		sum += (x[i] - avg(x, size)) * (y[i] - avg(y, size));
	}
	return sum / size;
}

// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	float sdX = sqrtf(var(x, size));
	float sdY = sqrtf(var(y, size));
	return cov(x, y, size) / (sdX * sdY);
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	float x[size];
	float y[size];
	for(int i = 0; i < size; i++) {
		x[i] = points[i] -> x;
		y[i] = points[i] ->y;
	}
	float a = cov(x, y, size) / var(x, size);
	float b = avg(y, size) - a * avg(x, size);
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line l = linear_reg(points, size);
	return fabs(l.f(p.x) - p.y);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	return fabs(l.f(p.x) - p.y);
}




