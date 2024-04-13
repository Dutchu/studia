#include <iostream>

class Resistor {
private:
    double resistance;
public:
    Resistor() {
        Resistor::resistance = 0.0;
    }

public:
    [[maybe_unused]] explicit Resistor(double resistance) : resistance(resistance) {}

    [[nodiscard]] double getResistance() const {
        return resistance;
    }

    void setResistance(double resistance) {
        Resistor::resistance = resistance;
    }

    friend Resistor operator + (const Resistor &r1,const Resistor &r2);

    friend Resistor operator * (const Resistor &res1, const Resistor &res2);

    friend std::ostream &operator << (std::ostream &output, const Resistor &Res);
};

Resistor operator + (const Resistor &r1, const Resistor &r2) {
    return Resistor(r1.resistance + r2.resistance);
}

Resistor operator * (const Resistor &r1, const Resistor &r2) {
    double divisor = r1.resistance + r2.resistance;

    if (divisor == 0) std::cerr << "Zero Division!" << std::endl;
    return Resistor((r1.resistance * r2.resistance) / divisor);
}

std::ostream &operator << (std::ostream &output, const Resistor &r) {
    output << "resistance = " << r.resistance;
    return output;
}

int main() {
    auto res1 = Resistor(2);
    auto res2 = Resistor(5);

    std::cout << res1 << "\n";
    std::cout << res2 << "\n";

    std::cout << res1 + res2 << "\n";
    std::cout << res1 * res2 << "\n";


    return 0;
}