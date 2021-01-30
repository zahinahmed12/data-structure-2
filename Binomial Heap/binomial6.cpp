#include<stdio.h>
#include<iostream>
#include <bits/stdc++.h>
#define MIN -9999999
using namespace std;

class heapNode
{
public:
    int key;
    int deg;

    heapNode *p;
    heapNode *c;
    heapNode *s;

    heapNode()
    {
        key=MIN;
        deg=0;

        p=NULL;
        c=NULL;
        s=NULL;
    }
};



class binomialHeap
{
public:

heapNode *root = NULL;
heapNode *Hroot;

binomialHeap()
{
    root=NULL;

    Hroot=NULL;
}


void Link(heapNode *x,heapNode *y);

heapNode* Merge(heapNode *x, heapNode *y);

heapNode* newNode(int );

heapNode* findMin();

void Reverse(heapNode *h);

heapNode* Union(heapNode *x, heapNode *y);

void Insert(int x);

void extractMin(heapNode *h);


void print(heapNode *h)
{
    int c=0;

    while (h)
    {

        cout << h->key << " ";
        c++;
        //cout<<"\nLEVEL "<<c<<" COMPLETED"<<endl;
        //cout<<"\nLEVEL "<<c<<endl;
        print(h->c);

        //cout<<"\nLEVEL "<<c<<" COMPLETED"<<endl;
        h = h->s;
    }
    //printf("\n");

}

};

void binomialHeap::extractMin(heapNode *h)
{
    Hroot=NULL;

    heapNode *x=h;

    if (x == NULL)
    {
        printf("HEAP IS EMPTY\n");

        return ;//NULL;
    }

    int minVal = x->key;

    heapNode *node = x;

    heapNode *prev = NULL;

    heapNode *now = x;

    while (now->s != NULL)
    {
        if ((now->s)->key < minVal)
        {
            minVal = (now->s)->key;
            prev = now;
            node = now->s;
        }

        now = now->s;
    }

    if (prev == NULL && node->s == NULL)
    {
        //root=NULL;
        h= NULL;
        //return h;
    }

    else if (prev == NULL)
    {
         h = node->s;
    }

    else
    {
        prev->s = node->s;
    }

    if (node->c != NULL)
    {
        Reverse(node->c);
        (node->c)->s = NULL;
    }

     root= Union(h, Hroot);
    //return node;
    printf("THE MINIMUM KEY EXTRACTED\n");
}

void binomialHeap::Insert(int x)
{
    heapNode *a=NULL;

   /* a->deg=0;

    //a->key=x;

    a->p=0;

    a->s=0;

    a->c=0;*/
    heapNode *b= newNode(x);

    root =Union(root,b);
    printf("SUCCESSFULLY INSERTED %d\n",x);
}

heapNode* binomialHeap::Union(heapNode *x, heapNode *y)
{

    heapNode *pre = NULL;

    if (x == NULL && y == NULL)
    {
        printf("HEAPS ARE EMPTY\n");

        return NULL;

    }

    heapNode *temp = Merge(x, y);

    heapNode *now = temp;
    heapNode *nxt = now->s;


    while (nxt != NULL)
    {
        if ((now->deg != nxt->deg) || ((nxt->s != NULL) &&(nxt->s)->deg ==now->deg))
        {

            pre = now;


            now = nxt;
        }
        else
        {
            if (now->key <= nxt->key)
            {

                now->s = nxt->s;

                Link(nxt, now);
            }
            else
            {

                if (pre == NULL)
                {
                    temp = nxt;
                }

                else

                    pre->s = nxt;

                Link(now, nxt);


                now = nxt;
            }
        }


        nxt = now->s;
    }
    return temp;
}

void binomialHeap::Reverse(heapNode *h)
{
    if (h->s == NULL)
    {
        Hroot = h;

    }
    else
    {
         Reverse(h->s);
        (h->s)->s = h;
    }

}

void binomialHeap::Link(heapNode *x, heapNode *y)
{
    x->p = y;

    x->s = y->c;

    y->c = x;

    y->deg = y->deg + 1;
}

heapNode* binomialHeap::findMin()
{
    heapNode *y= NULL;

    heapNode *x= root;

    int minVal=9999999;

    while(x !=NULL)
    {
        //printf("h1\n");
        if(x->key < minVal)
        {
           // printf("h2\n");
            minVal= x->key;
            y=x;
        }
        x=x->s;
    }
    return y;
}

heapNode* binomialHeap::Merge(heapNode *x, heapNode *y)
{
    heapNode *r = NULL;

    /*if (y == NULL)
    {

        return x;

    }
    if (x == NULL)
    {
        return y;
    }

    if (x->deg > y->deg)
    {
        r = y;
    }
    else if (x->deg <= y->deg)
    {
        r = x;
    }*/
    heapNode *a=x;

    heapNode *b=y;

    if(b!=0)
    {
        if(a!=0)
        {
            if(a->deg<= b->deg)
            {
                r=a;
            }
            else if(a->deg > b->deg) r=b;
        }
        else r=b;
    }
    else r=a;


    while (x != NULL && y != NULL)
    {
        if (x->deg < y->deg)
        {
            x = x->s;
        }

        else if (x->deg == y->deg)
        {
            heapNode *t = x->s;
            x->s = y;
            x = t;
        }
        else
        {
            heapNode *t = y->s;
            y->s = x;
            y = t;
        }
    }
    return r;
}


heapNode* binomialHeap::newNode(int n)
{
    heapNode *a = new heapNode;

    a->deg = 0;

    a->key = n;

    a->p = a->s = a->c = NULL;
    return a;
}



int main()
{
    //heapNode n;
    binomialHeap b;

    /*b.Insert(8);
    b.Insert(14);
    b.Insert(2);
    b.Insert(4);
    b.Insert(17);*/
   // b.display(b.root);
    printf("ENTER YOUR OPTION: \n");

    while(1)
    {
        int x;
        printf("1.Insert 2.Extract Min 3. Find Min 4. Print 5. Exit\n");
        scanf("%d",&x);
        if(x==1)
        {
            int a;
            printf("ENTER THE KEY VALUE\n");
            scanf("%d",&a);
            b.Insert(a);
        }
        else if(x==2)
        {
            //heapNode* a=
             b.extractMin(b.root);
        }
        else if(x==3)
        {
            heapNode *a=b.findMin();
            if(a==NULL) printf("THE HEAP IS EMPTY\n");
            else printf("THE MINIMUM KEY IS %d\n",a->key);
        }
        else if(x==4)
        {
            b.print(b.root);
            cout<<endl;
        }
        else if(x==5)
        {
            return 0;
        }
    }

}
