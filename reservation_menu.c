//
// Created by Kushan Mehta on 28-10-2017.
//

#include "reservation_menu.h"

void reservation_menu() {
    int sel;
    int i = 0;

    do {
        if (i != 0) {
            printf("\nPlease make a valid selection. Press Enter to try again...");
            getch();
        } else
            i++;

        showReservationMenu();

        printf("\nEnter your selection: ");
        scanf("%d", &sel);
    } while (sel < 1 || sel > 6);

    switch (sel) {
        case 1:
            while (!add_train());
            return;
        case 2:
            //  while (!createAccount());
            displayTrains();
            return;

        case 3:
            findTrain();
            return;
        case 4:
            while (!book_train());
            return;
        case 5:
            while (!delTrain());
            return;
        case 6:
            exit(0);
    }


}

void showReservationMenu() {

    clear();
    printf("Select an option to use the Reservation System: \n\n");
    printf("1. Add Train\n");
    printf("2. Display all Trains\n");
    printf("3. Search for Trains\n");
    printf("4. Reserve a train ticket\n");
    printf("5. Delete a train\n");
    printf("6. Exit\n");

}