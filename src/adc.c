/*
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "stm32f0_discovery.h"

int main(void){
	init_usart2();
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOCEN;
    GPIOB->MODER |= 0x3;
    GPIOC->MODER &= ~(0x3 << 4*2 | 0x3 << 5*2);
    GPIOC->MODER |= (1 << 4*2) | (1 << 5*2);
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    RCC->CR2 |= RCC_CR2_HSI14ON;
    while(!(RCC->CR2 & RCC_CR2_HSI14RDY));
	ADC1 -> CFGR1 &= ~(ADC_CFGR1_RES_0 | ADC_CFGR1_RES_1);
	ADC1->CFGR1 |= ADC_CFGR1_RES_1;

    ADC1->CR |= ADC_CR_ADEN;
    while(!(ADC1->ISR & ADC_ISR_ADRDY));
    while((ADC1->CR & ADC_CR_ADSTART));
    int counter = 0;
    int sum = 0;
    while(1){
        ADC1->CHSELR = 0;
        ADC1->CHSELR |= 1 << 8;
        while(!(ADC1->ISR & ADC_ISR_ADRDY));
        ADC1->CR |= ADC_CR_ADSTART;
        while(!(ADC1->ISR & ADC_ISR_EOC));
        // sum += ADC1->DR;
        // counter ++;
        // if(counter == 100){
        // 	sum = sum/counter;
			// if (sum < 240)
			// {
		writechar(ADC1 -> DR);
        	// }
        	// else
        	// {
        		// writechar (240);
        	// }
        	sum = 0;
        	// counter = 0;
        }
        //writechar(ADC1->DR);
    }
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

void writechar(char c) {
	while (!(USART2 -> ISR & USART_ISR_TXE));
	USART2 -> TDR = c;
}

void i2c_init(void) {
    RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

    GPIOB->MODER |= 2<<(2*6) | 2<<(2*7);
    GPIOB->AFR[0] |= 1<<(4*6) | 1<<(4*7);

    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
    //RCC->CFGR3 |= RCC_CFGR3_I2C1SW;  // set for 48MHz sysclk

    // I2C CR1 Config
    I2C1->CR1 &= ~I2C_CR1_PE;           // Disable to perform reset.
    I2C1->CR1 &= ~I2C_CR1_ANFOFF;       // 0: Analog noise filter enabled.
    I2C1->CR1 &= ~I2C_CR1_ERRIE;        // Errors interrupt disable
    I2C1->CR1 &= ~I2C_CR1_NOSTRETCH;    // Enable clock stretching

    // From table 83. p642 of FRM.  Set for 400 kHz with 8MHz clock.
    I2C1->TIMINGR = 0;
    I2C1->TIMINGR &= ~I2C_TIMINGR_PRESC;// Clear prescaler
    I2C1->TIMINGR |= 0 << 28;           // Set prescaler to 0
    I2C1->TIMINGR |= 3 << 20;           // SCLDEL
    I2C1->TIMINGR |= 1 << 16;           // SDADEL
    I2C1->TIMINGR |= 3 << 8;            // SCLH
    I2C1->TIMINGR |= 9 << 0;            // SCLL

    // I2C Own address 1 register (I2C_OAR1)
    I2C1->OAR1 &= ~I2C_OAR1_OA1EN;
    I2C1->OAR1 =   I2C_OAR1_OA1EN | (0x1<<1);// Set 7-bit own address 1

    I2C1->CR2 &= ~I2C_CR2_ADD10;        // 0 = 7-bit mode; 1 = 10-bit mode
    I2C1->CR2 |= I2C_CR2_AUTOEND;       // Enable the auto end
    I2C1->CR2 |= I2C_CR2_NACK;          // For slave mode: set NACK

    I2C1->CR1 |= I2C_CR1_PE;            // Enable I2C1
}

//===========================================================================
// Clear NACK condition.
int i2c_checknack(void) {
    if (I2C1->ISR & I2C_ISR_NACKF)
        return 1;
    return 0;
}

//===========================================================================
// Clear NACK condition.
void i2c_clearnack(void) {
    if (I2C1->ISR & I2C_ISR_NACKF)
        I2C1->ICR |= I2C_ICR_NACKCF;
}

//===========================================================================
// Clear STOP condition.
int i2c_checkstop(void) {
    if (I2C1->ISR & I2C_ISR_STOPF)
        return 1;
    return 0;
}

//===========================================================================
// Clear STOP condition.
void i2c_clearstop(void) {
    if (I2C1->ISR & I2C_ISR_STOPF)
        I2C1->ICR |= I2C_ICR_STOPCF;
}

//===========================================================================
// Look at the ISR and display the error.
void display_i2c_error(void) {
    if (I2C1->ISR & I2C_ISR_BERR)
        display1("Bus error");
    else if (I2C1->ISR & I2C_ISR_ARLO)
        display1("Arbitration Lost");
    else if (I2C1->ISR & I2C_ISR_TIMEOUT)
        display1("I2C TIMEOUT");
    else if (I2C1->ISR & I2C_ISR_BUSY)
        display1("I2C BUSY");
    else if (I2C1->ISR & I2C_ISR_PECERR)
        display1("I2C PEC Error");
    else if (I2C1->ISR & I2C_ISR_STOPF)
        display1("I2C Stopped");
    else if (I2C1->ISR & I2C_ISR_NACKF)
        display1("I2C NACK");
    else
        display1("???");
}

//===========================================================================
// Generate a start bit.
void i2c_start(uint32_t devaddr, uint8_t size, uint8_t dir) {
    // dir: 0 = master requests a write transfer
    // dir: 1 = master requests a read transfer
    uint32_t tmpreg = I2C1->CR2;
    tmpreg &= ~(I2C_CR2_SADD | I2C_CR2_NBYTES |
                I2C_CR2_RELOAD | I2C_CR2_AUTOEND |
                I2C_CR2_RD_WRN | I2C_CR2_START | I2C_CR2_STOP);
    if (dir == 1)
        tmpreg |= I2C_CR2_RD_WRN;  // Read from slave
    else
        tmpreg &= I2C_CR2_RD_WRN;  // Write to slave
    tmpreg |= ((devaddr<<1) & I2C_CR2_SADD) | ((size << 16) & I2C_CR2_NBYTES);
    tmpreg |= I2C_CR2_START;
    I2C1->CR2 = tmpreg;
}

//===========================================================================
// Generate a stop bit.
void i2c_stop(void) {
    if (I2C1->ISR & I2C_ISR_STOPF)
        return;
    // Master: Generate STOP bit after current byte has been transferred.
    I2C1->CR2 |= I2C_CR2_STOP;
    // Wait until STOPF flag is reset
    while( (I2C1->ISR & I2C_ISR_STOPF) == 0);
    I2C1->ICR |= I2C_ICR_STOPCF; // Write  to clear STOPF flag
}

//===========================================================================
// Check wait for the bus to be idle.
void i2c_waitidle(void) {
    while ( (I2C1->ISR & I2C_ISR_BUSY) == I2C_ISR_BUSY);  // while busy, wait.
}

//===========================================================================
// Send multiple bytes to a target slave.
// - Wait for idle.
// - Send data, byte by byte.
// - After all bytes sent, hardware sets the TC flag.
//   Software waits until TC is set.
//   Hardware automatically clears TC flag when START bit or STOP bit in
//   CR2 is set.
int8_t i2c_senddata(uint8_t devaddr, void *pdata, uint8_t size) {
    int i;
    if (size <= 0 || pdata == 0) return -1;
    uint8_t *udata = (uint8_t*)pdata;
    i2c_waitidle();
    // Last argument is dir: 0 = sending data to the slave.
    i2c_start(devaddr, size, 0);

    for(i=0; i<size; i++) {
        // TXIS bit is set by hardware when the TXDR register is empty and the
        // data to be transmitted must be written in the TXDR register.  It is
        // cleared when the next data to be sent is written in the TXDR reg.
        // The TXIS flag is not set when a NACK is received.
        int count = 0;
        while( (I2C1->ISR & I2C_ISR_TXIS) == 0) {
            count += 1;
            if (count > 1000000)
                return -1;
            if (i2c_checknack()) {
                i2c_clearnack();
                i2c_stop();
                return -1;
            }
        }

        // TXIS is cleared by writing to the TXDR register.
        I2C1->TXDR = udata[i] & I2C_TXDR_TXDATA;
    }

    // Wait until TC flag is set or the NACK flag is set.
    while((I2C1->ISR & I2C_ISR_TC) == 0 && (I2C1->ISR & I2C_ISR_NACKF) == 0);

    if ( (I2C1->ISR & I2C_ISR_NACKF) != 0)
        return -1;
    i2c_stop();
    return 0;
}

//===========================================================================
// Receive multiple bytes from a target slave.
int8_t i2c_recvdata(uint8_t devaddr, void *pdata, uint8_t size) {
    int i;
    if (size <= 0 || pdata == 0) return -1;
    uint8_t *udata = (uint8_t*)pdata;
    i2c_waitidle();
    i2c_start(devaddr, size, 1); // 1 = receiving from the slave
    for(i=0; i<size; i++) {
        // Wait until RXNE flag is set
        int count = 0;
        while ( (I2C1->ISR & I2C_ISR_RXNE) == 0) {
            count += 1;
            if (count > 1000000)
                return -1;
            if (i2c_checknack()) {
                i2c_clearnack();
                i2c_stop();
                return -1;
            }
        }
        udata[i] = I2C1->RXDR & I2C_RXDR_RXDATA;
    }

    int x=0;
    while((I2C1->ISR & I2C_ISR_TC) == 0)
        x++;  // Wait until TCR flag is set

    i2c_stop();
    return 0;
}

//===========================================================================
// Initialize the EEPROM to 0x00, 0xAA, 0xCC, 0xF0, ...
void init_eeprom(void) {
    int updated = 0;
    // Set the current address with a zero-byte write.
    uint8_t buf[] = {0,0};
    i2c_senddata(0x50, buf, sizeof buf);
    // Iterate through address ranges 32 bytes at a time.
    int addr;
    for(addr=0; addr<4096; addr+=32) {
        char line[32];
        // Spend a second trying to read the 32-byte line.
        int tries;
        for(tries=0; tries<200; tries += 1) {
            if (i2c_recvdata(0x50, line, sizeof line) == 0)
                break;
            if (tries == 199) {
                display1("EEPROM not responding");
                for(;;);
            }
            nano_wait(5000000); // wait 5ms
        }
        // Check that the line appears as we want it to.
        int ok = 1;
        int c;
        for(c=0; c<32; c+=1) {
            switch(c & 3) {
            case 0: if (line[c] != 0x00) {
                ok = 0;
            }
            break;
            case 1: if (line[c] != 0xAA) {
                ok = 0;
            }
            break;
            case 2: if (line[c] != 0xCC) {
                ok = 0;
            }
            break;
            case 3: if (line[c] != 0xF0) {
                ok = 0;
            }
            break;
            }
        }
        if (ok == 1)
            continue;
        // The line is not correct.  Rewrite it.
        // Use a buffer where the first two bytes are the EEPROM address.
        // The following 32 bytes are the new contents of the line.
        updated += 1;
        char newdata[] = { 0, 0,
                0x00, 0xaa, 0xcc, 0xf0, 0x00, 0xaa, 0xcc, 0xf0,
                0x00, 0xaa, 0xcc, 0xf0, 0x00, 0xaa, 0xcc, 0xf0,
                0x00, 0xaa, 0xcc, 0xf0, 0x00, 0xaa, 0xcc, 0xf0,
                0x00, 0xaa, 0xcc, 0xf0, 0x00, 0xaa, 0xcc, 0xf0,
        };
        newdata[0] = (addr >> 8) & 0xf;
        newdata[1] = addr & 0x0ff;
        i2c_senddata(0x50, newdata, sizeof newdata);
        sprintf(line, "Writing to 0x%03x", addr);
        display1(line);
    }
    if (updated == 0)
        display1("Nothing to set");
    else
        display1("DONE");
    for(;;);
}

//===========================================================================
// Continually read the first four bytes of the EEPROM
void test_eeprom(void) {
    int count = 0;
    for(;;) {
        uint8_t buf[] = {0,0};
        i2c_senddata(0x50, buf, sizeof buf);
        count += 1;
        char line[4];
        if (i2c_recvdata(0x50, line, sizeof line) != 0) {
            display_i2c_error();
        } else {
            char msg[16];
            sprintf(msg, "Read #%d", count);
            display1(msg);
        }
        nano_wait(1000000);  // Wait a ms before reading again.
    }
}

//===========================================================================
// Write 32 bytes to a region of the EEPROM.
void write_eeprom(int addr, const char *msg) {
	char new_msg[34];
	strcpy(&new_msg[2], msg);
	new_msg[0] = 0;
	new_msg[1] = 0;
    new_msg[0] = (addr >> 8) & 0xf;
    new_msg[1] = addr & 0x0ff;
    //strcat(new_msg, msg);

    i2c_senddata(0x50, new_msg, sizeof new_msg);
    while (1) {
		if (i2c_senddata(0x50, new_msg, sizeof new_msg) < 0) {
			I2C1->ICR |= I2C_ICR_NACKCF;
			I2C1->ICR |= I2C_ICR_STOPCF;
		}
		else
			break;
	}
}

//===========================================================================
// Read a <255-byte string from an specified address of the EEPROM.
char* display_eeprom(int addr, int len) {
    if (len > 255)
        return;
    // Do a zero-byte write to set the current address...
    char buf[255+16] = {0};
    buf[0] = (addr >> 8) & 0x0f;
    buf[1] = addr & 0x0ff;
    i2c_senddata(0x50, buf, 2);

    // Put a string on the front end, so we can slide the string in.
    strcpy(buf, "                ");
    // Read the string.
    if (i2c_recvdata(0x50, &buf[16], len) < 0) {
        display_i2c_error();
        for(;;);
    }
    buf[len+16] = '\0';
    // for(;;) {
    //     int x;
    //     for(x=0; x<255+16; x+=1) {
    //         if (buf[x] == 0)
    //             break;
    //         display1(&buf[x]);
    //         nano_wait(100000000);
    //     }
    // }
	return buf;
}
