/*
 * display.c
 *
 *  Created on: Oct 27, 2018
 *      Author: niraj
 */


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

static void nano_wait(int t) {
    asm("       mov r0,%0\n"
        "repeat:\n"
        "       sub r0,#83\n"
        "       bgt repeat\n"
        : : "r"(t) : "r0", "cc");
}


static short dispmem[] = {
        0x002,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
        0x0c0,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
        0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220, 0x220,
};

//===========================================================================
// Send a command to the LCD.
void cmd(char b) {
    while((SPI2->SR & SPI_SR_TXE) != SPI_SR_TXE);
    SPI2->DR = b;
}

//===========================================================================
// Send a character to the LCD.
void data(char b) {
    while((SPI2->SR & SPI_SR_TXE) != SPI_SR_TXE);
    SPI2->DR = 0x200 | b;
}

//===========================================================================
// Initialize the LCD.
void init_lcd_spi(void){
	RCC -> AHBENR |= RCC_AHBENR_GPIOBEN;
	for (int i = 12; i <= 15; i++)
	{
		GPIOB -> MODER &= ~(3 << (i * 2));
		GPIOB -> MODER |= 2 << (i * 2);
		// GPIOB -> AFR [1] &= ~(0xF << ((i - 8) * 4)); // Leave at zero, AF0 is the function selected
	}

	RCC -> APB2ENR |= RCC_APB2ENR_SPI1EN;
	RCC -> APB1ENR |= RCC_APB1ENR_SPI2EN;

	SPI2 -> CR1 |= SPI_CR1_MSTR | SPI_CR1_BR;
	SPI2 -> CR1 |= SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE;
	SPI2 -> CR1 |= SPI_CR1_BR_0 | SPI_CR1_BR_1 | SPI_CR1_BR_2;
	SPI2 -> CR2  = SPI_CR2_SSOE | SPI_CR2_NSSP | SPI_CR2_DS_3 | SPI_CR2_DS_0;
	SPI2 -> CR1 |= SPI_CR1_SPE;

	nano_wait(100000000); // Give it 100ms to initialize
	cmd(0x38); // 0011 NF00 N=1, F=0: two lines
	cmd(0x0c); // 0000 1DCB: display on, no cursor, no blink
	cmd(0x01); // clear entire display
	nano_wait(6200000); // clear takes 6.2ms to complete
	cmd(0x02); // put the cursor in the home position
	cmd(0x06); // 0000 01IS: set display to increment
}

//===========================================================================
// Initialize the LCD to use circular DMA to write to the SPI channel.
void init_lcd(void) {
	init_lcd_spi();
	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel5 -> CCR  &= ~DMA_CCR_EN;
	DMA1_Channel5 -> CMAR = (uint32_t) dispmem;
	DMA1_Channel5 -> CPAR = (uint32_t) &(SPI2 -> DR);
	DMA1_Channel5 -> CNDTR = 34;
	DMA1_Channel5 -> CCR |= DMA_CCR_DIR;
	DMA1_Channel5 -> CCR |= DMA_CCR_MINC;
	DMA1_Channel5 -> CCR |= DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
	DMA1_Channel5 -> CCR |= DMA_CCR_CIRC;
	DMA1_Channel5 -> CCR &= ~(DMA_CCR_PINC | DMA_CCR_TCIE | DMA_CCR_HTIE);
	DMA1_Channel5 -> CCR &= ~DMA_CCR_PL;
	SPI2 -> CR2 		 |= SPI_CR2_TXDMAEN;
	DMA1_Channel5 -> CCR |= DMA_CCR_EN;
}

//===========================================================================
// Display a string on line 1 by writing to SPI directly.
void display1_spi(const char *s) {
    cmd(0x02); // put the cursor on the beginning of the first line.
    int x;
    for(x=0; x<16; x+=1)
        if (s[x])
            data(s[x]);
        else
            break;
    for(   ; x<16; x+=1)
        data(' ');
}

//===========================================================================
// Display a string on line 2 by writing to SPI directly.
void display2_spi(const char *s) {
    cmd(0xc0); // put the cursor on the beginning of the second line.
    int x;
    for(x=0; x<16; x+=1)
        if (s[x] != '\0')
            data(s[x]);
        else
            break;
    for(   ; x<16; x+=1)
        data(' ');
}

