class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev=NULL;
        ListNode* curr=head;
        ListNode* after=NULL;
        while(curr!=NULL){
            after=curr->next;
            curr->next=prev;
            prev=curr;
            curr=after;
        }
        head=prev;
        return head;
    }
};