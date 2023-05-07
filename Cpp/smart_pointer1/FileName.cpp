#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor." << std::endl; }
    ~MyClass() { std::cout << "MyClass Destructor." << std::endl; }
    void sayHello() { std::cout << "Hello, World!" << std::endl; }
};

int main() {
    // 使用 unique_ptr 动态分配 MyClass 对象的内存
    std::unique_ptr<MyClass> ptr(new MyClass);

    // 调用 MyClass 对象的成员函数
    ptr->sayHello();

    // 当程序退出作用域时，unique_ptr 会自动释放 MyClass 对象的内存
    return 0;
}
