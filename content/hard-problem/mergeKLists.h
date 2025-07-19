/**
 * Author: Cellul4r
 * Description: None
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;

        while (lists.size() > 1) {
            vector<ListNode*> temp;
            for (int i = 0; i < lists.size(); i += 2) {
                ListNode* l1 = lists[i];
                ListNode* l2 = (i + 1 < lists.size()) ? lists[i + 1] : nullptr;
                temp.push_back(merge(l1, l2));
            }
            lists = temp;
        }

        return lists[0];
    }

private:
    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* current = &dummy;

        while (l1 && l2) {
            if (l1->val > l2->val) {
                current->next = l2;
                l2 = l2->next;
            } else {
                current->next = l1;
                l1 = l1->next;
            }
            current = current->next;
        }

        current->next = (l1 != nullptr) ? l1 : l2;
        return dummy.next;
    }
};
