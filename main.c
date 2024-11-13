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
        //printf("Node allocation fail in create Node.");
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
        //printf("Tree is empty.\n");
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

// find parent
Node * findParent(Node * root, Node * target){
    // if tree empty or no parent aka root
    if( root == NULL || root == target)
        return NULL;
    
    // if found
    if( root->right == target || root->left == target)
        return root;
    
    // look right if target is greater
    if(strcmp(target->name,root->name) > 0){
        return findParent(root->right,target);

    } else{ //look left if target is less
        return findParent(root->left, target);
    }
}

// no child
int isLeaf(Node * curr){
    if(curr->right == NULL && curr->left == NULL)
        return 1;
    return 0;
}
//find max only in a subtree
Node * findMax(Node * root){
    if(root->right != NULL)
        return findMax(root->right);
    return root;
}

//if has a left child
int hasLeftChild(Node * target){
    if(target->right == NULL && target->left != NULL)
        return 1;
    return 0;
}

int hasRightChild(Node * target){
    if(target->left == NULL && target->right != NULL)
        return 1;
    return 0;
}

Node * deleteNode(Node * root,Node * curr){
    Node * temp;
    Node * parent = findParent(root,curr);

    // if leave node
    if(isLeaf(curr)){
        // case where is only one node
        if(parent == NULL){
            free(root);
            return NULL; 
            // if child is on the left
        } else if(strcmp(curr->name,parent->name) < 0){
            free(curr);
            parent->left = NULL;
            //if on the right
        } else{
            free(curr);
            parent->right = NULL;
        }
        return root;
    }
    //if has one child

    if(hasLeftChild(curr)){
        // delete if root
        if(parent == NULL){
        temp = curr->left;
        free(curr);
        return temp;
    }
    // if its to the left of parent
    if(strcmp(curr->name,parent->name) < 0){
        parent->left = curr->left;
        free(curr);
    } // if its to the right of parent
    else{
        parent->right = curr->left;
        free(curr);
        }
    return root;
    }

    if(hasRightChild(curr)){
        // delete if root
        if(parent == NULL){
        temp = curr->right;
        free(curr);
        return temp;
    }
    // if its to the left of parent
    if(strcmp(curr->name,parent->name) < 0){
        parent->left = curr->right;
        free(curr);
    } // if its to the right of parent
    else{
        parent->right = curr->right;
        free(curr);
        }
    return root;
    }
    
    // case where it has two childs
    Node * toBeDeleted = findMax(curr->left);
    temp = toBeDeleted;
    char tempName[MAX_LEN];
    strcpy(tempName,toBeDeleted->name);
    int tmpFine = toBeDeleted->fine;

    root = deleteNode(root,toBeDeleted);
    
    // reassign temp values to curr
    strcpy(curr->name,tempName);
    curr->fine = tmpFine;


    return root;
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
    if(root == NULL) return 0;
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
    int depth;
   
    // amount to process
    int qeuries;
    scanf("%d",&qeuries);
    
    for (int i = 0; i < qeuries; i++){
        // 
        char command[MAX_LEN];
        char name[MAX_LEN];
        depth = 0;
        Node * targetNode = NULL;
        scanf("%s",command);
            if(strcmp(command, "add") == 0){

                int fine;
                scanf("%s %d",name, &fine);
                mainRoot = addFine(mainRoot,name,fine);
                // searches for the updated node
                targetNode = search(mainRoot,name,&depth);

                printf("%s %d %d\n",name,targetNode->fine,depth);

            } else if(strcmp(command, "deduct") == 0){

                int deduct;
                scanf("%s %d",name,&deduct);
                targetNode = search(mainRoot,name, &depth);
                // if not found
                if(targetNode == NULL)
                    printf("%s not found\n",name);

                //deduct from fine
                else if(targetNode->fine - deduct > 0){
                    targetNode->fine -= deduct;
                    printf("%s %d %d\n", name, targetNode->fine, depth);

                }
                else{ //delete node since its negative
                    mainRoot = deleteNode(mainRoot,targetNode);
                    printf("%s removed\n", name);
                }
                
                
            } else if(strcmp(command, "search") == 0){

                scanf("%s", name);
                targetNode = search(mainRoot,name,&depth);
                if(targetNode == NULL)
                    printf("%s not found\n",name);
                else{
                    printf("%s %d %d\n",name,targetNode->fine,depth);
                }
                
            } else if(strcmp(command, "average") == 0){

                printf("%.2f\n", average(mainRoot));
                
            } else if(strcmp(command, "height_balance") == 0){
                if(mainRoot == NULL){
                    printf("left height = %d right height = %d not balanced\n", -1, -1);
                }else{
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
                }
                
            } else { // print total for everything that is less than name: command calc_below
                scanf("%s", name);
                int total = 0;

                calcBelow(mainRoot,name,&total);
                printf("%d\n", total);

                
            }
        
    }

    //printInOrder(mainRoot);
    freeTree(mainRoot);
}
