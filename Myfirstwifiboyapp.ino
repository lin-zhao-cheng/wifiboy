#include <wifiboypro.h>
#include <Arduino.h>
#include "esp32-hal.h"
#include "wb-sprite.h"

// int masterX=100;//100
// int masterY=100;//100


int starX[100];
int starY[100];
int k;
int sum_r = 0;
int sum_l =0;
int flag=0;
int cho = 0;
// int starSpeed[100];
// const int enemyX = 200;
// const int enemyY = 200;
int status = 0;

void blit_str256(const char *str, int x, int y)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= '@' && str[i] <= ']')
            wbpro_blitBuf8(8 * (str[i] - '@'), 0, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] >= '!' && str[i] <= '>')
            wbpro_blitBuf8(8 * (str[i] - '!'), 8, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] == '?')
            wbpro_blitBuf8(8 * 14, 16, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] == 'c')
            wbpro_blitBuf8(8 * 13, 16, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites);
        if (str[i] == 'w')
            wbpro_blitBuf8(7, 16, 240, x + i * 8, y, 26, 8, (uint8_t *)sprites);
        if (str[i] == 'x')
            wbpro_blitBuf8(42, 16, 240, x + i * 8, y, 61, 8, (uint8_t *)sprites);
    }
}

void setup()
{
    wbpro_init();//初始化
    wbpro_initBuf8();//初始化螢幕緩存
    wbpro_fillScreen(wbYELLOW);
    for(int i =0; i<256;i++)//定義256色
    {
        wbpro_setPal8(i,wbpro_color565(standardColour[i][0],standardColour[i][1],standardColour[i][2]));
    }
    ////////////////////////////////////////////////
    for(int i = 0; i<100;i++){
        starX[i]=random(0,240);//0,240
        starY[i]=random(0,320);//0,320
        // starSpeed[i]=random(2,5);
    }
    ////////////////////////////////
    pinMode(33,INPUT);
    pinMode(0,INPUT);
    pinMode(2,INPUT);
    pinMode(36,INPUT);
    pinMode(39,INPUT);
    pinMode(16,OUTPUT);
    pinMode(32,INPUT);
    pinMode(34,INPUT);
    pinMode(35,INPUT);


}
void loop()
{
    wbpro_clearBuf8();//清除緩存
    // if(digitalRead(33)==0){
    //     cho=1;
    // }
    
    

    switch(cho){
        case 0:
            open(); 
            //oc();
        break;
        case 1:
            normal(); 
            //select();
            
        break;
        case 2:
            HARD(); 
            //select();
        break;

    }
    wbpro_blit8();//點亮螢幕
}
void open(){
        blit_str256("KICK KICK!",74,130);
        blit_str256("NORMAL GAME",90,160);
        blit_colour256(10,10,70,160,48);//gree

        blit_str256("HARD GAME",90,180);
        blit_colour256(10,10,70,180,224);//red
        if(digitalRead(33)==0){
           cho=1;
           delay(100);
        }
        if(digitalRead(32)==0){
           cho=2;
           delay(100);
        }

    }

void normal(){
    blit_colour256(10,10,0,300,48);//gree
    blit_str256("BACK",15,300);//start
    blit_str256("START",200,300);//start

    blit_num256(sum_l, 0, 0, 1);//left
    if(flag==1){
        blit_str256("WIN!",0,10);//left
    }
    if(flag==2){
        blit_str256("WIN!",210,10);//right
    }
    if(sum_l>=10){
        blit_str256("LEFT WINEER!",74,150);
        blit_str256("STAR",105,190);
        //delay(1000);
        status=5;
    }
    if(sum_r>=10){
        blit_str256("RIGHT WINEER!",74,150);
        blit_str256("START",105,190);
        // delay(1000);
        status=5;
        
    }
    blit_num256(sum_r, 200, 0, 1);//right
    for(int i = 0; i<100;i++){///星星動
        wbpro_setBuf8(starX[i]+starY[i]*240,wbWHITE);

        // starY[i] += starSpeed[i];
        // if(starY[i] >= 320){
        //     starY[i]=0;
        // }
    }
        // blit_num256(1,50,50,255);
        // blit_num256(1,50,58,255);
        restar();
        
        switch(status){
        
        case 0:

            k = random(600) % 2;
            count();
            status=k+1;
            //flag=0;
            break;
        case 1:
            blit_colour256(100,100,70,100,3);//blue
            Click1();
            break;
        case 2:
            
            blit_colour256(100,100,70,100,252);//yellow
            Click2();
            break;
        case 3:
            //blit_str256("RIGHT",100,100);
            flag=2;
            sum_r+=1;
            
            reclick();
            
            break;
        case 4:
            //blit_str256("LEFT",100,100);
            flag=1;
            sum_l+=1;
            
            reclick();
            
            break;
        // case 5:
        //     break;
    }
     if(digitalRead(33)==0){
          sum_r=0;
          sum_l=0;
          cho=0;
          flag=0;
          delay(100);
        
      }

}
void Click1(){

    if(digitalRead(36)==0){
       
        status =4;
        //sum_l+=1;
    }
    if(digitalRead(34)==0){
        
        status =3;
        //sum_r+=1;
    }
}
void Click2(){

    if(digitalRead(39)==0){
        
        status =4;
        //sum_l+=1;
    }
    if(digitalRead(35)==0){
        
        status =3;
        //sum_r+=1;
    }
}
void reclick(){
    status =0;
}
void restar(){
    if(digitalRead(0)==0){
        sum_r=0;
        sum_l=0;
        status=0;
        flag=0;
    }
}

void count(){
    delay(500);
}
// void score_r(){
//     sum_r;
//     blit_num256(sum_r+=1,2,2,255);

// }

// void score_l(){
//     sum_l;
//     blit_num256(sum_l+=1,60,2,255);
// }

//////////////////////////////////////////////////////////////////////////////////
void HARD(){
     //wbpro_blitBuf8(0,0,240,0,0,200,200,(uint8_t *)img8bit);
     //wbpro_blitBuf8(50,50,128,0,0,128,128,(uint8_t *)img8bit); // 8bit 圖片不會造成圖片 顯色差
     wbpro_blitBuf8(0,0,128,0,0,128,128,(uint8_t *)people8bit);
     blit_str256("BACK",15,300);//start
     if(digitalRead(33)==0){
           sum_r=0;
           sum_l=0;
           cho=0;
          flag=0;
          delay(100);
        
       }
}

// width 色塊寬度
// height 色塊高度
// x X座標
// y Y座標
// colourMode 顏色選擇
void blit_colour256(int width,int height, int x,int y,uint8_t colourMode)
{
    for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            wbpro_setBuf8(i * 240 + j, colourMode);
        }
    }
}


// num 只能傳正整數
// x X座標
// y Y座標
// colourMode 顏色選擇
void blit_num256(uint16_t num, uint16_t x, uint16_t y, uint8_t colourMode)
{
    uint16_t d[5];

    d[0] = num / 10000;
    d[1] = (num - d[0] * 10000) / 1000;
    d[2] = (num - d[0] * 10000 - d[1] * 1000) / 100;
    d[3] = (num - d[0] * 10000 - d[1] * 1000 - d[2] * 100) / 10;
    d[4] = num - d[0] * 10000 - d[1] * 1000 - d[2] * 100 - d[3] * 10;

    for (int i = 0; i < 5; i++)
    {
        wbpro_blitBuf8(d[i] * 8 + 120, colourMode * 8, 240, x + i * 8, y, 8, 8, (uint8_t *)sprites); //將d[0]~d[4]逐個顯示並排列
    }
}