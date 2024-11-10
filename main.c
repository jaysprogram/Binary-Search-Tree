//COP 3502C Assignment 5 
//This program is written by: Reyjay Collazo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 26

typedef struct Node{

    struct Node * left;
    struct Node * right;
    char name[MAX_LEN];
    int fine;

}Node;

// create a new Node
Node * createNode(char * name, int value){

    Node * newNode = malloc(sizeof(Node));
    if(newNode == NULL){
        printf("Node allocation fail in create Node.");
        abort();
    }
    // assign new values
    strcpy(newNode->name,name);
    newNode->fine = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// insert Node, if already exist add to fine
Node * addFine(Node * root,char * name,int value, int * depth){
    // Base case
    if( root == NULL){
        printf("Tree is empty.\n");
        Node * newRoot = createNode(name, value);
        return newRoot;
    }

    int ranking = strcmp(name,root->name); 

    // go right if greater
    if(ranking > 0)
        if(root->right == NULL){ // check if its empty first
            root->right = createNode(name, value);
        }
        else{ //traverse towards the right
            root->right = addFine(root->right, name, value, depth);
        }
    
    // go left is less than
    if(ranking < 0)
        if(root->left == NULL){ // check if its empty first
            root->left = createNode(name, value);
        }
        else{ //traverse towards the right
            root->left = addFine(root->left, name, value,depth);
        }
    // increase fine if equal
    if(ranking == 0){
        root->fine += value;
    }

    return root;
        
}

Node * search(Node * root, char * name){
    if( root == NULL)
        return NULL;

    int ranking = strcmp(name,root->name);

    // go right if greater 
    if(ranking > 0)
        return search(root->right, name);
    // go left is less than
    if(ranking < 0)
        return search(root->left, name);
    // return node if found
    if(ranking == 0)
        return root;
    
    // if not found
    printf("Not found.\n");
    return NULL;

}



void printInOrder(Node * root){
    if( root == NULL)
        return;
    printInOrder(root->left);
    printf("%s:%d, ",root->name,root->fine);
    printInOrder(root->right);
}


int main(){
    // init empty tree
    Node * mainRoot = NULL;
    int depth = 0;
    // test code
    mainRoot = addFine(mainRoot, "jay", 500,&depth);
    mainRoot = addFine(mainRoot, "amy", 300,&depth);
    mainRoot = addFine(mainRoot, "zoe", 200,&depth);
    mainRoot = addFine(mainRoot, "mike", 150,&depth);
    mainRoot = addFine(mainRoot, "sara", 250,&depth);
    mainRoot = addFine(mainRoot, "tom", 100,&depth);
    mainRoot = addFine(mainRoot, "bob", 400,&depth);
    mainRoot = addFine(mainRoot, "bob", 400,&depth);
    
    printInOrder(mainRoot);








    //
    // amount to process
    int qeuries;
    scanf("%d",&qeuries);

    for (int i = 0; i < qeuries; i++){
        char command[MAX_LEN];
        char name[MAX_LEN];
        scanf("%s",command);
            if(strcmp(command, "add") == 0){
                int fine;
                scanf("%s %d",name, &fine);
                // function call
            } else if(strcmp(command, "deduct") == 0){
                int fine;
                scanf("%s %d",name,&fine);
                //function call
                
            } else if(strcmp(command, "search") == 0){
                scanf("%s", name);
                //function call
                
            } else if(strcmp(command, "average") == 0){
                //function call
                
            } else if(strcmp(command, "height_balance") == 0){
                //function call
                
            } else {
                scanf("%s", name);
                
                
            }
        
    }



}