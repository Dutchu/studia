#include <iostream>
class Point {
private:
    float x;
    float y;
public:
    Point() {
        Point::x = 0.;
        Point::y = 0.;
    }
    Point(float x, float y) : x(x), y(y) {
    }
    Point operator + (Point const &p) const {
        Point result;
        result.x = Point::x + p.x;
        result.y = Point::y + p.y;
        return result;
    }
    Point operator - (Point const &p) const {
        Point result;
        result.x = Point::x - p.x;
        result.y = Point::y - p.y;
        return result;
    }
    Point operator * (Point const &p) const {
        Point result;
        result.x = Point::x * p.x;
        result.y = Point::y * p.y;
        return result;
    }
    [[nodiscard]] std::string to_string() const {
        std::string s = std::string("Point{x=");
        s.append(std::to_string(x));
        s.append(",y=");
        s.append(std::to_string(x));
        s.append("}");
        return s;
    }
};

class Vector {
private:
    static unsigned int COUNT;
    Point start;
    Point end;

public:
    Vector(const Point &start, const Point &anEnd) : start(start), end(anEnd) {
        std::cout << "Vector object created!" <<std::endl;
        COUNT ++;
    }

    static unsigned int get_count() {
        return COUNT;
    }
    void add(const Vector& v) {
        Vector::start = Vector::start + v.start;
        Vector::end = Vector::end + v.end;
    }

    void sub(const Vector& v) {
        Vector::start = Vector::start - v.start;
        Vector::end = Vector::end - v.end;
    }
    void mul(const Vector& v) {
        Vector::start = Vector::start * v.start;
        Vector::end = Vector::end * v.end;
    }
    void print() {
        std::cout << "Vector{start = " << Vector::start.to_string() << ", end = " << Vector::end.to_string() << "}" << std::endl;
    }
    ~Vector() {
        COUNT --;
        std::cout << "Vector object deleted!" << std::endl;
    }
};


unsigned int Vector::COUNT = 0;



int main() {

    auto* v1 = new Vector(Point(20,40), Point(-40,-20));
    auto* v2 = new Vector(Point(0,1), Point(-1,0));

    v1->add(*v2);
    v1->print();

    v1->sub(*v2);
    v1->print();

    v1->mul(*v2);
    v1->print();

    std::cout << "Object count is: " << Vector::get_count() << std::endl;

    delete v1;
    delete v2;

    std::cout << "Object count is: " << Vector::get_count() << std::endl;

    return 0;
}
