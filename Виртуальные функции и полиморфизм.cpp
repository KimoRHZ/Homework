#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

//Енумы для задания 4 вынес в глобал что бы использовать ихв мейне.. Или есть еще какой то решения для этого?
enum Suit {
    clubs,
    hearts,
    diamonds,
    spades,
};
enum Card_values {
    ace = 1,
    king = 10,
    queen = 10,
    jack = 10,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10,
};

//================================Задание-1=========================================
class Figure {
protected:
    double S; //Общего у всех фигур только площадь из свойств, так что только ее и оставил
    virtual double area() = 0;
};

//Далее переменные будут называться так как обычно записываются в геометрии. Сетеры я добавлять не стал, так как не планирую тут менять параметры объектов после создания
//по той же причине не задал значения по умолчанию, что бы фигуры без заданных значений не создавались
class Circle : public Figure {
private:
    double l; //Все свойства и методы присущие только кругу, определены в приват области
    double r;
    double d;
    double lengthCircle() {
        l = 2 * M_PI * r;
        return l;
    }
    double area() override {
        S = M_PI * pow(r, 2);
        return S;
    }
public:
    Circle(double r) : r(r) { //Решил выбрать радиус для инициализации круга
        l = lengthCircle();
        d = r * 2;
        S = area();
    }
    void getLength() const {
        std::cout << "Length of circle: " << l << std::endl;
    }
    void getRadius() const {
        std::cout << "Radius: " << r << std::endl;
    }
    void getDiameter() const {
        std::cout << "Diameter: " << d << std::endl;
    }
    void getArea() const {
        std::cout << "Area: " << S << std::endl;
    }
};

class Parallelogram : public Figure {
private:
    double h; //Все свойства и методы присущие только паралеллограму определены в приват области
    double height() { //Высота есть и у прямоугольника, но у него она равна стороне а, так что оставил ее только паралеллограму
        h = ab * sin(A * M_PI / 180);
        return h;
    }
    double area() override {
        S = bc * height();
        return S;
    }
protected:
//Переменные используемые остальными дочерними классами
    double ab; //Стороны
    double bc;
    double cd;
    double ad;
    double d1; //Длинная диагональ
    double d2; //Короткая диагональ
    double A; //Углы
    double B;
    double C;
    double D;
    double P; //Периметр (просто докучи)
    double perimeter() { //Периметр у всех считается одинаково
        P = ab * 2 + bc * 2;
        return P;
    }
    virtual double diag1() { //Для ромба, но там я их переопределяю
        d1 = sqrt(pow(ab, 2) + pow(bc, 2) + 2 * ab * bc * cos(A * M_PI / 180));
        return d1;
    }
    virtual double diag2() {
        d2 = sqrt(pow(ab, 2) + pow(bc, 2) - 2 * ab * bc * cos(A * M_PI / 180));
        return d2;
    }
  /*double angles() { //Эта функция закомменчена, так как это только один из вариантов для определения углов через высоту ниже видно зачем
        A = h / bc;
        return A;
    }*/
public:
    Parallelogram(double bc, double ab, double A) : bc(bc), ab(ab), A(A) { //Для инициализации выбрал острый угол
        cd = ab;
        ad = bc;
        B = 180 - A;
        C = A;
        D = B;
        h = height();
        d1 = diag1();
        d2 = diag2();
        P = perimeter();
        S = area();
    }
  /*Parallelogram(double bc = 10, double ab = 8, double A = 60) : bc(bc), ab(ab), h(h) { //Оставил возможность для инициализации через высоту, а не угол
        cd = ab;
        ad = bc;
        A = angles();
        B = 180 - A;
        C = A;
        D = B;
        d1 = diag1();
        d2 = diag2();
        P = perimeter();
        S = area();
    }*/
    void getSide() const { //Функции для печати
        std::cout << "a side: " << ab << std::endl;
        std::cout << "b side: " << bc << std::endl;
        std::cout << "c side: " << cd << std::endl;
        std::cout << "d side: " << ad << std::endl;
    }
    void getAngle() const {
        std::cout << "A angle: " << A << std::endl;
        std::cout << "B angle: " << B << std::endl;
        std::cout << "C angle: " << C << std::endl;
        std::cout << "D angle: " << D << std::endl;
    }
    void getHeight() const {
        std::cout << "Height: " << h << std::endl;
    }
    void getPerimeter() const {
        std::cout << "Perimeter: " << P << std::endl;
    }
    void getArea() const {
        std::cout << "Area: " << S << std::endl;
    }
    void getDiag() const {
        std::cout << "Long diagonal: " << d1 << std::endl;
        std::cout << "Short diagonal: " << d2 << std::endl;
    }
};

