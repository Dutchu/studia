#include <iostream>
#include <cmath>

template<typename T> class Sequence {
public:
    Sequence<T>()= default;

    T get(T n) {
        if (n <= 1) return n;
        return get(n - 1) + get(n - 2);
    }

    bool contains(T e) {
        return square(5 * e * e + 4) || square(5 * e * e - 4);
    }

    bool square(T n) {
        T sqr = sqrt(n);
        return (sqr * sqr == n);
    }
};

int main() {
    auto fib1 = Sequence<int>();
    auto fib2 = Sequence<long>();
    auto fib3 = Sequence<float>();

    std::cout << fib1.get(7) << std::endl;
    std::cout << fib2.get(7) << std::endl;
    std::cout << fib3.get(7.) << std::endl;

    std::cout << fib1.contains(7) << std::endl;
    std::cout << fib2.contains(13) << std::endl;
    std::cout << fib3.contains(20.0) << std::endl;
    return 0;
}