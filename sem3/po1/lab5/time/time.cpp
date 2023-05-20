#include <iostream>
#include <fstream>
#include <chrono>

#define FILENAME "../test-time.txt"
class base {
public:
    virtual void print()
    {
        std::cout << "print base class\n";
    }

    void show()
    {
        std::cout << "show base class\n";
    }
};

class derived : public base {
public:
    void print()
    {
        std::cout << "print derived class\n";
    }

    void show()
    {
        std::cout << "show derived class\n";
    }
};
class TestTime {
public:
     void read(const std::string &f) {

        std::string data;
        std::ifstream file;
        file.open(f);
        file >> data;
        file.close();

    }

    virtual void _read(const std::string &filename) = 0;

};


class _TestTime : public TestTime {

public:
    void _read(const std::string &f) override {
        std::string data;
        std::ifstream file;
        file.open(f);
        file >> data;
        file.close();
    }

};

int main() {

    auto tt = _TestTime();
    int i;
    auto start = std::chrono::high_resolution_clock::now();
    for(i = 0; i < 1000; i++)
        tt.read(FILENAME);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << "Czas wykonania funkcji 1000 razy w milli sekundach: " << duration.count() << '\n';


    start = std::chrono::high_resolution_clock::now();
    for(i = 0; i < 1000; i++)
        tt._read(FILENAME);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
    std::cout << "Czas wykonania funkcji wirtualnej 1000 razy w milli sekundach: " << duration.count() << '\n';


    return 0;
}
