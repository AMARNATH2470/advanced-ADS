#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int val, degree;
    Node *parent, *child, *sibling;
};
Node *root = NULL;

int binomialLink(Node *h1, Node *h2)
{
    h1->parent = h2;
    h1->sibling = h2->child;
    h2->child = h1;
    h2->degree = h2->degree + 1;
}

Node *createNode(int n)
{
    Node *new_node = new Node;
    new_node->val = n;
    new_node->parent = NULL;
    new_node->sibling = NULL;
    new_node->child = NULL;
    new_node->degree = 0;
    return new_node;
}

Node *mergeBHeaps(Node *h1, Node *h2)
{
    if (h1 == NULL)
        return h2;
    if (h2 == NULL)
        return h1;
    Node *res = NULL;

    if (h1->degree <= h2->degree)
        res = h1;

    else if (h1->degree > h2->degree)
        res = h2;
    while (h1 != NULL && h2 != NULL)
    {
        if (h1->degree < h2->degree)
            h1 = h1->sibling;
        else if (h1->degree == h2->degree)
        {
            Node *sib = h1->sibling;
            h1->sibling = h2;
            h1 = sib;
        }
        else
        {
            Node *sib = h2->sibling;
            h2->sibling = h1;
            h2 = sib;
        }
    }
    return res;
}

Node *unionBHeaps(Node *h1, Node *h2)
{
    if (h1 == NULL && h2 == NULL)
       return NULL;
    Node *res = mergeBHeaps(h1, h2);
    Node *prev = NULL, *curr = res,
         *next = curr->sibling;
    while (next != NULL)
    {
        if ((curr->degree != next->degree) ||
                ((next->sibling != NULL) &&
                 (next->sibling)->degree ==
                 curr->degree))
        {
            prev = curr;
            curr = next;
        }

        else
        {
            if (curr->val <= next->val)
            {
                curr->sibling = next->sibling;
                binomialLink(next, curr);
            }
            else
            {
                if (prev == NULL)
                    res = next;
                else
                    prev->sibling = next;
                binomialLink(curr, next);
                curr = next;
            }
        }
        next = curr->sibling;
    }
    return res;
}

void binomialHeapInsert(int x)
{
    root = unionBHeaps(root, createNode(x));
}

void display(Node *h)
{
    while (h)
    {
        cout << h->val << " ";
        display(h->child);
        h = h->sibling;
    }
}

int revertList(Node *h)
{
    if (h->sibling != NULL)
    {
        revertList(h->sibling);
        (h->sibling)->sibling = h;
    }
    else
        root = h;
}
Node *findNode(Node *h, int val)
{
    if (h == NULL)
      return NULL;
    if (h->val == val)
        return h;
    Node *res = findNode(h->child, val);
    if (res != NULL)
       return res;

    return findNode(h->sibling, val);
}
int main()
{
   int n,temp,del;
   cout<<"Enter no of elements in the heap"<<endl;
   cin>>n;
   cout<<"Enter elements"<<endl;
   for(int i=0;i<n;i++)
   {
    cin>>temp;
    binomialHeapInsert(temp);
    }
    cout << "The heap is:\n";
    display(root);
    cout<<endl;

    return 0;
}
