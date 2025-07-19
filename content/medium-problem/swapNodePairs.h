/**
 * Author: Cellul4r
 * Description: None
 */

ListNode* swapPairs(ListNode* head) {
    ListNode* cur = head;
    ListNode* prev = NULL;
    while(cur != NULL && cur->next != NULL) {
        cout << cur->val << endl;
        ListNode* A = cur;
        ListNode* B = cur->next;
        A->next = B->next;
        B->next = A;
        if(prev != NULL) {
            prev->next = B;
        }
        prev = A;
        if(cur == head) {
            head = B;
        }
        cur = A->next;
    }    
    return head;
}
