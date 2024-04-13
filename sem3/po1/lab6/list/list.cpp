#include <iostream>
#include <cstring>

template<typename T>
class List {
private:
    size_t cap = 1;
    size_t size = 0;
    T *data = new T[cap];

    void swap(int*, int*);
public:
    List() = default;

    void sort();

    [[nodiscard]] T min() const;

    [[nodiscard]] T max() const;

    [[nodiscard]] size_t index(T e) const;

    void push(T value);

    void display() const;

    virtual ~List();

};

template<typename T>
List<T>::~List() {
    delete[] data;
}

template<typename T>
void List<T>::push(T value) {
    if (size == cap) {
        T *tmp = new T[cap * 2];
        memcpy(tmp, data, size * sizeof(*data));
        cap = cap * 2;
        delete[] data;
        data = tmp;
    }
    data[size++] = value;
}

template<typename T>
void List<T>::sort() {
    int i, j;
    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
            if (data[j] > data[j + 1])
                swap(&data[j], &data[j + 1]);
}

template<typename T>
void List<T>::swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

template<typename T>
T List<T>::min() const {
    T tmp_min = data[0];
    for (int i = 0; i < size; ++i) {
        if (data[i] < tmp_min) tmp_min = data[i];
    }
    return tmp_min;
}

template<typename T>
T List<T>::max() const {
    T tmp_max = data[0];
    for (int i = 0; i < size; ++i) {
        if (data[i] > tmp_max) tmp_max = data[i];
    }
    return tmp_max;
}

template<typename T>
size_t List<T>::index(T e) const {
    int x = -1;
    for (int i = 0; i < size; ++i)
        if (data[i] == e) x = i;

    return x;
}

template<typename T>
void List<T>::display() const {
    for (int i = 0; i < size; ++i) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    auto test = List<int>();
    test.push(1);
    test.push(23);
    test.push(3111);
    test.push(8);
    test.push(2);
    std::cout << "tablica: ";
    test.display();
    std::cout << "min: " << test.min() << "\n";
    std::cout << "maks: " << test.max() << "\n";

    size_t res;
    int x = 20;
    std::cout << "indeks elementu \"" << x << "\": ";
    if ((res = test.index(x)) == -1) {
        std::cout << "brak szukanego elementu" << std::endl;
    } else {
        std::cout << res << std::endl;
    }
    x = 8;
    std::cout << "indeks elementu \"" << x << "\": ";
    if ((res = test.index(x)) == -1) {
        std::cout << "brak szukanego elementu" << std::endl;
    } else {
        std::cout << res << std::endl;
    }

    test.sort();
    std::cout << "sortowanie...\n";
    test.display();
    return 0;
}