
#include <iostream>
#include <stack>
struct Node {
  int data;
  Node * next;
  Node(int d) : data{ d }, next{ nullptr } { }
};

/**
 * Insert to the head of the list
 * @param head - Current head of list
 * @param data - new node's data
 */
void insert( Node * & head, int data ) {
  Node * newNode = new Node(data);
  newNode->next = head;
  head = newNode;
}

/**
 * [deleteList - delete the entire list]
 * @param head - head of the list
 */
void deleteList( Node * & head ) {
  Node * nextNode;
  while(head) {
    nextNode = head->next;
    delete(head);
    head = nextNode;
  }
}

/**
 * printList - Helper routine to print the list
 * @param head - Current head of the list.
 */
void printList( Node * head ) {
  std::cout << "List: ";
  while(head) {
    std::cout << head->data << "-->";
    head = head->next;
  }
  std::cout << "null" << std::endl;
}

Node* lastKthNode(Node *head, int k)
{
    // double pointer

    // move  k steps first.
    Node* fast = head;
    Node* slow = head;
    for (size_t i = 0; i < k; i++)
    {
        fast = fast->next;
    }

    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

void deleteMiddle(Node *head)
{
    // double pointer
    // move fast every time by 2.
    Node* fast = head;
    Node* slow = head;
    Node* slow_pre = head;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            fast = fast->next;
        }
        else
        {
            break;
        }
        slow_pre = slow;
        slow = slow->next;
    }

    // slow is the middle node. Delete it.
    slow_pre->next = slow->next;

}

// swap the nodes of the list from position left to position right, and return the reversed list.
Node* swapBetween(Node* head, int left, int right) {

    // left < right, left >=1, right <= length of list.

    auto getNode = [head](int pos){
        auto left_temp = head;
        while (pos > 0)
        {
            // left_pri = left_temp;
            left_temp = left_temp->next;
            pos--;
        }
        return left_temp;
    };

    // Get left-1, right-1.
    // 2 temps to left and right.
    // left-1's next ->  right temp
    // right-1's next -> left temp
    auto left_pri = getNode(left-1);
    Node *left_temp = left_pri->next;

    auto right_pri = getNode(right - 1);
    auto right_temp = right_pri->next;

    left_pri->next = right_temp;
    right_pri->next = left_temp;

    auto left_copy = left_temp->next;
    left_temp->next = right_temp->next;
    right_temp->next = left_copy;

    return head;
}

// in-place modification.
// One pass
// Using stack (first in last out)
// FIXME
Node* reverseBetween(Node* head, int left, int right) {

    auto getNode = [head](int pos){
        auto left_temp = head;
        while (--pos > 0)
        {
            // left_pri = left_temp;
            left_temp = left_temp->next;
        }
        return left_temp;
    };

    auto left_pri = getNode(left-1);
    auto left_n = left_pri->next;

    auto temp = left_n;
    std::stack<Node*> lifo;
    for (size_t i = 0; i < right - left + 1; i++)
    {
        lifo.push(temp);
        temp = temp->next;
    }
    auto r_next = temp; // record next after the reverse range.

    while (!lifo.empty())
    {
        temp = lifo.top();
        left_pri->next = temp;
        left_pri = temp;
        lifo.pop();
    }
    left_pri->next = r_next;

    return head;
}

int main(int argc, char const *argv[])
{
    auto creteList8 = [](){
        Node * head = nullptr;
        for (int i = 7; i > 0; i--) {
            insert(head, i);
        }
        return head;
    };

    {
        auto head = creteList8();
        std::cout << "List: ";
        printList(head);

        auto i = 4;
        std::cout << i << "th node from last (Recursive) : ";
        Node *n = lastKthNode(head, i);
        std::cout << "node:"<< n->data  << std::endl;
    }

    {
        Node * head = nullptr;
        for (int i = 3; i > 0; i--) {
        insert(head, i);
        }
        std::cout << "List: ";
        printList(head);

        deleteMiddle(head);
        std::cout << "Delete middle 2:" << std::endl;
        printList(head);
    }

    {
        auto head = creteList8();
        // std::cout << "swap between" << std::endl;
        // auto head_new = swapBetween(head, 1, 5);
        auto head_new  = reverseBetween(head, 2, 6);
        std::cout << "1,6...2,7" << std::endl;
        printList(head_new);
    }


    return 0;
}
