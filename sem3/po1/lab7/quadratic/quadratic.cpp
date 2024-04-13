#include <iostream>
#include <cmath>
#include <utility>


class QuadraticBinomialException : public std::exception {
private:
    std::string message;

public:
    explicit QuadraticBinomialException(std::string msg) : message(std::move(msg)) {}
    std::string what () {
        return message;
    }
};


int main() {

    double a, b, c, x1, x2, delta, re, im;
    std::cout << "Podaj wspolczynniki a, b, c:";
    std::cin >> a >> b >> c;
    delta = b * b - 4 * a * c;

    std::cout << "a:" << a << "\nb:" << b << "\nc:" << c << std::endl;

    if (a == 0 && b == 0 && c == 0) {
        try {
            throw QuadraticBinomialException("Wszystkie wspolczynniki sa zerami!");
        } catch (QuadraticBinomialException& e) {
            std::cerr << e.what();
        }
        return 0;
    }


    if (a == 0 && b == 0) {
        try {
            throw QuadraticBinomialException("Bledne wspolczynniki!");
        } catch (QuadraticBinomialException& e) {
            std::cerr << e.what();
        }
        std::cout << "Rownanie nie jest kwadratowe i jest liczba stala." << std::endl;
        std::cout << "c = " << c;
        return 0;
    }

    if (a == 0 && b != 0) {
        try {
            throw QuadraticBinomialException("Bledne wspolczynniki!");
        } catch (QuadraticBinomialException& e) {
            std::cerr << e.what();
        }
        x1 = -c / b;
        std::cout << "Rownanie nie jest kwadratowe i ma jedno rozwiazanie." << std::endl;
        std::cout << "x1 = " << x1;
        return 0;
    }


    if (delta > 0) {
        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);
        std::cout << "Pierwiastki sa liczbami rzeczywistymi." << std::endl;
        std::cout << "x1 = " << x1 << std::endl;
        std::cout << "x2 = " << x2 << std::endl;
    }

    else if (delta == 0) {

        std::cout << "Pierwiastki sa rzeczywiste i takie same." << std::endl;
        x1 = -b/(2*a);
        std::cout << "x1 = x2 =" << x1 << std::endl;
    }

    else {
        try {
            throw QuadraticBinomialException("Podane wspolczynniki tworza delte mniejsza od zera!");
        } catch (QuadraticBinomialException &e) {
            std::cerr << e.what() << std::endl;
        }
        re = -b / (2 * a);
        im = sqrt(-delta) / (2 * a);
        std::cout << "Pierwiastki sa liczbami zespolonymi."  << std::endl;
        std::cout << "x1 = " << re << "+" << im << "i" << std::endl;
        std::cout << "x2 = " << re << "-" << im << "i" << std::endl;
    }

    return 0;
}