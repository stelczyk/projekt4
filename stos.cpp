#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning(disable: 4996)

typedef struct Student {
    char imie[50];
    char nazwisko[50];
    int rok_urodzenia;
} Student;


typedef struct Node {
    Student data;
    struct Node* next;
} Node;


typedef enum {
    DODAJ = 1,
    POBIERZ,
    SZUKAJ,
    WYPISZ,
    ILOSC,
    USUN_WSZYTKO,
    ZAKONCZ
} MenuOpcje;



Node* createNode(const char* imie, const char* nazwisko, int rok) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Brak pamieci!\n");
        return NULL;
    }
    strncpy(newNode->data.imie, imie, sizeof(newNode->data.imie) - 1);
    newNode->data.imie[sizeof(newNode->data.imie) - 1] = '\0';
    strncpy(newNode->data.nazwisko, nazwisko, sizeof(newNode->data.nazwisko) - 1);
    newNode->data.nazwisko[sizeof(newNode->data.nazwisko) - 1] = '\0';
    newNode->data.rok_urodzenia = rok;
    newNode->next = NULL;
    return newNode;
}


void push(Node** top, const char* imie, const char* nazwisko, int rok) {
    Node* newNode = createNode(imie, nazwisko, rok);
    if (!newNode) return;
    newNode->next = *top;
    *top = newNode;
}


int pop(Node** top) {
    if (!(*top)) {
        printf("Stos jest pusty!\n");
        return 0;
    }
    Node* temp = *top;
    *top = (*top)->next;
    printf("Pobrano element: %s %s, %d\n", temp->data.imie, temp->data.nazwisko, temp->data.rok_urodzenia);
    free(temp);
    return 1;
}


void search(Node* top, const char* nazwisko) {
    Node* current = top;
    int znaleziono = 0;
    while (current) {
        if (strcmp(current->data.nazwisko, nazwisko) == 0) {
            printf("Znaleziono: %s %s, %d\n", current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
            znaleziono = 1;
        }
        current = current->next;
    }
    if (!znaleziono) {
        printf("Nie znaleziono studenta o nazwisku %s.\n", nazwisko);
    }
}


void printAll(Node* top) {
    if (!top) {
        printf("Stos jest pusty!\n");
        return;
    }
    Node* current = top;
    printf("Zawartosc stosu (od góry):\n");
    while (current) {
        printf("%s %s, %d\n", current->data.imie, current->data.nazwisko, current->data.rok_urodzenia);
        current = current->next;
    }
}


int countElements(Node* top) {
    int count = 0;
    while (top) {
        count++;
        top = top->next;
    }
    return count;
}


void clearStack(Node** top) {
    Node* current = *top;
    while (current) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    *top = NULL;
    printf("Stos zostal wyczyszczony.\n");
}

int main() {
    Node* stack = NULL;
    int wybor;
    int rok;
    char imie[50], nazwisko[50];

    do {
        printf("\n=== MENU ===\n");
        printf("%d. Dodaj element\n", DODAJ);
        printf("%d. Pobierz element\n", POBIERZ);
        printf("%d. Szukaj po nazwisku\n", SZUKAJ);
        printf("%d. Wypisz wszystkie elementy\n", WYPISZ);
        printf("%d. Ilosc elementow\n", ILOSC);
        printf("%d. Usun caly stos\n", USUN_WSZYTKO);
        printf("%d. Zakoncz\n", ZAKONCZ);
        printf("Wybor: ");
        if (scanf("%d", &wybor) != 1) {
            printf("Niepoprawny wybor\n");
            
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }


        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch ((MenuOpcje)wybor) {
        case DODAJ:
            printf("Podaj imie: ");
            if (fgets(imie, sizeof(imie), stdin) == NULL) break;
            imie[strcspn(imie, "\n")] = '\0';

            printf("Podaj nazwisko: ");
            if (fgets(nazwisko, sizeof(nazwisko), stdin) == NULL) break;
            nazwisko[strcspn(nazwisko, "\n")] = '\0';

            printf("Podaj rok urodzenia: ");
            if (scanf("%d", &rok) != 1) {
                printf("Niepoprawna wartosc.\n");
                while ((c = getchar()) != '\n' && c != EOF);
                break;
            }
            while ((c = getchar()) != '\n' && c != EOF);

            push(&stack, imie, nazwisko, rok);
            break;

        case POBIERZ:
            pop(&stack);
            break;

        case SZUKAJ:
            printf("Podaj nazwisko do wyszukania: ");
            if (fgets(nazwisko, sizeof(nazwisko), stdin) == NULL) break;
            nazwisko[strcspn(nazwisko, "\n")] = '\0';
            search(stack, nazwisko);
            break;

        case WYPISZ:
            printAll(stack);
            break;

        case ILOSC:
            printf("Liczba elementow w stosie: %d\n", countElements(stack));
            break;

        case USUN_WSZYTKO:
            clearStack(&stack);
            break;

        case ZAKONCZ:
            clearStack(&stack);
            printf("Zakonczono program.\n");
            break;

        default:
            printf("Nie ma takiej opcji w menu.\n");
            break;
        }
    } while ((MenuOpcje)wybor != ZAKONCZ);

    return 0;
}
