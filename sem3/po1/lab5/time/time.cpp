#include <iostream>
#include <fstream>
#include <chrono>

#define FILENAME "../test-time.txt"

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

    auto start = std::chrono::high_resolution_clock::now();
    tt.read(FILENAME);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
    std::cout << duration.count() << '\n';


    start = std::chrono::high_resolution_clock::now();
    tt._read(FILENAME);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
    std::cout << duration.count() << '\n';


    return 0;
}
