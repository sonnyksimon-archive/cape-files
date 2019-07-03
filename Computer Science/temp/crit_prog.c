#include <stdio.h>
#include <stdlib.h>

typedef struct database {
    char barcode[20];
    char name[20];
    char price[20];
}inventory;

#define ARRAYLEN 10

inventory a[ARRAYLEN];

FILE *pointer;

void append();
void display();

int main() {
    int input;
    printf("1 or 0: ");
    scanf("%i", &input);
    switch(input){
        case 1:
        append();
        break;
        default:
            display();
            break;
    }
    return 0;
}

void append() {
    pointer = fopen("inventory.dat", "a+");
    printf("enter number of items\n");
    int items, i;
    scanf("%i", &items);
        for(i=0;i<items;i++)
        printf("Barcode#: \n");
        scanf("%s", a[i].barcode);
        printf("Name: \n");
        scanf("%s", a[i].name);
        printf("Price: \n");
        scanf("%s", a[i].price);
        fwrite(&a[i], sizeof(a), 1, pointer);
    fclose(pointer);
}

void display(){
    int i;
    pointer = fopen("inventory.dat", "r");
    for (i=0; i<ARRAYLEN; i++) {
        fread(&a[i], sizeof(a), 1, pointer);
        printf("Display.Barcode:%s\n", a[i].barcode);
        printf("Display.Name:   %s\n", a[i].name);
        printf("Display.Price:  %s\n", a[i].price);
    }
    fclose(pointer);
}
