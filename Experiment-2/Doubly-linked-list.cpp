//Doubly linked list program with functions- insertAtHead, insertAtTail, insertByPos, deleteByVal, reverse, print

#include<iostream>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node* prev;
    Node(int val){
        data=val;
        next=NULL;
        prev=NULL;
    }
};

class List{
    Node* head;
    Node* tail;

    public:
    List(){
        head=tail=NULL;
    }

    void insertAtHead(int val){
        Node* newNode=new Node(val);
        if(head==NULL){
            head=tail=newNode;
        } else {
            newNode->next=head;
            head->prev=newNode;
            head=newNode;
        }
    }

    void insertAtTail(int val){
        Node* newNode=new Node(val);
        if(head==NULL){
            head=tail=newNode;
        } else {
            tail->next=newNode;
            newNode->prev=tail;
            tail=newNode;
        }
    }

    void insertByPos(int val, int pos){
        if(pos<0) return;
        if(pos==0){
            insertAtHead(val);
            return;
        }
        Node* newNode=new Node(val);
        Node* temp=head;
        for(int i=0;i<pos-1 && temp!=NULL;i++){
            temp=temp->next;
        }
        if(temp==NULL) return;
        if(temp->next==NULL){
            insertAtTail(val);
            return;
        }
        newNode->next=temp->next;
        newNode->prev=temp;
        temp->next->prev=newNode;
        temp->next=newNode;
    }

void deleteByVal(int val) {
        if (head==NULL) return;
        Node* temp= head;
        if (head->data==val) {
            head= head->next;
            if (head != NULL) head->prev= NULL;
            else tail= NULL;
            delete temp;
            return;
        }
        while (temp != NULL && temp->data != val) {
            temp= temp->next;
        }
        if (temp==NULL) return;
        if (temp==tail) {
            tail= tail->prev;
            tail->next = NULL;
        } else {
            temp->prev->next= temp->next;
            temp->next->prev= temp->prev;
        }
        delete temp;
    }

    void reverse(){
        Node* before=NULL;
        Node* curr=head;
        Node* after=NULL;
        tail=head;
        while(curr!=NULL){
            after=curr->next;
            curr->next=before;
            curr->prev=after;
            before=curr;
            curr=after;
        }
        head=before;
    }

    void print(){
        Node* temp=head;
        while(temp!=NULL){
            cout<<temp->data<<" <-> ";
            temp=temp->next;
        }
        cout<<"NULL";
        cout<<endl;
    }

};

int main(){
    List obj;
    obj.insertAtHead(10);
    obj.insertAtTail(30);
    obj.insertByPos(20,1);
    obj.print();

    obj.deleteByVal(100);

    obj.reverse();
    obj.print();

    return 0;
}