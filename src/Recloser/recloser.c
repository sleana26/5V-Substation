#include <stdio.h>
#include <gpiod.h>
#include <config.h>
#include <communication.h>
#include <faultDetector.h>
#include <authentication.h>

/**
 * Prompt for recloser configuration
 * @param 
 */ 
recloserStartup() {
    //authentication

    //check for existing configuration and print it

    //make sure user wants to proceed with existing configuration

    //NEED TO MAKE SURE NO RECLOSER IS SET UP AND READY BEFORE
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

/**
 * transmits data via MQTT using websockets. Sends information such as voltage, recloser status, to broker
 */
transmitData() {

}



int main() {
    //takes care of authentication and configuration
    if(login()) {
        config();
        logout();
    }

    //when tech plugs into recloser program will display
    print("Recloser is active\n");
    print("Enter 1 to change config\n");

    //runs the main functions of the recloser
    while() {
        

        //sc
    }

    return 0;
}