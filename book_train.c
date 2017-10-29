//
// Created by Kushan Mehta on 29-10-2017.
//

#include "book_train.h"


/*
struct TRAIN_S1 {
    unsigned int train_number;
    char train_name[30];
    char origin[30];
    char destination[30];
    char departure_time[6];
    char arrival_time[6];
    unsigned int seat_available;
};
*/

int book_train() {


}


int findTrain() {
    struct TRAIN_S obj, objRData;

    getFindDetails(&objRData);

    FILE *fp;

    fp = fopen(train_record_file, "rb");

    if (fp != NULL) {

        displayMenu_Header();
        displayMenu_Separator();

        while (fread(&obj, sizeof(obj), 1, fp)) {

            //    if (objRData.origin == obj.origin && objRData.destination == obj.destination) {

            if (stricmp(objRData.origin, obj.origin) == 0 && stricmp(objRData.destination, obj.destination) == 0) {
                //displayFoundTrains(obj);

                displayMenu_TrainDetails(&obj);

            }
        }

        displayMenu_Separator();
        displayMenu_Footer();


        fclose(fp);

        return 0;
    }

}


void getFindDetails(struct TRAIN_S *obj) {
    char t_date[20];

    clear();

    printf("Find Train details:\n\n");

    printf("Origin Station: ");
    getString(obj->origin);

    printf("Destination Station: ");
    getString(obj->destination);

    printf("Travel Date: ");
    getString(t_date);


}