//	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;
//	DMA1_Channel5 -> CCR &= DMA_CCR_EN;
//	DMA1_Channel5 -> CMAR = (uint32_t) dispmem;
//	DMA1_Channel5 -> CPAR = (uint32_t) SPI2 -> DR;
//	DMA1_Channel5 -> CNDTR = sizeof (dispmem);
//	DMA1_Channel5 -> CCR |= DMA_CCR_DIR;
//	DMA1_Channel5 -> CCR |= DMA_CCR_TCIE;
//	DMA1_Channel5 -> CCR &= ~DMA_CCR_HTIE;
//	DMA1_Channel5 -> CCR &= ~DMA_CCR_MSIZE;
//	DMA1_Channel5 -> CCR &= ~DMA_CCR_PSIZE;
//	DMA1_Channel5 -> CCR |= DMA_CCR_MINC;
//	DMA1_Channel5 -> CCR |= DMA_CCR_PINC;
//	DMA1_Channel5 -> CCR |= DMA_CCR_MEM2MEM;
//	DMA1_Channel5 -> CCR &= ~DMA_CCR_PL;
//	NVIC -> ISER[0] = 1 << DMA1_Channel5_IRQn;
//	DMA1_Channel5 -> CCR |= DMA_CCR_EN;

//===========================================================================
// Display a string on line 1 by using DMA to write to SPI.
void display1_dma(const char *s) {
	int x;
	for(x=0; x<16; x+=1)
		if (s[x] != '\0')
			dispmem [x + 1] = s[x] | 0x200;
		else
			break;
	for(   ; x<16; x+=1)
		dispmem [x + 1]  = 0x220;

	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel5 -> CCR  &= ~DMA_CCR_EN;
	DMA1_Channel5 -> CMAR = (uint32_t) dispmem;
	DMA1_Channel5 -> CPAR = (uint32_t) (&(SPI2 -> DR));
	DMA1_Channel5 -> CNDTR = sizeof (dispmem) / 2;

	DMA1_Channel5 -> CCR |= DMA_CCR_DIR;
	DMA1_Channel5 -> CCR &= ~(DMA_CCR_TCIE | DMA_CCR_HTIE);
	DMA1_Channel5 -> CCR |= DMA_CCR_MSIZE_0 | DMA_CCR_PSIZE_0;
	DMA1_Channel5 -> CCR |= DMA_CCR_MINC;
	DMA1_Channel5 -> CCR &= ~DMA_CCR_PINC;
//	DMA1_Channel5 -> CCR &= ~DMA_CCR_PL;
	SPI2 -> CR2 		 |= SPI_CR2_TXDMAEN;
	DMA1_Channel5 -> CCR |= DMA_CCR_EN;
}

//===========================================================================
// Display a string on line 2 by using DMA to write to SPI.
void display2_dma(const char *s) {
	int x;
	for(x=17; x<33; x+=1)
		if (s[x - 17] != '\0')
			dispmem [x + 1] = s[x - 17] | 0x200;
		else
			break;
	for(   ; x<33; x+=1)
		dispmem [x + 1]  = 0x220;


	RCC -> AHBENR |= RCC_AHBENR_DMA1EN;
	DMA1_Channel5 -> CCR  &= ~DMA_CCR_EN;
	DMA1_Channel5 -> CMAR = (uint32_t) dispmem;
	DMA1_Channel5 -> CPAR = (uint32_t) (&(SPI2 -> DR));
	DMA1_Channel5 -> CNDTR = sizeof (dispmem) / 2;

	DMA1_Channel5 -> CCR |= DMA_CCR_DIR;
	DMA1_Channel5 -> CCR |= DMA_CCR_MINC;
//	DMA1_Channel5 -> CCR &= ~DMA_CCR_PL;
	SPI2 -> CR2 		 |= SPI_CR2_TXDMAEN;
	DMA1_Channel5 -> CCR |= DMA_CCR_EN;
}

//===========================================================================
// Display a string on line 1 by writing to the DMA source.
void display1(const char *s) {
//	cmd (0x02);
	int x;
	for(x=0; x<16; x+=1)
			if (s[x] != '\0')
				dispmem [x + 1] = s[x] | 0x200;
			else
				break;
		for(   ; x<16; x+=1)
			dispmem [x + 1]  = 0x220;
}

//===========================================================================
// Display a string on line 2 by writing to the DMA source.
void display2(const char *s) {
//	cmd (0xc0);
	int x;
		for(x=17; x<33; x+=1)
			if (s[x - 17] != '\0')
				dispmem [x + 1] = s[x - 17] | 0x200;
			else
				break;
		for(   ; x<33; x+=1)
			dispmem [x + 1]  = 0x220;
}
