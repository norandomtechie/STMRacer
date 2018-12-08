/**
  ******************************************************************************
  * @file    main.c
  * @author  Karthick Shankar, Niraj Menon, Shreya Ilango
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"
#include "stdlib.h"

// int pixels[10] = {942, 943, 944, 945, 973, 974, 977, 978, 1005, 1010};
int pixels[16] = {942, 943, 944, 945, 973, 974, 975, 976, 977, 978, 1005, 1006, 1007, 1008, 1009, 1010};

char screen[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // 0
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // 7
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // 15
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,       // 23
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,
                 0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0};      // 31

                        // Left Center = 1007 (13 spaces), Right center = 1008 (13 spaces)
                        /*
                            Using left center, we have 25 (0 - 24) spaces.
                            ...77, 78, 79, ***80***, 81, 82, 83...
                        */
						/*					  Car pixels
							942, 943, 944, 945, 973, 974, 977, 978, 1005, 1010
						*/

                        /*                  Obstacle
                                            0   1   0
                                            1   0   1
                                            0   1   0
                        */

char start_1[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          // 0
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,
                  0,1,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,1,0,
                  0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,0,1,1,0,1,1,1,0,
                  0,0,1,0,0,1,0,0,1,0,1,0,1,0,1,1,0,0,1,0,1,0,1,0,0,1,0,0,1,1,0,0,
                  0,1,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,0};         // 6

char start_2[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          // 7
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0};         // 14

char start_3[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          // 15
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0};         // 21

char start_4[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,          // 22
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
                  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};         // 31

