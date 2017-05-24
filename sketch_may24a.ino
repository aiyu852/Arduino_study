unsigned long tepTimer ;    
int redPin = 9;
int greenPin = 10;
int bluePin = 11;

void setup(){ 
      Serial.begin(9600);        
      pinMode(redPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
      pinMode(bluePin, OUTPUT);
}

void loop(){ 
      int val;            
      double data;       
      val=analogRead(0);   
      data = (double) val * (5/10.24);  
     
      if(data<27){           
          colorRGB(random(0,255),random(0,255),random(0,255));  
          delay(1000);
      } else { 
          fadeOn(1000,5);
          fadeOff(1000,5);
        }
     
      if(millis() - tepTimer > 500){     
               tepTimer = millis();
               Serial.print("temperature: ");     
               Serial.print(data);         
               Serial.println("C");         
}
}
void fadeOn(unsigned int time,int increament){
        for (byte value = 0 ; value < 255; value+=increament){ 
            analogWrite(redPin, value);
                delay(time/(255/increament));
        } 
}
void fadeOff(unsigned int time,int decreament){
        for (byte value = 255; value >0; value-=decreament){ 
            analogWrite(redPin, value); 
                delay(time/(255/decreament)); 
        }
}

void colorRGB(int red, int green, int blue){
      analogWrite(redPin,constrain(red,0,255));
      analogWrite(greenPin,constrain(green,0,255));
      analogWrite(bluePin,constrain(blue,0,255));
}
