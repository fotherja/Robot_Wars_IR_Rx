# Robot_Wars_IR_Rx
This Repository contains a Arduino Uno class for abstracting away the protocols used for robust IR receiving needed for the GMC. There is also an attached minimal example to demo use.

The protocols used by the class for those interested are:
 - Manchested encoded data
 - 1 to 32 bits per packet
 - 800us bit period
 - 200us/600us or 600/200us high/low times for channel 1 / channel 2 start bits
 - Although it doesn't have to be the case, a packet is expected to start every 40ms
