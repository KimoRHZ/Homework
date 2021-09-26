#include <iostream>

//==============================Задание-1==================================
class Person 
{
protected:
    std::string name;
    std::string gender;
    float weight;
    int age;
public:
    Person(std::string name = "", std::string gender = "", float weight = 0, int age = 0)
        : name(name), gender(gender), weight(weight), age(age)
    {

    }
    void setName(std::string newName) { name = newName; }
    void setGender(std::string Gender) { gender = Gender; }
    void setWeight(float newWeught) { weight = newWeught; }
    void setAge(int newAge) { age = newAge; }
    std::string getName() const { return name; }
    std::string getGender() const { return gender; }
    float getWeight() const { return weight; }
    int getAge() const { return age; }

};

class Student : public Person 
{
private:
    int yearOfStudy;
public:
    Student(std::string name = "", std::string gender = "", float weight = 0, int age = 0, int yearOfStudy = 0)
    : Person(name, gender, weight, age), yearOfStudy(yearOfStudy) //Такой способ инициализации высмотрел продолжая погружаться в тему. Вроде работает
    {

    }
    void setYear(int newYear) {  yearOfStudy = newYear;  } //Задать год обучения
    void upYear() {  yearOfStudy++;  } //Увеличить год обучения
    int getYear() const { return yearOfStudy; }
};

void createStudent(Student* list,int &stCounter) { //Создаю студента
    std::string name; //Сначала запрашиваю все будущие члены класса с ввода
    std::string gender;
    float weight;
    int age;
    int yearOfStudy;
    std::cout << "Enter name:" << std::endl;
    std::cin >> name;
    std::cout << "Enter gender:" << std::endl;
    std::cin >> gender;
    std::cout << "Enter weight:" << std::endl;
    std::cin >> weight;
    std::cout << "Enter age:" << std::endl;
    std::cin >> age;
    std::cout << "Enter year of study:" << std::endl;
    std::cin >> yearOfStudy;
    Student student(name, gender, weight, age, yearOfStudy); //После инициализирую объект
    list[stCounter] = student; //Записываю в массив
    stCounter++; //Увеличиваю счетчик студентов
}

void PrintStudent(Student* list, int number) { //Функция для вывода информации о студенте
    std::cout << "Name: " << list[number].getName() << std::endl;
    std::cout << "Gender: " << list[number].getGender() << std::endl;
    std::cout << "Weight: " << list[number].getWeight() << std::endl;
    std::cout << "Age: " << list[number].getAge() << std::endl;
    std::cout << "Year of study: " << list[number].getYear() << std::endl;
}

void findStudent(Student* list, int &stCounter) { //Поиск нужного студента и вывод информации о нем
    int i = 0;
    std::string name;
    std::cout << "Enter finding name:" << std::endl;
    std::cin >> name;
    while (i < stCounter && name != list[i].getName()) { //Увеличиваю счетчик пока не найду или не дойду до последнего студента
        i++;
    }
    if (name == list[i].getName()) { //Проверяю есть ли в счетчике нужное имя и если есть вывожу
        PrintStudent(list, i);
    }
    else { //Если нет, значит список пройден целиком и такого студента нет, пишу об этом
        std::cout << "Not listed" << std::endl;
    }
}

//==============================Задание-2==================================

class Fruit {
protected:
    std::string name;
    std::string color;
public:
    Fruit(std::string name = "", std::string color = "") : name(name), color(color) {

    }
};

class Apple : public Fruit{ //Тут наследуется публично для того что бы гренни смит мог достучаться
protected:
    Apple(std::string name, std::string color) : Fruit(name, color) {

    }
public:
    Apple(std::string a_color) : Fruit("apple", a_color) {

    }
    void setColor(std::string color) { color = color; }
    std::string getName() const { return name; }
    std::string getColor() const { return color; }
};

class Banana : Fruit {
public:
    Banana() : Fruit("banana", "yellow") {

    }
    void setColor(std::string color) { color = color; }
    std::string getName() const { return name; }
    std::string getColor() const { return color; }
};

class GrannySmith : Apple {
public:
    GrannySmith() : Apple("Granny Smith apple", "green") {

    }
    void setColor(std::string color) { color = color; }
    std::string getName() const { return name; }
    std::string getColor() const { return color; }
};

int main()
{
//=================================Задание-1=======================================
    int trainPlaces = 50;
    int stCounter = 0;
    Student* School = new Student[trainPlaces];
    createStudent(School, stCounter);
    createStudent(School, stCounter);
    createStudent(School, stCounter);
    createStudent(School, stCounter);
    findStudent(School, stCounter);

//=================================Задание-2==========================================
    Apple a("red"); //Код из задания
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}