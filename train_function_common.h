//
// Created by Kushan Mehta on 29-10-2017.
//

#ifndef SEM1_C_MINI_PROJECT_TRAIN_FUNCTION_COMMON_H
#define SEM1_C_MINI_PROJECT_TRAIN_FUNCTION_COMMON_H

#include "global.h"

int trainExists(int);

/*int trainExists(int tno) {
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
}*/


#endif //SEM1_C_MINI_PROJECT_TRAIN_FUNCTION_COMMON_H
