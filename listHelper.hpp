

#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

static void insert( ListNode * & head, int data ) {
  ListNode * newNode = new ListNode(data);
  newNode->next = head;
  head = newNode;
}

static ListNode* createList(int n)
{
    ListNode * head = nullptr;
    for (int i = 7; i > 0; i--) {
        insert(head, i);
    }
    return head;
}

void printList( ListNode * head ) {
  std::cout << "List: ";
  while(head) {
    std::cout << head->val << "-->";
    head = head->next;
  }
  std::cout << "null" << std::endl;
}
