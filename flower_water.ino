#define WetPoint A1
#define jidianqi 13


//设置阴极接口
int a = 1;
int b = 2;
int c = 3;
int d = 4;
int e = 5;
int f = 6;
int g = 7;
//设置阳极接口
int d4 = 9;
int d3 = 10;
int d2 = 11;
int d1 = 12;

//定义湿度上限
int wetTopLevel=850;  //湿度的上限，这里的上限代表很干燥
int wetLowLevel=650; //湿度的下限
int waterTime=5000; //浇水的时间
int num;  //实时湿度读取变量

//设计loopCheckTime everyLoopTime commonDelay 和 showNumTime是考虑避免多线程 ，原理是 总的监测时间除以一次LOOP的大概总时间 赋值为count_top ，每次LOOP循环则把currentCount+1，如果currentCount大于count_top 则执行湿度监测
int loopCheckTime=30*60;//这是30分钟的监测时间 
int everyLoopTime=0; //Loop函数的大概总时间 在loop函数开始出初始计算获得
int commonDelay=1000; //公共等待时间 用于调整总等待毫秒数
int showNumTime=250;
int count_top=0;
int currentCount=0;
void setup() {
  //初始化引脚
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(jidianqi, OUTPUT);
}



void loop() {
   everyLoopTime=(commonDelay+showNumTime*4)/1000; //算出每次系统循环所消耗的总时间 单位为秒
   count_top=loopCheckTime/everyLoopTime; //算出Loop计数上限值
   num=analogRead(WetPoint); //首先需要读取湿度
   divNumAndLight(num,showNumTime); //显示湿度数值
   currentCount=currentCount+1;
    if(num<=wetLowLevel)  //如果湿度已经远远超过湿度下限 就立即停止抽水
    {
        //停止抽水
        digitalWrite(jidianqi,HIGH);  
        //响蜂鸣器
    }
    if(num>=wetTopLevel && currentCount==1) //如果湿度数值高于湿度上限 而且是第一次 就立即抽5秒水
    {
        digitalWrite(jidianqi,LOW); //抽水
        delay(waterTime);
        digitalWrite(jidianqi,HIGH);//停止抽水
    }
    if(currentCount>=count_top) //现在系统已经循环超过了浇水监测时间【默认是30分钟】
    {
       if(num>=wetTopLevel) 
       {
          digitalWrite(jidianqi,LOW); //抽水
          delay(waterTime);
          digitalWrite(jidianqi,HIGH);//停止抽水
          currentCount=1; //赋值为1就避免了第二个if 避免两次浇水
        }   
    }
  delay(commonDelay);  //公共等待时间  用于凑整调优系统运行时间
}

void pickDigit(int x)  //定义pickDigit(x),其作用是开启dx端口 指定使用哪个数码管
{
  digitalWrite(d1, HIGH);
  digitalWrite(d2, HIGH);
  digitalWrite(d3, HIGH);
  digitalWrite(d4, HIGH);
  switch(x)
  {
  case 1: 
    digitalWrite(d1, LOW); 
    break;
  case 2: 
    digitalWrite(d2, LOW); 
    break;
  case 3: 
    digitalWrite(d3, LOW); 
    break;
  default: 
    digitalWrite(d4, LOW); 
    break;
  }
}

void divNumAndLight(int num,int delaytime){
    int qian,bai,shi,ge;
    qian=num/1000;
    bai=(num/100)%10;
    shi=(num%100)/10;
    ge=num%10;

    digitalWrite(d1, HIGH);
    digitalWrite(d2, HIGH);
    digitalWrite(d3, HIGH);
    digitalWrite(d4, HIGH);

     digitalWrite(d1, LOW); //先让第一个亮 
      showNum(qian);
      delay(delaytime);
    digitalWrite(d1, HIGH);

     digitalWrite(d2, LOW); 
      showNum(bai);
      delay(delaytime);
    digitalWrite(d2, HIGH);    

     digitalWrite(d3, LOW); 
      showNum(shi);
      delay(delaytime);
    digitalWrite(d3, HIGH);     

      digitalWrite(d4, LOW); 
      showNum(ge);
      delay(delaytime);
    digitalWrite(d4, HIGH);       
  }


  void showNum(int num)
  {
    switch(num)
    {
      case 0:
          digitalWrite(a,HIGH);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,HIGH);  
          digitalWrite(f,HIGH);  
          digitalWrite(g,LOW);
          break;
      case 1:
          digitalWrite(a,LOW);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,LOW);  
          digitalWrite(e,LOW);  
          digitalWrite(f,LOW);  
          digitalWrite(g,LOW);  
          break;  
      case 2:
          digitalWrite(a,HIGH);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,LOW);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,HIGH);  
          digitalWrite(f,LOW);  
          digitalWrite(g,HIGH);
          break;
      case 3:
          digitalWrite(a,HIGH);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,LOW);  
          digitalWrite(f,LOW);  
          digitalWrite(g,HIGH);
          break;
      case 4:
          digitalWrite(a,LOW);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,LOW);  
          digitalWrite(e,LOW);  
          digitalWrite(f,HIGH);  
          digitalWrite(g,HIGH);
          break;
      case 5:
          digitalWrite(a,HIGH);  
          digitalWrite(b,LOW);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,LOW);  
          digitalWrite(f,HIGH);  
          digitalWrite(g,HIGH);
          break;
      case 6:
          digitalWrite(a,HIGH);  
          digitalWrite(b,LOW);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,HIGH);  
          digitalWrite(f,HIGH);  
          digitalWrite(g,HIGH);
          break;
      case 7:
          digitalWrite(a,HIGH);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,LOW);  
          digitalWrite(e,LOW);  
          digitalWrite(f,LOW);  
          digitalWrite(g,LOW);
          break;
      case 8:
          digitalWrite(a,HIGH);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,HIGH);  
          digitalWrite(f,HIGH);  
          digitalWrite(g,HIGH);
          break;
      case 9:
          digitalWrite(a,HIGH);  
          digitalWrite(b,HIGH);  
          digitalWrite(c,HIGH);  
          digitalWrite(d,HIGH);  
          digitalWrite(e,LOW);  
          digitalWrite(f,HIGH);  
          digitalWrite(g,HIGH);
          break;
    }   
  }
