#include <string>
#include <iostream>


class InputNotNumber : public std::exception {
public:
    char * what () {
        return "Your input is not a number!";
    }
};

class InputNumberToBig : public std::exception {
public:
    char * what () {
        return "Your input is to big to convert to int!";
    }
};

int convert(std::string str) {
    int x;
    std::string::size_type sz;
    try {
        x = std::stoi(str, &sz);
    } catch (std::invalid_argument& e ) {
        throw InputNotNumber();

    } catch (std::out_of_range& e ) {
        throw InputNumberToBig();
    }
    ;
    return x;
}

int main() {
    std::string txt;
    std::cout << "Wprowadz liczbe:" << std::endl;
    std::cin >> txt;
    try {
        std::cout << convert(txt);
    } catch (InputNotNumber& e) {
        std::cerr << e.what();
    } catch (InputNumberToBig& e) {
        std::cerr << e.what();
    }

    return 0;
}