class Rectangle : public Parallelogram {
private:
    const double angle = 90; //Все углы у него всегда 90 градусов
    double d;
    double diag() {
        d1 = sqrt(pow(ab, 2) + pow(bc, 2));
        return d1;
    }
    double area() override {
        S = ab * bc;
        return S;
    }
public:
    Rectangle(double bc, double ab) : Parallelogram(bc, ab, 90) { //Костыль конечно, но я чет не смог подругому решить этот момент =(
        cd = ab;
        ad = bc;
        d1 = diag();
        d2 = d1;
        P = perimeter();
        S = area();
    }
    void getSide() const {
        std::cout << "a side: " << ab << std::endl;
        std::cout << "b side: " << bc << std::endl;
        std::cout << "c side: " << cd << std::endl;
        std::cout << "d side: " << ad << std::endl;
    }
    void getAngle() const {
        std::cout << "A angle: " << A << std::endl;
        std::cout << "B angle: " << B << std::endl;
        std::cout << "C angle: " << C << std::endl;
        std::cout << "D angle: " << D << std::endl;
    }
    void getPerimeter() const {
        std::cout << "Perimeter: " << P << std::endl;
    }
    void getArea() const {
        std::cout << "Area: " << S << std::endl;
    }
    void getDiag() const {
        std::cout << "Long diagonal: " << d1 << std::endl;
        std::cout << "Short diagonal: " << d2 << std::endl;
    }
};

class Rhombus : public Parallelogram {
private:
    double diag1() override {
        d1 = ab * sqrt(2 + 2 * cos(A * M_PI / 180));
        return d1;
    }
    double diag2() override {
        d2 = ab * sqrt(2 - 2 * cos(A * M_PI / 180));
        return d2;
    }
    double area() override {
        S = pow(ab, 2) * sin(ab * M_PI / 180);
        return S;
    }
public:
    Rhombus(double ab, double A) : Parallelogram(ab, ab, A) { //Снова тот же костыль
        bc = ab;
        cd = bc;
        ad = ab;
        d1 = diag1();
        d2 = diag2();
        B = 180 - A;
        C = A;
        D = B;
        P = perimeter();
        S = area();
    }
    void getSide() const {
        std::cout << "a side: " << ab << std::endl;
        std::cout << "b side: " << bc << std::endl;
        std::cout << "c side: " << cd << std::endl;
        std::cout << "d side: " << ad << std::endl;
    }
    void getAngle() const {
        std::cout << "A angle: " << A << std::endl;
        std::cout << "B angle: " << B << std::endl;
        std::cout << "C angle: " << C << std::endl;
        std::cout << "D angle: " << D << std::endl;
    }
    void getPerimeter() const {
        std::cout << "Perimeter: " << P << std::endl;
    }
    void getArea() const {
        std::cout << "Area: " << S << std::endl;
    }
    void getDiag() const {
        std::cout << "Long diagonal: " << d1 << std::endl;
        std::cout << "Short diagonal: " << d2 << std::endl;
    }
};

//================================Задание-2=========================================

class Car {
protected:
    std::string company;
    std::string model;
public:
    Car(std::string company = "Car", std::string model = "Model") : company(company), model(model) {
        std::cout << "Mark: " << company << std::endl;
        std::cout << "Model: " << model << std::endl;
    }
};

class PassengerCar : virtual public Car{
public:
    PassengerCar(std::string company = "Passenger Car", std::string model = "Model") : Car(company, model) {
        std::cout << "Passenger Car Mark: " << company << std::endl;
        std::cout << "Passenger Car Model: " << model << std::endl;
    }
};

class Bus : virtual public Car {
public:
    Bus(std::string company = "Bus", std::string model = "Model") : Car(company, model) {
        std::cout << "Bus Mark: " << company << std::endl;
        std::cout << "Bus Model: " << model << std::endl;
    }
};

class Minivan : public PassengerCar, public Bus {
public:
    Minivan(std::string company = "Minivan", std::string model = "Model") : PassengerCar(company, model), Bus(company, model) { //Добавил оба из любоптыства, к тому же судя по выводу, второй родительский класс тоже строился, но со знач. по умолчанию
        std::cout << "Minivan Mark: " << company << std::endl;
        std::cout << "Minivan Model: " << model << std::endl;
    }
};

