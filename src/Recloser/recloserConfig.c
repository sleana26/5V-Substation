/**
 * recloserConfig will take care of the configuration of the recloser. The modeled recloser is comprised of the
 * relay and the potentiometer. There will be an initial configuration prior to initial commisioning. There will be an
 * option to change configuration from the SCADA control room
 * 
 * @author Sean Leana
 * @file recloserConfig
 */

#include <stdio.h>
#include <gpiod.h>
#include <authentication.h>


/**
* Prompts for recloser configuration and writes it to config file. Normal status, whether the 
* recloser is normally open or normally closed. Max number of cycles that recloser will run
* after detecting a fault before remaining open. Open interval is the duration the recloser
* is open for a single cycle
*/ 
initialConfig() {
    //asks for authentication credentials

    //prompts for settings(eg. normalStatus NO or NC, maxCycles, openInterval)
    
    //checks edge cases and sends an error message if entered values are not correct

    //writes to config file

    //lets user know that configuration was successful
}

/**
* change recloser configuration. Prompts if user would like to change each setting.
* (eg "Change normal status? y/n")
*/
changeConfig() {
    //asks for authentication credentials

    //prompts for each setting (eg "Change normal status? y/n")

    //checks edge cases and sends an error message if entered values are not correct

    //writes to config file

    //lets user know that recloser settings have been updated
}