#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

enum Suit {
    clubs,
    hearts,
    diamond,
    spades,
};

enum Card_values {
    ace = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10,
    jack = 10,
    queen = 10,
    king = 10,
    blackjack = 21, //Добавил константу целевого значения
    bonusAce = 10, // Константа для увеличения очков за туз при недоборе
};


//=================================Задание-1=========================================
class Vector {
private:
    size_t SIZE;
    int* array;
    int data;
    int count = 0;
public:
    Vector() : SIZE(0), array(nullptr) { //Конструктор по умолчанию

    }
    Vector(size_t SIZE) : SIZE(SIZE) {//Для создания массива только с размером. Нулевой решил не создавать в этом случае
        assert(SIZE > 0);
        array = new int[SIZE];
    }
    Vector(const std::initializer_list<int>& list) : Vector(list.size()) { //Для инициализации через initializer_list
        count = 0;
        for (const int& element : list) {
            array[count++] = element;
        }
    }
    void clear() {
        delete[] array;
        array = nullptr;
        SIZE = 0;
    }
    void pushBack(int data) {
        if (count < SIZE) {
            array[count++] = data;
        }
        else {
            int* tmpArr = new int[++SIZE];
            for (size_t i = 0; i < SIZE - 1; ++i) {
                tmpArr[i] = array[i];
            }
            tmpArr[count++] = data;
            delete[] array;
            array = tmpArr;
        }
    }
    void popBack() { //Не уверен правильно ли поступаю копируя элементы, но решил освобождать память
        if (count > 0) {
            int* tmpArr = new int[--SIZE];
            for (size_t i = 0; i < SIZE; ++i) {
                tmpArr[i] = array[i];
            }
            delete[] array;
            array = tmpArr;
            count--;
        }
        else {
            std::cout << "Array is empty" << std::endl;
        }
    }
    void popFront() {
        if (count > 0) {
            int* tmpArr = new int[--SIZE];
            for (size_t i = 1; i < SIZE; ++i) {
                tmpArr[i - 1] = array[i];
            }
            delete[] array;
            array = tmpArr;
            count--;
        }
        else {
            std::cout << "Array is empty" << std::endl;
        }
    }
    void sortArr() { //Пузырьком быстрее... Написать. Зато стабильность.. в ассимптотике.))
        int tmp;
        for (rsize_t i = 0; i < SIZE; ++i) {
            for (rsize_t j = 0; j < SIZE; ++j) {
                if (array[j] > array[j + 1] && j < SIZE - 1) {
                    tmp = array[j + 1];
                    array[j + 1] = array[j];
                    array[j] = tmp;
                }
            }
        }
    }
    void resize(int newSize) {
        if (newSize == SIZE) {
            return;
        }
        if (newSize <= 0) {
            clear();
            return;
        }
        int* tmpArr = new int[newSize];
        if (SIZE > 0) {
            int elementsToCopy = (newSize > SIZE) ? SIZE : newSize;
            for (size_t i = 0; i < elementsToCopy; ++i) {
                tmpArr[i] = array[i];
            }
        }
        delete[] array;
        array = tmpArr;
        SIZE = newSize;
    }
    void printArr() {
        for (size_t i = 0; i < SIZE; ++i) {
            std::cout << '[' << array[i] << ']';
        }
        std::cout << std::endl;
    }
    int getSize() {
        return SIZE;
    }
    int operator[] (size_t index) {
        assert(index >= 0 && index < SIZE);
        return array[index];
    }
    ~Vector() {
        delete[] array;
    }
};

//=================================Задание-3=========================================
class Card {
private:
    Suit suit;
    Card_values value;
    bool position;
    void flip() {
        position = !position;
    }
public:
    Card(Suit suit, Card_values value) : suit(suit), value(value) {
        position = false;
    }
    Card_values getValue() {
        return value;
    }
    int operator+ (Card card) {
        return static_cast<int>(value) + static_cast<int>(card.getValue());
    }
    int operator+ (int num) {
        return static_cast<int>(value) + num;
    }
    int operator+ (Card_values num) {
        return static_cast<int>(value) + static_cast<int>(num);
    }
};

