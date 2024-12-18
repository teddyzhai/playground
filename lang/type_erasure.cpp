#include <iostream>
#include <functional>
#include <memory>
#include <string>

// Type-erased wrapper
class Callable {
    std::function<void()> func;

public:
    template <typename T>
    Callable(T&& callable) : func(std::forward<T>(callable)) {}

    void operator()() const {
        func();
    }
};

// Different callable implementations
void freeFunction() {
    std::cout << "Free function called\n";
}

class Functor {
public:
    void operator()() const {
        std::cout << "Functor called\n";
    }
};

// Type-erased shape

// Decoupling Interfaces from Implementations
class Shape {
    struct Concept {
        virtual ~Concept() = default;
        virtual void draw() const = 0;
    };

    template <typename T>
    struct Model : Concept {
        T data;
        Model(T obj) : data(std::move(obj)) {}
        void draw() const override { data.draw(); }
    };

    std::unique_ptr<Concept> self;

public:
    template <typename T>
    Shape(T obj) : self(std::make_unique<Model<T>>(std::move(obj))) {}

    void draw() const { self->draw(); }
};

// Concrete shape implementations (real, unittests, etc)
class Circle {
public:
    void draw() const { std::cout << "Drawing Circle\n"; }
    // void doSomething(void) { std::cout << "Circle doSomething" << std::endl;}
};

class Square {
public:
    void draw() const { std::cout << "Drawing Square\n"; }
};

int main() {
    Callable c1 = freeFunction;
    Callable c2 = Functor();

    c1(); // Free function called
    c2(); // Functor called

    Shape s1 = Circle();
    Shape s2 = Square();

    s1.draw(); // Drawing Circle
    s2.draw(); // Drawing Square

    return 0;
}
