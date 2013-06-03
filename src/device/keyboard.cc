/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                       K E Y B O A R D                                         * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "device/keyboard.h"
#include "useful/plugbox.h"
#include "useful/kout.h"
#include "useful/pic.h"

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */
Keyboard::Keyboard(){
    //super-class construcors (without arguments) are called automatically
}

void Keyboard::plugin(){
    plugbox.assign(33,*this);
    pic.allow(PIC::keyboard);
}

void Keyboard::trigger(){
    Key k = key_hit();

    if(k.ctrl() && k.alt() && (k.scancode()==83)){
        reboot();
    } else {
        if(k.valid()){
            kout.setpos(20,15);
            kout << k;
        }
    }
}
