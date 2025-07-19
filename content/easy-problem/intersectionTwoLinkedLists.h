/**
 * Author: Cellul4r
 * Description: None 
 */
int countNode(ListNode *head) {
        ListNode* curr = head;
        int cnt = 0;
        while(curr != NULL) {
            cnt++;
            curr = curr->next;
        }
        return cnt;
    }
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int a = countNode(headA);
        int b = countNode(headB);
        ListNode* currA = headA;
        ListNode* currB = headB;
        if(a < b) {
            // tak b - a steps on B
            for(int i = 0; i < b - a; i++) {
                currB = currB->next;
            }
        } else {
            for(int i = 0; i < a - b; i++) {
                currA = currA->next;
            }
        }
        if(currA == currB) {
            return currA;
        }
        while(currA != NULL && currB != NULL) {
            currA = currA->next;
            currB = currB->next;
            if(currA == currB) {
                return currA;
            }
        }
        return NULL;
    }
