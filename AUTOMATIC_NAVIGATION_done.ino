#include <Encoder.h>
Encoder knobXaxis(2, 3);
Encoder knobYaxis(18, 19);
int FinalX = -10;
int FinalY = -10;
long newXaxis, newYaxis;
int s1 = 11, s2 = 10, s3 = 13, s4 = 12;
int s_1, s_2, s_3, s_4;
int d_1, d_2, d_3, d_4;
int d1 = 6, d2 = 7, d3 = 4, d4 = 5;
int w=0;
volatile int d_x;
volatile int d_y;

void func_want(int x, int y,int w)
{
  int sf = 1;
  w=0;
  s_1 = sf * (-0.35 * x + 0.35 * y + 0.25 * w);
  s_2 = sf * (-0.35 * x -0.35 * y + 0.25 * w);
  s_3 = sf * (0.35 * x - 0.35 * y + 0.25 * w);
  s_4 = sf * (0.35* x + 0.35 * y + 0.25 * w);
  Serial.print("s_1:::");
  Serial.println(s_1);
  Serial.print("s_2:::");
  Serial.println(s_2);
  Serial.print("s_3:::");
  Serial.println(s_3);
  Serial.print("s_4:::");
  Serial.println(s_4);
  Serial.println();
      

  d_1 = (s_1 > 0 ? 1 : 0);
  d_2 = (s_2 > 0 ? 1 : 0);
  d_3 = (s_3 > 0 ? 1 : 0);
  d_4 = (s_4 > 0 ? 1 : 0);
  Serial.print("d_1:::");
  Serial.println(d_1);
  Serial.print("d_2:::");
  Serial.println(d_2);
  Serial.print("d_3:::");
  Serial.println(d_3);
  Serial.print("d_4:::");
  Serial.println(d_4);
  Serial.println();
  
  //digital output for 4 motor
  digitalWrite(d1, d_1);
  digitalWrite(d2, d_2);
  digitalWrite(d3, d_3);
  digitalWrite(d4, d_4);

  //analog output speed for 4 motor
  analogWrite(s1, s_1);
  analogWrite(s2, s_2);
  analogWrite(s3, s_3);
  analogWrite(s4, s_4);
}
void setup() {
  Serial.begin(9600);
  Serial.println("TwoKnobs Encoder Test:");
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
}
void loop() {
  delay(1000);
    if (newXaxis <= FinalX || newYaxis <= FinalY)
    {
      newYaxis = knobXaxis.read();
      newXaxis = knobYaxis.read();
      newXaxis=newXaxis/800;   
      newYaxis=newYaxis/800;
      int d_x = FinalX - newXaxis; 
      int d_y = FinalY - newYaxis; 
      
      Serial.print("x-axis=");
      Serial.println(newXaxis);
      Serial.print("Yaxis = ");
      Serial.println(newYaxis);
      Serial.println();
      int angle = atan(d_y / d_x) * 57;  //angle between x axis and line joining to final coordinate and x axis
      //d_x = map((90 - angle), -90, 90, -255, 255);
      w = map(angle, -90, 90, 255, -255);
      func_want(d_x, d_y, w);
    }
    if (newXaxis == FinalX && newYaxis == FinalY)
    {
      func_want(0,0,0);
      exit(0);
    }
  }
