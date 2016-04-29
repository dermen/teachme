#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<set>

struct Node{
    int data;
    Node* left;
    Node* right;
};


// BORROWED CODE
int _print_t(Node *tree, int is_left, int offset, int depth, char s[20][255])
{
    char b[20];
    int width = 5;

    if (!tree) return 0;

    sprintf(b, "(%03d)", tree->data);

    int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
    int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

#ifdef COMPACT
    for (int i = 0; i < width; i++)
        s[depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[depth - 1][offset + left + width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[depth - 1][offset - width/2 + i] = '-';

        s[depth - 1][offset + left + width/2] = '.';
    }
#else
    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset + left + width + right + width/2] = '+';

    } else if (depth && !is_left) {

        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '-';

        s[2 * depth - 1][offset + left + width/2] = '+';
        s[2 * depth - 1][offset - width/2 - 1] = '+';
    }
#endif

    return left + width + right;
}

int print_t(Node *tree)
{
    char s[20][255];
    for (int i = 0; i < 20; i++)
        sprintf(s[i], "%80s", " ");

    _print_t(tree, 0, 0, 0, s);

    for (int i = 0; i < 20; i++)
        printf("%s\n", s[i]);
}
// END BORROWED CODE


// root of binary tree

Node* makeNewNode(int x){
    Node * newNode = new Node();
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->data = x;
    return newNode;
}

Node* Insert(Node * p, int x){
    //#Node* newNode = makeNewNode(x);
    if (p == NULL){
        p = makeNewNode(x);
        return p;
    }
    if (p->data > x)
        p->left = Insert(  p->left, x);
    else if (p->data < x)
        p->right = Insert( p->right, x); 
}

Node * randomBinaryTree( Node * p , int leafNumber  ){
    srand (time(NULL));
    std::set<int> numbers;
    for(int i=0; i < 15; i++){
        int num = rand()%100 + 1;
        while ( numbers.find(num) != numbers.end() )
            num = rand()%100 + 1;
        numbers.insert( num);
        p = Insert( p, num);
    }
    return p;
    
}


Node * findMinNode( Node* p){
    Node* temp = p;
    while ( temp->left != NULL)
        temp = temp->left;
    return temp;
}

Node* deleteNode(Node* p, int x){
    if( p == NULL){
        return NULL;
    }
    if (p ->data < x)
       p->right = deleteNode( p->right, x);
    else if (p->data > x)
       p->left = deleteNode( p->left, x); 

    else{ // found the node!
        // case 1: no left or right child
        if( p->right == NULL & p->left == NULL ){
            delete p;
            p = NULL;
            return p;
        }
        // CASE 2: only left child
        else if (p->right == NULL ){
            Node * temp = p;
            p = p->left;
            delete  temp;
            return p;
        }
        // CASE 3: only right child
        else if( p->left == NULL){
            Node * temp = p;
            p = p->right;
            delete temp;
            return p;
        }
        else { // has two children
            Node* temp= findMinNode(p->right);
            p->data = temp->data;
            p->right = deleteNode(p->right ,temp->data);
            return p;
        }
    }
}

int main(){
    Node* root = NULL;
    root = randomBinaryTree(root, 15); 
    std::cout << "\n\n  Here is the randomized binary tree:\n\n"; 
    print_t(root);
    
    int num;
    while(1){
        std::cout << "  Enter a number to delete (or 0 to stop):";
        std::cin >> num;
        if (num==0) break;
        std::cout << "\n  Deleting value " << num << std::endl;

        root = deleteNode(root,num);
        print_t(root);
    }
}




