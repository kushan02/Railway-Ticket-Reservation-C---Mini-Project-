//
// Created by Kushan Mehta on 28-10-2017.
//

#include "global.h"


void clear() {
    system("cls");
    printf("\n");
}

void getString(char *str) {
    scanf("%s", str);
    fflush(stdin);
}

void clearBuffer()
{
    fflush(stdin);
}

void displayMenu_Header() {
    clear();
    printf("\n%15s%15s%15s%15s%15s%15s%15s", "TRAIN NO.", "TRAIN NAME", "ORIGIN", "DEPARTURE", "DESTINATION",
           "ARRIVAL", "SEATS AVBL");
}

void displayMenu_Separator() {
    int i;
    printf("\n");
    for (i = 0; i < 7 * 15; i++) {
        printf("-");
    }
}

void displayMenu_TrainDetails(struct TRAIN_S *obj) {
    printf("\n%15d%15s%15s%15s%15s%15s%15d", obj->train_number, obj->train_name, obj->origin,
           obj->departure_time, obj->destination, obj->arrival_time, obj->seat_available);
}


void displayMenu_Footer() {
    printf("\n\n\t\tPress enter to continue...");
    getch();
}

void anyKeytoExit(char *er) {
    char ch;
    printf("\nERROR: %s", er);
    printf("\nPress enter to try again or any other key to exit...\n");
    if ((ch = getch()) != '\r')
        exit(0);
}

