//
// Created by Kushan Mehta on 28-10-2017.
//

#include "login.h"


void login() {

    int sel;
    int i = 0;

    do {
        if (i != 0) {
            printf("\nPlease make a valid selection. Press Enter to try again...");
            getch();
        } else
            i++;

        showLoginMenu();
        printf("\nEnter your selection: ");
        scanf("%d", &sel);
    } while (sel < 1 || sel > 3);

    switch (sel) {
        case 1:

            while (!loginForm()); // While the login detail isnt correct

            return; // Out of login() function stack frame

            break;
        case 2:
            //   createAccount();
            while (!createAccount()); // While the login detail isnt correct

            return;
            break;
        case 3:
            exit(0);
    }

}

struct login_file {

    // TODO: Add different Account Access Levels (Admin,user etc)

    char name[50];
    char username[50];
    char password[50];
} login_obj;

int createAccount() {
    FILE *fp;

    char password[50];
    char ch;
    int i = 0;

    clear();

    printf("Enter your details to create your account:\n\n");

    printf("Name: ");
    getString(login_obj.name);


    printf("Username: ");
    getString(login_obj.username);


    do {
        if (i != 0) {
            printf("\n Passwords do not match, please try again\n\n");
        }

        i = 0;
        printf("Password: ");


        while ((ch = getch()) != '\r') {

            if (ch == '\b' && i > 0) {
                printf("\b \b");

                i--;
                continue;
            }
            printf("*");
            login_obj.password[i++] = ch;
        }
        login_obj.password[i] = '\0';

        i = 0;

        printf("\nRe-enter Password: ");

        while ((ch = getch()) != '\r') {

            if (ch == '\b' && i > 0) {
                printf("\b \b");

                i--;
                continue;
            }
            printf("*");
            password[i++] = ch;
        }
        password[i] = '\0';

    } while (strcmp(login_obj.password, password) != 0);


    //   printf("\n\n%s, %s, %s", login_obj.name, login_obj.username, login_obj.password);



    if (!userExists(login_obj.username)) {

        fp = fopen("user_info.dat", "ab");

        if (fp != NULL) {

            fwrite(&login_obj, sizeof(login_obj), 1, fp);
            fclose(fp);
            printf("\n\n%s your account has been created successfully, you can now login!", login_obj.name);
            return 1;
        }
        else
        {
            printf("FUCK THIS");
        }
    } else {
        //   fclose(fp);
        printf("\n\nERROR: Account creation failed. User %s already exists.", login_obj.username);
        printf("\nPress enter to try again or any other key to exit...\n");
        if ((ch = getch()) != '\r')
            exit(0);
        return 0;
    }
}


void showLoginMenu() {

    clear();
    printf("Select an option to continue to use the system: \n\n");
    printf("1. Login\n");
    printf("2. Create Account\n");
    printf("3. Exit\n");

}

int loginForm() {

    char username[50], password[50], ch;
    int i = 0;

    clear();

    printf("Login to continue to your account:\n\n");

    printf("Username: ");
    getString(username);

    printf("Password: ");

    while ((ch = getch()) != '\r') {

        if (ch == '\b' && i > 0) {
            printf("\b \b");

            i--;
            continue;
        }
        printf("*");
        password[i++] = ch;
    }
    password[i] = '\0';

    printf("%s  %s", username, password);

    clear();

    if (authenticateLogin(username, password)) {
        printf("\n Login Successful!\n");
        getch();
        return 1;
    } else {
        printf("Invalid credentials! Login unsuccessful\n");
        printf("Press Enter to try again or any other key to exit...\n");
        if ((ch = getch()) != '\r')
            exit(0);
        return 0;
    }


}

int userExists(char *username) {
    FILE *fp;

    fp = fopen("user_info.dat", "rb");

    if(!fp)
    {
        printf("THIS FUCK");
    }

    while (fread(&login_obj, sizeof(login_obj), 1, fp)) {
        if (strcmp(login_obj.username, username) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;

}


int authenticateLogin(char *uname, char *pwd) {

    FILE *fp;

    fp = fopen("user_info.dat", "rb");

    while (fread(&login_obj, sizeof(login_obj), 1, fp)) {
        if (strcmp(login_obj.username, uname) == 0 && strcmp(login_obj.password, pwd) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;

}


void displayUsers() {
    FILE *fp;

    fp = fopen("user_info.dat", "rb");

    while (fread(&login_obj, sizeof(login_obj), 1, fp)) {
        printf("%s, %s\n", login_obj.username, login_obj.password);
    }


    fclose(fp);

}


