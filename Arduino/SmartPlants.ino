
#include "LedControl.h"
#include <SoftwareSerial.h>
#include <String.h>

String temp_array[6]; // String이 분할되어 저장되는 배열 

/*timer 함수가 사용하는 변수*/
int second = 0;
int minute = 0;
int hour = 0;
int day = 0;

/*센서 값이 저장되는 변수*/
int soil_sensorValue;
int temp_sensorValue;
int light_sensorValue;

int plants_status[3] = { 0, 0, 0 };  //식물의 상태 값이 저장되는 배열
int plants_emotion = 0;            //식물의 감정이 저장되는 변수

/*App으로부터 받은 데이터가 저장되는 변수(디폴드 값 존재)*/
int Bcycle_moisture = 3;            //수분공급주기
int Bstandard_moisture = 50;        //토양습도기준값
int Bstandard_temp_LOW = 20;        //최저온도기준값
int Bstandard_temp_HIGH = 40;       //최대온도기준값
int Bstandard_light_tendency = 2;   //빛성향
int Bstandard_emergency_cycle = 7;  //긴급신고주기
int Buser_emotion = 0;              //사용자의 기분값

int isSupply = 0;     //수분공급주기인지 판단하는 변수
int night_count = 0;  //isNight()에서 사용하는 count
int count = 0;        //센서값 측정주기

/*judg_Emergency()에서 사용하는 변수*/
int emergency_stat = 0;     //긴급상황상태값
int emergency_second = 0;
int emergency_minute = 0;

/*블루투스 통신핀설정*/
SoftwareSerial BTSerial(4, 5); // TX : 4번핀, RX = 5번핀

/*도트매트릭스 핀설정*/
LedControl lc = LedControl(12, 11, 10, 1);


byte normal[] =  //평소 표정 :)
{
  B00000000,
  B00000000,
  B00100100,
  B00000000,
  B00100100,
  B00011000,
  B00000000,
  B00000000
};

byte happy[] =  //웃는 표정 :D
{
  B00000000,
  B00000000,
  B00100100,
  B00000000,
  B00111100,
  B00100100,
  B00011000,
  B00000000
};
byte sad[] =  //슬픈 표정 :(
{
  B00000000,
  B00000000,
  B11100111,
  B01000010,
  B00011000,
  B00100100,
  B00000000,
  B00000000
};
void setup()
{
    Serial.begin(9600);
    lc.shutdown(0, false);
    lc.setIntensity(0, 5);
    lc.clearDisplay(0);
    BTSerial.begin(9600);   //블루투스 통신속도 9600bps로 설정
}
void loop()
{
    /*Battery 잔량측정*/
    int vol = analogRead(A3);
    vol = map(vol, 0, 1023, 0, 100);

    Buser_emotion = -2; //Bsuer_emotion = -2로 초기화

    /*블루투스로 App에서 Data받기*/
    bluetooth();


    if (Buser_emotion != -2) {            //사용자의 기분값을 받았으면 
        display_emotion(Buser_emotion); //도트매트릭스에 표시
    }

    /*절전모드*/
    if (isNight() || vol <= 50)          //밤이거나 배터리잔량 <= 50% 이면 실행
    {
        if (count == 60)                   //절전모드일시, 60초마다 센서값 측정
        {                                 // + App으로 Data 전송
            readSensor();
            plants_emotion = cal_status();
            send_data();
            display_emotion(plants_emotion);
            count = 0;
        }
    }
    else {
        if (count == 10)                 //절전모드가 아니면 10초마다 센서값 측정
        {                                // + App으로 Data 전송
            readSensor();
            plants_emotion = cal_status();
            send_data();
            display_emotion(plants_emotion);
            count = 0;
        }
    }

    /*긴급상황판단*/
    judg_emergency(vol);

    /*timer()함수 실행*/
    timer();
    count++; //count : 1초마다 +1
    delay(1000);
}
/*
        [식물상태계산]
        plants_status[0...2] = 상태( 0 : good, 1 : a lots, -1 : lack)
        bad_stat = (0 : good, 1~2 : soso, 3 : bad)
*/
int cal_status()
{
    int bad_stat = 0;

    //토양상태측정
    if (isCycle() && !isSupply) //수분공급주기이면 상태를 측정
    {
        if (soil_sensorValue < Bstandard_moisture - 10)
        {
            plants_status[0] = -1;
            bad_stat++;
        }
        else if (soil_sensorValue > Bstandard_moisture + 10)
        {
            plants_status[0] = 1;
            bad_stat++;
            isSupply = 1;
        }
        else {
            plants_status[0] = 0;
            isSupply = 1;
        }
    }

    //온도상태측정
    if (temp_sensorValue > Bstandard_temp_HIGH)
    {
        plants_status[1] = 1;
        bad_stat++;
    }
    else if (temp_sensorValue < Bstandard_temp_LOW)
    {
        plants_status[1] = -1;
        bad_stat++;
    }
    else
    {
        plants_status[1] = 0;
    }

    //조도상태측정
    if (Bstandard_light_tendency == 2)
    {
        plants_status[2] = 0;
    }
    else if (!isNight())
    {
        if (Bstandard_light_tendency == 1)
        {
            if (light_sensorValue < 80)
            {
                plants_status[2] = -1;
                bad_stat++;
            }
            else
            {
                plants_status[2] = 0;
            }
        }
        else if (Bstandard_light_tendency == 0)
        {
            if (light_sensorValue > 30)
            {
                plants_status[2] = 1;
                bad_stat++;
            }
            else
            {
                plants_status[2] = 0;
            }
        }
    }
    else
    {
        plants_status[2] = 0;
    }

    return bad_stat;
}
/*
        [긴급상태판단]
        plants_emotion == 3(bad) 또는
        Battery 남은전력 <= 30% 이면
        카운트증가

        카운트 > 긴급신고주기 이면
        emergency_stat = 1
*/
void judg_emergency(int vol)
{
    if (plants_emotion == 3 || vol <= 30)
        emergency_second++;
    else {
        emergency_second = 0;
        emergency_minute = 0;
        emergency_stat = 0;
    }

    if (emergency_second == 60) {
        emergency_second = 0;
        emergency_minute++;
    }

    if (emergency_minute > Bstandard_emergency_cycle * 24 * 60)
        emergency_stat = 1;
}
/*
        [지금이 밤인지 낮인지 판별]
        10분마다 조도센서의 값을 확인
        조도센서의 값 < 30 이면
        night_count++

        night_count >= 6 이면 밤
*/
int isNight() {
    if (minute % 10 == 0)
        if (light_sensorValue < 30)
            night_count++;
        else
            night_count = 0; Z

            if (night_count >= 6)
                return 1;
            else
                return 0;
}
/*
      [도트매트릭스]
      a = 1~2 : normal
      a = 0 : happy
      a = else : sad
*/
void display_emotion(int a)
{
    if (a >= 1 && a <= 2) {
        for (int i = 0; i < 8; i++)
        {
            lc.setRow(0, i, normal[i]);
        }
    }
    else if (a == 0) {
        for (int i = 0; i < 8; i++)
        {
            lc.setRow(0, i, happy[i]);
        }
    }
    else {
        for (int i = 0; i < 8; i++)
        {
            lc.setRow(0, i, sad[i]);
        }
    }
}
/*
  [Bluetooth App -> Arduino]
  받아야할 값 :
                  Bcycle_moisture (수분공급주기)
                  Bstandard_moisture (토양습도센서기준값)
                  Bstandard_temp_LOW (온도센서_LOW 값)
                  Bstandard_temp_HIGH(온도센서_HIGH 값)
                  Bstandard_light_tendency (빛성향값)
                  Bstandard_emergency_cycle (긴급신고주기)
*/
void bluetooth() {

    if (BTSerial.available() > 0) //데이터 받기
    {
        String str = BTSerial.readStringUntil('\n');
        split(str, ',');            //구분자로 문자열 분리
        if (temp_array[0].equals("A")) {
            Buser_emotion = temp_array[1].toInt();

        }
        else {

            Bcycle_moisture = temp_array[0].toInt();
            Bstandard_moisture = temp_array[1].toInt();
            Bstandard_temp_LOW = temp_array[2].toInt();
            Bstandard_temp_HIGH = temp_array[3].toInt();
            Bstandard_light_tendency = temp_array[4].toInt();
            Bstandard_emergency_cycle = temp_array[5].toInt();
        }

    }
}

