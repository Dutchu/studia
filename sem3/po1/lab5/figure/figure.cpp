#include <iostream>
#include <cmath>

class Solid {
public:
    virtual double field() {return 0.;}

    virtual double volume() {return 0.;}

    virtual double diagonal() {return 0.;}

    virtual ~Solid() = default;
};

class Sphere : public Solid {
private:
    double r;
public:
    explicit Sphere(double r) : r(r) {}

    double field() override {
        return 4.0 * 3.14 * pow(r, 2);
    }

    double volume() override {
        return (4.0  * 3.14 * pow(r, 3)) / 3.0;
    }

    double diagonal() override {
        return 2 * r;
    }


};

class Cube : public Solid {
private:
    double a, b, c;
public:
    Cube(double a, double b, double c) : a(a), b(b), c(c) {}

    double field() override {
        return 2 * ((a * b) + (a * c) + (b * c));
    }

    double volume() override {
        return a * b * c;
    }

    double diagonal() override {
        return sqrt(pow(a, 2) + pow(b, 2) + pow(c, 2));
    }

};

class Pyramid : public Solid {
public:
    double a, h;

    Pyramid(double a, double h) : a(a), h(h) {}

    double field() override {
        return pow(a, 2) + (2 * a * h);
    }

    double volume() override {
        return (1.0 / 3.0) * pow(a, 2) * h;
    }

};

int main() {

    auto sphere = Sphere(1);
    std::cout << "Sphere field = " << sphere.field() << "\n";
    std::cout << "Sphere volume: " << sphere.volume() << "\n";
    std::cout << "Sphere diagonal: " << sphere.volume() << "\n";

    auto cube = Cube(1, 2, 3);
    std::cout << "Cube field: " << cube.field() << "\n";
    std::cout << "Cube volume: " << cube.volume() << "\n";
    std::cout << "Cube diagonal: " << cube.diagonal() << '\n';

    auto pyramid = Pyramid(4, 8);
    std::cout << "Pyramid field: " << pyramid.field() << '\n';
    std::cout << "Pyramid volume: " << pyramid.volume() << '\n';
    return 0;
}