//================================Задание-3=========================================
class Fraction {
private:
    friend Fraction operator+ (const Fraction& a, const Fraction& b);
    friend Fraction operator- (const Fraction& a, const Fraction& b);
    friend Fraction operator* (const Fraction& a, const Fraction& b);
    friend Fraction operator/ (const Fraction& a, const Fraction& b);
    friend bool operator== (const Fraction& a, const Fraction& b);
    friend bool operator!= (const Fraction& a, const Fraction& b);
    friend bool operator> (const Fraction& a, const Fraction& b);
    friend bool operator< (const Fraction& a, const Fraction& b);
    friend bool operator>= (const Fraction& a, const Fraction& b);
    friend bool operator<= (const Fraction& a, const Fraction& b);
    int integer = 0;
    int numerator;
    int denominator;
    double decfrac;
public:
    Fraction(int numerator = 1, int denominator = 2) : numerator(numerator), denominator(denominator) {
        decfrac = decFraction(); //Эта функция помимио приведения к десятичной, сразу и приводит дробь к правильной
    }
    void printFraction() {
        if (integer == 0) {
            std::cout << numerator << '/' << denominator << std::endl;
        }
        else if (numerator == 0) {
            std::cout << integer << std::endl;
        }
        else {
            std::cout << integer << ' ' << numerator << '/' << denominator << std::endl;
        }
    }
    void printDecFrac() {
        std::cout << decfrac << std::endl;
    }
    void setNumerator(int num) {
        numerator = num;
    }
    void setDenominator(int denom) {
        denominator = denom;
    }
    void correctingFrac() { //Приведение неправильной дроби к правильной
        integer = numerator / denominator;
        numerator = numerator % denominator;
    }
    double decFraction() { //Просто решил добавить приведение к десятичной дроби
        correctingFrac();
        decfrac = 1 / denominator * numerator + integer;
        return decfrac;
    }
    void operator- () {
        numerator = -numerator;
    }
};

int commonMultiple(int x, int y) { //Функция для поиска наименьшего общего кратного
    int min = (x < y) ? x : y;
    int max = (x > y) ? x : y;
    for (int i = 2; i <= min; i++) {
        if (x % i == 0 && y % i == 0) {
            if (i < max) {
                return max;
            }
            else {
                return i;
            }
        }
        else if (i == min) {
            return 1;
        }
    }
}

int nod(int x, int y) { //Функция для поиска наименьшего общего делителя
    int count = (x < y) ? x : y;
    for (int i = 2; i <= count; i++) {
        if (x % i == 0 && y % i == 0) {
            return i;
        }
        else if (i == count) {
            return 1;
        }
    }
}

Fraction operator+ (const Fraction& a, const Fraction& b) {
    if (a.denominator == b.denominator) { //Если знаменатели равны
        return Fraction(a.numerator + b.numerator, a.denominator);
    }
    else { //Если не равны
        int common_multiple = commonMultiple(a.denominator, b.denominator); //Проверяю имеют ли НОК            
        if (common_multiple > 1) { //Если имеют, то привожу доробь к общему знаменателю на его основании
            return Fraction(a.numerator * (common_multiple / a.denominator) + b.numerator * (common_multiple / b.denominator), common_multiple);
        }
        else { //Если не имеют (например оба числа простые), то просто умножаю, это и будет наименьше общее кратное
            return Fraction((a.numerator * b.denominator) + (b.numerator * a.denominator), a.denominator * b.denominator);
        }
    }
}

Fraction operator- (const Fraction& a, const Fraction& b) {
    if (a.denominator == b.denominator) { //Если знаменатели равны
        return Fraction(a.numerator - b.numerator, a.denominator);
    }
    else { //Если не равны
        int common_multiple = commonMultiple(a.denominator, b.denominator); //Проверяю имеют ли НОК
        if (common_multiple > 1) { //Если имеют, то привожу доробь к общему знаменателю на его основании
            return Fraction(a.numerator * (common_multiple / a.denominator) - b.numerator * (common_multiple / b.denominator), common_multiple);
        }
        else { //Если не имеют (например оба числа простые), то просто умножаю это и будет наименьшее общее кратное
            return Fraction((a.numerator * b.denominator) - (b.numerator * a.denominator), a.denominator * b.denominator);
        }
    }
}

Fraction operator* (const Fraction& a, const Fraction& b) {
    int num = nod(a.numerator * b.numerator, a.denominator * b.denominator); //Сокращаю дробь через наименьший общий делитель, если он есть
    return Fraction((a.numerator * b.numerator) / num, (a.denominator * b.denominator) / num);
}

Fraction operator/ (const Fraction& a, const Fraction& b) {
    int num = nod(a.numerator * b.denominator, a.denominator * b.numerator); //Сокращаю дробь через наименьший общий делитель, если он есть
    return Fraction((a.numerator * b.denominator) / num, (a.denominator * b.numerator) / num);
}