/*구분자로 문자열을 분리*/
void split(String sData, char cSeparator)
{
    int nCount = 0;
    int nGetIndex = 0;

    //임시저장
    String sTemp = "";

    //원본 복사
    String sCopy = sData;

    while (true)
    {
        //구분자 찾기
        nGetIndex = sCopy.indexOf(cSeparator);

        //리턴된 인덱스가 있나?
        if (-1 != nGetIndex)
        {
            //있다.

            //데이터 넣고
            sTemp = sCopy.substring(0, nGetIndex);
            temp_array[nCount] = sTemp;

            //뺀 데이터 만큼 잘라낸다.
            sCopy = sCopy.substring(nGetIndex + 1);
        }
        else
        {
            //없으면 마무리 한다.
            temp_array[nCount] = sCopy;
            break;
        }

        //다음 문자로~
        ++nCount;
    }

}
/*
      Arduino -> App : Data Transfer
      전송형태 : "온도상태|조도상태|토양습도상태|긴급상황상태"
*/
void send_data()
{
    String str = String(plants_status[1]);
    String str1 = String(plants_status[2]);
    String str2 = String(plants_status[0]);
    String str3 = String(emergency_stat);
    str.concat("|");
    str.concat(str1);
    str.concat("|");
    str.concat(str2);
    str.concat("|");
    str.concat(str3);

    //BTSerial.write는 String형을 전송하지 못하므로 char 포인터 형으로 변환
    char* cString = (char*)malloc(sizeof(char) * (str.length() + 1));
    str.toCharArray(cString, str.length() + 1);
    BTSerial.write(cString);

}
/* 센서값을 읽고 mapping */
void readSensor() {
    soil_sensorValue = analogRead(A0);
    temp_sensorValue = analogRead(A1);
    light_sensorValue = analogRead(A2);

    soil_sensorValue = map(soil_sensorValue, 1, 1023, 0, 100);    //토양습도센서
    temp_sensorValue = map(temp_sensorValue, 20, 358, -40, 125);    //온도센서
    light_sensorValue = map(light_sensorValue, 0, 1023, 0, 100); //조도센서
}
/*수분공급주기인지 계산*/
int isCycle() {
    if (day % Bcycle_moisture != 0)
        isSupply = 1;

    return (day % Bcycle_moisture == 0);
}
/* timer 함수 */
void timer() {
    second++;
    if (second == 60) {
        second = 0;
        minute++;
    }

    if (minute == 60) {
        minute = 0;
        hour++;
    }

    if (hour == 24) {
        hour = 0;
        day++;
    }

}
