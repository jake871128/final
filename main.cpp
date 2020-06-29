#include "mbed.h"

#include "bbcar.h"


Ticker servo_ticker;

Ticker encoder_ticker;
DigitalInOut pin10(D10);   //ping
PwmOut pin8(D8), pin9(D9);  // servo

DigitalIn pin3(D3);  // encodera
Serial pc(USBTX,USBRX); 
Serial uart(D1,D0); // OpenMV
Serial xbee(D12, D11); // Xbee

float info[50];


BBCar car(pin8, pin9, servo_ticker);


int main() {
    
    parallax_encoder encoder0(pin3, encoder_ticker);
    parallax_ping  ping1(pin10);
    encoder0.reset();
    xbee.printf("connected!\r\n"); 
// straight 150cm
    car.goStraight(100);

    while(ping1>19) wait_ms(50);
    xbee.printf("goStraight!\r\n"); 
    car.stop();
    wait_ms(50);
// turn left
    car.turn(90,-0.5);
    wait_ms(1000);
    xbee.printf("left!\r\n");
    car.stop();
    wait_ms(50);

//        mission 1
// straight to 3
    car.goStraight(100);
    while(ping1>16) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
// turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// back
    car.goStraight(-100);
    wait_ms(1300);
    xbee.printf("back!\r\n");
    car.stop();
    wait_ms(1000);
    // take picture
    car.stop();
    wait_ms(1000);
    xbee.printf("picture!\r\n");
    wait_ms(1000);
    char s[21];
    sprintf(s,"image_classification"); // sent the command to OpenMV for taking picture
    uart.puts(s); // sent the command by UART
    wait_ms(1000);
// get away the spot
    car.goStraight(100);
    while(ping1>18) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);

//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(1000);
// go stright
    car.goStraight(100);           
    wait_ms(2800);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
 // turn left
    car.turn(90,-0.5);
    wait_ms(1000);
    xbee.printf("left!\r\n");
    car.stop();
    wait_ms(1000);   
// spot
    car.goStraight(-100);
    wait_ms(2000);
    xbee.printf("back!\r\n");
    car.stop();
    wait_ms(1000);
// get away the spot
    car.goStraight(100);
    while(ping1>18) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright
    car.goStraight(100);
    xbee.printf("goStraight!\r\n");           
    wait_ms(1600);
    car.stop();
    wait_ms(50);

// straight way
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright
    car.goStraight(100);           
    while(ping1>20) wait_ms(50);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);

// mission 2
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(50);
// go stright
    car.goStraight(100);           
    wait_ms(1800);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
//turn right
    car.turn(120,0.5);
    wait_ms(1000);
    xbee.printf("right!\r\n");
    car.stop();
    wait_ms(500);
// go stright
    car.goStraight(100);           
    wait_ms(1800);
    xbee.printf("goStraight!\r\n");
    car.stop();
    wait_ms(50);
// turn left mission2 target
    car.stop();
    wait_ms(1000);
    
    // save the ping data
    for(int i=0;i<50;i++)
    {
        info[i] = ping1;
        wait_ms(50);
    }

// exit


float data[50]; // the array to save the ping data in Mission 2

/*--------------------------------Main Function--------------------------------*/

int main() {

    xbee.printf("start!\n\r"); // to check if Xbee is connected or not
    parallax_ping  ping1(pin10);
    int i=0;


/*---------------------Mission 2---------------------*/

    // turn right 90
    car.turn(70,0.1);
    wait(1.0);
    car.stop();
    wait(1);
    
    // Straight 10 cm
    car.goStraight(75);
    wait(1.8);
    car.stop();
    wait(1);

    // save the ping data
    for(i=0;i<50;i++)
    {
        data[i] = ping1;
        wait(0.02);
    }

    // back 10 cm
    car.goStraight(-75);
    wait(1.6);
    car.stop();
    wait(1);

    // turn left 90
    car.turn(50,-0.1);
    wait(1.0);
    car.stop();
    wait(1);

    // Straight 70 cm
    car.goStraight(75);
    wait(5.2);
    car.stop();
    wait(1);

    // turn right 90, exit Mission 2
    car.turn(50,0.1);
    wait(0.6);
    car.stop();
    wait(1);
    
/*--------------------Normal  way--------------------*/

    // Straight 150 cm
    car.goStraight(75);
    wait(10);
    car.stop();

/*----------Finally, send the data by XBee-----------*/ 

    int flag = 0;
    for(i=0;i<50;i++)
    {
        xbee.printf("%f\n\r",data[i]);
        wait(0.1);
        if(data[i]>14) flag=1;
    }
    if(!flag) xbee.printf("rectengle.");
    
}