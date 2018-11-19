//Rachel Shpringer
//CS20A
//Programming Project #4
//Due: November 18, 2018


/*
1. Implement MERGE SORT using a linked list.
2. Create a list of length 50 with random numbers
3. Run implemented merge sort on the list
4. Print results
*/


#include <iostream>
using namespace std;


struct node {
    int value;
    node *next;
};

node* NewNode(int i) {
    struct node *temp = new node;
    temp->value = i;
    temp->next = NULL;
    return temp;
}

// this adds each new node to the end of the list as the random number generator pulls values
node* AddToList(node *tail, int value) {
    struct node *newnode;
    newnode = NewNode(value);
    
    if(tail == NULL) {
        tail = newnode;
    }
    else {
        tail->next = newnode;
        tail = tail->next;
    }
    
    return tail;
}

node* Merge(node* L1, node* L2) {
    node *N1 = new node;
    node *N2 = new node;
    node *Ntemp = new node;
    
// troubleshooting: what to do if either of the two lists becomes empty?
    if(L1 == NULL)
        return L2;
    
    if(L2 == NULL)
        return L1;
    
    N1 = L1;
  
    
// now we merge the nodes:
    while (L2 != NULL) {
        N2 = L2;
        L2 = L2->next;
        N2->next = NULL;
        
        if(L1->value > N2->value) {
            N2->next = L1;
            L1 = N2;
            N1 = L1;
            continue;
        }
        
    flag:
        if(N1->next == NULL) {
            N1->next = N2;
            N1 = N1->next;
        }
        else if((N1->next)->value <= N2->value) {
            N1 = N1->next;
            goto flag;
        }
        else {
            Ntemp = N1->next;
            N1->next = N2;
            N2->next = Ntemp;
        }
    }

    return L1;
}

void MergeSort(node **head) {
    node *first = new node;
    node *second = new node;
    node *temp = new node;
    first = *head;
    temp = *head;

    if(first == NULL || first->next == NULL) {
        return;
    }
    else {
        while(first->next != NULL) {
            first = first->next;
            if(first->next != NULL) {
                temp = temp->next;
                first = first->next;
            }
        }
        second = temp->next;
        temp->next = NULL;
        first = *head;
    }
    
    MergeSort(&first);
    MergeSort(&second);
    *head = Merge(first, second);
}


// main function begins here
int main() {
    int n, i, num;
    struct node *head = new node;
    struct node *tail = new node;
    head = NULL;
    tail = NULL;
    n = 50;
    
    srand((unsigned)time(0)); // srand ensures that the random number generator pulls new values each time
    for(i = 0; i < n; i++) {
        num=(rand()%200)-100; // i selected the data range of -100 to 100
        
        tail = AddToList(tail, num);
        if(head == NULL)
            head = tail;
    }
    
    MergeSort(&head);
    
    cout << "\nSorted Values in Ascending Order:" << endl;
    
    while(head != NULL) {
        cout<<head->value;
        cout << endl;
        head=head->next;
    }
    return 0;
}

