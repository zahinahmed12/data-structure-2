#include<stdio.h>
#include<stdlib.h>
#include "minHeapDijkstra2.cpp"
#define NULL_VALUE -999999
#define INFINITY 999999
#include<cstring>
#include<bits/stdc++.h>
using namespace std;

class ArrayList
{
	int *list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
    void insertItem(int item) ;
	int getItem(int position) ;
	int getW(int position) ;
	int getLength();
} ;

ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}


int ArrayList::getLength()
{
	return length ;
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
	int nVertices, nEdges ;
    ArrayList  * adjList ;
    bool directed ;

public:
    int **weight;
    int *dist;
    int *prev;
    Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v, int w);
    void Dijkstra(int s);
    void DijkstraPath(int v);
};

Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	if(adjList!=0) delete[] adjList ;
	adjList = new ArrayList[nVertices] ;
    weight= new int*[nVertices];
    for(int i = 0; i < nVertices; ++i)
    {
        weight[i] = new int[nVertices];
    }
    dist=new int[nVertices];
    prev=new int[nVertices];
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    if(!directed){

        adjList[u].insertItem(v) ;
        adjList[v].insertItem(u) ;
        this->nEdges++ ;
        this->nEdges++ ;
        weight[u][v]=w;
        weight[v][u]=w;
    }
    else
    {
        adjList[u].insertItem(v) ;
        this->nEdges++ ;
        weight[u][v]=w;

    }

}

void Graph::DijkstraPath(int v)
{
    if(prev[v]==NULL_VALUE)
    {
        return;
    }
    DijkstraPath(prev[v]);
    printf("%d->",prev[v]);

}

void Graph::Dijkstra(int s)
{
    //int dist[nVertices];
    //int prev[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        dist[i]=INFINITY;
        prev[i]=NULL_VALUE;
    }
    dist[s]=0;
    minNodes * p= new minNodes[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        p[i].set_min_v(i);
        p[i].set_min_w(INFINITY);
    }
    p[s].set_min_v(s);
    p[s].set_min_w(0);
    MinHeap h(50);
    for(int i=0;i<nVertices;i++)
    {
        h.insertKey(p[i]);
        h.pos[i]=i;
    }
    h.pos[s]=s;
    while(!h.heap_is_empty())
    {
        minNodes *a=h.getMin();
        int u=a->getminv();
        h.extractMin();
        for(int i=0;i<adjList[u].getLength();i++)
        {
            int v=adjList[u].getItem(i);
            if(h.exists(v) &&dist[u]!=INFINITY && dist[v]> dist[u]+weight[u][v]){

                prev[v]=u;
                //h.deleteAnode(v);
                dist[v] = dist[u]+weight[u][v];
                /*minNodes newN;
                newN.set_min_v(v);
                newN.set_min_w(dist[v]);*/
                h.decreaseKey(h.pos[v],dist[v],v);
            }
        }
    }
    printf("Shortest distances from the source :\n");
    printf("Vertex---dist---prev\n");
    for(int i=0;i<nVertices;i++)
    {
        printf("%d---%d---%d\n",i,dist[i],prev[i]);
    }
    for(int i=0;i<nVertices;i++)
    {
        printf("path for vertex %d----",i);
        DijkstraPath(i);
        printf("%d",i);
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList!=0) delete[] adjList ;
	adjList = 0;
}

int main()
{
    Graph g;
    const int sz = 1001;
    int array[sz];
    freopen("inputForDijkstra.txt","r", stdin);
    int index = 0, num;
    while(scanf("%d",&num) == 1) {
        array[index++] = num;
    }
    int n=array[0];
    int m=array[1];
    g.setnVertices(n);

    for(int i=2;i<index-2;i=i+3)
    {
        int u,v,w;
        u=array[i];
        v=array[i+1];
        w=array[i+2];

        g.addEdge(u,v,w);
    }
    freopen ("myOutputDijkstra.txt","w",stdout);
    //printf ("This sentence is redirected to a file.");
    g.Dijkstra(m);
    fclose (stdout);
    //g.Dijkstra();
}



