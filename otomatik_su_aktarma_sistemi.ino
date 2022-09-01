// l293 motor sürücü ile hazırlanmış otomatik su aktarma  sistemi.
#include <AFMotor.h> // motor sürücü kutuphanesini eklliyoruz.
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
int sensorDurum=0;
void setup() 
{
Serial.begin(9600);

motor1.setSpeed(200);// motorumuzun hızını pwm sinyal bakımından 255 uzerınden 200'e ayarlıyoruz.
motor1.run(RELEASE);// motorumuzu durduruyoruz ki verimsiz çalışma olmasın.

}
void loop() 
{
  
  Serial.println(analogRead(A5));// Taşınabilir depomuzun su oranını su seviye sensoru ile seri ekranda izliyoruz.
  int sensorDurum=analogRead(A5);
  
  if(sensorDurum<30)// belirlediğimiz seviyeye göre yer altı depomuzdan yer yuzeyinde ki depoya su aktarıyoruz.
  {
    motor1.run(FORWARD);
  }
  else{
     motor1.run(RELEASE);
  }
  
}
