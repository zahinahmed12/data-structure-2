#include<iostream>
#include<stdio.h>
#include<bits/stdc++.h>
#include<vector>
#include<math.h>
#define MAX_ELEMENT 9999999
#define MIN_ELEMENT -9999999

using namespace std;

class splayTreeNode
{
public:
    int key;
    splayTreeNode *left, *right;
};

class splayTree
{
public:

splayTreeNode* root;

void Search(int key)
{
    root=Splay(root, key);
    if(root->key==key) printf("FOUND\n");
    else printf("NOT FOUND\n");
    printNode(root);
}

splayTreeNode* Join(splayTreeNode* ltree, splayTreeNode* rtree)
{
    if(ltree)
    {
        //int m=maxElement(ltree);
        ltree=Splay(ltree,MAX_ELEMENT);
        ltree->right=rtree;
        return ltree;
    }
    else
    {
        return rtree;
    }
}

void Delete2(int n)
{
    root=Splay(root,n);

    if(root->key==n)
    {
        //return root;
        splayTreeNode *lt;
        splayTreeNode *rt;
        lt=root->left;
        rt=root->right;
        root=Join(lt, rt);
    //return root;
    }

}

splayTreeNode* newNode(int data)
{
   splayTreeNode *node= new splayTreeNode();
   node->key=data;
   node->left=NULL;
   node->right=NULL;
   return node;
}

void Insertion(int n)
{
    if(!root)
    {
        root=newNode(n);
        return ;
    }
    root=Splay(root,n);

    if(root->key!=n)
    {
        splayTreeNode *treeNode=newNode(n);

        if(root->key <=n)
        {
            treeNode->right=root->right;
            root->right=NULL;
            treeNode->left=root;
            root=treeNode;
        }
        else
        {
            treeNode->left=root->left;
            root->left=NULL;
            treeNode->right=root;
            root=treeNode;
        }
    }
}

splayTreeNode* InsertDuplicateItem(splayTreeNode *a,int n)
{
    if (a == NULL)
    {
       root= newNode(n);
       return root;
    }
    if (a->key >= n)
    {
        a->left= InsertDuplicateItem(a->left,n);
    }
    else if (a->key<n)
    {
        a->right=InsertDuplicateItem(a->right, n);
    }
    root=Splay(a,n);
    return root;
}

splayTreeNode* Splay(splayTreeNode* node, int k)
{
    if (node == NULL || node->key == k)
    {
         return node;
    }

    if (node->key > k)
    {
        if (node->left == NULL)
        {
              return node;
        }
        if (node->left->key < k)
        {
            node->left->right = Splay(node->left->right, k);

            if (node->left->right != NULL)
            {
                node->left = leftRotation(node->left);
            }
        }
        else if (node->left->key > k)
        {
            node->left->left = Splay(node->left->left, k);

            node=rightRotation(node);
        }
        if(node->left == NULL)
        {
            return node;
        }
        else
        {
            return rightRotation(node);
        }
    }
    else
    {
        if (node->right == NULL)
        {
             return node;
        }
        if (node->right->key < k)
        {
            node->right->right = Splay(node->right->right, k);
            node = leftRotation(node);
        }
        else if (node->right->key > k)
        {
            node->right->left = Splay(node->right->left, k);

            if (node->right->left != NULL)
            {
                 node->right = rightRotation(node->right);
            }
        }
         if(node->right == NULL)
         {
             return node;
         }
         else
         {
             return leftRotation(node);
         }
    }
}

void SplitTree(splayTreeNode **l, splayTreeNode **r,int n)
{
    if(root)
    {
        if(root->left==NULL && root->right==NULL)
        {
            *l=NULL;
            *r=NULL;
            return ;
        }

        root=Splay(root,n);

        *l=root;
        *r=root->right;
        (*l)->right=NULL;

    }
    else
    {
        *l=NULL;
        *r=NULL;
    }
}

void InsertItem(int k)
{
    if (root == NULL)
    {
        root=newNode(k);
        return;
    }

    splayTreeNode *l=NULL;
    splayTreeNode *r=NULL;

        root=Splay(root,k);
       // printNode(root);
        l=newNode(root->key);

        if(root->right) r= newNode(root->right->key);
        else r=NULL;

        if(l)
        {
            if(root->left) l->left=root->left;
            else l->left=NULL;

            l->right=NULL;
        }
        else l=NULL;

        if(r)
        {
            if(root->right->right) r->right=root->right->right;
            else r->right=NULL;

            if(root->right->left) r->left=root->right->left;
            else r->left=NULL;
        }

    if(root->key != k)
    {
        splayTreeNode* treeNode  = newNode(k);

        if(l->left==NULL && r==NULL)
        {
            if(root->key> treeNode->key)
            {
                treeNode->right=l;
                root=treeNode;
                return ;
            }
            else
            {
                treeNode->left=l;
                root=treeNode;
                return;
            }
        }
        if(root->key > k)
        {
            if(l->left==NULL)
            {
                l->right=r;
                treeNode->right=l;
                root=treeNode;
                return;
            }

            splayTreeNode *temp, *rr;
            temp=Splay(l->left,MAX_ELEMENT);
            root=Splay(root,temp->key);

            rr=root->right;
            root->right=NULL;
            treeNode->left=root;
            treeNode->right=rr;
            root=treeNode;
        }
        else
        {
            if(l->left==NULL)
            {
                //splayTreeNode *temp;
                //temp= Splay(r,MIN_ELEMENT);
                r = Splay(r,MIN_ELEMENT);
                treeNode->right=r;
               // root->right=NULL;
                treeNode->left=l;
                root=treeNode;
                return;
            }
            //root->right=NULL;
            treeNode->left=l;
            treeNode->right=r;
            root=treeNode;
        }
    }
}

splayTreeNode* leftRotation(splayTreeNode *x)
{
    splayTreeNode *temp = x->right;
    x->right = temp->left;
    temp->left = x;
    return temp;

}

splayTreeNode* rightRotation(splayTreeNode *y)
{
    splayTreeNode *temp = y->left;
    y->left = temp->right;
    temp->right = y;
    return temp;
}

