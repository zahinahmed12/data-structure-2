#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

using namespace std;

class ListNode
{
public:
    string str;
    int item;
    ListNode * next;
};

class LinkedList
{

    ListNode * list;
    int length;

public:
    LinkedList()
    {
        list=0; //initially set to NULL
        length=0;
    }

    int getLength()
    {
        return length;
    }

    void insertItem(string s, int item) //insert at the beginning
    {
        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->str=s;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;
        //return SUCCESS_VALUE ;
    }

    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp;
            length--;
        }
        else
        {
            prev->next = temp->next ;
            delete temp;
            length--;
        }
        return SUCCESS_VALUE ;
    }

    ListNode* searchItem(string s)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->str == s) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }

    void printList()
    {
        ListNode * temp;
        temp = list;
        while(temp!=0)
        {
            cout<< "("<<temp->str<<" ";
            cout<<temp->item<<")"<<" -> ";
            //printf("%d->", temp->item);
            temp = temp->next;
        }
        printf("\n");
        //printf("Length: %d\n",length);
    }

    ListNode * getItemAt(int pos)
    {
         //write your codes here
         if(pos>length)
         {
             return 0;
         }
         ListNode * temp;
         temp = list;
         int c=0;
         while(temp!=NULL){
         c++;
         if(c==pos)
         {
             return temp;
         }
         temp=temp->next;
    }

    }


    ~LinkedList()
    {
        //write your codes here
        ListNode * temp =list;
        while(temp!=0)
        {
            ListNode *trav=temp;
            delete trav;
            temp=temp->next;
            length--;
        }
        delete list;
        delete temp;
    }

};



