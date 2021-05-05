#include <Servo.h> // include Servo library 

Servo horizontal; // horizontal servo
int servoh = 90;     // stand horizontal servo

Servo vertical;   // vertical servo 
int servov = 20;     // stand vertical servo

// LDR pin connections
//  name  = analogpin;
int ldrlt = 0; //LDR top left
int ldrrt = 1; //LDR top rigt
int ldrld = 2; //LDR down left
int ldrrd = 3; //ldr down rigt

/*int ldrlt = 3; //LDR top left
int ldrrt = 2; //LDR top rigt
int ldrld = 1; //LDR down left
int ldrrd = 0; //ldr down rigt
*/
void setup()
{
    Serial.begin(9600);
    // servo connections
    // name.attacht(pin);
    vertical.attach(2);
    horizontal.attach(5); 
   
}

void loop() 
{
    int lt = analogRead(ldrlt); // top left
    int rt = analogRead(ldrrt); // top right
    int ld = analogRead(ldrld); // down left
    int rd = analogRead(ldrrd); // down rigt
    
    int dtime = 60; // read potentiometers  
    int tol = 50;
    
    int avt = (lt + rt) / 2; // average value top
    int avd = (ld + rd) / 2; // average value down
    int avl = (lt + ld) / 2; // average value left
    int avr = (rt + rd) / 2; // average value right
    
    int dvert = avt - avd; // check the diffirence of up and down
    int dhoriz = avl - avr;// check the diffirence og left and rigt
    
    if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
    {
        if (avt > avd)
        {
            servov = --servov;
             if (servov > 170) 
             { 
                servov = 170;
             }
        }
        else if (avt < avd)
        {
            servov= ++servov;
            if (servov < 10)
            {
                servov = 10;
            }
        }
        vertical.write(servov);
    }
    
    if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
    {
        if (avl > avr)
        {
            servoh = --servoh;
            if (servoh < 10)
            {
                servoh = 10;
            }
        }
        else if (avl < avr)
        {
            servoh = ++servoh;
             if (servoh > 170)
             {
                servoh = 170;
             }
        }
        else if (avl = avr)
        {
            // nothing
        }
        horizontal.write(servoh);
    }
    delay(dtime); 
}
