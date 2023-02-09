#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32_
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// The "key" argument is invalid - must be changed to a Car type.
// PrintList function needs a revision.

typedef struct {
    char brand[30];
    char model[30];
    int fabYear;
    int modelYear;
    float price;
} Car;

// Node structure for a DLL.
typedef struct Node {
    Car data;
    // Pointer to the next Node.
    struct Node *next;
    // Pointer to the previous Node.
    struct Node *previous;
} Node;

/*DLL*/

// Push operation on DLL.
void push(Node **head,
          Car data);   //"int data" must be changed to the Car structure.
// Delete a Node from list.
void delete(Node **head, int position);
// Print the Nodes of list.
void printList(Node *head);
// Update a desired Node of list.
void update(Node **head, int key, Car data);

/*INTERACTION*/

void addNewCar(Node **head);
void carsView(Node *head);

int main(int argc, char *argv) {
    Node *head = NULL;
    int opt = 0;
    system(CLEAR);
    while (true) {
        printf("\tREGISTRO\n\n");
        printf("%s", "1 - Registrar novo veículo.\n");
        printf("%s", "2 - Atualizar dados de veículo.\n");
        printf("%s", "3 - Ver veículos.\n");
        printf("%s", "4 - Excluir veículo.\n");
        printf("%s", "5 - Sair.\n");
        scanf("%d", &opt);
        switch (opt) {
        case 1:
            addNewCar(&head);
            break;
        case 3:
            printList(head);
            break;

        default:
            break;
        }
    }

    return 0;
}

void push(struct Node **head, Car data) {
    Node *newNode = malloc(sizeof(Node));

    newNode->data = data;
    newNode->next = (*head);
    newNode->previous = NULL;

    if ((*head)) {
        (*head)->previous = newNode;
    }

    // The head's now pointing to the new node.
    (*head) = newNode;
}

void delete(struct Node **head, int position) {
    Node *tmp = malloc(sizeof(Node));
    Node *previous = malloc(sizeof(Node));

    tmp = (*head);
    previous = (*head);

    // Navigate to desired position.
    for (int i = 0; i < position; i++) {
        if (i == 0 && position == 1) {
            *head = (*head)->next;
            free(tmp);
        } else {
            if (i == position - 1 && tmp) {
                previous->next = tmp->next;
                free(tmp);
            } else {
                previous = tmp;
                // Position is bigger than the DLL length.
                if (previous == NULL) {
                    break;
                }
                tmp = tmp->next;
            }
        }
    }
}

void printList(struct Node *head) {
    system(CLEAR);
    printf("\tREGISTRO\n\n");
    while (head) {
        printf("%s", "MARCA: ");
        printf("%s\n", head->data.brand);
        printf("%s", "MODELO: ");
        printf("%s\n", head->data.model);
        printf("%s", "ANO DO MODELO: ");
        printf("%d\n", head->data.modelYear);
        printf("%s", "ANO DE FABRICAÇÃO: ");
        printf("%d\n", head->data.fabYear);
        printf("%s", "PREÇO: ");
        printf("%.2f\n", head->data.price);
        printf("%s", "--------------\n");
        head = head->next;
    }
}

// void update(Node **head, int key, Car data) {
//     Node **current = malloc(sizeof(Node));

//     *current = (*head);
//     while (current) {
//         if ((*current)->data == key) {
//             (*current)->data = data;
//             break;
//         }
//         (*current) = (*current)->next;
//     }
// }

void addNewCar(Node **head) {
    system(CLEAR);
    Car newCar;
    printf("\tREGISTRO\n\n");
    printf("%s", "MARCA: \n");
    scanf("%s", &newCar.brand);
    fflush(stdin);
    printf("%s", "MODELO: \n");
    scanf("%s", &newCar.model);
    fflush(stdin);
    printf("%s", "ANO DO MODELO: \n");
    scanf("%d", &newCar.modelYear);
    fflush(stdin);
    printf("%s", "ANO DE FABRICAÇÃO: \n");
    scanf("%d", &newCar.fabYear);
    fflush(stdin);
    printf("%s", "PREÇO: \n");
    scanf("%f", &newCar.price);
    fflush(stdin);
    push(head, newCar);
}