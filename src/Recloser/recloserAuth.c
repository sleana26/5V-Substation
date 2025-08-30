/**
 * @file recloserAuth.c
 * @brief handles local Recloser authentication once logged in the user can access configuration.
 * @author Sean Leana
 * @date 8/14/25
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/rand.h>

//hash library
#include "argon2.h"
#include "../Common/files.h"

#define MAX_PASS_LEN = 16
#define HASH_LEN = 32
#define SALT_LEN = 16
#define BUFFER_SIZE = 100

/**
 * Generates random salt for hash, prints error if there is an error
 */
static uint8_t *generateSalt(uint8_t *salt) {

    memset(salt, 0x00, SALT_LEN);

    if(RAND_bytes(salt, saltLength)) {
        return salt;
    } else {
        printf(stderr, "Error generating random salt.");
        exit(EXIT_FAILURE);
    }
}

/**
* hashes the password
*/
static uint8_t *hashPass(char *enteredPass, uint8_t *salt, uint8_t *hash) {

    //duplicates password entered by user
    uint8_t *enteredPassDup = (uint8_t *)strdup(enteredPass);

    //gets length of paaword
    uint32_t enteredPassLen = strlen((char *)enteredPassDup);

    //two passes
    uint32_t t_cost = 2;
    uint32_t m_cost = (1 << 16);

    //number of threads
    uint32_t parallelism = 1;

    //hash
    argon2i_hash_raw(t_cost, m_cost, parallelism, enteredPassDup, enteredPassLen, saltPtr, SALT_LEN, hash, HASH_LEN);

    return hash;
}

/**
* compares hash from login attempt and stored hash. returns 1 if they are equal
* @
*/
static int compareHash(char *passAttempt, char *user) {
    FILE *passfile = openPasswordFile('r');
    // read line from password file
    char *line[100];
    scanLine(passfile, line);
    //find user in pass file
    int i = 0;
    char *buff[100];
    while(line[i] != ':') {

    }

    // read salt from password file

    // read hash from password file

    // hash the attempted password 

    // compare attempted password hash to the stored hash
    

    fclose(passfile);
}

/**
* Stores the authentication info in password file and returns 1 if successful
*/
static int storeHash(uint8_t *salt, uint8_t *hash) {
    //open password file in write mode
    FILE *passfile = openPasswordFile('w');

    //write hash to password file

    fclose(passfile);
}


/**
 * Checks if a password has been set for the admin account, if not the user will be prompted to set a password.
 * If a password has been set, the user will be prompted to enter the password to login.
 * @returns 1 if user was successfully signed in
 */
int login() {
    // I think I need to check if user and pass file is empty and then I can go through a setup process where
    // user sets pass for admin "first startup, set password for admin: ", otherwise user is prompted for username "enter username"
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
static int loginAttempt(char *username) {
    printf(stdout, "Enter username: ");
    printf(stdout, "Enter password: ");
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
        if(comparePass(passAttempt, user)) {
            printf("Welcome.\n");
            return 1;
        }
        else if(attemptCount == 3) {
            printf("Three attempts failed, please wait 30s before trying again.\n");
            time.sleep(10);
        }
    }
}

       // uint8_t salt[SALT_LEN];
       // for another function
       // generateSalt(salt);
       // hashedPassAttempt = hashPass(passAttempt, salt, hash);

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
        passSet[j + 1] = '\0';
        if(j < 9 || j > 17) {
            printf(stdout, "Password must be between 8 and 16 characters long. Try again: ");
            ch = getchar();
            j = 0;
        } else {
            passwordAccepted = 1;
            uint8_t salt[SALT_LEN];
            salt = generateSalt(salt);
            uint8_t hash[HASH_LEN];
            hash = hashpass(passSet, salt, hash);
            if(storeAuth(salt, hash)) {
                return 1;
            }
        }
    }
}