char game_over[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,0,1,1,1,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int high_score[] = {33,35,37,39,40,41,43,45,47,48,50,51,53,54,55,57,58,59,61,62,62,
                    65,67,69,71,75,77,79,82,85,87,89,91,93,97,98,99,101,103,107,108,
                    109,111,112,114,117,119,121,122,123,125,126,126,129,131,133,135,
                    137,139,141,144,146,149,151,153,154,157,161,163,165,167,168,169,
                    171,173,175,176,178,179,181,182,183,185,187,189,190,190,291,323,
                    355,387,419,421,545,546,547,579,609,610,611,641,673,674,675,677,
                    801,802,803,835,865,866,867,899,929,930,931,933};

int num_char_1[] = {311,343,375,407,439};
int num_char_2[] = {311,312,313,345,375,376,377,407,439,440,441};
int num_char_3[] = {311,312,313,345,375,376,377,409,439,440,441};
int num_char_4[] = {311,343,345,375,376,377,409,441};
int num_char_5[] = {311,312,313,343,375,376,377,409,439,440,441};
int num_char_6[] = {311,312,313,343,375,376,377,407,409,439,440,441};
int num_char_7[] = {311,312,313,345,377,409,441};
int num_char_8[] = {311,312,313,343,345,375,376,377,407,409,439,440,441};
int num_char_9[] = {311,312,313,343,345,375,376,377,409,441};
int num_char_0[] = {311,312,313,343,345,375,377,407,409,439,440,441};

#define GPIOset(GPIOx, NUM) (GPIOx -> BSRR = 1 << NUM)
#define GPIOclr(GPIOx, NUM) (GPIOx -> BRR  = 1 << NUM)

// Pin-out on GPIOC to display
#define LED_G1  0       // Top half green
#define LED_G2  1       // Bottom half green
#define LED_B   2       // Row select B
#define LED_D   3       // Row select D
#define LED_LAT 4       // Latch signal to indicate end of data
#define LED_R1  5       // Top half red
#define LED_B1  6       // Top half blue
#define LED_R2  7       // Bottom half red
#define LED_B2  8       // Bottom half blue
#define LED_A   9       // Row select A
#define LED_C   10      // Row select C
#define LED_CLK 11      // Clock signal
#define LED_OE  12      // Output enable (GND to turn on, VCC to turn off)

// Programming constants
#define FUNC_SUCCESS 1
#define FUNC_FAILURE 0

// Main file for STMRacer

int configurePorts (void);              // Set up GPIO pins
int testInput (void);                   // Move the car when triggering one of two inputs
int flashScreen (void);                 // Flash all LEDs with different colors - use as test
void printOneRow (int half, int row, char* data);
int displayMainMenu (void);         // New Game, High Scores, Reset
int gameInit (void);                // Change screen and enable timer, PWM,
int printImageMap (char* map);     // Given an image map, print it to the screen
void configureDisplay();
void tim1_init();
void tim3_init();
char readchar();
int** determinePixelSet (int val);

static void nano_wait(int t) {
    asm("       mov r0,%0\n"
        "repeat:\n"
        "       sub r0,#83\n"
        "       bgt repeat\n"
        : : "r"(t) : "r0", "cc");
}

int score = 0;
int main(void)
{
    configurePorts();
    configureDisplay();
    init_lcd();
    display1 ("Timer: 00:00:00");

    initStartSequence();
    init_usart2();
    parseUSARTinput();
    init_tim2();
    tim14_init();
    tim3_init();
    return 0;
}

void initStartSequence()
{
    int freerun = 500;
    while (freerun != 0)
    {
        printImageMap_startSequence (start_1, 1);
        freerun--;
    }

    freerun = 250;
    while (freerun != 0)
    {
        printImageMap_startSequence (start_1, 1);
        printImageMap_startSequence (start_2, 2);
        freerun--;
    }

    freerun = 125;
    while (freerun != 0)
    {
        printImageMap_startSequence (start_1, 1);
        printImageMap_startSequence (start_2, 2);
        printImageMap_startSequence (start_3, 3);
        freerun--;
    }

    freerun = 100;
    while (freerun != 0)
    {
        printImageMap_startSequence (start_1, 1);
        printImageMap_startSequence (start_2, 2);
        printImageMap_startSequence (start_3, 3);
        printImageMap_startSequence (start_4, 4);
        freerun--;
    }
}

int printImageMap_startSequence (char* map, int opt)
{
	char line[32] = {0};
    int pixels = 0;
    int row = 0;
    int half = 0;
    switch (opt)
    {
        case 1:
            pixels = 224;
            row = 0;
            half = 0;
        break;

        case 2:
            pixels = 256;
            row = 7;
            half = 0;
        break;

        case 3:
            pixels = 224;
            row = 15;
            half = 1;
        break;

        case 4:
            pixels = 320;
            row = 22;
            half = 1;
        break;
    }
	for (int i = 0; i < pixels; i += 32)
	{
		for (int j = i; j < i + 32; j++)
		{
			line[j - i] = map [j];
		}
		printOneRow (half, row++, line);
		row = row == 32 ? 0 : row;
	}
}

void gameOver(){
    int freerun = 350;
    while (freerun != 0)
    {
        printImageMap (game_over);
        freerun--;
    }
    // freerun = 1000;
    // while (freerun != 0)
    if (score < 250)
    {
      viewHighScore (250, 255, 300);
    }
    else if (score > 250 && score < 260)
    {
      viewHighScore (250, score, 300);
    }
    else
    {
      viewHighScore (250, 255, score);
    }
    while (1)
    {
        printImageMap (screen);
    }
}

// to move a number to the second score:
// Add 32*8

// to move a number to the third score:
// Add 32*16

// to move a number to the one's place:
// Add 4

void viewHighScore (int lo, int mi, int hi)
{
    for (int i = 0; i < 1024; i++)
    {
      screen [i] = 0;
    }
    for (int i = 0; i < (sizeof high_score / sizeof (int)); i++)
    {
      screen [high_score [i]] = 1;
    }

    int low = lo;
    int mid = mi;
    int high = hi;

   convertCharToPixel (high, 0);
   convertCharToPixel (mid, 1);
   convertCharToPixel (low, 2);
}

void convertCharToPixel (int score, int opt)
{
    int low_dig = score % 10;
    int high_dig = (score / 10) % 10;
    int high_2_dig = score / 100;

    int low_pixel_set[13];
    int high_pixel_set[13];
    int high_2_pixel_set[13];

    char high_2_pixel_size = 0;
    char high_pixel_size = 0;
    char low_pixel_size = 0;

    switch (low_dig)
    {
        case 0:
            memcpy (low_pixel_set, num_char_0, sizeof (num_char_0));
            low_pixel_size = sizeof (num_char_0) / sizeof (int);
            break;
        case 1:
            memcpy (low_pixel_set, num_char_1, sizeof (num_char_1));
            low_pixel_size = sizeof (num_char_1) / sizeof (int);
            break;
        case 2:
            memcpy (low_pixel_set, num_char_2, sizeof (num_char_2));
            low_pixel_size = sizeof (num_char_2) / sizeof (int);
            break;
        case 3:
            memcpy (low_pixel_set, num_char_3, sizeof (num_char_3));
            low_pixel_size = sizeof (num_char_3) / sizeof (int);
            break;
        case 4:
            memcpy (low_pixel_set, num_char_4, sizeof (num_char_4));
            low_pixel_size = sizeof (num_char_4) / sizeof (int);
            break;
        case 5:
            memcpy (low_pixel_set, num_char_5, sizeof (num_char_5));
            low_pixel_size = sizeof (num_char_5) / sizeof (int);
            break;
        case 6:
            memcpy (low_pixel_set, num_char_6, sizeof (num_char_6));
            low_pixel_size = sizeof (num_char_6) / sizeof (int);
            break;
        case 7:
            memcpy (low_pixel_set, num_char_7, sizeof (num_char_7));
            low_pixel_size = sizeof (num_char_7) / sizeof (int);
            break;
        case 8:
            memcpy (low_pixel_set, num_char_8, sizeof (num_char_8));
            low_pixel_size = sizeof (num_char_8) / sizeof (int);
            break;
        case 9:
            memcpy (low_pixel_set, num_char_9, sizeof (num_char_9));
            low_pixel_size = sizeof (num_char_9) / sizeof (int);
            break;
    }

    switch (high_2_dig)
    {
      case 0:
          memcpy (high_2_pixel_set, num_char_0, sizeof (num_char_0));
          high_2_pixel_size = sizeof (num_char_0) / sizeof (int);
          break;
      case 1:
          memcpy (high_2_pixel_set, num_char_1, sizeof (num_char_1));
          high_2_pixel_size = sizeof (num_char_1) / sizeof (int);
          break;
      case 2:
          memcpy (high_2_pixel_set, num_char_2, sizeof (num_char_2));
          high_2_pixel_size = sizeof (num_char_2) / sizeof (int);
          break;
      case 3:
          memcpy (high_2_pixel_set, num_char_3, sizeof (num_char_3));
          high_2_pixel_size = sizeof (num_char_3) / sizeof (int);
          break;
      case 4:
          memcpy (high_2_pixel_set, num_char_4, sizeof (num_char_4));
          high_2_pixel_size = sizeof (num_char_4) / sizeof (int);
          break;
      case 5:
          memcpy (high_2_pixel_set, num_char_5, sizeof (num_char_5));
          high_2_pixel_size = sizeof (num_char_5) / sizeof (int);
          break;
      case 6:
          memcpy (high_2_pixel_set, num_char_6, sizeof (num_char_6));
          high_2_pixel_size = sizeof (num_char_6) / sizeof (int);
          break;
      case 7:
          memcpy (high_2_pixel_set, num_char_7, sizeof (num_char_7));
          high_2_pixel_size = sizeof (num_char_7) / sizeof (int);
          break;
      case 8:
          memcpy (high_2_pixel_set, num_char_8, sizeof (num_char_8));
          high_2_pixel_size = sizeof (num_char_8) / sizeof (int);
          break;
      case 9:
          memcpy (high_2_pixel_set, num_char_9, sizeof (num_char_9));
          high_2_pixel_size = sizeof (num_char_9) / sizeof (int);
          break;
    }

    switch (high_dig)
    {
      case 0:
          memcpy (high_pixel_set, num_char_0, sizeof (num_char_0));
          high_pixel_size = sizeof (num_char_0) / sizeof (int);
          break;
      case 1:
          memcpy (high_pixel_set, num_char_1, sizeof (num_char_1));
          high_pixel_size = sizeof (num_char_1) / sizeof (int);
          break;
      case 2:
          memcpy (high_pixel_set, num_char_2, sizeof (num_char_2));
          high_pixel_size = sizeof (num_char_2) / sizeof (int);
          break;
      case 3:
          memcpy (high_pixel_set, num_char_3, sizeof (num_char_3));
          high_pixel_size = sizeof (num_char_3) / sizeof (int);
          break;
      case 4:
          memcpy (high_pixel_set, num_char_4, sizeof (num_char_4));
          high_pixel_size = sizeof (num_char_4) / sizeof (int);
          break;
      case 5:
          memcpy (high_pixel_set, num_char_5, sizeof (num_char_5));
          high_pixel_size = sizeof (num_char_5) / sizeof (int);
          break;
      case 6:
          memcpy (high_pixel_set, num_char_6, sizeof (num_char_6));
          high_pixel_size = sizeof (num_char_6) / sizeof (int);
          break;
      case 7:
          memcpy (high_pixel_set, num_char_7, sizeof (num_char_7));
          high_pixel_size = sizeof (num_char_7) / sizeof (int);
          break;
      case 8:
          memcpy (high_pixel_set, num_char_8, sizeof (num_char_8));
          high_pixel_size = sizeof (num_char_8) / sizeof (int);
          break;
      case 9:
          memcpy (high_pixel_set, num_char_9, sizeof (num_char_9));
          high_pixel_size = sizeof (num_char_9) / sizeof (int);
          break;
    }

    for (int i = 0; i < low_pixel_size; i++)
    {
        switch (opt)
        {
            case 0:
                screen [low_pixel_set [i] + 4] = 3;
                break;

            case 1:
                screen [low_pixel_set [i] + 32 * 8 + 4] = 3;
                break;

            case 2:
                screen [low_pixel_set [i] + 32 * 16 + 4] = 3;
                break;
        }
    }

    for (int i = 0; i < high_pixel_size; i++)
    {
        switch (opt)
        {
            case 0:
                screen [high_pixel_set [i]] = 3;
                break;

            case 1:
                screen [high_pixel_set [i] + 32 * 8] = 3;
                break;

            case 2:
                screen [high_pixel_set [i] + 32 * 16] = 3;
                break;
        }
    }

    for (int i = 0; i < high_2_pixel_size; i++)
    {
        switch (opt)
        {
            case 0:
                screen [high_2_pixel_set [i] - 4] = 3;
                break;

            case 1:
                screen [high_2_pixel_set [i] + 32 * 8 - 4] = 3;
                break;

            case 2:
                screen [high_2_pixel_set [i] + 32 * 16 - 4] = 3;
                break;
        }
    }
}

void configureDisplay(void)
{
	//Begin with OE, CLK and LAT low
	GPIOclr(GPIOC, LED_OE);
	GPIOclr(GPIOC, LED_CLK);
	GPIOclr(GPIOC, LED_LAT);
}

int printImageMap (char* map)
{
	char line[32] = {0};
	int row = 0;
	for (int i = 0; i < 1024; i += 32)
	{
		for (int j = i; j < i + 32; j++)
		{
			line[j - i] = map [j];
		}
		printOneRow (i < 512 ? 0 : 1, row++, line);
		row = row == 32 ? 0 : row;
	}
}

void printOneRow (int half, int row, char* data){
    for(int i = 0; i < 32; i++){
		if (data[i] == 0)
		{
			if (!half)	// Top half
			{
				GPIOclr (GPIOC, LED_R1);
				GPIOclr (GPIOC, LED_B1);
				GPIOclr (GPIOC, LED_G1);
			}
			else
			{
				GPIOclr (GPIOC, LED_R2);
				GPIOclr (GPIOC, LED_B2);
				GPIOclr (GPIOC, LED_G2);
			}
		}
		else if (data[i] == 1)
		{
			if (!half)
			{
				GPIOset (GPIOC, LED_R1);
				GPIOset (GPIOC, LED_B1);
				GPIOset (GPIOC, LED_G1);
			}
			else
			{
				GPIOset (GPIOC, LED_R2);
				GPIOset (GPIOC, LED_B2);
				GPIOset (GPIOC, LED_G2);
			}
		}
		else if (data[i] == 2)
        {
            if (!half)
            {
                GPIOclr (GPIOC, LED_R1);
                GPIOset (GPIOC, LED_B1);
                GPIOset (GPIOC, LED_G1);
            }
            else
            {
                GPIOclr (GPIOC, LED_R2);
                GPIOset (GPIOC, LED_B2);
                GPIOset (GPIOC, LED_G2);
            }
        }
		else if (data[i] == 3)
        {
            if (!half)
            {
                GPIOclr (GPIOC, LED_R1);
                GPIOclr (GPIOC, LED_B1);
                GPIOset (GPIOC, LED_G1);
            }
            else
            {
                GPIOset (GPIOC, LED_R2);
                GPIOclr (GPIOC, LED_B2);
                GPIOclr (GPIOC, LED_G2);
            }
        }
        else if (data[i] == 4)
        {
            if (!half)
            {
                GPIOclr (GPIOC, LED_R1);
                GPIOclr (GPIOC, LED_B1);
                GPIOset (GPIOC, LED_G1);
            }
            else
            {
                GPIOset (GPIOC, LED_R2);
                GPIOclr (GPIOC, LED_B2);
                GPIOclr (GPIOC, LED_G2);
            }
        }
        GPIOset(GPIOC, LED_CLK);
		nano_wait (5000);
        GPIOclr(GPIOC, LED_CLK);
		nano_wait (5000);
    }
    GPIOset(GPIOC, LED_OE);
    GPIOset(GPIOC, LED_LAT);
    GPIOclr(GPIOC, LED_LAT);

    //Set ABCD
    GPIOC->BSRR = 0;
    GPIOC->BSRR = 1 << (16 * (1 - (row & 1)) + LED_A);
    GPIOC->BSRR = 1 << (16 * (1 - ((row & 2) >> 1)) + LED_B);
    GPIOC->BSRR = 1 << (16 * (1 - ((row & 4) >> 2)) + LED_C);
    GPIOC->BSRR = 1 << (16 * (1 - ((row & 8) >> 3)) + LED_D);

    GPIOclr(GPIOC, LED_OE);
}


int configurePorts (void)
{
    // Set up Port C to set all pins as outputs
    RCC -> AHBENR |= RCC_AHBENR_GPIOCEN;
    RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
    GPIOA -> MODER &= ~((3 << 2 * 9) | (3 << 2 * 8) | (3 << 2 * 10));
    GPIOA -> MODER |= 1 << (2 * 10);
    for (int i = 0; i <= 12; i++)
    {
        GPIOC -> MODER &= ~(3 << (i * 2));
        GPIOC -> MODER |= 1 << (i * 2);
    }

    return FUNC_SUCCESS;
}

int cur_pos = 120;
int new_pos = 120;
int game_over_flag = 0;

void parseUSARTinput (void)
{
    new_pos = readchar ();

    if (new_pos % 10 > 5)      // Fine tuning car movement
    {
    	return;
    }
    else
    {
        new_pos = (new_pos / 10) * 10;
    }
//	sprintf(line, "cur_pos: %d", cur_pos);
//	display2(line);

	if (new_pos < cur_pos)// && TIM3->CNT % 10 == 0)
	{
        for (int j = 0; j < (cur_pos - new_pos) / 10; j++)
		{
            for (int i = 0; i < sizeof (pixels) / sizeof (int); i++)
            {
                if (screen [pixels [i] - 1] == 3)
                {
                    TIM2 -> CR1 &= ~TIM_CR1_CEN;
                    game_over_flag = 1;
                    gameOver();
                }
                screen [pixels [i] - 1] = 2;
                screen [pixels [i]] = 0;
                pixels [i] = pixels [i] - 1;
            }
		}
	}
	else if (new_pos > cur_pos)// && TIM3->CNT % 10 == 0)
	{
        for (int j = 0; j < (new_pos - cur_pos) / 10; j++)
		{
            for (int i = sizeof (pixels) / sizeof (int) - 1; i >= 0 ; i--)
            {
                if (screen [pixels [i] + 1] == 3)
                {
                    TIM2 -> CR1 &= ~TIM_CR1_CEN;
                    game_over_flag = 1;
                    gameOver();
                }
                screen [pixels [i] + 1] = 2;
                screen [pixels [i]] = 0;
                pixels [i] = pixels [i] + 1;
            }
		}
	}
    cur_pos = new_pos;
}

void TIM3_IRQHandler(void){
	TIM3->CR1 &= ~TIM_CR1_CEN;
	if (!game_over_flag)
	{
		printImageMap (screen);
		parseUSARTinput();
	}
	else
	{
		if ((TIM3 -> SR & TIM_SR_UIF) != 0)
		{
			TIM3 -> SR &= ~TIM_SR_UIF;
		}
		gameOver();
	}

	if ((TIM3 -> SR & TIM_SR_UIF) != 0)
	{
		TIM3 -> SR &= ~TIM_SR_UIF;
	}
	TIM3->CR1 |= TIM_CR1_CEN;
}


int ob_row = 0;
// char obstacle[] = {0, 3, 0,
//                    3, 0, 3,
//                    0, 3, 0};
char obstacle[] = { 3,3,3,
                    3,0,3,
                    3,0,3,
                    3,0,3,
                    3,3,3};
int num_obs = 5;
int randint = 5;
void TIM2_IRQHandler (void)
{

    if (ob_row == 0){
        /*int bit7 = (lfsr >> 7) & 1;
        int bit3 = (lfsr >> 3) & 1;
        bit7 ^= bit3;
        lfsr = lfsr << 1;
        lfsr |= bit7;
        randint = lfsr % 32;
        lfsr += randint;*/
        randint = rand() % 32;
    }

    if(randint > 28){
        randint = 28;
    }
    int continue_flag = 0;
    for(int i = 1023; i > 31; i--){
        if(screen [i] == 2){
            continue;
        }
        //TRansition from up to down
        screen[i] = screen[i-32];

        if(screen[i] == 3 && screen[i+32] == 2)
            {
            TIM2->CR1 &= ~TIM_CR1_CEN;
            gameOver();
        }
    }


    for (int i = 0; i < 32; i++){
        screen [i] = 0;
    }
    if (ob_row <= 5){
        for (int i = 0; i < 3; i++)
        {
             screen [randint+i] = obstacle[i+3*ob_row];
        }
    }



    ob_row++;
    if(ob_row == 20){
        ob_row = 0;
    }
    if ((TIM2 -> SR & TIM_SR_UIF) != 0)
    {
        TIM2 -> SR &= ~TIM_SR_UIF;
    }
}

void TIM14_IRQHandler (void) {
	if ((TIM14 -> SR & TIM_SR_UIF) != 0)
	{
		TIM14 -> SR &= ~TIM_SR_UIF;
	}

	static int seconds = 0;
	static int minutes = 0;
	static int hours = 0;
	seconds += 1;
	if(seconds % 5 == 0){
	    score+= 5;
	    if (TIM2 -> PSC - 5000 > 3000)
      {
          TIM2->PSC = TIM2->PSC - 5000;
      }
      else
      {
        TIM2 -> PSC = TIM2 -> PSC - 150;
      }
	}
	if (seconds > 59) {
		seconds = 0;
		minutes += 1;
	}
	if (minutes > 59) {
		minutes = 0;
		hours += 1;
	}


	char line[20];
	char line2[20];
	sprintf(line, "Timer: %02d:%02d:%02d", hours, minutes, seconds);
	display1(line);
	sprintf(line2, "Score: %d", score);
	display2(line2);
	TIM14 -> SR &= ~TIM_SR_CC1IF;
}

void init_tim2(void) {
	RCC -> APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2 -> PSC = 48000 - 1;
	TIM2 -> ARR = 200 - 1;
	TIM2 -> DIER |=  TIM_DIER_UIE;
	TIM2 -> CR1 |= 2 << 8;
	TIM2 -> CR1 |= TIM_CR1_CEN;
	NVIC -> ISER[0] = 1 << TIM2_IRQn;
}

void init_usart2(void) {
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC -> APB1ENR |= RCC_APB1ENR_USART2EN;

	GPIOA -> MODER &= ~(3 << 4);
	GPIOA -> MODER &= ~(3 << 6);
	GPIOA -> MODER |= 2 << 4;
	GPIOA -> MODER |= 2 << 6;

	GPIOA -> AFR[0] &= ~(0xf << 8);
	GPIOA -> AFR[0] &= ~(0xf << 12);
	GPIOA -> AFR[0] |= 1 << 8;
	GPIOA -> AFR[0] |= 1 << 12;

	GPIOA -> OSPEEDR |= 3 << 4;
	GPIOA -> OSPEEDR |= 3 << 6;

	USART2 -> CR1 &= ~USART_CR1_UE;
	USART2 -> BRR = 0x1A1;
	USART2 -> CR2 &= ~(USART_CR2_STOP_0 | USART_CR2_STOP_1);
	USART2 -> CR1 &= ~(1 << 12 | 1 << 28 | USART_CR1_PCE | USART_CR1_OVER8);
	USART2 -> CR1 |= USART_CR1_TE | USART_CR1_RE;
	USART2 -> CR1 |= USART_CR1_UE;
}

char readchar()
{
	if (USART2 -> ISR & USART_ISR_ORE)
	{
		USART2 -> ICR = USART_ICR_ORECF;
	}
	while (!(USART2 -> ISR & USART_ISR_RXNE));
	char c = USART2 -> RDR;
	return c;
}

void tim14_init ()
{
    // Enable the system clock for timer 4
    RCC -> APB1ENR |= RCC_APB1ENR_TIM14EN;
    // Counting direction: 0=up, 1=down
    TIM14->CR1 &= ~TIM_CR1_DIR;
    // Set pre-scaler output to 1kHz (48MHz/48000)
    TIM14->PSC = 48000 - 1;
    // Auto-reload 1000
    TIM14->ARR = 1000 - 1;
    // Enable output for channel 4 active-high output


    TIM14 -> CCR1 = 1;
    TIM14 -> CCMR1 &= ~TIM_CCMR1_CC1S;
    TIM14 -> CCER |= TIM_CCER_CC1E;
    TIM14 -> CCMR1 |= TIM_CCMR1_IC1F_3 | TIM_CCMR1_IC1F_2 | TIM_CCMR1_IC1F_1 | TIM_CCMR1_IC1F_0;

    TIM14->DIER |= TIM_DIER_UIE;
    TIM14->BDTR |= TIM_BDTR_MOE;
    TIM14->CR1 |= 2 << 8;
    // Enable timer 3
    TIM14->CR1 |= TIM_CR1_CEN;
    NVIC->ISER[0] |= 1 << TIM14_IRQn;
}

void tim3_init ()
{
    // Enable the system clock for timer 3
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    // Counting direction: 0=up, 1=down
    TIM3->CR1 &= ~TIM_CR1_DIR;
    // Set pre-scaler output to 1kHz (8MHz/8000)
    TIM3->PSC = 480 - 1;
    // Auto-reload 1000
    TIM3->ARR = 100 - 1;

    // Enable output for channel 4 active-high output
    TIM3->DIER |= TIM_DIER_UIE;

    // Enable timer 3
    TIM3->CR1 |= TIM_CR1_CEN;

    NVIC->ISER[0] |= 1 << TIM3_IRQn;
}
