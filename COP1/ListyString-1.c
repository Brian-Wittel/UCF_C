// Name---: Brian Wittel
// NID----: br933378
// Project: ListyString
// Class--: COP 3502C
// Date---: 2018/03/05

#include <stdio.h>
#include <stdlib.h>
#include "ListyString.h"

int processInputFile(char *filename) {
    int F1;
    FILE *fp;
    char buff[1024];
    char buff2[1024];
    char buff3[1];

    ListyString *LS = malloc(sizeof(ListyString));

    fp = fopen(filename, "r");
    if(fp == NULL) {
        printf("\n---Filename Error!---\n");
        return 1;
    }
    else {
        fscanf(fp, "%s", buff);
        LS = createListyString(buff);

        while(fscanf(fp, "%s", buff2) != EOF) {
            if(buff2[0]=='@'){
                fscanf(fp, "%s", buff3);
                fscanf(fp, "%s", buff2);
                replaceChar(LS, buff3[0], buff2);
            } else if(buff2[0]=='+') {
                fscanf(fp, "%s", buff2);
                listyCat(LS, buff2);
            } else if(buff2[0]=='-') {
                fscanf(fp, "%s", buff3);
                replaceChar(LS, buff3[0], NULL);
            } else if(buff2[0]=='~') {
                reverseListyString(LS);
            } else if(buff2[0]=='?') {
                printf("%d\n", LS->length);
            } else if(buff2[0]=='!') {
                printListyString(LS);
            } else {
                printf("---File Read Error! (Incorrect input)---\n");
            }
        }
        return 0;
    }
}

ListyString *createListyString(char *str) {
    int i;

    ListyNode *temp;
    ListyString *LS = malloc(sizeof(ListyString));
    LS->head = NULL;

    if(str==NULL || str=="" || str=='\0') {
        printf("\nNULL\n");
        LS->length = 0;
        return LS;
    } else {
        LS->head = malloc(sizeof(ListyNode));
        temp = LS->head;
        for(i=0;str[i]!='\0';i++) {
            temp->data = str[i];
            temp->next = malloc(sizeof(ListyNode));
            temp = temp->next;
        }
        LS->length = i;
        temp->data = str[i];
        temp->next = NULL;
        return LS;
    }
}

ListyString *destroyListyString(ListyString *listy) {
    if (listy == NULL) {
        return NULL;
    } else if (listy->head == NULL) {
        free(listy);
        return NULL;
    } else {
        ListyNode *current;
        ListyNode *temp;
        current = listy->head;
        while(current->next != NULL) {
            temp = current->next;
            free(current);
            current = temp;
        }
        free(current);
        free(listy);
        return NULL;
    }
}

ListyString *cloneListyString(ListyString *listy) {
    if(listy==NULL) {
        return NULL;
    } else if(listy->head == NULL) {
        ListyString *LS = malloc(sizeof(ListyString));

        LS->head = NULL;
        LS->length = 0;

        return LS;
    } else {
        int i;
        ListyString *LS = malloc(sizeof(ListyString));

        LS->head = malloc(sizeof(ListyNode));
        LS->length = listy->length;
        ListyNode *temp;
        ListyNode *ListyTemp;
        temp = LS->head;
        ListyTemp = listy->head;

        for(i=0;i<LS->length;i++){
            temp->data = ListyTemp->data;
            temp->next = malloc(sizeof(ListyNode));
            temp = temp->next;
            ListyTemp = ListyTemp->next;
        }

        temp->data = ListyTemp->data;
        temp->next = NULL;

        return LS;
    }
}

