/**
 * @file recloserAuth.c
 * handles local Recloser authentication
 * once logged in the user can access configuration.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//hash library
#include "argon2.h"
//salt library
#include ""

#include "../Common/files.c"

#define MAX_PASS_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16
#define BUFFER_SIZE = 100

/**
 * When zero, user is not logged in. When one, user is logged in
 */
int loggedIn = 0;

/**
 * Checks if a password has been set for the admin account, if not the user will be prompted to set a password.
 * If a password has been set, the user will be prompted to enter the password to login.
 * @returns 1 if user was successfully signed in
 */
int login() {
    //checks if user "admin" already has a password
    if(doesPasswordExists()) {
        //prompts user and checks if hash matches
        if(loginAttempt()) {
            loggedIn = 1;
            return 1;
        }
    } else {
        if(setPass()) {
            loggedIn = 1;
            return 1;
        }
    }
}

/**
 * Logs user out of session
 */
void logOut() {
    loggedIn = 0;
}

/**
 * Checks if a password exists or if one needs to be created
 * @returns 1 if password exists, 0 if no password
 */
static int doesPasswordExist() {
    //open password file to see if admin account already has a password set
    //Maybe setjmp longjmp to catch errors, or handle an error from openFile someother way
    FILE *passfile = openFile('../env/passwords.txt', 'r');
    //change this to scan user name
    //functionality will check to see if there is only one colon in password.txt line
    // meaning the user has no password
    int colonCount = 0;
    char ch = fgetc(passfile);
    while(ch != EOF && ch != '\0') {
        ch = fgetc(passfile);
        colonCount++;
    }
    if(colonCount = 1) {
        return 0;
    } else {
        return 1;
    }
}

/**
 *
 * 
 */
static int loginAttempt() {
    printf(stdout, "Enter admin password: ");
    //stores entered pass
    char passAttempt[BUFFER_SIZE] = {};
    int k = 0;
    int passwordMatched = 0;
    int attemptCount = 0;
    ch = getchar();
    while(!passwordMatched) {
        while(ch != EOF && ch != '\0') {
            passAttempt[k] = ch;
            ch = getchar();
            k++;
        }
        attemptCount++;
        uint_t hashedPassAttempt = hashPass(passAttempt);
        passwordMatched = compareHash(hashedPassAttempt);
        if(passwordMatched) {
            printf("Welcome\n");
            return 1;
        }
        if(attemptCount == 3) {
            printf("Three attempts failed, please wait 30s before trying again\n");
            time.sleep(10);
        }
    }
}

/**
 * User sets the password
 * @returns 1 if password is set
 */
static int setPass() {
    char passSet[MAX_PASS_LEN + 1] = { };
    printf(stdout, "Set a password between 8 and 16 characters long for 'admin': ");
    int j = 0;
    ch = getchar();
    int passwordAccepted = 0;
    while(!passwordAccepted) {
        while(ch != EOF && ch != '\0') {
            passSet[j] = ch;
            ch = getchar();
            j++;
        }
        if(j < 8 || j > 16) {
            printf(stdout, "Password must be between 8 and 16 characters long. Try again: ");
            ch = getchar();
            j = 0;
        } else {
            passwordAccepted = 1;
            hashSet = hashpass(passSet);
            if(storeHash(hashSet)) {
                return 1;
            }
        }
    }
}

/**
* hashes the password and stores it
*/
static uint_t hashPass(char * enteredPass) {
    uint8_t hash[HASH_LEN];

    uint8_t salt = generateSalt();

    //GENERATE A SALT

    memset(salt, )



}

static uint8_t *generateSalt() {

}

/**
* compares hash from login attempt and stored hash. returns 1 if they are equal
* @
*/
static int compareHash(uint8_t hashedPassAttempt) {
    FILE *passfile = openPasswordFile('r');




    fclose(passfile);
}

/**
* Stores the password and returns 1 if successful
* @
*/
static int storeHash(uint8_t) {
    FILE *passfile = openPasswordFile('w');




    fclose(passfile);
}