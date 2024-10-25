
#include <cstdint>
// #include <stdio.h>
#include <iostream>
#include <functional>
#include <memory>
#include <cstring>
#include <mutex>
#include <thread>

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

    return 0;
}
