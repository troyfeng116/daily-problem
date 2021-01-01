#include <iostream>
using namespace std;

/*
Given two rectangles, find the area of intersection.

Rectangle(min_x, min_y, max_x, max_y) defines rectangle

ex.
rect1 = Rectangle(0, 0, 3, 2)
rect2 = Rectangle(1, 1, 3, 3)

intersection_area(rect1, rect2) = 2
*/

struct Rectangle {
    int min_x;
    int min_y;
    int max_x;
    int max_y;
    Rectangle() {
        min_x = 0;
        min_y = 0;
        max_x = 0;
        max_y = 0;
    }
    Rectangle(int a, int b, int c, int d) {
        min_x = a;
        min_y = b;
        max_x = c;
        max_y = d;
    }
};

/* APPROACH 1: Find width and height of intersection. min(r1.max_x, r2.max_x) - max(r1.min_x, r2.min_x)
gives width and min(r1.max_y, r2.max_y) - max(r1.min_y, r2.min_y) gives height.
Leftmost right side - rightmost left side = width, lowest top side - highest bottom side = height.
O(1) */
int findIntersectionArea(Rectangle *r1, Rectangle *r2) {
    int width = min(r1->max_x, r2->max_x) - max(r1->min_x, r2->min_x);
    if (width <= 0) return 0;
    int height = min(r1->max_y, r2->max_y) - max(r1->min_y, r2->min_y);
    if (height <= 0) return 0;
    return width * height;
}

int main(int argc, char **argv) {
    Rectangle *r1 = new Rectangle(0, 0, 3, 2);
    Rectangle *r2 = new Rectangle(1, 1, 3, 3);
    std::cout << findIntersectionArea(r1, r2) << '\n';
    return 0;
}
