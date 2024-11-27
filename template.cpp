
#include <cstdint>
// #include <stdio.h>
#include <iostream>
#include <functional>
#include <memory>
#include <cstring>
#include <mutex>
#include <string>
#include <thread>
#include <type_traits>
#include <vector>

using namespace std;

/// using template for type-agnostic list
template<typename T>
struct ListNode_S
{
    T   *node;
    struct ListNode_S *next;
};

template<typename T>
void list_append(struct ListNode_S<T> **head, struct ListNode_S<T> *node)
{
    struct listNode_S *temp = *head;
    if (temp == NULL)
    {
        *head = node;
    }
    else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = node;
    }
}

// Generic AlertIF with abstract alert type and alert meta-data
template<typename AlertType, typename AlertData>
class AlertIF
{
public:
    AlertIF() = default;
    AlertIF(AlertIF &&) = default;
    AlertIF(const AlertIF &) = default;
    AlertIF &operator=(AlertIF &&) = default;
    AlertIF &operator=(const AlertIF &) = default;
    ~AlertIF() = default;

    virtual void setAlert(AlertType alert, const AlertData alertData);
    virtual void clearAlert(AlertType alert);

private:

};

struct IsolationAlertData
{
    int a;
    int b;
};

// Implementation class
// Template specialization with specific type handling.
template<typename AlertType, typename AlertData = struct IsolationAlertData>
class IsolationAlert : public AlertIF<AlertType, AlertData>
{
public:
    IsolationAlert() = default;
    IsolationAlert(IsolationAlert &&) = default;
    IsolationAlert(const IsolationAlert &) = default;
    IsolationAlert &operator=(IsolationAlert &&) = default;
    IsolationAlert &operator=(const IsolationAlert &) = default;
    ~IsolationAlert() = default;

    void setAlert(AlertType a, const struct IsolationAlertData alertData) override
    {
        cout << "Set Isolation alert" << a << endl;

        std::cout << "data 1: " << alertData.a << std::endl;

    }
    void clearAlert(AlertType alert) override { cout << "Clear Isolation alert" << alert << endl;}

private:

};

/// Learn static polymorphism (using enable_if)
// chatgpt
// Enable for integral types
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print(T value) {
    std::cout << "static poly Integral value: " << value << std::endl;
}

// Enable for floating-point types
template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
print(T value) {
    std::cout << "static poly  Floating-point value: " << value << std::endl;
}

// Type traits for container
template<typename T>
struct is_type_container : false_type {};
template<typename T>
struct is_type_container<vector<T>> : true_type {};

// enable for container type
template <typename T>
typename std::enable_if<is_type_container<T>::value, void>::type
print(T value)
{
    for (auto &i : value)
    {
        std::cout << "... " << i << std::endl;
    }
}

// enable for user type
class House
{
public:
    House() = default;
    House(House &&) = default;
    House(const House &) = default;
    House &operator=(House &&) = default;
    House &operator=(const House &) = default;
    ~House() = default;

    string name_;
};

template<typename T>
struct is_type_house : false_type {};

template<>
struct is_type_house<House> : true_type {};

// prior to C++17
// template <typename T>
// typename std::enable_if<is_type_house<T>::value, void>::type
// print(T value)
// {
//     // for (auto &i : value)
//     // {
//     std::cout << "House: " << value.name_ << std::endl;
//     // }
// }


/// c++17 style
// enable_if_t

// alternative way of using if constexpr

// for integer
template<typename T, enable_if_t<is_integral_v<T>, bool> = true>
void print17(T value)
{
    std::cout << "17 Integer: " << value << std::endl;
}

template<typename T>
constexpr bool is_type_house_v = is_type_house<T>::value;

template<typename T, enable_if_t<is_type_house_v<T>, bool> = true>
void print17(T value)
{
    std::cout << "17 house: " << value.name_ << std::endl;
}

/// c++17 syntax: if constexpr
template<typename T>
void print17_ifconstexpr(T value)
{
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integral value 17: " << value << std::endl;
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "Floating-point value 17: " << value << std::endl;
    }
    else if constexpr (is_type_house_v<T>) {
        std::cout << "House if constexpr: " << value.name_ << std::endl;
    }
}


int main(void)
{

    int x = 2, y = 3;

    struct ListNode_S<int> h, h1;
    h.node = &x;
    h1.node = &y;

    h.next = &h1;
    h1.next = NULL;

    struct ListNode_S<int> *temp = &h;
    cout<< "h: " << *(h.node) << endl;

    IsolationAlert<int, struct IsolationAlertData> a;
    // OK if without -Wpedantic
    a.setAlert(1, {.a=10,  .b=20});
    a.clearAlert(2);

    print(42);        // Matches the integral overload
    print(3.14);      // Matches the floating-point overload
    vector<int> v = {1,2,3};
    print(v);

    House house;
    house.name_ = string("name");
    // print(house);

    print17(10);
    print17(house);

    print17_ifconstexpr(house);

    return 0;
}
