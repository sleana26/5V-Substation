/**
 * handles authentication on site
 * 
 */
#include <stdio>
#include "argon2.h"
#include <stdlib>

#define MAX_PASS_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16

readPass() {
    
    //open password file to see if admin account already has a password set
    FILE *passfptf;
    passfptf = fopen("_____", "r");
    if(fptr == NULL) {
        printf("Error: Can't access password(s).\n");
        return 1;
    }
    //check if password file contains a password in password file
    fscanf(passfptf, "%c", &password)

    fscanf(passfptf, "%c", &password)
    while()

    fclose(passfptf)

    //if password is needed
    //Initialize password array
    char pass[MAX_PASS_LEN] = "";
    printf("Set password for admin account: ")
    while()
    pass[i] = getchar();

    
    //if password file is empty
    if()
    printf("Set password for admin account: ")
    
    printf("Please")
}


for(i = 0; i < MAX_PASS_LEN; i++) {
    pass[i] = 
}


hashpass() {

}

/*
 * The program will add salt and hash the password using argon2. Password will be stored in a text or SQLite file
 */
login() {
    //if pass is admin, prompt user to set new password, else prompt for user then pass

    //check password.txt file to check if user and pass match, prompt up to 3 times then timeout for 30 seconds before accepting login attempt

}