    void printNode (splayTreeNode* root)
    {
        int maxlevel = maxLevel(root) ;
        vector<splayTreeNode*> nodes ;
        nodes.push_back(root) ;
        printNodeInternal(nodes,1,maxlevel) ;
    }

    void printNodeInternal(vector<splayTreeNode*> nodes , int level, int maxLevel)
    {
        if( nodes.size()== 0 || isAllElementsNull(nodes) ) return ;
        int floor = maxLevel - level;
        int endgeLines =(int) pow(2, (max(floor - 1, 0)));
        int firstSpaces =  (int)pow(2, (floor)) - 1;
        int betweenSpaces = (int)pow(2, (floor + 1)) - 1;

        printWhitespaces(firstSpaces);

        vector<splayTreeNode*> newNodes ;

        for(int z=0; z<nodes.size(); z++)
        {
            if(nodes[z]!=NULL)
            {
                cout << nodes[z]->key ;
                newNodes.push_back(nodes[z]->left);
                newNodes.push_back(nodes[z]->right) ;
            }
            else
            {
                newNodes.push_back(NULL);
                newNodes.push_back(NULL) ;
                cout << " " ;
            }
            printWhitespaces(betweenSpaces);
        }
        cout<< "\n" ;

        for (int i = 1; i <= endgeLines; i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                printWhitespaces(firstSpaces - i);

                if (nodes.at(j) == NULL) {
                    printWhitespaces(endgeLines + endgeLines + i + 1);
                    continue;
                }
                if (nodes.at(j)->left != NULL)
                    printf("/");
                else
                    printWhitespaces(1);

                printWhitespaces(i + i - 1);

                if (nodes.at(j)->right != NULL)
                    printf("\\");
                else
                    printWhitespaces(1);

                printWhitespaces(endgeLines + endgeLines - i);

            }
            cout << "\n";
        }
        printNodeInternal(newNodes, level + 1, maxLevel);
    }

    int maxLevel(splayTreeNode* root)
    {
        if(root== NULL)
        {
            return 0 ;
        }
        return max(maxLevel(root->left),maxLevel(root->right)) + 1 ;
    }
    void printWhitespaces(int count) {
        for (int i = 0; i < count; i++)
            printf(" ");
    }

    bool isAllElementsNull(vector<splayTreeNode*> list)
    {
        for(unsigned int i = 0 ; i < list.size() ; i++)
        {
            if(list[i]!= NULL)
                return false ;
        }
        return true ;
    }

};

int main()
{
    splayTree t;
    t.root=NULL;

    printf("CHOOSE AN OPERATION\n");
    while(1)
    {
        printf("1.Insert  2.Search  3.Print  4.Delete  5.Exit\n");
        int x;
        scanf("%d",&x);
        if(x==1)
        {
            printf("Enter the value:\n");
            int n;
            scanf("%d",&n);
            //t.InsertItem(n);
            t.Insertion(n);
            //splayTreeNode *temp=t.InsertDuplicateItem(t.root,n);
        }
        else if(x==2)
        {
            printf("Enter the value:\n");
            int n;
            scanf("%d",&n);
            t.Search(n);
        }
        else if(x==3)
        {
            t.printNode(t.root);
        }
        else if(x==4)
        {
            printf("Enter the value:\n");
            int n;
            scanf("%d",&n);
            //splayTreeNode *node;
            t.Delete2(n);
        }
        else if(x==5)
        {
            return 0;
        }
    }
}
