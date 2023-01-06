#include "mbed.h"
#include "RF24.h"
#include "nRF24L01P.h"
#include "SPI.h"


DigitalOut led(PC_13);
DigitalIn btn(PB_12);

RF24 radio(PA_7, PA_6, PA_5,PA_4,PB_0);
Serial pc(USBTX,USBRX) ;

const uint64_t address = 0xF0F0F0F0D2LL;
int main()
{
    pc.printf("\n uno");
    radio.begin();
    radio.setPALevel(RF24_PA_HIGH);
    radio.setRetries(15,15);
    radio.openReadingPipe(1, address);
    radio.openWritingPipe(address);
    


//    radio.startListening();
//    radio.stopListening();
    pc.printf("\n%u",radio.testRPD());
    pc.printf("\n%u",radio.getPALevel());
    radio.powerUp();
//    radio.printDetails();
    pc.printf("\n%s",radio.get_status());
    pc.printf("\n ok");

    while(1) {
//pc.printf("\n Radio is %u",radio.available());
        if(btn) {
            radio.startListening();
            if(radio.available() ) {
                pc.printf("\n Radio is ");

                char text[50];                 //Saving the incoming data
                radio.read(&text, sizeof(text));    //Reading the data
                pc.printf("%s",text);
            }
        } else {
            radio.stopListening();
            char text[50] = " rs\n\r";
            radio.write(&text, sizeof(text));
            pc.printf(text);
            wait_ms(1);
        }


    }
}
