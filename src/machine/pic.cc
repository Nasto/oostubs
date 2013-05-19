/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                   Technische Informatik II                                    * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 *                                                                                               * 
 *                                            P I C                                              * 
 *                                                                                               * 
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    INCLUDES                     #
\* * * * * * * * * * * * * * * * * * * * * * * * */
#include "machine/pic.h"
#include "machine/io_port.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

/** \todo \~german verstehen \~english understand */
PIC::PIC(){
  IO_Port ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1);
  //initialising the PIC's registers
  //I have no idea about the specific values used here
  ctrl_1.outb(0x11);
  ctrl_2.outb(0x11);
  
  mask_1.outb(32);
  mask_2.outb(40);
  
  mask_1.outb(4);
  mask_2.outb(2);
  
  mask_1.outb(3);
  mask_2.outb(3);
  
  mask_1.outb(0xFB);
  mask_2.outb(0xFF);
}

void PIC::allow(Interrupts interrupt){
    IO_Port mask_1(0x21), mask_2(0xa1); //registers we need to write to

    CPU::enable_int();              //allowing a special interrupt is pointless if interrupts are disabled globally

    unsigned char ocw1;

    if (interrupt <= 8){            //first PIC
        ocw1 = mask_1.inb();        //get current state to ensure previous bits stay setted
        ocw1 &= ~(1 << interrupt);  //set the curresponding bit to 0 so that it's allowed
        mask_1.outb(ocw1);          //and write it to the register
    } else {                        //second PIC
        ocw1 = mask_2.inb();
        ocw1 &= ~(1<<(interrupt-8));
        mask_2.outb(ocw1);
    }

}

void PIC::forbid(Interrupts interrupt){
    IO_Port mask_1(0x21), mask_2(0xa1);

    unsigned char ocw1;

    if (interrupt <= 8){            //first PIC
        ocw1 = mask_1.inb();        //get current state to ensure previous bits stay setted
        ocw1 |= (1 << interrupt);   //set the curresponding bit to 1 so that it's forbidden
        mask_1.outb(ocw1);          //and write it to the register
    } else {                        //second PIC
        ocw1 = mask_2.inb();
        ocw1 |= (1<<(interrupt-8));
        mask_2.outb(ocw1);
    }
}


/** \todo \~german implementieren \~english write implementation*/
void PIC::ack(bool secondPIC){
    IO_Port ctrl_1(0x20), ctrl_2(0xa0);

    //I'm done here
    ctrl_1.outb(0x20);
    ctrl_2.outb(0x20);
}

/** \todo \~german implementieren \~english write implementation*/
unsigned char PIC::getISR(bool secondPIC){
  ///todo remove dummy
  return 0;
}
