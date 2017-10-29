//
// Created by Kushan Mehta on 28-10-2017.
//

#ifndef SEM1_C_MINI_PROJECT_LOGIN_H
#define SEM1_C_MINI_PROJECT_LOGIN_H

#include "global.h"

void login();
void showLoginMenu();
int loginForm();

int authenticateLogin(char*, char*);

int createAccount();
int userExists(char*);

void displayUsers();

struct login_file;


#endif //SEM1_C_MINI_PROJECT_LOGIN_H
