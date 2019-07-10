// Name---: Brian Wittel
// NID----: br933378
// Project: KindredSpirits
// Class--: COP 3502C
// Date---: 2018/04/01

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"
//Personal structure for comparing trees
typedef struct list {
	int data;
	struct list *next;
} list;
//Used to visualize trees
void printTree(node *a, int b, int c) {
    if(a == NULL) {
        return;
    }
    if(c==0) {
        printf("Head - %3d | Level - %d\n", a->data, b);
    } else if(c==1) {
        printf("Left - %3d | Level - %d\n", a->data, b);
    } else {
        printf("Rght - %3d | Level - %d\n", a->data, b);
    }
    printTree(a->left, b+1, 1);
    printTree(a->right, b+1, 2);
    return;
}
//Preorder Trace of tree
list *preTrace(node *a, list *b) {

    b->data = a->data;
    b->next = malloc(sizeof(list));
    b->next->data = 0;
    b->next->next = NULL;
    if(a->left != NULL) {
        b = preTrace(a->left, b->next);
    }
    if(a->right != NULL) {
        b = preTrace(a->right, b->next);
    }
    return b;

}
//Postorder Trace of tree
list *pstTrace(node *a, list *b) {

    if(a->left != NULL) {
        b = pstTrace(a->left, b);
    }
    if(a->right != NULL) {
        b = pstTrace(a->right, b);
    }

    b->data = a->data;
    b->next = malloc(sizeof(list));
    b->next->data = 0;
    b->next->next = NULL;

    return b->next;
}
//Used to visualize traces of lists
void printList(list *a) {
    while(a->next != NULL) {
        printf("%p | %2d |%p\n", a, a->data, a->next);
        a = a->next;
    }
}
//Sees if given tree is a reflection
int isReflection(node *a, node *b) {
    //Checks for NULL trees
    if(a == NULL && b == NULL) {
        return 1;
    //Looks for a single NULL tree
    } else if((a == NULL && b != NULL) || (a != NULL && b == NULL)) {
        return 0;
    //Looks for end of tree
    } else if(a->left == NULL && a->right == NULL && b->left == NULL && b->right == NULL) {
        if(a->data != b->data) {
            return 0;
        }
        return 1;
    //Looks for non NULL trees
    } else if(a != NULL && b != NULL) {
        //Recursive call if criteria met
        if(a->left != NULL && b->right != NULL) {
            isReflection(a->left, b->right);
        //Else not a mirror
        } else {
            return 0;
        }
        //Recursive call if node is mirror
        if(a->right != NULL && b->left != NULL) {
            isReflection(a->right, b->left);
        //Not mirrored
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
//Creates a reflection of given tree and new address
node *makeReflection(node *root) {
    //Checks for NULL tree
    if(root == NULL) {
        return NULL;
    }
    //Creates new node with data
    node *b = malloc(sizeof(node));
    b->left = NULL;
    b->right = NULL;
    b->data = root->data;
    //Recursive calls for each side
    b->right = makeReflection(root->left);
    b->left = makeReflection(root->right);

    return b;
}
//Checks if two given trees are Kindred Spirits
int kindredSpirits(node *a, node *b) {
    //Creates comparison lists
    list *aList = malloc(sizeof(list));
    list *bList = malloc(sizeof(list));
    aList->next = NULL;
    bList->next = NULL;
    //Checks basic information on given trees
    if(a == NULL && b == NULL) {
        return 1;
    } else if(a == NULL && b != NULL) {
        return 0;
    } else if(a != NULL && b == NULL) {
        return 0;
    }
    //Performs operations
    preTrace(a, aList);
    pstTrace(b, bList);
    //Compares created lists if trees are not Kindred Spirits
    while(aList->next != NULL && bList->next != NULL) {
        if(aList->data == bList->data) {
            return 0;
        }
        aList = aList->next;
        bList = bList->next;
    }
    //If while loop is passed they are Kindred Spirits
    return 1;
}

double difficultyRating(void) {


    return 4.0;
}

double hoursSpent(void) {


    return 15.0;
}