class Hand {
private:
    std::vector<Card*> array;
public:
    Hand() = default;
    void const addCard(Card* card) {
        array.push_back(card);
    }
    void clear() {
        array.clear();
    }
    int getValue() {
        int sum = 0;
        size_t checkAce = 0; //Счетчик для учета тузов по 11 очков, на случай, 
        //если перебор будет уже после начисления 11 очков
        for (size_t i = 0; i < array.size(); ++i) {
            if (array[i]->getValue() == ace) {
                if (sum + (array[i]->getValue() + bonusAce) <= blackjack) {
                    sum = sum + (array[i]->getValue() + bonusAce);
                    checkAce++;
                }
                else {
                    sum = sum + array[i]->getValue();
                }
            }
            else {
                sum = sum + array[i]->getValue();
            }
        }
        while (sum > blackjack && checkAce > 0) { //Цикл отнимающий от тузов 10-ку при переборе, 
        //если было начислено 11 
            sum = sum - bonusAce;
            checkAce--;
        }
        return sum;
    }
};

int main() {
//=================================Задание-1=========================================
    Vector arr(2);
    arr.pushBack(5);
    arr.pushBack(4);
    arr.pushBack(2);
    arr.pushBack(8);
    arr.printArr();
    arr.clear();
    Vector arr2 = { 2,4,9,8,6,3,15,10 };
    arr2.sortArr();
    arr2.printArr();
    arr2.clear();
//=================================Задание-2=========================================
    std::vector<int> vec = { 59, 63, 9, 46, 87, 96, 75, 84, 30, 71, 28, 85, 90, 49, 34, 41, 47, 46, 26, 12, 44, 29, 49, 45, 25 };
    size_t count = 0; // Способ 1, с неотсортированным массивом, подумалось что на достаточно длинных рандомных массивах, с таким способом сложность будет меньше n2... Но я не уверен.
    std::vector<int> tmp;
    bool check = false;
    for (size_t i = 0; i < vec.size()-1; ++i) {
        if (i == 0) {
            tmp.push_back(vec[i]);
            count++;
            i++;
        }
        if (vec[i] != vec[i + 1]) {
            for (size_t j : tmp) {
                if (vec[i + 1] == j) {
                    check = true;
                }
            }
            if (!check) {
                tmp.push_back(vec[i+1]);
                count++;
            }
        }
        check = false;
    }
    std::cout << count << std::endl;
    count = 0;
    sort(vec.begin(), vec.end()); //Чит! Так же можно?)
    for (size_t i = 0; i < vec.size()-1; ++i) { //Линейная сложность... Если не считать сортировки. =)
        if (vec[i] != vec[i+1]) {
            count++;
        }
    }
    std::cout << count << std::endl;
//=================================Задание-3=========================================
    Card card1(clubs, five);
    Card card2(diamond, ace);
    Card card3(diamond, three);
    Card card4(hearts, ace);
    Card card5(hearts, queen);
    Card card6(spades, three);
    std::vector<Card*> array;
    array.push_back(&card1);
    array.push_back(&card2);
    array.push_back(&card3);
    std::cout << card1.getValue() << std::endl;
    std::cout << array[0]->getValue() << std::endl;
    std::cout << static_cast<int>(card2.getValue()) << std::endl;
    std::cout << card1 + card3 << std::endl;
    Hand ha;
    ha.addCard(&card1);
    ha.addCard(&card2);
    ha.addCard(&card2);
    ha.addCard(&card3);
    ha.addCard(&card4);
    ha.addCard(&card5);
    ha.addCard(&card6);
    std::cout << ha.getValue();

    return 0;
}