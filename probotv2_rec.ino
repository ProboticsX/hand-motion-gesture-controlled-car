#include <VirtualWire.h>
#include <AFMotor.h>

AF_DCMotor motor1(3);
AF_DCMotor motor2(2);
const int led_pin = 6;
const int transmit_pin = 12;
const int receive_pin = 52;
const int transmit_en_pin = 3;

void setup()
{
  Serial.begin(9600);
  motor1.setSpeed(200);
  motor2.setSpeed(200);
 
  motor1.run(RELEASE);   
  motor2.run(RELEASE);
   
    delay(1000);
    Serial.begin(9600);  // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);  // Bits per sec
      vw_rx_start();       // Start the receiver PLL running

   

  
}

void left(){
 motor1.run(FORWARD); 
 motor2.run(RELEASE);
}

void right(){
   motor1.run(RELEASE);
   motor2.run(FORWARD);

}

void up(){
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

void down(){
  motor1.run(BACKWARD); 
  motor2.run(BACKWARD);
}

void neutral(){
   motor1.run(RELEASE);
   motor2.run(RELEASE);

}


void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;



    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
     char a;
  int i;// Serial.println("hi");
  int y=0;
  for (i = 0; i < buflen; i++)
  {
      
         a=char(buf[i]);
          Serial.println(a); 
      }

if(a=='l')
left();

if(a=='r')
right();

if(a=='u')
up();

if(a=='d')
down();

if(a=='n')
neutral();

        
    }
}

