#include<iostream>
#include<climits>
#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

class minNodes
{
    int value;
    int weight;
    public:
        minNodes()
        {
            value=0;
        }
        int getminv()
        {
            return value;
        }
        int getminw()
        {
            return weight;
        }
        void set_min_v(int v)
        {
            value=v;
        }
        void set_min_w(int w)
        {
            weight=w;
        }
};

class MinHeap
{
    minNodes *arr;
    int capacity;
    int heap_size;

    int parent(int i) { return (i-1)/2; }

    int left(int i) { return (2*i + 1); }

    int right(int i) { return (2*i + 2); }

public:
    int *pos;


void swap(minNodes* x, minNodes* y)
{
    minNodes temp = *x;
    *x = *y;
    *y = temp;
}

    MinHeap(int capacity);

    void MinHeapify(int );

    void set_heap_size(int n) { heap_size = n;}

    void extractMin();

    void decreaseKey(int i, int new_val, int n);

    //int find_Min() { return arr[0]; }

    //void deleteKey(int i);
    void deleteAnode(int val)
    {
        arr[pos[val]].set_min_v( arr[heap_size-1].getminv());
        arr[pos[val]].set_min_w(arr[heap_size-1].getminw());
        heap_size--;
        MinHeapify(pos[val]);

    }

    void insertKey(minNodes );
    minNodes* getMin();

    void build_minheap(int n)
    {
        for(int i=(n/2) -1; i>=0; i--)
            MinHeapify(i);
    }

    int heapsize()
    {
        return heap_size;
    }

    bool heap_is_empty()
    {
        return heapsize() == 0;
    }

    /*void siftup(int i)
    {
        if(i<heap_size && i>0 && arr[i]< arr[parent(i)])
        {
            swap(&arr[i], &arr[parent(i)]);
            siftup(parent(i));
        }
        while (i != 0 && arr[parent(i)] > arr[i])
        {
           swap(&arr[i], &arr[parent(i)]);
           i = parent(i);
        }
    }

    void siftdown(int i)
    {
       int smallest = i;
       if (left(i) < heap_size && arr[smallest] > arr[left(i)])
            smallest = left(i);
       if (right(i) < heap_size && arr[smallest] > arr[right(i)])
            smallest = right(i);
       if (smallest != i)
       {
           swap(&arr[i], &arr[smallest]);
           siftdown(smallest);
       }
    }*/

    void delete_min()
    {
        if (heap_size <= 0)
        return ;

    /*if (heap_size == 1)
    {
        heap_size--;
        return arr[0];
    }*/
        arr[0].set_min_v(arr[heap_size-1].getminv());
        arr[0].set_min_w(arr[heap_size-1].getminw());
        heap_size--;
        MinHeapify(0);
    }

    /*void Replace(int val)
    {
        arr[0] = val;
        siftdown(0);
    }

    void create_heap(int cap)
    {
       heap_size = 0;
       capacity = cap;
       arr = new int[cap];
    }*/

    void deleteKey(int i)
    {
        if (heap_size <= 0)
           return ;
        /*if (heap_size == 1)
        {
           heap_size--;
           return ;
        }*/
        if(i>=heap_size)
        {
            cout <<"ERROR"<<endl;
            return;
        }
        arr[i].set_min_v( arr[heap_size-1].getminv());
        arr[i].set_min_w(arr[heap_size-1].getminw());
        heap_size--;
        MinHeapify(i);
    }

void print()
    {
        cout << "THE CURRENT SIZE OF HEAP: "<<this->heap_size << endl;
        for(int i = 0; i < this->heap_size; i++)
            cout<<this->arr[i].getminw()<<"->";
        printf("\n");
    }

 bool exists(int n)
 {
   if(pos[n]<heap_size)
            return true;

     return false;
 }
~MinHeap()
{
        heap_size = 0;
        capacity = 0;
        delete[] arr;
        delete[] pos;
}

};

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    arr = new minNodes[cap];
    pos=new int[cap];
}

void MinHeap::insertKey(minNodes k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
        heap_size++;
        arr[heap_size -1].set_min_w(INT_MAX) ;
        arr[heap_size-1].set_min_v(k.getminv());
        decreaseKey(heap_size -1, k.getminw(),k.getminv());
}

void MinHeap::decreaseKey(int i, int new_val, int n)
{
    if(i>=heap_size)
        {
            cout <<"ERROR"<<endl;
            return;
        }
    if(new_val>arr[i].getminw())
    {
        cout<< "ERROR" << endl;
        return;
    }
    arr[i].set_min_w(new_val);
    arr[i].set_min_v(n);
    while (i != 0 && arr[parent(i)].getminw() > arr[i].getminw())
    {
       pos[arr[parent(i)].getminv()]=i;
       pos[arr[i].getminv()]=parent(i);
       swap(&arr[i], &arr[parent(i)]);
       i = parent(i);
    }
}

void MinHeap::extractMin()
{
    if (heap_size <= 0)
        return ;
    if (heap_size == 1)
    {
        heap_size--;
        minNodes *p;
        p=&arr[0];
        //pos[arr[0].getminv()]=INFINITY;
        //return p;
        return;
    }
    minNodes *root = &arr[0];
    minNodes *firstNode = &arr[0];
    minNodes *lastNode= &arr[heap_size-1];

    pos[arr[0].getminv()]=heap_size-1;
    pos[arr[heap_size-1].getminv()]=0;

    firstNode=lastNode;
    arr[0].set_min_v(arr[heap_size-1].getminv());
    arr[0].set_min_w(arr[heap_size-1].getminw());
    heap_size--;
    MinHeapify(0);
    //return root;
}
minNodes* MinHeap::getMin()
{
    minNodes *root = &arr[0];
    return root;
}

void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l <= heap_size && arr[l].getminw() < arr[i].getminw())
        smallest = l;
    else smallest=i;
    if (r <= heap_size && arr[r].getminw() < arr[smallest].getminw())
        smallest = r;
    if (smallest != i)
    {
        pos[arr[smallest].getminv()]=i;
        pos[arr[i].getminv()]=smallest;
        swap(&arr[i], &arr[smallest]);
        MinHeapify(smallest);
    }
}




