#include <iostream>
#include <cmath>
#include <utility>

class MojWyjatek : public std::exception {

    virtual const char *what() const throw() { return "Moj wyjatek"; }

};


int main() {

    MojWyjatek myex;

    double x,y,z, zz, xx;

    zz = z*z;
    xx = x*x;


    double y = sqrt (xx - zz) / sqrt(x - y);

    try {
        throw myex;
    }

    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;

}