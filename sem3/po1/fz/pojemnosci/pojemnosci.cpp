#include <iostream>
#include <cmath>

class Cappacitor {
private:
    double pojemnosc;
public:
    Kondensator() : pojemnosc(0) {

    }

    explicit Kondensator(double pojemnosc) : pojemnosc(pojemnosc) {

    }

    double capacity() {
        return this->pojemnosc;
    }

    void capacity(double cap) {
        this->pojemnosc = cap;
    }

    friend Kondensator operator+(const Kondensator &res1, const Kondensator &res2) {
        return Kondensator(pow((1 / res1.pojemnosc) + (1 / res2.pojemnosc), -1));
    }

    friend Kondensator operator*(const Kondensator &res1, const Kondensator &res2) {
        return Kondensator(res1.pojemnosc + res2.pojemnosc);
    }

    friend std::ostream &operator<<(std::ostream &output, const Kondensator &Res) {
        output << "C: " << Res.pojemnosc;
        return output;
    }

};


int main() {
    Kondensator res1 = Kondensator(5);
    Kondensator res2 = Kondensator(15);

    std::cout << res1 << "\n";
    std::cout << res2 << "\n";

    std::cout << res1 + res2 << "\n";
    std::cout << res1 * res2;

    return 0;
}
