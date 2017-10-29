//
// Created by Kushan Mehta on 28-10-2017.
//

#include "add_train.h"


//const char train_record_file[] = "TRAIN.dat";

/*

struct TRAIN_S {
    unsigned int train_number;
    char train_name[30];
    char origin[30];
    char destination[30];
    char departure_time[6];
    char arrival_time[6];
    unsigned int seat_available;
} train_obj;
*/

struct TRAIN_S train_obj;


//static const struct TRAIN_S EmptyTrainStruct;


int add_train() {

    FILE *fp;
    char ch;

    getTrainDetails(); // Get the train details into the structure


    if (!trainExists(train_obj.train_number)) { // Check if the entered train no. is unique or not

        fp = fopen(train_record_file, "ab");

        if (fp != NULL) {
            fwrite(&train_obj, sizeof(train_obj), 1, fp);
            fclose(fp);
            return 1;
        }
    } else {
        printf("\nERROR: Train number %d already exists! Add a unique train!\n", train_obj.train_number);
        printf("Press enter to try again or any other key to exit...\n");
        if ((ch = getch()) != '\r')
            exit(0);
        return 0;
    }
}


int trainExists(int tno) {
    FILE *fp;

    struct TRAIN_S objT;

    fp = fopen(train_record_file, "rb");

    if (fp != NULL) {
        while (fread(&objT, sizeof(objT), 1, fp)) {
            if (objT.train_number == tno) {
                return 1;
            }
        }
    }

    fclose(fp);

    return 0;
}

void getTrainDetails() {
    clear();

    //  train_obj = EmptyTrainStruct;

    printf("Add Train details:\n\n");

    printf("Train Number: ");
    scanf("%d", &train_obj.train_number);

    printf("Train Name: ");
    getString(train_obj.train_name);

    printf("Origin: ");
    getString(train_obj.origin);

    printf("Destination: ");
    getString(train_obj.destination);

    printf("Departure time: ");
    getString(train_obj.departure_time);

    printf("Arrival time: ");
    getString(train_obj.arrival_time);

    printf("Seats available: ");
    scanf("%d", &train_obj.seat_available);

}

void displayTrains() {

    //   clear();

    FILE *fp;
    fp = fopen(train_record_file, "rb");

    int i;

//    printf("\n%15s%15s%15s%15s%15s%15s%15s\n", "TR NO.", "TRN NAME", "ORIGIN", "DEP", "DESTN", "ARRV", "SEAT AVL");

//    printf("\n%15s%15s%15s%15s%15s%15s%15s\n", "TRAIN NO.", "TRAIN NAME", "ORIGIN", "DEPARTURE", "DESTINATION",
//           "ARRIVAL", "SEATS AVBL");


    displayMenu_Header();

    displayMenu_Separator();

/*
    for (i = 0; i < 7 * 15; i++) {
        printf("-");
    }
*/

    //  printf("\n");

    if (fp != NULL) {
        while (fread(&train_obj, sizeof(train_obj), 1, fp)) {
            /*  printf("%15d%15s%15s%15s%15s%15s%15d\n", train_obj.train_number, train_obj.train_name, train_obj.origin,
                     train_obj.departure_time, train_obj.destination, train_obj.arrival_time, train_obj.seat_available);
  */

            displayMenu_TrainDetails(&train_obj);

        }

        fclose(fp);

        displayMenu_Separator();

        /*   for (i = 0; i < 7 * 15; i++) {
               printf("-");
           }*/
    }

    displayMenu_Footer();

    /* printf("\nPress enter to continue...");
     getch();*/
}