/*
 * Title: IR Demo Code
 * Author: James Fotherby
 * Date: 6/4/2016

  This code demonstates all that is required for IR receiving using the GMC protocols. Ensure the IR receive is powered properly.
*/

//--- Defines: -------------------------------------------------------------------
#define   IR_In                       11                                          // PB3 which is PCINT3
#define   IR_IN_STATE                 PINB & 0x08                                 //digitalRead(IR_In) - (If you change the IR_In pin this needs changing too!

//--- Includes: ------------------------------------------------------------------
#include "IR_Receive.h"

//--- Globals: -------------------------------------------------------------------
IR_Receive IR_Rx;                                                                 // Create instance of the IR_Receive Class

//--- Setup: ---------------------------------------------------------------------
void setup() 
{     
  Serial.begin(115200);
  Serial.println("Waiting for IR Data...");

  pinMode(IR_In, INPUT_PULLUP);

  IR_Rx.Configure_Timer2_Interrupts();                                            // Configure timer2 for Compare A match interrupts. 

  // Pin change interrupts:
  PCMSK0 = 0b00001000;                                                            // Unmask interrupt on PCINT3 (pin 11)  (IR_In) 
  PCICR = 0b00000001;                                                             // Enable Interrupts on PCI_0
}

//--- Main: ----------------------------------------------------------------------
void loop() 
{
  //IR_Rx.Set_Expected_Bits(17);
  
  if(long IR_Data = IR_Rx.Check_Data())
    Serial.println(IR_Data, BIN);  
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//########## INTERRUPT DETECTION ROUTINES ###############################################################################################################################
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
ISR (TIMER2_COMPA_vect)                                                           // IR dedicated timer compare match  
{  
  IR_Rx.Timer_Interrupt();                                                        
} 

//--------------------------------------------------------------------------------
ISR (PCINT0_vect)                                                                 // IR_Pin Change. It doesn't matter what interrupt triggers this
{ 
  IR_Rx.Pin_Change_Interrupt();                                                   // This must be called on an IR Pin change to receive data. 
}


