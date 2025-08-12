/**
 * handles authentication on site
 * 
 */
#include <stdio>

string user = admin;
string pass = admin;

/*
 * The program will add salt and hash the password using argon2. Password will be stored in a text or SQLite file
 */
login() {
    //if pass is admin, prompt user to set new password, else prompt for user then pass

    //check password.txt file to check if user and pass match, prompt up to 3 times then timeout for 30 seconds before accepting login attempt

}