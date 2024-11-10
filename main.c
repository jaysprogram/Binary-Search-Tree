//COP 3502C Assignment 5 
//This program is written by: Reyjay Collazo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 26

typedef struct Node{

    struct Node * left;
    struct Node * right;
    char * name[MAX_LEN];
    int fine;

}Node;

Node * search(Node * root, char * name){

}

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
            Node * newNode = createNode(name, value);
            root->right = newNode;
            return newNode;
        }
        else{ //traverse towards the right
            return add(root->right, name, value);
        }
    
    // go left is less than
    if(ranking < 0)
        if(root->left == NULL){ // check if its empty first
            Node * newNode = createNode(name, value);
            root->left = newNode;
            return newNode;
        }
        else{ //traverse towards the right
            return add(root->left, name, value);
        }
    // increase fine if equal
    if(ranking == 0){
        root->fine += value;
        return root;
    }
        
}


int main(){
    Node * mainRoot = NULL;
    // amount to process
    // test code










    //
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
                
            } else if(strcmp(command, "average") == 0){
                
            } else if(strcmp(command, "height_balance") == 0){
                
            } else {
                
                
            }
        
    }



}