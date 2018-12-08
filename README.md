# STMRacer
Go retro with this car racing game!

## Description
STMRacer is a racing game in which a player drives a car using a steering wheel and tries to avoid obstacles on the way. If the car collides with an obstacle, the game is over and the player will be able to see for how long they played along with their score. The game is displayed on a RGB LED matrix and is clocked with GPIO on the STM32. 

## Project members
 - Niraj Menon
 - Karthick Shankar
 - Shreya Ilango
 - Somesh Dube

## Project Components
1. 32x32 RGB LED Matrix
2. STM32 Microcontroller
3. CFAL1602 LCD Display
4. 74HC541N Level Shifters
5. 3D Printed Steering Wheel
6. Potentiometer
7. 24LC32A EEPROM
8. Reset Pushbutton


## Challenges Faced
The main challenge we faced was getting the LED matrix to light up. After some extensive research we found that there was quite a complicated way of getting to display data, and even after clocking in the data, the display would immediately turn off after about 100 ms. To handle this, we implemented an interrupt that would refresh the display at roughly 1000 Hz. 


When we finally got the matrix to light up the way we wanted it to, there was a lot of interference. In our constant rewiring sessions, we found that noise seemed to occur if there were loose wires, or the grounds hadn’t been tied together.


Once we got rid of the noise, we had to come up with a way to push data into the screen. The annoying thing about that was if we wanted to show complex screens like “Ready, set go!” and high scores, we would have to find a way to convert them into a compatible format within C. We accomplished this by creating a Python script that would parse an image file, convert it to 24-bit bitmap if needed, read every pixel and then output the ones that weren’t off in the form of an array declaration in C. That helped us visualize what we wanted to see on the screen easily.


Obstacle generation was a bit tricky because we didn’t want to provide the same pattern every time due to lack of space for huge obstacle course bitmaps and the fact that people would get used to the same course quickly. Taking the LFSR from ECE 270, we created a pseudorandom obstacle course generator, thereby saving a lot more space.


Originally, we wanted to use the wheel like in a regular car - turning left would go left, and vice versa - but it was extremely hard to control the speed of the car moving in either direction, and it would flicker between left and right positions intensely. Therefore we decided to map the orientation itself to the pixels on the board, so that turning left would hold it on the left side, and vice versa.


We wanted to save high scores, but then we realized that it wouldn’t be saved when the STM32 rebooted. As a result, we got a 4 KB EEPROM that we configured with I2C to store the highest three scores whenever a game was over.


## YouTube video: 
https://youtu.be/J_dTIens0Uw
