/*
// Definition for a Node.
class Node {
public:
   int val;
   Node* next;
   Node* random;
       
   Node(int _val) {
       val = _val;
       next = NULL;
       random = NULL;
   }
};
*/
#include <iostream>
#include <map>

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == nullptr){
            return nullptr;
        }

        Node* dummy = new Node(INT32_MIN);
        dummy -> next = head;

        while(head != NULL){
            Node* tmpNode = new Node(head->val);
            tmpNode->next = head->next;
            head->next = tmpNode;
            head = tmpNode->next;
        }

        head = dummy->next;
        while(head != NULL){
            Node* newNode =  = head ->next;
            if(head->random != NULL){
                newNode -> random = head->random->next;
            }else {
                newNode -> random = NULL;
            }
            head = newNode->next;
        }

        head = dummy->next;
        Node* newDummy = new Node(INT32_MIN);
        newDummy->next = head->next;
        Node* newHead = = head->next;

        while (newHead -> next != NULL){  //head!=NULL  -> newNode!=NULL
            head ->next = newHead ->next;
            head = head ->next;
            newHead ->next = head ->next;
            newHead = newHead -> next;
        }
        newHead -> next = NULL;
        head -> next = NULL;
        return newDummy->next;
    }
};
