#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<bits/stdc++.h>
//#include "maxHeapforVC.cpp"
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;


class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
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

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	/*if(length==1)
    {
        length=0;
        return;
    }*/
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
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

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  *adjList ;
	ArrayList *edgeList;
	int *color;
	int *parent;
	int *dist;
	int *discoveryTime;
	int *finishTime;
	int time;

public:
    vector<int> l;
    int *degree;
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(); //will run dfs in the graph
	void dfs_visit(int u);
	int currDeg(int );
    int vertexCover1();
    int vertexCover2();
   // void printvc1();
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	color = 0;
	parent = 0;
	dist = 0;
	discoveryTime = 0;
	finishTime = 0;
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	if(parent!=0) delete[] parent ;
	parent = new int[nVertices];

	if(dist!=0) delete[] dist ;
	dist = new int[nVertices];

	if(discoveryTime!=0) delete[] discoveryTime ;
	discoveryTime = new int[nVertices];

	if(finishTime!=0) delete[] finishTime ;
	finishTime = new int[nVertices];

	if(color!=0) delete[] color ;
	color = new int[nVertices];

	edgeList=new ArrayList[nVertices];
	degree = new int[nVertices];
	for(int i=0;i<nVertices;i++)
    {
        degree[i]=0;
    }
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    if(directed){
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	edgeList[u].insertItem(v);
    }
	if(!directed) {
        adjList[u].insertItem(v) ;
        edgeList[u].insertItem(v);
        adjList[v].insertItem(u) ;
        edgeList[v].insertItem(u);
        this->nEdges++ ;
        degree[u]+=2;
        degree[v]+=2;
        //this->nEdges++ ;
	}
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(!isEdge(u,v)) return;
    else
    {
        if(!directed){
        edgeList[u].removeItem(v) ;
        edgeList[v].removeItem(u) ;
        this->nEdges-- ;
        degree[u]-=2;
        degree[v]-=2;
        //this->nEdges-- ;
        return;
        }
        else if(directed){
            edgeList[u].removeItem(v) ;
            //this->nEdges-- ;
            return;
        }

    }
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(edgeList[u].searchItem(v)!= NULL_VALUE)
    {
        //printf("EDGE FOUND\n");
        return true;
    }
    else
    {
        //printf("NO EDGE FOUND\n");
        return false;
    }
}
int Graph::currDeg(int u)
{
    //return edgeList[u].getLength();
    return degree[u];
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(!directed){
    return 2*adjList[u].getLength();
    }
    else if(directed){
          return adjList[u].getLength();
    }
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
        for(int i=0;i<adjList[v].getLength();i++)
        {
            for(int j=0;j<adjList[u].getLength();i++)
            {
                if(adjList[u].getItem(j)==adjList[v].getItem(j))
                {
                    printf("ADJACENT VERTICES FOUND\n");
                    return true;
                }
            }
        }
        printf("ADJACENT VERTICES NOT FOUND\n");
        return false;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

int Graph::vertexCover1()
{
    while(nEdges!=0){

        int u=rand()%nVertices;

        if(edgeList[u].getLength()!=0)
        {
            l.push_back(u);
            int x;
            for(int j=0;j<edgeList[u].getLength();j++)
            {
                x=edgeList[u].getItem(j);
                l.push_back(x);
                break;
            }
            while(edgeList[u].getLength()!=0)
            {
                //printf("hi\n");
                int y=edgeList[u].getItem(0);
                //edgeList[u].removeItem(y);
                //printf("%d\n",edgeList[u].getLength());
                // printf("%d\n",this->nEdges);
                removeEdge(u,y);
            }
           // printf("out while 1\n");
            while(edgeList[x].getLength()!=0)
            {
               // printf("hi2\n");
                int y=edgeList[x].getItem(0);
                //edgeList[x].removeItem(y);
                //printf("%d\n",edgeList[x].getLength());
                 //printf("%d\n",this->nEdges);
                 removeEdge(x,y);
            }
            //printf("out while 2\n");

             //printf("%d\n",nEdges);

        }
    }
    /*for(int i=0; i<l.size();i++)
    {
        //c++;
        printf("%d " ,l[i]);
    }

    printf("\n%d \n",l.size());*/
    return l.size();
}

int Graph::vertexCover2()
{
   /* maxNodes * p= new maxNodes[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        p[i].set_max_v(i);
        p[i].set_max_w(degree[i]);
    }
    MaxHeap h(1050);
    for(int i=0;i<nVertices;i++)
    {
        h.insertKey(p[i]);
    }
    while(nEdges>1)
    {
        maxNodes* x=h.getMax();
        maxNodes* y=h.getMax();
        int u=x->getmaxv();
        l.push_back(u);

        int v=y->getmaxv();
        l.push_back(v);
        h.extractMax();
        h.extractMax();
        while(edgeList[u].getLength()!=0)
        {
            //printf("hi1\n");
            int y=edgeList[u].getItem(0);
            removeEdge(u,y);
            for(int i=0;i<nVertices;i++)
            {
                //printf("hell1\n");
                if(h.arr[i].getmaxv()==y)
                {
                    //printf("ye\n");
                    h.arr[i].set_max_w(currDeg(y));
                    //h.MaxHeapify(i);
                    //printf("hola\n");
                }
                h.MaxHeapify(0);
            }
        }
        while(edgeList[v].getLength()!=0)
        {
            printf("hi2\n");
            int y=edgeList[v].getItem(0);
            removeEdge(u,y);
            for(int i=0;i<nVertices;i++)
            {
                if(h.arr[i].getmaxv()==y)
                {
                    h.arr[i].set_max_w(currDeg(y));
                    h.MaxHeapify(i);
                }
            }
        }
    }*/
    while(nEdges!=0)
    {
        int large1=-999999,large2=-9999999;
        int idx1,idx2;
        for(int i=0;i<nVertices;i++)
        {
            if(degree[i]!=0&& degree[i]>large1)
            {
               large1=degree[i];
               idx1=i;
            }
        }
        degree[idx1]=0;
        int u=idx1;
        l.push_back(u);
        for(int i=0;i<edgeList[u].getLength();i++)
        {
            int x=edgeList[u].getItem(i);
            if(degree[x]!=0 && degree[x]>large2)
            {
                large2=degree[x];
                idx2=x;
            }
        }
        degree[idx2]=0;
        int v=idx2;
        l.push_back(v);
        while(edgeList[u].getLength()!=0)
        {
             int y=edgeList[u].getItem(0);
             removeEdge(u,y);
        }
        while(edgeList[v].getLength()!=0)
        {
             int y=edgeList[v].getItem(0);
             removeEdge(v,y);
        }
    }
    /*for(int i=0; i<l.size();i++)
    {
        //c++;
        printf("%d " ,l[i]);
    }*/

    return l.size();
}

/*void Graph::printvc1()
{
    vertexCover1();
    int c=0;
    for(int i=0; i<l.size();i++)
    {
        c++;
        printf("%d " ,l[i]);
    }
    printf("vertex cover = %d\n",c);

}*/

Graph::~Graph()
{
    //write your destructor here
    if(adjList!=0) delete[] adjList ;
	if(color!=0) delete[] color ;
	if(parent!=0) delete[] parent ;
	if(dist!=0) delete[] dist ;
	if(discoveryTime!=0) delete[] discoveryTime ;
	if(finishTime!=0) delete[] finishTime ;
	adjList = 0;
	color = 0;
	parent = 0;
	dist = 0;
	discoveryTime = 0;
	finishTime = 0;
}

/*int main()
{
    //srand(unsigned(time(0)));
    int n,m;
    Graph g;
    scanf("%d",&n);
    g.setnVertices(n);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    /*ifstream fin;
    fin.open("graph 4.txt",ios::in);
    if(fin>> n>> m)
    {
        g.setnVertices(n);
        int u,v;
        while(fin >>u>>v)
        {
            g.addEdge(u-1,v-1);
        }
    }
    printf("%d\n",g.vertexCover2());
}*/

/*int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2. Remove edge. 3. Degree\n");
        printf("4. is Edge. 5. Print Graph  6. Exit. 7. Common Adjacent vertices.\n");
        printf("8. BFS. 9. Get Shortest Distance. 10. DFS\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);

        }
        else if(ch==3)
        {
            int u;
            scanf("%d", &u);
            printf("%d\n",g.getDegree(u));

        }
        else if(ch==4)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.isEdge(u, v);
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            break;
        }
        else if(ch==7)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.hasCommonAdjacent(u, v);

        }
        else if(ch==8)
        {
            int u;
            scanf("%d", &u);
            g.bfs(u);
        }
        else if(ch==9)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            printf("%d\n",g.getDist(u, v));

        }
         else if(ch==10)
        {
            g.dfs();
        }
    }

}*/

