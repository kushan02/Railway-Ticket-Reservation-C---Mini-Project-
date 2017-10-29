//
// Created by Kushan Mehta on 29-10-2017.
//

#include "book_train.h"

/*struct TXN_S {
    char name[50];
    unsigned long long mobile;
    char date[11];
    char email[50];
    char gender;
    int age;
    //  char class[50];
    // char berth[50];
    unsigned int train_no;
    long long ticket_no;
    unsigned int no_of_seats;
    unsigned long fare;
} txn_obj;*/

struct TXN_S txn_obj;

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

            txn_obj.train_no = tno;
            txn_obj.no_of_seats = tickets;
            txn_obj.fare = total_fare;

            bookTicket(tno, tickets);

            getUserDetails();

            generateTicket();

            dispTicket();

            return 1;


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

    printf("\n\nYour ticket has been reserved successfully for Train number %d for %d seats!", tno, tickets);
    printf("\n\nPress enter to generate your ticket!");
    getch();

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

    int i = 0;

    do {
        if (i != 0) {
            printf("\nERROR: Enter date in proper format. eg 29/10/2017\n");
        }
        printf("\nDate of Journey (dd/mm/yyyy): ");
        getString(txn_obj.date);
        ++i;
    } while (!checkDate(txn_obj.date));
}

const char txn_fname[] = "TXN.dat";

void generateTicket() {

    FILE *fp;

    fp = fopen(txn_fname, "ab");

    long ticket_no;

    do {
        ticket_no = rand_ticket_no(1111, 8888);
    } while (ticketNoExists(ticket_no));


    // printf("\n##%ld\n\n", ticket_no);

    txn_obj.ticket_no = ticket_no;

    fwrite(&txn_obj, sizeof(txn_obj), 1, fp);

    fclose(fp);


}

void getUserDetails() {

    clear();

    printf("Enter you details to generate your e-Ticket:\n\n");

    // TODO: Create a new structure to store transaction details (log) and also used for generating e-ticket

    int i = 0;

    clearBuffer();

    printf("Name: ");
    getString(txn_obj.name);

    printf("\nMobile Number: ");
    scanf("%llu", &txn_obj.mobile);

    printf("\nEmail: ");
    getString(txn_obj.email);

    do {
        if (i != 0) {
            printf("\nERROR: Enter a valid gender (m for male and f for female)\n");
        }
        clearBuffer();
        printf("\nGender (m/f): ");
        scanf("%c", &txn_obj.gender);
        ++i;

    } while (!(txn_obj.gender == 'm' || txn_obj.gender == 'f'));

    printf("\nAge: ");
    scanf("%d", &txn_obj.age);

    // TODO: Add Class and berth option

    /*
    printf("\nClass: ");
    getString(txn_obj.class);
*/


    printf("\n\nPress enter to view your e-Ticket!");
    getch();


}


void dispTicket() {

    clear();

    printf("\nTICKET DETAILS:\n\n");

    printf("TICKET NO. %llu\n\n", txn_obj.ticket_no);

    printf("Name: %s\n", txn_obj.name);
    printf("Mobile no: %llu\n", txn_obj.mobile);
    printf("Email: %s\n", txn_obj.email);
    printf("Gender: %c\n", txn_obj.gender);
    printf("Age: %d\n", txn_obj.age);
    printf("Date of Journey: %s\n", txn_obj.date);
    printf("Train Number: %d\n", txn_obj.train_no);
    printf("Seats booked: %d\n", txn_obj.no_of_seats);
    printf("Total fare: %lu\n\n", txn_obj.fare);

    /*printf("\n%s, %llu, %s, %s, %c, %d, %d, %llu, %d, %ld", txn_obj.name, txn_obj.mobile, txn_obj.date, txn_obj.email,
           txn_obj.gender, txn_obj.age, txn_obj.train_no, txn_obj.ticket_no, txn_obj.no_of_seats, txn_obj.fare);
*/

    printf("Have a safe journey!\n\n");

    printf("\nPress enter to return back to main menu...");
    getch();

}


int ticketNoExists(unsigned long tickno) {
    FILE *fp;

    fp = fopen(txn_fname, "rb");

    struct TXN_S obj;

    while (fread(&obj, sizeof(obj), 1, fp)) {
        if (obj.ticket_no == tickno) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;

}


unsigned long rand_ticket_no(unsigned long min, unsigned long max) {
    /* int r;
     const unsigned long range = 1 + max - min;
     const unsigned long buckets = RAND_MAX / range;
     const unsigned long limit = buckets * range;

     *//* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. *//*
    do {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);*/

    srand(time(NULL));   // should only be called once
    //unsigned long r = rand();

    unsigned long r = rand() % (max + 1 - min) + min;


}

void displayTxns() {

    FILE *fp;
    fp = fopen(txn_fname, "rb");

    displayBooking_Header();

    displayBooking_Separator();

    struct TXN_S obj;

    if (fp != NULL) {

        while (fread(&obj, sizeof(obj), 1, fp)) {
            displayBooking_TrainDetails(&obj);
        }
        fclose(fp);

        displayBooking_Separator();
    }

    displayMenu_Footer();

}



