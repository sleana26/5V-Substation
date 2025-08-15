/**
 * @file authetication.h
 * @brief local recloser authentication
 * @author Sean Leana
 * @date 8/14/25
 */

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

/**
 * Checks if a password has been set for the admin account, if not the user will be prompted to set a password.
 * If a password has been set, the user will be prompted to enter the password to login.
 * @returns 1 if user was successfully signed in
 */
 int login();

/**
 * Logs user out of session
 */
void logOut() {
    loggedIn = 0;
}

 #endif