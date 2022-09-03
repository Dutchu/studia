#include <iostream>

class Vector {
public:
    static unsigned int obj_count;
    double start;
    double end;

public:
    Vector(double start, double end) {
        this->start = start;
        this->end = end;
        obj_count++;
    }
};


int main() {
}
