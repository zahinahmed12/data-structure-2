#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<bits/stdc++.h>
#include "vc22.cpp"

using namespace std;

int main()
{
    srand(unsigned(time(0)));
    printf("METHOD 1:\n\n");
    Graph g1,g2,g3,g4;
    Graph g12, g13,g14,g15;
    Graph g22, g23,g24,g25;
    Graph g32, g33,g34,g35;
    Graph g42, g43,g44,g45;
    Graph g21, g222, g232, g242;
    int a,b,c,d;
    int max=-9999999,min=9999999;
    float avg;
    int n,m,s=0;
    int arr[5];
    ifstream fin;
    fin.open("graph 1.txt",ios::in);
    if(fin>> n>> m)
    {
        g1.setnVertices(n);
        g12.setnVertices(n);
        g13.setnVertices(n);
        g14.setnVertices(n);
        g15.setnVertices(n);

        g21.setnVertices(n);
        int u,v;
        while(fin >>u>>v)
        {
            g1.addEdge(u-1,v-1);
            g12.addEdge(u-1,v-1);
            g13.addEdge(u-1,v-1);
            g14.addEdge(u-1,v-1);
            g15.addEdge(u-1,v-1);

            g21.addEdge(u-1,v-1);
        }
    }
    /*Graph g12, g13,g14,g15;
    g12.setnVertices(n);
    g13.setnVertices(n);
    g14.setnVertices(n);
    g15.setnVertices(n);
    g12=g1;
    g13=g1;
    g14=g1;
    g15=g1;*/
    /*for(int i=0;i<5;i++)
    {
       arr[i]=g1.vertexCover1();
       s+=arr[i];
    }*/
    arr[0]=g1.vertexCover1();
    s+=arr[0];
    arr[1]=g12.vertexCover1();
    s+=arr[1];
    arr[2]=g13.vertexCover1();
    s+=arr[2];
    arr[3]=g14.vertexCover1();
    s+=arr[3];
    arr[4]=g15.vertexCover1();
    s+=arr[4];
    avg=s/5;
    for(int i=0;i<5;i++)
    {
       if(min>arr[i])
       {
           min=arr[i];
       }
       if(max<arr[i])
       {
           max=arr[i];
       }
   }
   a=g21.vertexCover2();
   printf("GRAPH 1-> BEST: %d, WORST: %d, AVG: %0.3f\n",min,max,avg);
   fin.close();
   min=9999999;
   max=-9999999;
   s=0;

    fin.open("graph 2.txt",ios::in);
    if(fin>> n>> m)
    {
        g2.setnVertices(n);
        g22.setnVertices(n);
        g23.setnVertices(n);
        g24.setnVertices(n);
        g25.setnVertices(n);

        g222.setnVertices(n);
        int u,v;
        while(fin >>u>>v)
        {
            g2.addEdge(u-1,v-1);
            g22.addEdge(u-1,v-1);
            g23.addEdge(u-1,v-1);
            g24.addEdge(u-1,v-1);
            g25.addEdge(u-1,v-1);

            g222.addEdge(u-1,v-1);
        }
    }
    arr[0]=g2.vertexCover1();
    //s+=arr[0];
    arr[1]=g22.vertexCover1();
    //s+=arr[1];
    arr[2]=g23.vertexCover1();
    //s+=arr[2];
    arr[3]=g24.vertexCover1();
    //s+=arr[3];
    arr[4]=g25.vertexCover1();
    //s+=arr[4];
    for(int i=0;i<5;i++)
    {
       //arr[i]=g2.vertexCover1();
       s+=arr[i];
    }
    avg=s/5;
    for(int i=0;i<5;i++)
    {
       if(min>arr[i])
       {
           min=arr[i];
       }
       if(max<arr[i])
       {
           max=arr[i];
       }
   }
   b=g222.vertexCover2();
   printf("GRAPH 2-> BEST: %d, WORST: %d, AVG: %0.3f\n",min,max,avg);
   fin.close();

   min=9999999;
   max=-9999999;
   s=0;

    fin.open("graph 3.txt",ios::in);
    if(fin>> n>> m)
    {
        g3.setnVertices(n);
        g32.setnVertices(n);
        g33.setnVertices(n);
        g34.setnVertices(n);
        g35.setnVertices(n);

        g232.setnVertices(n);
        int u,v;
        while(fin >>u>>v)
        {
            g3.addEdge(u-1,v-1);
            g32.addEdge(u-1,v-1);
            g33.addEdge(u-1,v-1);
            g34.addEdge(u-1,v-1);
            g35.addEdge(u-1,v-1);

            g232.addEdge(u-1,v-1);
        }
    }
    arr[0]=g3.vertexCover1();
    //s+=arr[0];
    arr[1]=g32.vertexCover1();
    //s+=arr[1];
    arr[2]=g33.vertexCover1();
    //s+=arr[2];
    arr[3]=g34.vertexCover1();
    //s+=arr[3];
    arr[4]=g35.vertexCover1();
    //s+=arr[4];
    for(int i=0;i<5;i++)
    {
       //arr[i]=g3.vertexCover1();
       s+=arr[i];
    }
    avg=s/5;
    for(int i=0;i<5;i++)
    {
       if(min>arr[i])
       {
           min=arr[i];
       }
       if(max<arr[i])
       {
           max=arr[i];
       }
   }
   c=g232.vertexCover2();
   printf("GRAPH 3-> BEST: %d, WORST: %d, AVG: %0.3f\n",min,max,avg);
   fin.close();

   min=9999999;
   max=-9999999;
   s=0;

    fin.open("graph 4.txt",ios::in);
    if(fin>> n>> m)
    {
        g4.setnVertices(n);
        g42.setnVertices(n);
        g43.setnVertices(n);
        g44.setnVertices(n);
        g45.setnVertices(n);

        g242.setnVertices(n);
        int u,v;
        while(fin >>u>>v)
        {
            g4.addEdge(u-1,v-1);
            g42.addEdge(u-1,v-1);
            g43.addEdge(u-1,v-1);
            g44.addEdge(u-1,v-1);
            g45.addEdge(u-1,v-1);

            g242.addEdge(u-1,v-1);
        }
    }
    arr[0]=g4.vertexCover1();
   // s+=arr[0];
    arr[1]=g42.vertexCover1();
    //s+=arr[1];
    arr[2]=g43.vertexCover1();
    //s+=arr[2];
    arr[3]=g44.vertexCover1();
    //s+=arr[3];
    arr[4]=g45.vertexCover1();
    //s+=arr[4];
    for(int i=0;i<5;i++)
    {
       //arr[i]=g4.vertexCover1();
       s+=arr[i];
    }
    avg=s/5;
    for(int i=0;i<5;i++)
    {
       if(min>arr[i])
       {
           min=arr[i];
       }
       if(max<arr[i])
       {
           max=arr[i];
       }
   }
   d=g242.vertexCover2();
   printf("GRAPH 4-> BEST: %d, WORST: %d, AVG: %0.3f\n",min,max,avg);
   fin.close();
   printf("\nMETHOD 2:\n\n");

   printf("GRAPH 1: OPTIMAL RES: 420 --- APPROX. RES: %d\n",a);
   printf("GRAPH 2: OPTIMAL RES: 560 --- APPROX. RES: %d\n",b);
   printf("GRAPH 3: OPTIMAL RES: 720 --- APPROX. RES: %d\n",c);
   printf("GRAPH 4: OPTIMAL RES: 900 --- APPROX. RES: %d\n",d);

   printf("\nTHE NEWLY CONSTRUCTED GRAPH THAT GIVES THE WORST:\n\n");

   fin.open("new graph.txt",ios::in);
   Graph xx;
   if(fin>> n>> m)
    {
        xx.setnVertices(n);
        int u,v;
        while(fin >>u>>v)
        {
            xx.addEdge(u-1,v-1);
        }
    }
    printf("OPTIMAL SHOULD BE: %d -- METHOD 1 : %d\n",n/2,xx.vertexCover1());
    printf("OPTIMAL SHOULD BE: %d -- METHOD 2 : %d\n",n/2,xx.vertexCover2());
    fin.close();


}

