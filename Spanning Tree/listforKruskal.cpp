#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
    ListNode * prev;
};

class LinkedListDoubly
{
    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListDoubly()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }
    ListNode* getHead()
    {
        return list;
    }
    ListNode* getTail()
    {
        return tail;
    }
    int getLength()
    {
        return length;
    }
    void updateLength(int n)
    {
        length=length+n;
    }
    void mergeList(LinkedListDoubly l2)
    {
        ListNode * a = l2.tail;
        a->next=list;
        list->prev=a;
        list=l2.list;
        length=length+l2.getLength();
        l2.list=NULL;
    }
    int insertFirst(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;

        if(list==0) //inserting the first item
        {
            newNode->next = 0;
            newNode->prev = 0;
            list = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = list;
            list->prev = newNode;
            newNode->prev = 0;
            list = newNode;
        }
        length++;
        return SUCCESS_VALUE ;
    }

    /*ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printListForward()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
    }

    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here
        ListNode * newNode = new ListNode() ;
        //ListNode *temp;
        if(list==NULL)
        {
             newNode->next = 0;
             newNode->prev = 0;
             tail=list;
             list=newNode;
             tail=newNode;
        }
        else
        {
             newNode->next=NULL;
             newNode->prev=tail;
             tail->next=newNode;
             tail=newNode;

        }
        newNode->item=item;
        length++;
        return SUCCESS_VALUE;

    }

    int deleteLast()
    {
        //write your codes here
        if(length==0)
        {
            printf("THE LIST IS EMPTY NOW\n");
            return NULL_VALUE;
        }
        tail=tail->prev;
        tail->next=NULL;
        length--;
        return SUCCESS_VALUE;
    }

    void printListBackward()
    {
        //will print the list backward starting from the tail position
        ListNode * temp;
        temp = tail;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->prev;
        }
        printf("\n");

    }*/
    void printListForward()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
    }

};

/*int main(void)
{
    LinkedListDoubly ll;
    LinkedListDoubly l2;

    while(1)
    {
        printf("1. Insert new item. 2. Delete last item. 3. Search item. \n");
        printf("4. Print forward. 5. Print backward. 6. exit. 7. Insert at Last.8.merge 9.length\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item1,item2;
            scanf("%d", &item1);
            ll.insertFirst(item1);
            scanf("%d", &item2);
            l2.insertFirst(item2);
        }
        else if(ch==2)
        {
            int item = ll.deleteLast();
            if(item!=NULL_VALUE) printf("Deleted: %d\n", item);
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            ll.printListForward();
        }
        /*else if(ch==5)
        {
            ll.printListBackward();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int item;
            scanf("%d", &item);
            ll.insertLast(item);
        }
        else if(ch==8)
        {
            ll.mergeList(l2);
        }
        else if(ch==9)
        {
            printf("%d",ll.getLength());
            printf("%d",l2.getLength());
        }
    }

}*/


