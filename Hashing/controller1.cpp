#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>
#include "customProb.cpp"
#include "dhash.cpp"
#include "chaining1.cpp"
using namespace std;

string wordGenerator(int n)
{
    string s="";
    for(int i=0;i<n;i++)
    {
        char ch=(abs(rand())%26)+'a';
        s+=ch;
    }
    return s;
}


int main()
{

    int b;
    scanf("%d",&b);
    hashTable H1(b);
    hashTable H2(b);

    openAddressing A(2*b);
    openAddressing B(2*b);

    openAddressing2 P(2*b);
    openAddressing2 R(2*b);
    int d=0;

    for(int i=1;i<=b;i++)
    {
        string s= wordGenerator(7);
        H1.insertkey1(s);
        H2.insertkey2(s);
        A.insert1(s);
        B.insert2(s);

        P.insert1(s);
        R.insert2(s);
    }

    printf("\t\t\t\tHash 1\t\t\t");
    printf("Hash 2\n\n");
    printf("Chaining method:\t");
    printf("No Of Coll: %d\t", H1.No_of_collision);
    printf("No Of Coll: %d\n\n", H2.No_of_collision);
    H1.gethit1();
    H2.gethit1();
    printf("\t\t\tAvg Hit: %f\t",H1.Avg_hits );
    printf("Avg Hit: %f\n\n", H1.Avg_hits);

    printf("Double Hashing:\t\t");
    //printf("Hash 1\t\t\t");
    //printf("Hash 2\n\n");
    printf("No Of Coll: %d\t", A.ncoll);
    printf("No Of Coll: %d\n\n", B.ncoll);
    float r=B.avgHit2();
    float s=A.avgHit1();

    printf("\t\t\tAvg Hit: %f\t", s);
    printf("Avg Hit: %f\n\n", r);

    printf("Custom Probing:\t\t");
    //printf("Hash 1\t\t\t");
    //printf("Hash 2\n\n");
    printf("No Of Coll: %d\t", P.ncoll);
    printf("No Of Coll: %d\n\n", R.ncoll);

    float y=R.avgHit2();
    float x=P.avgHit1();
    printf("\t\t\tAvg Hit: %f\t", x);
    printf("Avg Hit: %f\n\n", y);


}
