#include <iostream>
using namespace std;

/*
Given a time in the format of hour and minute, calculate the angle of the 
hour and minute hand on a clock.
*/

/* APPROACH 1: Find distance from each hand to midnight, counter-clockwise (i.e.
how far each hand has traveled from 12 o'clock in degrees). Subtract the
two angles, take absolute value, if > 180 subtract from 360. */
double angleBetweenClockHands(int h, int m) {
    double hAngle = (h%12)*30 + (m/60.0)*30;
    double mAngle = m*6.0;
    double diff = hAngle - mAngle;
    if (diff < 0) diff *= -1;
    if (diff > 180) diff = 360-diff;
    return diff;
}

int main(int argc, char **argv) {
    std::cout << angleBetweenClockHands(12, 30) << '\n';
    std::cout << angleBetweenClockHands(3, 30) << '\n';
    return 0;
}