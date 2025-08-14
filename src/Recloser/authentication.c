/**
 * handles local Recloser authentication
 * 
 */
#include <stdlib>
#include <stdio>
#include "argon2.h"
#include <string.h>

#define MAX_PASS_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16
#define BUFFER_SIZE = 100

/**
 * Checks if a password has been set for the admin account, if not the user will be prompted to set a password.
 * If a password has been set, the user will be prompted to enter the password.
 */
authentication() {
    
    //checks if the user "admin" needs a password
    if(doesPasswordExists(passfile)) {
        
    }
    //
    char user[] = "admin";
    char delimiter = ":"
    strncat(user, &delimiter, 1);
    char buffer[BUFFER_SIZE] = { };
    fgets(buffer, BUFFER_SIZE, passfile);
    if(strcmp(buffer, user) == 0) {
        //user sets password
        char passSet[MAX_PASS_LEN + 1] = { };
        printf(stdout, "Set a password between 8 and 16 characters long for admin: ");
        int j = 0;
        ch = getchar();
        int passwordAccepted = 0;
        while(!passwordAccepted) {
            while(ch != EOF && ch != '\0') {
                passSet[j] = ch;
                ch = getchar();
                j++;
            }
            if(j > 16 || j < 8) {
                printf(stdout, "Password must be between 8 and 16 characters long. Try again: ");
                ch = getchar();
                j = 0;
            } else {
                passwordAccepted = 1;
                hashSet = hashpass(passSet);
                storeHash(hashSet);
            }
        }
    } else {
        //user password attempt
        char passAttempt[BUFFER_SIZE] = {};
        printf(stdout, "Enter admin password(default is 'admin'): ");
        int k = 0;
        ch = getchar();
        
        while(!passwordMatched) {
            while(ch != EOF && ch != '\0') {
                passAttempt[k] = ch;
                ch = getchar();
                k++;
            }
            uint_t = hashedPass[32];
            hashedPass = hashPass(passAttempt);
            passwordMatched = compareHash(hashedPass);
        }
        uint_t = hashedPass[32];
        hashedPass = hashPass(passAttempt);
        compareHash(hashedPass);
    }
}

/**
 * Opens password file in read or write mode
 * @param mode 'r' for read, 'w' for write
 */
FILE *openPasswordFile(char mode) {
    FILE *passfile;
    passfile = fopen("env/password.txt", mode);
    //check if file was found
    if(!passfile) {
        fprintf(stderr, "Error: Can't access passwords.\n");
        exit(1);
    }
    return passfile;
}

/**
 * Checks if a password exists or if one needs to be created
 * @returns 1 if password exists
 */
int doesPasswordExists() {
    //open password file to see if admin account already has a password set
    openPasswordFile('r');
    char user[] = "admin";
    char delimiter = ":"
    strncat(user, &delimiter, 1);
    char buffer[BUFFER_SIZE] = { };
    fgets(buffer, BUFFER_SIZE, passfile);

    fclose(passfile);

    return strcmp(buffer, user);
}

char * loginAttempt() {
    //user password attempt
    char passAttempt[BUFFER_SIZE] = {};
    printf(stdout, "Enter admin password(default is 'admin'): ");
    int k = 0;
    ch = getchar();
    uint_t = hashedPass[32];
    
    while(!passwordMatched) {
        while(ch != EOF && ch != '\0') {
            passAttempt[k] = ch;
            ch = getchar();
            k++;
        }
        hashedPass = hashPass(passAttempt);
        passwordMatched = compareHash(hashedPass, );
    }
    printf("Welcome");
}


/**
 * User sets the password
 * @returns 1 if password is set
 */
int setPass(FILE * passFile) {
    char passSet[MAX_PASS_LEN + 1] = { };
    printf(stdout, "Set a password between 8 and 16 characters long for admin: ");
    int j = 0;
    ch = getchar();
    int passwordAccepted = 0;
    while(!passwordAccepted) {
        while(ch != EOF && ch != '\0') {
            passSet[j] = ch;
            ch = getchar();
            j++;
        }
        if(j > 16 || j < 8) {
            printf(stdout, "Password must be between 8 and 16 characters long. Try again: ");
            ch = getchar();
            j = 0;
        } else {
            passwordAccepted = 1;
            hashSet = hashpass(passSet);
            storeHash(hashSet);
        }
    }
    return 1;
}

/**
* hashes the password and stores it
*/
uint_t hashPass(char * enteredPass) {
    
}

/**
* compares hash from login attempt and stored hash. returns 1 if they are equal
* @
*/
int compareHash(uint8_t enteredHash) {

}

/**
* Stores the password and returns 1 if successful
* @
*/
int storeHash(uint8_t) {

}





















/*
 * The program will add salt and hash the password using argon2. Password will be stored in a text or SQLite file
 */
 {
    //if pass is admin, prompt user to set new password, else prompt for user then pass

    //check password.txt file to check if user and pass match, prompt up to 3 times then timeout for 30 seconds before accepting login attempt

}