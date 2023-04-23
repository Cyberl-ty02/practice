#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass() { std::cout << "MyClass Constructor." << std::endl; }
    ~MyClass() { std::cout << "MyClass Destructor." << std::endl; }
    void sayHello() { std::cout << "Hello, World!" << std::endl; }
};

int main() {
    // ʹ�� unique_ptr ��̬���� MyClass ������ڴ�
    std::unique_ptr<MyClass> ptr(new MyClass);

    // ���� MyClass ����ĳ�Ա����
    ptr->sayHello();

    // �������˳�������ʱ��unique_ptr ���Զ��ͷ� MyClass ������ڴ�
    return 0;
}
