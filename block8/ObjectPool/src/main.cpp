#include <iostream>
#include "../include/ObjectPool.hpp"

class Point {
public:
    int m_x, m_y;
    Point()                // конструктор без параметров
            : m_x(0), m_y(0) {}
    Point(int x, int y)    // конструктор с параметрами
            : m_x(x), m_y(y) {}
};


int main() {
    ObjectPool<Point> pp(10);     // выделена память под 10 объектов Point

    Point &p1 = pp.alloc();       // сработал конструктор Point()
    Point &p2 = pp.alloc(0, 1);   // сработал конструктор Point(0, 1)

    std::cout << p1.m_x << ", " << p1.m_y << std::endl
              << p2.m_x << ", " << p2.m_y << std::endl;
    return 0;
}