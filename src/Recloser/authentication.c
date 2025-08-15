/**
 * handles local Recloser authentication
 * once logged in the user can access configuration.
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
 * Opens password file in read or write mode
 * @param mode 'r' for read, 'w' for write
 */
static FILE *openPasswordFile(char mode) {
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
static int doesPasswordExists() {
    //open password file to see if admin account already has a password set
    FILE *passfile = openPasswordFile('r');
    char user[] = "admin";
    char delimiter = ":"
    strncat(user, &delimiter, 1);
    char buffer[BUFFER_SIZE] = { };
    fgets(buffer, BUFFER_SIZE, passfile);

    fclose(passfile);

    return strcmp(buffer, user);
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