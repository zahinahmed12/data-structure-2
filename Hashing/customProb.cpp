#include<bits/stdc++.h>
#include<stdio.h>

#define C1 41
#define C2 59

using namespace std;
const int m= 1e9+9;

class hashNode
{
public:
    string word;
    int val;
   /* hashNode()
    {
        //word=;
        val=-1;
    }*/
};

class openAddressing2
{
public:
    int tsize;
    int element;
    int ncoll=0;
    int ins=0;
    float hit=0.0;
    hashNode *arr1,*arr2;

    openAddressing2(int cap)
    {
        tsize=cap;
        arr1=new hashNode[tsize];
        for(int i=0; i<tsize; i++)
        {
            arr1[i].val=-1;
        }
        //arr2=new hashNode[tsize];
        element=0;
    }

    long long hashF1(string str )
    {
        const int p=31;
        long long hashVal=0;
        long long powerOfP=1;

        for(int i=0;i<str.size();i++)
        {
            hashVal=(hashVal + (str[i]-'a'+1)* powerOfP) % m;
            powerOfP=(powerOfP * p)%m;
        }
        return hashVal;
    }

    int auxHash(string str)
    {
        int  hashV = 0;
        string s=str;

        for (int i = 0; i < s.size(); i++)
        {
            hashV ^= s[i];
        }
        //printf("%d \n",hashV);

        return hashV =hashV % tsize ;
    }

    long long hashF2(string str )
    {
        const int p=37;
        long long hashVal=0;
        long long powerOfP=1;

        for(int i=0;i<str.size();i++)
        {
            hashVal=(hashVal + (str[i]-'a'+1)* powerOfP) % m;
            powerOfP=(powerOfP * p)%m;
        }
        return hashVal;
    }

    void insert1(string str)
    {
        if(element==tsize)
        {
            return;
        }
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].word==str)
        {
            //printf("im here1");
            return;
        }
        if(arr1[pIdx].val == -1)
        {
            //printf("%d ",pIdx);
            //printf("here lol");
            ins++;
            arr1[pIdx].word=str;
            arr1[pIdx].val=ins;
        }
        else
        {
            int sIdx=hashF2(str) % tsize;
            int i=0;
            while(1)
            {
                int New = (pIdx + C1*i*sIdx + C2* i*i)% tsize;
                if(arr1[New].word==str)
                {
                    //printf("here 2");
                    return;
                }
                ncoll++;
                if(arr1[New].val==-1)
                {
                    //printf("here lol2");
                    ins++;
                    arr1[New].val=ins;
                    arr1[New].word=str;
                    break;
                }
                i++;
            }

        }
        element++;
        //printf("%d\n",element);

    }

    void insert2(string str)
    {
        if(element==tsize)
        {
            return;
        }
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].word==str)
        {
            //printf("im here1");
            return;
        }
        if(arr1[pIdx].val == -1)
        {
            //printf("%d ",pIdx);
            //printf("here lol");
            ins++;
            arr1[pIdx].word=str;
            arr1[pIdx].val=ins;
        }
        else
        {
            //int sIdx=hashF2(str) % tsize;
            int sIdx=auxHash(str) % tsize;
            int i=0;
            while(1)
            {
                int New = (pIdx + C1*i*sIdx + C2* i*i)% tsize;
                if(arr1[New].word==str)
                {
                    //printf("here 2");
                    return;
                }
                ncoll++;
                if(arr1[New].val==-1)
                {
                    //printf("here lol2");
                    ins++;
                    arr1[New].val=ins;
                    arr1[New].word=str;
                    break;
                }
                i++;
            }

        }
        element++;
        //printf("%d\n",element);

    }

    int search1(string str)
    {
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].val == -1)
        {
            return 0;
        }
        hit=hit+1.0;
        if(arr1[pIdx].word==str)
        {
            return arr1[pIdx].val;
        }
        else
        {
            int sIdx=hashF2(str) % tsize;
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                hit=hit+1.0;
                if(arr1[New].word==str)
                {
                    return arr1[New].val;
                }
                if(arr1[New].val==-1)
                {
                    break;
                }
                i++;
            }
            return 0;

        }
    }
    int search2(string str)
    {
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].val == -1)
        {
            return 0;
        }
        hit=hit+1.0;
        if(arr1[pIdx].word==str)
        {

            return arr1[pIdx].val;
        }
        else
        {
            int sIdx=auxHash(str);
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                hit=hit+1.0;
                if(arr1[New].word==str)
                {
                    return arr1[New].val;
                }
                if(arr1[New].val==-1)
                {
                    break;
                }
                i++;
            }
            return 0;

        }
    }

    void delete1(string str)
    {
        int pIdx= hashF1(str) % tsize;

        if(arr1[pIdx].val == -1)
        {
            return;
        }
        if(arr1[pIdx].word==str)
        {
            arr1[pIdx].val=-1;
        }
        else
        {
            int sIdx=hashF2(str) % tsize;
            int i=0;
            while(1)
            {
                int New = (pIdx + i*sIdx)% tsize;
                if(arr1[New].word==str)
                {
                    arr1[New].val=-1;
                }
                if(arr1[New].val==-1)
                {
                    break;
                }
                i++;
            }
            //return 0;

        }
    }
    void print1()
    {
        for(int i=0;i<tsize;i++)
        {

            cout<<arr1[i].word<<" ";
            cout<<arr1[i].val<<endl;
        }
    }

     float avgHit1()
     {
         int c=0;
         for(int i=0;i<tsize;i++)
         {
             if(arr1[i].val!=-1)
             {
                 c++;
                 search1(arr1[i].word);
                 if(c==1000) break;
             }
         }
         return hit/1000;
     }
     float avgHit2()
     {
         int c=0;
         for(int i=0;i<tsize;i++)
         {
             if(arr1[i].val!=-1)
             {
                 c++;
                 search2(arr1[i].word);
                 if(c==1000) break;
             }
         }
         return hit/1000;
     }






};

/*int main()
{
    int b;
    scanf("%d",&b);
    openAddressing2 P(1.1*b);
    openAddressing2 R(1.1*b);

    for(int i=1;i<=b;i++)
    {
        string s= wordGenerator(7);

        P.insert1(s);
        R.insert2(s);

    }
    //printf("\n%d \n", A.ncoll);
    /*A.insert1("ancient");
    printf("hi2\n");
    A.insert1("angryyy");
    printf("hi3\n");
    A.insert1("blueeee");
    printf("hi4\n");
    A.insert1("zaheeen");
    printf("hi5\n");
    //A.print1();
    printf("Custom Probing:\n\n");
    printf("Hash 1\t\t\t");
    printf("Hash 2\n\n");
    printf("No Of Coll: %d\t", P.ncoll);
    printf("No Of Coll: %d\n\n", R.ncoll);
}*/

