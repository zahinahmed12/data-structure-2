#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
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
//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *color;
	int *parent;
	int *dist;
	int *discoveryTime;
	int *finishTime;
	int time;

public:
    int **weight;
    int **pred;
    int **apsp;
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(); //will run dfs in the graph
	void dfs_visit(int u);
	int countConnectedComponent();
	void floydWarshall();
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	weight=0;
	apsp=0;
	pred=0;
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

	weight= new int*[nVertices];
    for(int i = 0; i < nVertices; ++i)
    {
        weight[i] = new int[nVertices];
    }
    pred= new int*[nVertices];
    for(int i = 0; i < nVertices; ++i)
    {
        pred[i] = new int[nVertices];
        for(int j=0;j<nVertices; j++)
        {
            if(i==j) pred[i][j]=-11;
            else pred[i][j]=-1;
        }

    }
    apsp= new int*[nVertices];
    for(int i = 0; i < nVertices; ++i)
    {
        apsp[i] = new int[nVertices];
        for(int j=0;j< nVertices; j++)
        {
            if(i==j) apsp[i][j]=0;
            else apsp[i][j]=99999;
        }
    }
}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    if(directed){
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	weight[u][v]=w;
	apsp[u][v]=w;
	pred[u][v]=u+1;
    }
	if(!directed) {
        adjList[u].insertItem(v) ;
        adjList[v].insertItem(u) ;
        this->nEdges++ ;
        this->nEdges++ ;
        weight[u][v]=w;
        weight[v][u]=w;
	    apsp[u][v]=w;
	    apsp[v][u]=w;
	    pred[u][v]=u+1;
	    pred[v][u]=v+1;

	}
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(!isEdge(u,v)) return;
    else
    {
        if(!directed){
        adjList[u].removeItem(v) ;
        adjList[v].removeItem(u) ;
        this->nEdges-- ;
        this->nEdges-- ;
        return;
        }
        else if(directed){
            adjList[u].removeItem(v) ;
            this->nEdges-- ;
            return;
        }

    }
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(adjList[u].searchItem(v)!= NULL_VALUE)
    {
        printf("EDGE FOUND\n");
        return true;
    }
    else
    {
        printf("NO EDGE FOUND\n");
        return false;
    }
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

void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {//complete this part
        int u=q.dequeue();
        for(int j=0;j<adjList[u].getLength(); j++)
        {
            int i = adjList[u].getItem(j);
            if(color[i]==WHITE)
            {
                color[i]=GREY;
                dist[i]=dist[u]+1;
                parent[i]=u;
                q.enqueue(i);
            }
        }
        color[u]=BLACK;
        printf("%d->",u);
    }
    printf("\n");
}

int Graph::countConnectedComponent()
{
    int c=0;
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
        dist[i] = 0;
    }
    time = 0;
    for(int i=0; i<nVertices; i++)
    {
        if(color[i] == WHITE)
        {
            dfs_visit(i);
            c++;
        }
    }
    return c;
}

void Graph::dfs()
{
    //write this function
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE;
        parent[i] = -1;
        dist[i] = 0;
    }
    time = 0;
    for(int i=0; i<nVertices; i++)
    {
        if(color[i] == WHITE)
        {
            dfs_visit(i);
        }
    }

}

void Graph::dfs_visit(int u)
{
    time++;
    discoveryTime[u] = time;
    color[u] = GREY;
    for(int i=0; i<adjList[u].getLength(); i++)
    {
        int v = adjList[u].getItem(i);
        if(color[v] == WHITE)
        {
            parent[v] = u;
            dfs_visit(v);
        }
    }
    color[u] = BLACK;
    time++;
    finishTime[u] = time;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    bfs(u);
    return dist[v];

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
void Graph::floydWarshall()
{
    for(int k=0;k<nVertices;k++)
    {
        for(int i=0;i<nVertices;i++)
        {
            for(int j=0;j<nVertices;j++)
            {
                if(apsp[i][j]> apsp[i][k]+apsp[k][j])
                {
                    apsp[i][j]=apsp[i][k]+apsp[k][j];
                    pred[i][j]=pred[k][j];
                }
            }
        }
    }
    for(int i=0;i<nVertices;i++)
    {
        if(apsp[i][i]<0)
        {
            printf("Negative Cycle Detected\n;");
            return;
        }
    }
    printf("All Pair Shortest Paths :\n");
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            printf("%5d  ", apsp[i][j]);
        }
        printf("\n");
    }
    printf("Predecessor Matrix :\n");
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            printf("%5d  ", pred[i][j]);
        }
        printf("\n");
    }
    printf("Negative Cycle : NO");
}

Graph::~Graph()
{
    if(apsp)
    {
        for(int i = 0; i < nVertices; i++)
        {
            delete [] apsp[i];
            apsp[i] = 0;
        }
        delete [] apsp;
    }
	apsp = 0;
    if(pred)
    {
        for(int i = 0; i < nVertices; i++)
        {
            delete [] pred[i];
            pred[i] = 0;
        }
        delete [] pred;
    }
	pred = 0;
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

int main(void)
{
    freopen("input.txt", "r", stdin);

    int  n, u, v, w, m;
    cin >> n;
    cin >> m;

    Graph g(true);
    g.setnVertices(n);

    for(int i=0; i<m; i++)
    {
        cin >> u >> v >> w;
        g.addEdge(u-1, v-1, w);
    }
    freopen("myOutput.txt", "w", stdout);
    g.floydWarshall();
    fclose (stdout);

    return 0;
}


