#include <stdio.h>
#include <gpiod.h>

#include "communication.h"
#include "faultDetector.h"
#include "recloserAuth.h"

/**
 * Structure holding the Recloser configuration 
 */
struct recloserConfig {
    /**
     * Reclose attempts
     */
    int recloseAttempts;

    /**
     * The duration the recloser will open for on first cycle (ms)
     */
    int recloseOpenInterval1;

    /**
     * The duration the recloser will open for on first cycle (ms)
     */
    int recloseOpenInterval2;

    /**
     * The duration the recloser will open for on first cycle (ms)
     */
    int recloseOpenInterval3;

    /**
     * The duration the recloser will open for on first cycle (ms)
     */
    int recloseOpenInterval4;

    /** the topics that the recloser subscribes to */
    char *subcriptions[];

}

/**
 * Prompt for recloser configuration
 * @param 
 */ 
recloserStartup() {
    //authentication
    login();
    
    //check for existing configuration file and print it
    config(struct RecloserConfig);
}

/** 
 * opens recloser
 */
openRecloser() {

}

/** 
 * closes recloser
 */
closeRecloser() {

}

/**
 * If manually switched for segment maintenece 
 */
manualSwitch() {

}

/** 
 * Recloser cycles during fault detection 
 * @returns cycleStatus whether the recloser is open or closed
 */
initiateCycle() {
    //open recloser for x seconds

    //close and check for fault if no fault remain closed and exit, if fault, continue for y cycles

    //if max cycles are complete. Leave recloser open and change recloser status
}


int main() {
    //takes care of authentication and configuration
    //we will use a default username of 'admin' for system setup
    recloserStartup();


    //when tech plugs into recloser program will display
    print("Recloser is active\n");
    //prompt for login
    
    print("Enter 1 to change config\n");

    //runs the main functions of the recloser
    while() {
        

        //sc
    }

    return 0;
}