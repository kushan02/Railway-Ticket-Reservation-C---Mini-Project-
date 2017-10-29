//
// Created by Kushan Mehta on 28-10-2017.
//

#include "add_train.h"


struct TRAIN_S train_obj;


int add_train() {

    FILE *fp;
    char ch;

    getTrainDetails(); // Get the train details into the structure


    if (!trainExists(train_obj.train_number)) { // Check if the entered train no. is unique or not

        fp = fopen(train_record_file, "ab");

        if (fp != NULL) {
            fwrite(&train_obj, sizeof(train_obj), 1, fp);
            fclose(fp);

            printf("\n\nTrain %s added successfully! Press enter to continue...", train_obj.train_name);
            getch();

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
                fclose(fp);
                return 1;
            }
        }
    }

    fclose(fp);

    return 0;
}

void getTrainDetails() {
    clear();

    printf("Add Train details:\n\n");

    printf("Train Number: ");
    scanf("%d", &train_obj.train_number);

    printf("\nTrain Name: ");
    getString(train_obj.train_name);

    printf("\nOrigin: ");
    getString(train_obj.origin);

    printf("\nDestination: ");
    getString(train_obj.destination);

    printf("\nDeparture time: ");
    getString(train_obj.departure_time);

    printf("\nArrival time: ");
    getString(train_obj.arrival_time);

    printf("\nSeats available: ");
    scanf("%d", &train_obj.seat_available);

    printf("\nFare: ");
    scanf("%d", &train_obj.fare);

}

void displayTrains() {

    FILE *fp;
    fp = fopen(train_record_file, "rb");

    displayMenu_Header();

    displayMenu_Separator();

    if (fp != NULL) {

        while (fread(&train_obj, sizeof(train_obj), 1, fp)) {
            displayMenu_TrainDetails(&train_obj);
        }
        fclose(fp);

        displayMenu_Separator();
    }

    displayMenu_Footer();

}

int delTrain() {

    int tno;
    FILE *fp, *fp_tmp;

    clear();

    printf("Delete a train entry:\n\n");

    printf("Enter Train Number of train to delete: ");
    scanf("%d", &tno);

    if (trainExists(tno)) {
        fp = fopen(train_record_file, "rb");
        fp_tmp = fopen("tmp.dat", "wb");

        while (fread(&train_obj, sizeof(train_obj), 1, fp)) {
            if (train_obj.train_number == tno)
                continue;

            fwrite(&train_obj, sizeof(train_obj), 1, fp_tmp);
        }

        fclose(fp);
        fclose(fp_tmp);

        remove(train_record_file);

        rename("tmp.dat", train_record_file);

        printf("\nTrain number %d deleted successfully! Press enter to continue.", tno);
        getch();
        return 1;

    } else {
        char ch;
        printf("\nERROR: Train number %d does not exists", tno);
        printf("\n\nPress enter to try again or any other key to exit...\n");
        if ((ch = getch()) != '\r')
            exit(0);

        return 0;
    }


}