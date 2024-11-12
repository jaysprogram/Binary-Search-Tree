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
Node * addFine(Node * root,char * name,int value){
    // Base case
    if( root == NULL){
        printf("Tree is empty.\n");
        Node * newRoot = createNode(name, value);
        return newRoot;
    }

    int ranking = strcmp(name,root->name); 

    // go right if greater
    if(ranking > 0){
    
        if(root->right == NULL){ // check if its empty first
            root->right = createNode(name, value);
    
        }
        else{ //traverse towards the right
            root->right = addFine(root->right, name, value);
        }
    }
    // go left is less than
    if(ranking < 0){
        
        if(root->left == NULL){ // check if its empty first
            root->left = createNode(name, value);
        }
        else{ //traverse towards the right
            root->left = addFine(root->left, name, value);
        }
    }
    // increase fine if equal
    if(ranking == 0){
        root->fine += value;
    }

    return root;

        
}

// deduct from fine or delete
Node * deduct(Node * root, char * name, int deductFine){

}

Node * delete(Node){
    
}

// search for a node with a given name
Node * search(Node * root, char * name, int *depth){
    if( root == NULL)
        return NULL;

    int ranking = strcmp(name,root->name);

    // return node if found
    if(ranking == 0)
        return root;

    (*depth)++;
    // go right if greater 
    if(ranking > 0){
        return search(root->right, name,depth);
    }
    // go left is less than
    else{
        return search(root->left, name, depth);
    }
    
    
    // if not found
    return NULL;
}

//helper function for average
void sumAndCount(Node * root,int * sum, int * amount){
    if(root == NULL) {
        return;
    }
    // add to sum and increment count
    (*sum) += root->fine;
    (*amount)++;

    //traverse left and right
    sumAndCount(root->left,sum,amount);
    sumAndCount(root->right,sum,amount);
}

double average(Node * root){
    int sum = 0;
    int amount = 0;

    sumAndCount(root,&sum,&amount);

    if(amount == 0)
        return 0;

    return (double)sum /amount;   

}


int calcHeight(Node * root){
    // base case
    if(root == NULL)
        return -1; // return -1 since we are only count edges 
    
    int leftHeight = calcHeight(root->left);
    int rightHeight = calcHeight(root->right);

    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void calcBelow(Node * root, char * name, int * total){
    // base case
    if(root == NULL)
        return;
    
    // recursivly check the tree
    calcBelow(root->left, name,total);

    if(strcmp(name,root->name) >= 0){
        *total += root->fine;
        // only check right if root is greater
        calcBelow(root->right, name,total);
    }
}

void printInOrder(Node * root){
    if( root == NULL)
        return;
    printInOrder(root->left);
    printf("%s:%d, ",root->name,root->fine);
    printInOrder(root->right);
}

void freeTree(Node * root){
    if( root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}


int main(){
    // init empty tree
    Node * mainRoot = NULL;
    int depth = 0;
   
    // amount to process
    int qeuries;
    scanf("%d",&qeuries);
    
    for (int i = 0; i < qeuries; i++){
        // 
        char command[MAX_LEN];
        char name[MAX_LEN];
        depth = 0;
        Node * updatedNode = NULL;
        scanf("%s",command);
            if(strcmp(command, "add") == 0){

                int fine;
                scanf("%s %d",name, &fine);
                mainRoot = addFine(mainRoot,name,fine);
                // searches for the updated node
                updatedNode = search(mainRoot,name,&depth);

                printf("%s %d %d\n",name,updatedNode->fine,depth);

            } else if(strcmp(command, "deduct") == 0){

                int deduct;
                scanf("%s %d",name,&deduct);
                //function call
                
            } else if(strcmp(command, "search") == 0){

                scanf("%s", name);
                updatedNode = search(mainRoot,name,&depth);
                if(updatedNode == NULL)
                    printf("%s not found\n",name);
                else{
                    printf("%s %d %d\n",name,updatedNode->fine,depth);
                }
                
            } else if(strcmp(command, "average") == 0){

                printf("%0.2f\n", average(mainRoot));
                
            } else if(strcmp(command, "height_balance") == 0){
                int heightLeft = calcHeight(mainRoot->left);
                int heightRight = calcHeight(mainRoot->right);
                // print heights
                printf("left height = %d right height = %d ", heightLeft, heightRight);
                // print if balanced or not balanced
                if(heightLeft - heightRight == 0)
                    printf("balanced\n");
                else{
                    printf("not balanced\n");
                }
                
                
            } else { // print total for everything that is less than name: command calc_below
                scanf("%s", name);
                int total = 0;

                calcBelow(mainRoot,name,&total);
                printf("%d\n", total);

                
            }
        
    }

    printInOrder(mainRoot);
    free(mainRoot);
}