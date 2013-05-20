/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                         P L U G B O X                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/plugbox.h"
#include "useful/panic.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

//constructor
Plugbox::Plugbox(){

    for(int i=0;i<256;i++){
        assign(i,panic);            //initialise every slot to panic
    }
}

void Plugbox::assign(unsigned short slot, Gate& gate){
    gates[slot] = &gate;            //just put the corresponding gate in the class-array
}

Gate& Plugbox::report(unsigned short slot){
    if(slot<256){
        return *(gates[slot]);      //return the gate for the interrupt
    } else {
        return panic;               //invalid interrupts get panic anyways
    }
}
