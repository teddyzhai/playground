
#include <iostream>
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

int main(int argc, char const *argv[])
{
    {
    Node * head = nullptr;
    for (int i = 7; i > 0; i--) {
      insert(head, i);
    }
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
        std::cout << "Delete middle:" << std::endl;
        printList(head);
    }


    return 0;
}
