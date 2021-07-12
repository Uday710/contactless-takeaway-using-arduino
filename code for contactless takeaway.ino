#include <Servo.h>

#include <IRremote.h>

Servo servo_1, servo_2;

int us_1_trig=13; 
int us_1_echo=12;
int us_2_trig=10; 
int us_2_echo=9;

float duration_entry, distance_entry;
float duration_exit, distance_exit;

int ir_1=A2;
int ir_2=A3; 
int ir_3=A4; 
int ir_4=A5;

int led_r=2; 
int led_b=3; 
int led_g=4; 
int led_y=5;


void setup()
{
  Serial.begin(9600);
  servo_1.attach(11);
  servo_2.attach(8);
  pinMode(us_1_trig, OUTPUT);
  pinMode(us_1_echo, INPUT);
  pinMode(us_2_trig, OUTPUT);
  pinMode(us_2_echo, INPUT);
  pinMode(ir_1,INPUT);
  pinMode(ir_2,INPUT);
  pinMode(ir_3,INPUT);
  pinMode(ir_4,INPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_b, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_y, OUTPUT);
}

void loop()
{
  servo_1.write(0);
  servo_2.write(0);
  digitalWrite(led_r,LOW);
  digitalWrite(led_b,LOW);
  digitalWrite(led_g,LOW);
  digitalWrite(led_y,LOW);
  
  
  digitalWrite(us_1_trig, LOW);
  delay(2);
  digitalWrite(us_1_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(us_1_trig, LOW);
  duration_entry=pulseIn(us_1_echo, HIGH);
  distance_entry=duration_entry/58.4;
  if(distance_entry<300){
    servo_1.write(90);
    delay(1000);
    Serial.println("Entry Barricade opened");
    delay(2000);
    servo_1.write(0);
    delay(1000);
    Serial.println("Entry Barricade closed");
  
  
  Serial.println("Place your order");
  delay(5000);
  
  for(int i=A2; i<=A5; i=i+1){
    IRrecv receiver(i);
    decode_results output;
    receiver.enableIRIn();
    Serial.print("Press '1' to add ");
    Serial.print("Item "); 
    Serial.print(i-15);
    Serial.print(" to your order or Press '0' to go to next menu item \n");
    delay(2000);
  	if (receiver.decode(&output)){
        
        receiver.resume();
    if(output.value==16582903)
    {
      digitalWrite(i-14,HIGH);
      
      Serial.println("Item added to your order");
    }
  }
  }
  
  
  digitalWrite(us_2_trig,LOW);
  delay(2);
  digitalWrite(us_2_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(us_2_trig,LOW);
  duration_exit=pulseIn(us_2_echo,HIGH);
  distance_exit=duration_exit/58.4;
   if(distance_exit<=300){
    servo_2.write(90);
    delay(10);
    Serial.println("Exit Barricade opened");
    delay(5000);
    servo_2.write(0);
    delay(10);
    Serial.println("Exit Barricade closed");
  }
  }
}