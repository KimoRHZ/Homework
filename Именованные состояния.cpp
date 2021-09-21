#include <iostream>
#include <cstdint>

const size_t STACK_SIZE = 10; //Задал константный размер стека

//========================Задание-1===============================
class Power {
  
  private:
      int num;
      int power; 
  
  public:
      Power() {
          num = 1;
          power= 1;
      }
      void setPower(int num, int power) {
          num = num;
          power = power;
      }
      void Calculate(int num, int power) {
          int sum = num;
          for (int i = 0; i < power; ++i) {
              sum = sum*num;
          }
          std::cout << sum << std::endl;
      }
};

//========================Задание-2===============================
class RGBA {
    private:
        std::uint8_t m_red;
        std::uint8_t m_green;
        std::uint8_t m_blue;
        std::uint8_t m_alpha;
    public:
        RGBA (std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255) 
        : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) 
        {
            
        }
        void PrintRGB() { //Не понял нужно ли тут типы в int привести, вроде не написано, но с консолью эти типы не оч дружат... Либо я что то не так сделал.
            std::cout << "Red: " << m_red << std::endl;
            std::cout << "Green: " << m_green << std::endl;
            std::cout << "Blue: " << m_blue << std::endl;
            std::cout << "Alpha: " << m_alpha << std::endl;
        }
        
};

//========================Задание-3===============================
class Stack {
    private:
        int StackArray[STACK_SIZE];
        int sizeArr;
    
    public:
        Stack() : StackArray {0}, sizeArr(0) {
            
        }
        bool push(int data) {
            if (sizeArr < STACK_SIZE) {
                StackArray[sizeArr] = data;
                sizeArr++;
                return true;
            }
            else {
                std::cout << "Stack overflow!" << std::endl;
                return false;
            }
        }
        int pop() {
            if (sizeArr > 0) {
                int tmp = StackArray[sizeArr-1];
                StackArray[sizeArr-1] = 0;
                sizeArr--;
                return tmp;
            }
            else {
                std::cout << "Stack is empty!" << std::endl;
            }
        }
        void reset() {
            if (sizeArr > 0) {
                for (int i = 0; i < sizeArr; ++i) {
                    StackArray[i] = 0;
                }
                sizeArr = 0;
                std::cout << "Stack reset" << std::endl;
            }
            else {
                std::cout << "Stack is empty!" << std::endl;
            }
        }
        void print() {
            if (sizeArr > 0) {
                for (int i = sizeArr-1; i >=0; --i) {
                    std::cout << '[' << StackArray[i] << ']';
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "Stack is empty!" << std::endl;
            }
        }
};

int main() {
//========================Задание-1===============================    
    Power a; //Простите за эти имена, просто делал в обед на работе =))
    int num = 2;
    int power = 3;
    a.setPower(num,power);
    a.Calculate(num,power);
    
//========================Задание-2===============================    
    RGBA b(155,16,85,255);
    b.PrintRGB();

//========================Задание-3===============================     
    Stack stack;
    stack.reset(); //Тут выдаст предупреждение, так как я решил не сбрасывать пустой стек
    stack.print();
    
    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();
    
    stack.pop();
    stack.print(); //В задании указано что тут он должен вывести (3 7), но ведь это ошибка, порядок выхода из стека LIFO, так что (7 3)
    
    stack.pop();
    stack.pop();
    stack.print();

    return 0;

}
