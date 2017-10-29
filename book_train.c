//
// Created by Kushan Mehta on 29-10-2017.
//

#include "book_train.h"


int book_train() {

    int tno;
    int tickets;
    int i = 0;
    char ch;

    clear();

    printf("Reserve a train ticket:\n\n");

    while (!findTrain()); // Keep repeating until the train is not found

    i = 0;

    do {
        if (i != 0) {
            printf("\nERROR: Enter valid train number.");
        }
        printf("\n\nEnter Train Number of the Train to book the ticket: ");
        scanf("%d", &tno);
        ++i;
    } while (!trainExists(tno));

    i = 0;

    do {
        if (i != 0) {
            printf("\nERROR: Enter valid number of tickets greater than 0\n");
        }

        printf("\nEnter number of tickets to book: ");
        scanf("%d", &tickets);
        ++i;

    } while (tickets <= 0);

    long total_fare = 0;

    if (isTicketAvbl(tno, tickets, &total_fare)) {

        i = 0;

        printf("\n%d tickets for train number %d are available.", tickets, tno);

        total_fare = total_fare * tickets;

        printf("\n\nTotal fare for %d tickets : Rs. %ld", tickets, total_fare);


        do {
            clearBuffer();
            if (i != 0) {
                printf("\nERROR: Enter valid selection (y for yes and n for no).");
            }

            printf("\n\nDo you want to continue with your booking? (y/n): ");
            scanf("%c", &ch);

            ++i;

        } while (!(ch == 'y' || ch == 'n'));


        if (ch == 'y') {
            bookTicket(tno, tickets);
        } else {
            printf("\nYour booking is cancelled. You will now be redirected to main menu.\n\nPress enter to continue...");
            getch();
            return 1;
        }


    } else {
        printf("\nERROR: %d seats are not avaialable for booking, please input lesser number of seats to book",
               tickets);
        printf("\n\nPress enter to try again or any other key to exit...\n");
        if ((ch = getch()) != '\r')
            exit(0);

        return 0;
    }

}

int isTicketAvbl(int tno, int tickets, long *cost) {

    FILE *fp;
    fp = fopen("tmp_find.bin", "rb");

    struct TRAIN_S obj;
    while (fread(&obj, sizeof(obj), 1, fp)) {
        if (obj.train_number == tno) {

            if (obj.seat_available >= tickets) {
                *cost = obj.fare;
                fclose(fp);
                remove("tmp_find.bin");

                return 1;
            }
        }
    }

    fclose(fp);
    remove("tmp_find.bin");

    return 0;

}

void bookTicket(int tno, int tickets) {

    FILE *fp, *ftmp;
    fp = fopen(train_record_file, "rb");
    ftmp = fopen("tmp_book.bin", "wb");

    struct TRAIN_S obj;

    while (fread(&obj, sizeof(obj), 1, fp)) {
        if (tno == obj.train_number) {
            obj.seat_available = obj.seat_available - tickets;
        }

        fwrite(&obj, sizeof(obj), 1, ftmp);
    }

    fclose(fp);
    fclose(ftmp);

    remove(train_record_file);
    rename("tmp_book.bin", train_record_file);

    printf("\n\nYour ticket has been booked successfully for Train number %d for %d seats!", tno, tickets);
    printf("\n\nPress enter to view your e-Ticket!");
    getch();

}

void getUserDetails() {
    printf("Enter you details to continue with ticket booking:\n\n");

    // TODO: Create a new structure to store transaction details (log) and also used for generating e-ticket


    printf("Name: ");

}

int findTrain() {
    struct TRAIN_S obj, objRData;

    getFindDetails(&objRData);

    FILE *fp, *ftmp;
    int x = 0;

    ftmp = fopen("tmp_find.bin", "wb");

    fp = fopen(train_record_file, "rb");

    if (fp != NULL) {

        displayMenu_Header();
        displayMenu_Separator();

        while (fread(&obj, sizeof(obj), 1, fp)) {

            if (stricmp(objRData.origin, obj.origin) == 0 && stricmp(objRData.destination, obj.destination) == 0) {

                fwrite(&obj, sizeof(obj), 1, ftmp);

                ++x;

                displayMenu_TrainDetails(&obj);

            }
        }

        displayMenu_Separator();

        fclose(ftmp);
        fclose(fp);

        if (x == 0) {

            printf("\n\nERROR: No train found from %s to %s.", objRData.origin, objRData.destination);
            printf("\n\nPress enter to try again or any other key to exit...\n");
            if ((x = getch()) != '\r')
                exit(0);

            return 0;

        } else
            return 1;
    }

}


void getFindDetails(struct TRAIN_S *obj) {

    clear();

    printf("Find Train details:\n\n");

    printf("Origin Station: ");
    getString(obj->origin);

    printf("\nDestination Station: ");
    getString(obj->destination);
}
