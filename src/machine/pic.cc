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
#include "useful/cpu.h"


/* * * * * * * * * * * * * * * * * * * * * * * * *\
#                    METHODS                      # 
\* * * * * * * * * * * * * * * * * * * * * * * * */

PIC::PIC(){
  IO_Port ctrl_1(0x20), ctrl_2(0xa0), mask_1(0x21), mask_2(0xa1);
  //initialising the PIC's registers
  //Set ICW1 so we can initialise
  ctrl_1.outb(0x11);
  ctrl_2.outb(0x11);
  
  //initialise ICW2
  mask_1.outb(32);      //offset for the IRQs
  mask_2.outb(40);      //offset for the second PIC

  //initialise ICW3
  mask_1.outb(4);       //IRQ on the master for the slave
  mask_2.outb(2);       //IRQ on the slave for the master

  //initialise ICW4
  mask_1.outb(3);       //0b11 -> automatic End Of Interrupt and 8086-architecture
  mask_2.outb(3);
  
  //initialise OCW1
  mask_1.outb(0xFB);    //PIC1 (master) - allow only D2 -> slave
  mask_2.outb(0xFF);    //PIC2 (slave) - allow none
}

void PIC::allow(Interrupts interrupt){
    IO_Port mask_1(0x21), mask_2(0xa1); //registers we need to write to

    unsigned char ocw1;

    if (interrupt <= 8){            //first PIC
        ocw1 = mask_1.inb();        //get current state to ensure previous bits stay set
        ocw1 &= ~(1 << interrupt);  //set the corresponding bit to 0 so that it's allowed
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
        ocw1 = mask_1.inb();        //get current state to ensure previous bits stay set
        ocw1 |= (1 << interrupt);   //set the corresponding bit to 1 so that it's forbidden
        mask_1.outb(ocw1);          //and write it to the register
    } else {                        //second PIC
        ocw1 = mask_2.inb();
        ocw1 |= (1<<(interrupt-8));
        mask_2.outb(ocw1);
    }
}

void PIC::ack(bool secondPIC){
    IO_Port ctrl_1(0x20), ctrl_2(0xa0);

    //I'm done here
    if(secondPIC){
        ctrl_1.outb(0x20);
        ctrl_2.outb(0x20);
    } else {
        ctrl_1.outb(0x20);
    }
}

unsigned char PIC::getISR(bool secondPIC){
    IO_Port ctrl_1(0x20), ctrl_2(0xa0);
    unsigned char ret;

    if(secondPIC){
        ctrl_2.outb(0x0b);      //set OCW3 so we get ISR
        ret = ctrl_2.inb();     //get ISR
    } else {
        ctrl_1.outb(0x0b);
        ret = ctrl_1.inb();
    }

  return ret;
}
