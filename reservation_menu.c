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
    } while (sel < 1 || sel > 7);

    switch (sel) {
        case 1:
            while (!add_train());
            return;

        case 2:
            while (!delTrain());
            return;

        case 3:
            displayTrains();
            return;

        case 4:
            while (!book_train());
            return;

        case 5: // cancel ticket
            return;

        case 6:
            displayTxns();
            return;

        case 7:
            exit(0);
    }


}

void showReservationMenu() {

    clear();
    printf("Select an option to use the Reservation System: \n\n");
    printf("1. Add Train\n");
    printf("2. Delete a train\n");
    printf("3. Display all Trains\n");
    printf("4. Reserve a train ticket\n");
    printf("5. Cancel a train ticket\n");
    printf("6. Display all bookings\n");
    printf("7. Exit\n");

}