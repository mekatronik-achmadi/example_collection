# Simple AVR Example

## Simulation

This example show a very simple routine using a pulled-up button and a LED.

Simulation provided by Simul-IDE, you can visit or get install package from their [website](https://www.simulide.com/p/home.html).

Alternatively, for Arch-Linux user, its recommended to be installed from this [AUR](https://aur.archlinux.org/packages/simulide)

For this example, ATMega16 used with pin C5 and C6 for I/O.

![images](images/avrsim.gif?raw=true)

## BASCOM AVR

Here example in BASIC language.
Source example and its compiled binary can be found in *bascomavr* folder.

```basic
$regfile = "m16def.dat"
$crystal = 16000000

'C6 as output
Ddrc.6 = 1

'C5 as pull up button
Portc.5 = 1

Do
   If Pinc.5 = 1 Then
      Portc.6 = 0
   Else
      Portc.6 = 1
   End If
Loop

End
```

Tested on BASCOM IDE 2.0.7 run on Arch-Linux via Wine.

## GCC AVR

Here example in C language.
Source example and its compiled binary can be found in *winavrgcc* folder.

```c
#include <avr/io.h>
#include <util/delay.h>

int main(void){
    DDRC |= 1<<6; // A4 as output
    PORTC |= 1<<5; // A3 as Pull up Input

    while (1) {

        //if button unpressed pulled high
        if(PINC & (1<<5)){
            PORTC &= ~(1<<6);
        }

        else{
            PORTC |= 1<<6;
        }

        _delay_ms(100);
    }
    return 0;
}
```

Tested on GCC AVR 12 with recent GNU Make on Arch-Linux.

It should be also tested on winAVR package for Windows. 
You can visit their [website](https://winavr.sourceforge.net/).