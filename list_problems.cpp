
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

Node* lastKthNode(Node *head, int len, int k)
{
    // double pointer

    // move len - k steps
    Node* fast = head;
    Node* slow = head;
    for (size_t i = 0; i < k; i++)
    {
        fast = fast->next;
    }
    for (size_t i = 0; i < len-k; i++)
    {
        slow = slow->next;
        fast = fast->next;
    }


    return slow;
}

int main(int argc, char const *argv[])
{
    Node * head = nullptr;
    for (int i = 7; i > 0; i--) {
      insert(head, i);
    }
    std::cout << "List: ";
    printList(head);


    auto i = 4;
    std::cout << i << "th node from last (Recursive) : ";
    Node *n = lastKthNode(head, 7, i);
    std::cout << "node:"<< n->data  << std::endl;

    return 0;
}
