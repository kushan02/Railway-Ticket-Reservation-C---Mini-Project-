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
    } while (sel < 1 || sel > 5);

    switch (sel) {
        case 1:
            while (!add_train());
            return;
            break;
        case 2:
            //  while (!createAccount());
            displayTrains();
            return;
            break;

        case 3:
            findTrain();
            return;
            break;
        case 4:
            //    bookTrain();
            return;
            break;
        case 5:
            exit(0);
    }


}

void showReservationMenu() {

    clear();
    printf("Select an option to use the Reservation System: \n\n");
    printf("1. Add Train\n");
    printf("2. Display all Trains\n");
    printf("3. Search for Trains\n");
    printf("4. Reserve a train\n");
    printf("5. Exit\n");

}