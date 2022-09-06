#include <iostream>
#include <utility>

class Person {
protected:
    std::string name;
    std::string lname;
    std::string dob;

public:

    Person(std::string name, std::string lastName, std::string dateOfBirth) :
    name(std::move(name)),
    lname(std::move(lastName)),
    dob(std::move(dateOfBirth))
    {}

    virtual void print() {
        std::cout << "Person{" << name << ", " << lname << ", " << dob << "}" << std::endl;
    }
};

class Student : public Person {
protected:
    unsigned int year;
    int group;
    std::string index;

public:
    void print() override {
        std::cout << "Student{name=" << name << ", lname=" << lname << ", dob=" << dob
                  << ", year=" << year << ", group=" << group << ", index=" << index << "}" << std::endl;

    }

    Student(const std::string &name, const std::string &lastName, const std::string &dateOfBirth,
            const int year, int group, std::string index) : Person(name, lastName, dateOfBirth),
                                                                                 year(year),
                                                                                 group(group),
                                                                                 index(std::move(index))
                                                                                 {}
};

class Player : public Person {
protected:
    std::string position;
    std::string club;
    int score = 0;

public:
    Player(const std::string &name, const std::string &lname, const std::string &dob,
           std::string position, std::string club, int score) : Person(name, lname,dob),
                                                                                    position(std::move(position)),
                                                                                    club(std::move(club)),
                                                                                    score(score)
                                                                                    {}


    void print() override {
        std::cout << "Student{name=" << name << ", lname=" << lname << ", dob=" << dob
                  << ", position=" << position << ", club=" << club << ", score=" << score << "}" << std::endl;

    }

    void goal() {
        score++;
    }
};


int main() {

    auto p0 = Person("Jacek", "Kowalski", "10-10-1993");
    p0.print();

    auto p1 = Student("Bozydar", "Michalski", "10-10-1993", 12, 16, "234");
    p1.print();

    auto p2 = Player("Piotrek", "Palikot", "10-10-1993", "kopacz", "RTS", 0);
    p2.print();
    p2.goal();
    p2.print();


    return 0;
}