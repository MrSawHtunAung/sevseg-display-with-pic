# sevseg-display-with-pic | CCS(PCWHD) compiler 
3 digit 7 segment display multiplexing with PIC 16f677 CCS C 

Connect C0 to C6 to the segment A to G.

Connect B5 to A7 to the digit 1 to 3.

![image](https://github.com/MrSawHtunAung/sevseg-display-with-pic/assets/139736012/8de11dee-e763-4873-a29f-7096a9cdde42)

## You just only need to change number in Show( ); function. 
```cpp

void main() {
   CPU_SETUP(); 
   while (true){
      Show(123);  		// The number that you want to display.
   }
}
```
THANK YOU.
