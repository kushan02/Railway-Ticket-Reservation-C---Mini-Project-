#include "global.h"

#include "login.h"
#include "reservation_menu.h"

int main() {
    printf("Hello, World!\n");

    //   login();

    clear();
    // displayUsers();
    //  getch();

    while (1)
        reservation_menu();


    printf("\n\nback to main!!");

    getch();

    return 0;
}