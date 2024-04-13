#include <iostream>
#include <cmath>

template<typename T> class Fib {

public:
    T get(T n) {
        if (n <= 1) return n;
        return get(n - 1) + get(n - 2);
    }

    bool find(T e) {
        return square(5 * e * e + 4) || square(5 * e * e - 4);
    }

    bool square(T n) {
        T sqr = sqrt(n);
        return (sqr * sqr == n);
    }
};

int main() {
    auto fib1 = Fib<int>();
    auto fib2 = Fib<long>();
    auto fib3 = Fib<float>();

    int x = 7;
    std::cout << "Get " << x << "th element from fibonacci sequence of type int" << std::endl;
    std::cout << "" << fib1.get(x) << std::endl;
    long y = 7;
    std::cout << "Get " << y << "th element from fibonacci sequence of type long" << std::endl;
    std::cout << fib2.get(y) << std::endl;
    float z = 7.0;
    std::cout << "Get " << z << "th element from fibonacci sequence of type float" << std::endl;
    std::cout << fib3.get(z) << std::endl;

    x = 9;
    std::cout << "Find if number: " << x << " is in fibonacci sequence of type int" << std::endl;
    std::cout << fib1.find(x) << std::endl;
    y = 13;
    std::cout << "Find if number: " << y << " is in fibonacci sequence of type long" << std::endl;
    std::cout << fib2.find(y) << std::endl;
    z = 21;
    std::cout << "Find if number: " << z << " is in fibonacci sequence of type float" << std::endl;
    std::cout << fib3.find(z) << std::endl;
    return 0;
}