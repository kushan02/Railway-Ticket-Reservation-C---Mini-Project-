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

void clearBuffer() {
    fflush(stdin);
}

void displayMenu_Header() {
    clear();
    printf("\n%15s%15s%15s%15s%15s%15s%15s%15s", "TRAIN NO.", "TRAIN NAME", "ORIGIN", "DEPARTURE", "DESTINATION",
           "ARRIVAL", "FARE   ", "SEATS AVBL");
}

void displayMenu_Separator() {
    int i;
    printf("\n");
    for (i = 0; i < 8 * 15; i++) {
        printf("-");
    }
}

void displayMenu_TrainDetails(struct TRAIN_S *obj) {
    printf("\n%15d%15s%15s%15s%15s%15s%11d Rs.%15d", obj->train_number, obj->train_name, obj->origin,
           obj->departure_time, obj->destination, obj->arrival_time, obj->fare, obj->seat_available);
}


void displayMenu_Footer() {
    printf("\n\nPress enter to continue...");
    getch();
}

void anyKeytoExit(char *er) {
    char ch;
    printf("\nERROR: %s", er);
    printf("\nPress enter to try again or any other key to exit...\n");
    if ((ch = getch()) != '\r')
        exit(0);
}

int checkDate(char *date) {
    int len = strlen(date);
    if (len != 10)
        return 0;

    int i = 0;

    if (isdigit(date[0]) && isdigit(date[1]) && date[2] == '/' && isdigit(date[3]) && isdigit(date[4]) &&
        date[5] == '/' && isdigit(date[6]) &&
        isdigit(date[7]) && isdigit(date[8]) && isdigit(date[9])) {


        char dat[3];
        char month[3];
        char year[5];

        strncpy(dat, date, 2);
        strncpy(month, &date[3], 2);
        strncpy(year, &date[6], 4);

        dat[2] = '\0';
        month[2] = '\0';
        year[4] = '\0';

        int di = strToint(dat);
        int mi = strToint(month);
        int yi = strToint(year);

        //     printf("\n## %d, %d, %d\n", di, mi, yi);
        //    printf("\n## %s, %s, %s\n", dat, month, year);

        if (di > 0 && di <= 31) {
            if (mi > 0 && mi <= 12) {
                if (yi >= 2017 && yi <= 3000) {
                    return 1;
                }
            }
        }
        

    }

    return 0;
}


unsigned int strToint(char *str) {
    unsigned long mult = 1;
    unsigned long re = 0;
    int len = strlen(str);
    int i = 0;
    for (i = len - 1; i >= 0; i--) {
        re = re + ((int) str[i] - 48) * mult;
        mult = mult * 10;
    }
    return re;
}


void displayBooking_Header() {
    clear();
    printf("\n%20s%20s%20s%20s%20s", "TICKET NO.", "NAME  ", "D.O.J.  ", "TRAIN NO.", "FARE (in Rs.)");
}

void displayBooking_Separator() {
    int i;
    printf("\n");
    for (i = 0; i < 5 * 20; i++) {
        printf("-");
    }
}

void displayBooking_TrainDetails(struct TXN_S *obj) {

    printf("\n%20llu%20s%20s%20d%20ld", obj->ticket_no, obj->name, obj->date, obj->train_no, obj->fare);

}







