/* Program to reverse a linked list both loop method and recursion method*/

#include <iostream>

using namespace std;

class NODE
{
public:
    int data;
    NODE *next;
};

void loop_reverse(NODE **head)
{
    NODE *cur = *head;
    NODE *prev = NULL;
    NODE *next = NULL;

    while(cur!=NULL)
    {
        next = cur->next;

        cur->next = prev;
        prev = cur;
        cur = next;
    }

    *head = prev;

return;
}

void recursive_reverse(NODE **head)
{
    //If list is empty, then return
    if(*head == NULL) return;

    //Split the list into first node and rest of the nodes
    NODE *first = *head;
    NODE *rest = first->next;

    //If rest id empty, i.e only one node in list, return
    if(rest == NULL) return;

    // Else reverse the rest of the list
    recursive_reverse(&rest);

    //Add first node to end of revrsed rest (next-next of first is next of rest block)
    first->next->next = first;
    first->next = NULL;

    *head = rest;

    return;

}

void create_list(NODE **head)
{
    int list_size = 0;
    cout << "\nCreate a linked list" ;
    cout << "\nEnter number of elements to create : " ;
    cin >> list_size;

    NODE *prev = NULL;
    NODE *tmp = NULL;


    for(int node_cnt = 0; node_cnt < list_size; node_cnt++)
    {
        tmp = new NODE;
        cout << "\nEnter data : " ;
        cin >> tmp->data;
        tmp->next = NULL;
        if(node_cnt == 0)
        {
            *head = tmp;
            prev = tmp;
        }
        else
        {
            prev->next = tmp;
            prev = tmp;
        }

    }

}

void print_list(NODE *head)
{
    NODE * print_ptr = head;
    while(print_ptr!=NULL)
    {
        cout << print_ptr->data << endl;
        print_ptr= print_ptr->next;
    }

    return;

}

int main()
{
    //cout << "Hello World!" << endl;
    NODE *head = NULL;
    create_list(&head);
    print_list(head);

    //loop_reverse(&head);
    recursive_reverse(&head);
    print_list(head);
    return 0;
}