void replaceChar(ListyString *listy, char key, char *str) {
    if(listy == NULL || listy->head == NULL) {
        return;
    } else if(str == NULL || str == "") {
        ListyNode *temp;
        ListyNode *current;

        while(listy->head->data == key) {
            if(listy->head->next == NULL) {
                temp = listy->head;
                listy->head = NULL;
                free(temp);
                listy->length = 0;
                return;
            } else {
                temp = listy->head;
                listy->head = listy->head->next;
                free(temp);
                listy->length = listy->length - 1;
            }
        }

        current = listy->head;
        while(current->next != NULL) {
            if(current->next->data == key) {
                temp = current->next;
                while(temp->next->data == key)
                    temp = temp->next;
                current->next = temp->next;
                free(temp);
                current = current->next;
                listy->length = listy->length - 1;
            } else {
                current = current->next;
            }
        }
        return;
    } else {

        int i;
        ListyNode *temp;
        ListyNode *holding;
        ListyNode *current;

        if(listy->head->data == key) {
            listy->head->data = str[0];
            temp = malloc(sizeof(ListyNode));
            holding = temp;

            for(i=1;str[i]!='\0';i++) {
                temp->data = str[i];
                if(str[i+1]!='\0') {
                    temp->next = malloc(sizeof(ListyNode));
                    temp = temp->next;
                }
            }

            temp->next = listy->head->next;
            listy->head->next = holding;
            listy->length = listy->length + i-1;
        } else {
            current = listy->head->next;
        }

        current = listy->head->next;
        while(current->next != NULL) {
            if(current->data == key) {
                current->data = str[0];
                temp = malloc(sizeof(ListyNode));
                holding = current->next;
                current->next = temp;

                for(i=1;str[i]!='\0';i++) {
                    temp->data = str[i];
                    if(str[i+1]!='\0') {
                        temp->next = malloc(sizeof(ListyNode));
                        temp = temp->next;
                    }
                }

                temp->next = holding;
                listy->length = listy->length + i-1;
                current = temp;
                current = current->next;
            } else {
                current = current->next;
            }
        }
        return;
    }
}

void reverseListyString(ListyString *listy) {
    if(listy == NULL || listy->head == NULL || listy->head->next == NULL) {
        return;
    } else {

        ListyNode *NextNode;
        ListyNode *current;
        ListyNode *PrevNode;
        ListyNode *temp = malloc(sizeof(ListyNode));
        temp->next = NULL;
        temp->data = '\0';

        NextNode = NULL;
        current = listy->head->next;
        PrevNode = listy->head;
        PrevNode->next = temp;

        while(current != NULL) {
            NextNode = current->next;
            current->next = PrevNode;
            PrevNode = current;
            current = NextNode;
        }
        listy->head = PrevNode;
        return;
    }
}

ListyString *listyCat(ListyString *listy, char *str) {
    if(listy == NULL && str == NULL) {
        return NULL;
    } else if(listy == NULL && str == "") {
        listy = malloc(sizeof(ListyString));
        listy->head = NULL;
        listy->length = 0;
        return listy;
    } else if(listy == NULL) {
        int i;
        ListyNode *temp;
        listy = malloc(sizeof(ListyString));

        listy->head = malloc(sizeof(ListyNode));
        listy->length = 0;
        temp = listy->head;

        for(i=0;str[i]!='\0';i++) {
            temp->data = str[i];
            temp->next = malloc(sizeof(ListyNode));
            temp = temp->next;
        }
        temp->data = str[i];
        temp->next = NULL;
        listy->length = i;

        return listy;
    } else {
        int i;
        ListyNode *temp;
        temp = malloc(sizeof(ListyNode));
        temp = listy->head;
        while(temp->next != NULL) {
            temp = temp->next;
        }

        for(i=0;str[i]!='\0';i++) {
            temp->data = str[i];
            temp->next = malloc(sizeof(ListyNode));
            temp = temp->next;
        }
        temp->data = str[i];
        temp->next = NULL;
        listy->length = listy->length + i;
        return listy;
    }
}

int listyCmp(ListyString *listy1, ListyString *listy2) {
    if(listy1 == NULL && listy2 == NULL){
        return 0;
    } else if(listy1->head == NULL && listy2->head == NULL) {
        return 0;
    } else {
        ListyNode *temp1;
        ListyNode *temp2;
        temp1 = listy1->head;
        temp2 = listy2->head;
        while(temp1->next != NULL && temp2->next != NULL) {
            if(temp1->data == temp2->data) {
                temp1 = temp1->next;
                temp2 = temp2->next;
            } else {
                return 1;
            }
        }
        return 0;
    }
}

int listyLength(ListyString *listy) {
    if(listy == NULL) {
        return -1;
    } else if(listy->head == NULL) {
        return 0;
    } else {
        return listy->length;
    }
}

void printListyString(ListyString *listy) {
    ListyNode *temp;
    if(listy == NULL || listy->head == NULL){
        printf("(empty string)\n");
    } else {
        temp = listy->head;
        while(temp->next != NULL) {
            printf("%c", temp->data);
            temp = temp->next;
        } printf("\n");
    }
}

double difficultyRating(void) {
    return 4.0;
}

double hoursSpent(void) {
    return 20;
}

int main(int argc, char **argv) {
    processInputFile(argv[1]);
    //printf("\n---Program Complete!---\n");
    return 0;
}
