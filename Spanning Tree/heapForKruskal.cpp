#include<iostream>
#include<climits>
#include<bits/stdc++.h>
#include<stdio.h>
using namespace std;

class minNodes
{
    int value1, value2;
    int weight;
    public:
        minNodes()
        {
            value1=0;
            value2=0;
        }
        int getval1()
        {
            return value1;
        }
        int getval2()
        {
            return value2;
        }
        int getW()
        {
            return weight;
        }
        void setval1(int v)
        {
            value1=v;
        }
        void setval2(int v)
        {
            value2=v;
        }
        void setW(int w)
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

    void decreaseKey(int i, int new_val, int n, int m);

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

    void print()
    {
        cout << "THE CURRENT SIZE OF HEAP: "<<this->heap_size << endl;
        for(int i = 0; i < this->heap_size; i++)
            cout<<this->arr[i].getW()<<"->";
        printf("\n");
    }
    ~MinHeap()
     {
        heap_size = 0;
        capacity = 0;
        delete[] arr;
     }
};

MinHeap::MinHeap(int cap)
{
    heap_size = 0;
    capacity = cap;
    arr = new minNodes[cap];
}

void MinHeap::insertKey(minNodes k)
{
    if (heap_size == capacity)
    {
        cout << "\nOverflow: Could not insertKey\n";
        return;
    }
        heap_size++;
        arr[heap_size-1].setW(INT_MAX) ;
        arr[heap_size-1].setval1(k.getval1());
        arr[heap_size-1].setval2(k.getval2());
        decreaseKey(heap_size -1, k.getW(),k.getval1(),k.getval2());
}

void MinHeap::decreaseKey(int i, int w, int v1, int v2)
{
    if(i>=heap_size)
        {
            cout <<"ERROR"<<endl;
            return;
        }
    if( w > arr[i].getW())
    {
        cout<< "ERROR" << endl;
        return;
    }
    arr[i].setW(w);
    arr[i].setval1(v1);
    arr[i].setval2(v2);
    while (i != 0 && arr[parent(i)].getW() > arr[i].getW())
    {
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
        //delete []arr;
        return;
    }
    arr[0].setval1(arr[heap_size-1].getval1());
    arr[0].setval2(arr[heap_size-1].getval2());
    arr[0].setW(arr[heap_size-1].getW());
    heap_size--;
    MinHeapify(0);
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
    if (l <= heap_size && arr[l].getW() < arr[i].getW())
        smallest = l;
    else smallest=i;
    if (r <= heap_size && arr[r].getW() < arr[smallest].getW())
        smallest = r;
    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        MinHeapify(smallest);
    }
}
/*int main()
{
    minNodes *p=new minNodes[1];
    for(int i=0; i<1; i++)
    {
        int u,v,w;
        scanf("%d",&u);
        p[i].setval1(u);
        scanf("%d",&v);
        p[i].setval2(v);
        scanf("%d",&w);
        p[i].setW(w);
    }
    MinHeap h(10);
    for(int i=0;i<1;i++)
    {
        h.insertKey(p[i]);
    }
    h.print();
    minNodes *a=h.getMin();
    printf("%d ",a->getval1());
    printf("%d ",a->getval2());
    printf("%d \n",a->getW());
    h.extractMin();
    h.print();
    minNodes *b=h.getMin();
    printf("%d ",b->getval1());
    printf("%d ",b->getval2());
    printf("%d ",b->getW());


}*/
