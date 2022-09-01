#include <iostream>
#include <cmath>

class Complex {
private:
    double re;
    double im;

public:
    Complex(double re = 1., double im = 1.) {
        this->re = re;
        this->im = im;
    }

    void print() {
        std::cout << this->re;

        if (this->im > 0) {
            std::cout << " + " << this->im << "i";
        } else {
            std::cout << " - " << abs(this->im) << "i";
        }
    }

    void add(Complex c) {
        this->re = this->re + c.re;
        this->im = this->im + c.im;
    }

    void sub(Complex c) {
        this->re = this->re - c.re;
        this->im = this->im - c.im;
    }

    void mul(Complex c) {
        this->re = (this->re * c.re) - (this->im * c.im);
        this->im = (this->re * c.im) + (this->im * c.re);
    }

    void div(Complex c) {
        double divisor = std::pow(c.re, 2) + std::pow(c.im, 2);
        if (divisor == 0) {
            std::cout << "Can't divide by zero! Operation canceled." << std::endl;
            return;
        }
        this->re = ((this->re * c.re) + (this->im * c.im)) / divisor;
        this->im = ((this->im * c.re) - (this->re * c.im)) / divisor;

    }

};


int main() {
    Complex complex = Complex();
    complex.add(Complex(1, 2));
    complex.sub(Complex(5, 5));
    complex.mul(Complex(20, -20));
    complex.div(Complex(0,0));
    complex.print();
    return 0;
}