bool operator== (const Fraction& a, const Fraction& b) {
    int common_multiple = commonMultiple(a.denominator, b.denominator); //Привожу к единому знаменателю
    if (common_multiple != 1 && a.numerator * (common_multiple / a.denominator) == b.numerator * (common_multiple / b.denominator)) {
        return 1;
    }
    else {
        return 0;
    }           
}

bool operator!= (const Fraction& a, const Fraction& b) {
    if (a == b) {
        return 0;
    }
    else {
        return 1;
    }
}

bool operator> (const Fraction& a, const Fraction& b) {
    int common_multiple = commonMultiple(a.denominator, b.denominator); //Привожу к единому знаменателю
    if (common_multiple != 1 && a.numerator * (common_multiple / a.denominator) > b.numerator * (common_multiple / b.denominator)) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator< (const Fraction& a, const Fraction& b) {
    if (a > b) {
        return 0;
    }
    else {
        return 1;
    }
}

bool operator>= (const Fraction& a, const Fraction& b) {
    if (a > b || a == b) {
        return 1;
    }
    else {
        return 0;
    }
}

bool operator<= (const Fraction& a, const Fraction& b) {
    if (a < b || a == b) {
        return 1;
    }
    else {
        return 0;
    }
}

//================================Задание-4=========================================
class Card {
protected:
    Suit suit;
    Card_values value;
    bool position;
public:
    Card(Suit suit = clubs, Card_values value = ace, bool position = 0) : suit(suit), value(value), position(position) {

    }
    void flip() {
        position = !position;
    }
    int getValue() {
        return value;
    }
};

int main()
{
//================================Задание-1=========================================
    Parallelogram par(15, 11, 40); //Решил не заграмождать этот код cin'ами, добавил один простой для примера, так что небольшие magic numbers в качестве параметров фигур =)
    std::cout << "Parallelogram" << std::endl;
    par.getSide();
    par.getAngle();
    par.getDiag();
    par.getHeight();
    par.getArea();
    par.getPerimeter();
    std::cout << std::endl;
    bool check = false;
    double radius;
    do {
        std::cout << "Plese enter radius of circle: " << std::endl;
        std::cin >> radius;
        std::cout << std::endl;
        if (radius > 0) {
            check = true;
        }
    } while (!check);    
    Circle cir(radius);
    std::cout << "Circle" << std::endl;
    cir.getLength();
    cir.getRadius();
    cir.getDiameter();
    cir.getArea();
    std::cout << std::endl;
    Rectangle rec(18, 12);
    std::cout << "Rectangle" << std::endl;
    rec.getSide();
    rec.getAngle();
    rec.getDiag();
    rec.getArea();
    rec.getPerimeter();
    std::cout << std::endl;
    Rhombus romb(50, 72);
    std::cout << "Rhombus" << std::endl;
    romb.getSide();
    romb.getAngle();
    romb.getDiag();
    romb.getArea();
    romb.getPerimeter();
    std::cout << std::endl;
//================================Задание-2=========================================
    Car unnamedcar("Just car", "Just car");
    PassengerCar honda("Honda", "Civic");
    Bus paz("PAZ", "PAZ_3205");
    Minivan wolkswagen("Wolkswagen", "Multivan");
//================================Задание-3=========================================
    Fraction frac5(2, 7); //Проверял разные дроби
    Fraction frac6(3, 11);
    Fraction fracsum3 = frac5 + frac6;
    fracsum3.printFraction();
    Fraction frac1(2, 6);
    Fraction frac2(3, 9);
    Fraction fracsum1 = frac1 + frac2;
    fracsum1.printFraction();
    Fraction frac3(28, 53);
    Fraction frac4(15, 49);
    Fraction fracsum2 = frac3 - frac4;
    fracsum2.printFraction();
    Fraction frac7(2, 10);
    Fraction frac8(1, 5);
    Fraction fracsum4 = frac7 * frac8;
    fracsum4.printFraction();
    Fraction frac9(4, 7);
    Fraction frac10(2, 5);
    Fraction fracsum5 = frac9 / frac10;
    fracsum5.printFraction();
    Fraction frac11(7, 8);
    -frac11;
    frac11.printFraction();
    frac7 == frac8;
    frac3 == frac9;
    if (frac5 < frac6) {
        std::cout << "5 Larger 6" << std::endl;
    }
    if (frac1 <= frac2) {
        std::cout << "true" << std::endl;
    }
//================================Задание-4=========================================
    Card card(clubs, ace, 0);
    std::cout << card.getValue() << std::endl;

    return 0;
}
