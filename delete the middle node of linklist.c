/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

int countNodes(struct ListNode* head) {
    int count = 0;
    struct ListNode* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

struct ListNode* deleteMiddle(struct ListNode* head) {
    int size = countNodes(head);
    if (size == 1) return NULL;
    
    int middlePos = size / 2;
    struct ListNode* current = head;
    struct ListNode* prev = NULL;
    
    for (int i = 0; i < middlePos; i++) {
        prev = current;
        current = current->next;
    }
    
    if (prev != NULL) {
        prev->next = current->next;
    } else {
        head = current->next;
    }
    
    return head;
}