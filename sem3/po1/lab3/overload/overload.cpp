#include <iostream>

class Animal {
private:
    int age;
    std::string name;
    float income;

public:
    Animal() {
        std::cout << "Wywolano konstruktor domyslny" << std::endl;
        setAge(0);
        setName("");

    }
    Animal(int age) {
        std::cout << "Wywolano konstruktor z parametrem: age" << std::endl;
        setAge(age);
        setName("");
        std::cout << "pierwszy parametr konstruktora typu int ma wartosc: " << getAge() << std::endl;
    }
    Animal(int age, std::string name) {
        std::cout << "Wywolano konstruktor z parametrami: age, name" << std::endl;
        setAge(age);
        setName(name);
        std::cout << "pierwszy parametr konstruktora typu int ma wartosc: " << getAge() << ", drugi typu string: \"" << getName() << "\"" << std::endl;
    }
    Animal(int age, std::string name, float income) {
        std::cout << "Wywolano konstruktor z parametrami: age, name, income" << std::endl;
        setAge(age);
        setName(name);
        setIncome(income);
        std::cout << "pierwszy parametr konstruktora typu int ma wartosc: "<< getAge()
        << ", drugi typu string: \"" << getName() << "\""
        << ", trzeci typu float: " << getIncome()
        << std::endl;
    }
    Animal(const Animal &a) {
        std::cout << "Konstruktor kopiujacy" << std::endl;
        Animal::age = a.age;
        Animal::name = a.name;
        Animal::income = a.income;
    }



    void setAge(int age) {
        Animal::age = age;
    }

    void setName(const std::string &name) {
        Animal::name = name;
    }

    void setIncome(float income) {
        Animal::income = income;
    }

    [[nodiscard]] int getAge() const {
        return age;
    }

    [[nodiscard]] const std::string &getName() const {
        return name;
    }

    [[nodiscard]] const float &getIncome() const {
        return income;
    }

};
int main()
{
    Animal animal1 = Animal();
    Animal animal2 = Animal(1);
    Animal animal3 = Animal(2, "xd");
    Animal animal4 = Animal(2, "xd", 15.5);
    Animal animal5 = Animal(animal4);

}