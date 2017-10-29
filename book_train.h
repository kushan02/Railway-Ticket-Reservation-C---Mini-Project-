//
// Created by Kushan Mehta on 29-10-2017.
//

#ifndef SEM1_C_MINI_PROJECT_BOOK_TRAIN_H
#define SEM1_C_MINI_PROJECT_BOOK_TRAIN_H

#include "train_function_common.h"


int findTrain();

int book_train();

int isTicketAvbl(int, int, long *);

void displayFoundTrains(struct TRAIN_S train_obj);

void getFindDetails(struct TRAIN_S *obj);

void bookTicket(int, int);

void getUserDetails();

#endif //SEM1_C_MINI_PROJECT_BOOK_TRAIN_H
