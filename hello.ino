int val;            //用于存储LM35读到的值
double data;  

unsigned long jsTimer;
unsigned long tepTimer;
//继电器
int relayPin = 3;
int relayState = LOW;

int redPin = 5;
int greenPin =6 ;
int bluePin = 7;


//音频
float sinVal;
int toneVal;
static int times = 0;
int pinlv[9] = {262,294,330,349,392,440,494,523,478};
char SUNANA[128]="123556531233212.123556531233221.44466655312.123556531233221";

//
void colorRGB(int red, int green, int blue);

void setup() {

    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  
  // put your setup code here, to run once:
  pinMode(relayPin , OUTPUT);
  pinMode(10 , OUTPUT);
  Serial.begin(9600);
  //写入继电器
  digitalWrite(relayPin , relayState);
}

void loop() {
  // put your main code here, to run repeatedly:
      //灯光
       colorRGB(random(0,255),random(0,255),random(0,255));
      //继电器控制内容
      val=analogRead(0);   //LM35连到模拟口，并从模拟口读值
      data = (double) val * (5/10.24);  // 得到电压值，通过公式换成温度     
      if(millis() - tepTimer > 500){     // 每500ms，串口输出一次温度值
               tepTimer = millis();
               Serial.print("temperature: ");     // 串口输出“温度”
               Serial.print(data);         // 串口输出温度值
               Serial.println("C");         // 串口输出温度单位
       } 
      if (jsTimer == 0&&data>27||data>27&&(millis() - jsTimer)>360000) {
        /* code */
       colorRGB(0,0,0);
        relayState = HIGH;
        digitalWrite(relayPin , relayState);
        delay(10000);
        digitalWrite(relayPin , LOW);
        delay(3000);
        goSing(SUNANA);
        jsTimer = millis();
      }
          if(data<=27){
              colorRGB(random(0,255),random(0,255),random(0,255));
            }
            
      }


void goSing(char *music)
{
  for (int t = 0; t < 128; t++)
  {
    int index = music[t] - 48;
    if(index > 0 && index < 10)
    {
      tone(10,pinlv[index],200);

    }
    else
    {
      delay(500);
    }

    if(music[t] == 0)
    {
      break;
    }
    delay(200);
  }
}


void colorRGB(int red, int green, int blue){
      analogWrite(redPin,constrain(red,0,255));
      analogWrite(greenPin,constrain(green,0,255));
      analogWrite(bluePin,constrain(blue,0,255));
}
