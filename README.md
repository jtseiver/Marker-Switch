# Marker-Switch
MARKER LIGHT SWITCH
2021 Terry Seiver
 
Written for ATTiny85, although I would expect an ATTiny84 could also be used and would allow for far more I/O pins. 

This program enables a model locomotive with a basic DCC decoder to cycle between various lighting modes. The lighting modes are based on NSWGR/SRA prototype for locomotive marker lights, and utilise a headlight / rearlight functions as a means of control. 

The program assume the decoder is programmed to alternate between headlight and rearlight based on direction.

The modes are:
    1) off (default)
    2) directional - both markers 
    3) both red

 ATTiny pins used:
  
                       +====+
     rearlight (PB5) 1 |*   | 8 Fn common (Vcc)
     headlight (PB3) 2 |    | 7 frnt rd mrkr (PB2)
  frnt wh mrkr (PB4) 3 |    | 6 rear wh mrkr (PB1)
                 Gnd 4 |    | 5 rear rd mrkr (PB0)
                       +====+
  
