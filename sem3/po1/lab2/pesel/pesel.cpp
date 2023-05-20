#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define DELIMITER ","
#define FILENAME "../data.txt"
class Person {
private:
    std::string code;
    std::string name;
    std::string surname;
    std::string address;

public:
    Person(std::string code, std::string name, std::string surname, std::string address) {
        this->code = code;
        this->name = name;
        this->surname = surname;
        this->address = address;
    }

    static void load(std::string filename, std::vector<Person*>* destination) {

        std::fstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        size_t pos = 0;
        std::string line;
        std::string token;
        std::vector<std::string> tokens;
        std::string delimiter = DELIMITER;
        int data_index;
        int corrupted;

        try {
            file.open(filename, std::ios::in);
        } catch (std::ifstream::failure &e) {
          std::cerr <<  "Opening file failed!" << std::endl;
          std::cerr << e.what();
        }

        try {
            while (std::getline(file, line)){

                data_index = 0;
                corrupted = 0;
                while ( (pos = line.find(delimiter)) != std::string::npos ) {


                    token = line.substr(0, pos);
                    tokens.push_back(token);
                    line.erase(0, pos + delimiter.length());


                    if (data_index > 3) {
                        std::cerr << "Line Corrupted!" << std::endl;
                        corrupted = 1;
                        break;
                    }

                    data_index++;
                }

                if ( !corrupted && validate(&tokens[0]) ) {
                    destination->push_back( new Person(tokens[0], tokens[1], tokens[2], tokens[3]) );
                }

                tokens.clear();

            }
        } catch (std::ifstream::failure &e) {
//            std::cerr <<  "Reading file failed!" << std::endl;
//            std::cerr << e.what() << std::endl;
        }

        try {
            file.close();
        } catch (std::ifstream::failure &e) {
            std::cerr <<  "Closing file failed!" << std::endl;
            std::cerr << e.what();
        }
    }

    static bool validate(const std::string *pesel) {
        if (pesel->length() != 11) return false;
        return pesel->find_first_not_of("0123456789") == std::string::npos;
    }

    void print() {
        std::cout << "Person{" << this->code << ", " << this->name << ", " << this->surname << ", " << this->address << "}" << std::endl;
    }
};

int main()
{
    std::vector<Person*> persons;
    Person::load(FILENAME, &persons);


    for (auto & person : persons)
        person -> print();

    return 0;
}