//
// Created by Kushan Mehta on 28-10-2017.
//

#ifndef SEM1_C_MINI_PROJECT_GLOBAL_H
#define SEM1_C_MINI_PROJECT_GLOBAL_H


#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>


struct TRAIN_S {
    unsigned int train_number;
    char train_name[30];
    char origin[30];
    char destination[30];
    char departure_time[6];
    char arrival_time[6];
    unsigned int seat_available;
};

extern struct TRAIN_S train_obj;

#define T_R_F(X) #X
#define train_record_file T_R_F(TRAIN.dat)

void clear();

void clearBuffer();

void getString(char *str);

void displayMenu_Header();

void displayMenu_Separator();

void displayMenu_Footer();

void displayMenu_TrainDetails(struct TRAIN_S *obj);

void anyKeytoExit(char *er);


#endif //SEM1_C_MINI_PROJECT_GLOBAL_H
