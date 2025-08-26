#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
void delayMs(int n);
int main(void)
{
SYSCTL_RCGC2_R |= 0x20; // Enable clock to Port F
GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock PF0
GPIO_PORTF_CR_R = 0x1F; // Commit PF0–PF4
GPIO_PORTF_DEN_R = 0x1F; // Digital enable PF0–PF4
GPIO_PORTF_DIR_R = 0x0E; // PF1–PF3 output (LEDs), PF0 & PF4 input
GPIO_PORTF_PUR_R = 0x11; // Enable pull-up on PF0 & PF4
int count = 0;
uint32_t colors[3] = {0x02, 0x08, 0x04}; // Red, Green, Blue
while(1)
{
if (!(GPIO_PORTF_DATA_R & 0x01)) // Read SW2 (PF0)
{
delayMs(20); // debounce
if (!(GPIO_PORTF_DATA_R & 0x01)) // still pressed
{
count = (count + 1) % 3;
GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~0x0E) | colors[count];
while (!(GPIO_PORTF_DATA_R & 0x01)); // wait release
delayMs(20);
}
}
}
}
void delayMs(int n)
{
volatile int i, j;
for(i = 0; i < n; i++)
for(j = 0; j < 3180; j++) {} // ~1ms delay at 16 MHz
}
