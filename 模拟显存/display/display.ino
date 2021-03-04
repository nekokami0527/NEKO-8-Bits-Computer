#include "Adafruit_ssd1306syp.h"
#include "config.h"
uint8_t OE_Now, CE_Now, WE_Now;
uint16_t address_tmp = 0;
uint8_t data_tmp = 0;
uint8_t is_first = false;
uint8_t need_update = false;
uint8_t system_status = 0;
uint8_t char_display_buffer[DISPLAY_ASCII_WIDTH * DISPLAY_ASCII_HEIGHT] = {0};

Adafruit_ssd1306syp display(SDA_PIN, SCL_PIN);
void init_pin(){
  delay(1000);//千万不要删
  //配置PC6为输入 ****
  IOCR = 0x80;
  IOCR |= 0x03;
  DDRC |= 0x40;

  pinMode(A0,INPUT);pinMode(A1,INPUT);pinMode(A2,INPUT);pinMode(A3,INPUT);
  pinMode(A4,INPUT);pinMode(A5,INPUT);pinMode(A7,INPUT);pinMode(A8,INPUT);
  pinMode(A9,INPUT);pinMode(A10,INPUT);pinMode(A11,INPUT);pinMode(A12,INPUT);
  
  pinMode(CE,INPUT);pinMode(WE,INPUT);pinMode(OE,INPUT);

  pinMode(IO0,INPUT);pinMode(IO1,INPUT);pinMode(IO2,INPUT);pinMode(IO3,INPUT);
  pinMode(IO4,INPUT);pinMode(IO5,INPUT);pinMode(IO6,INPUT);pinMode(IO7,INPUT);
}
void write_A6(int value){
  if(value)
    PORTC |= 0x40;
  else
    PORTC &= 0xBF;
}
uint8_t read_A6(){
  return (PINC>>6)&0x01;
}
uint16_t get_address() {
  uint16_t address = 0;
  address = address << 1 | digitalRead(A12);
  address = address << 1 | digitalRead(A11);
  address = address << 1 | digitalRead(A10);
  address = address << 1 | digitalRead(A9);
  address = address << 1 | digitalRead(A8);
  address = address << 1 | digitalRead(A7);
  address = address << 1 | read_A6();
  address = address << 1 | digitalRead(A5);
  address = address << 1 | digitalRead(A4);
  address = address << 1 | digitalRead(A3);
  address = address << 1 | digitalRead(A2);
  address = address << 1 | digitalRead(A1);
  address = address << 1 | digitalRead(A0);
  return address;
}
uint8_t get_data() {
  uint8_t data = 0;
  pinMode(IO0, INPUT); pinMode(IO1, INPUT); pinMode(IO2, INPUT); pinMode(IO3, INPUT);
  pinMode(IO4, INPUT); pinMode(IO5, INPUT); pinMode(IO6, INPUT); pinMode(IO7, INPUT);
  data = data << 1 | digitalRead(IO7);
  data = data << 1 | digitalRead(IO6);
  data = data << 1 | digitalRead(IO5);
  data = data << 1 | digitalRead(IO4);
  data = data << 1 | digitalRead(IO3);
  data = data << 1 | digitalRead(IO2);
  data = data << 1 | digitalRead(IO1);
  data = data << 1 | digitalRead(IO0);
  return data;
}
uint8_t put_data(uint8_t data) {
  pinMode(IO0, OUTPUT); pinMode(IO1, OUTPUT); pinMode(IO2, OUTPUT); pinMode(IO3, OUTPUT);
  pinMode(IO4, OUTPUT); pinMode(IO5, OUTPUT); pinMode(IO6, OUTPUT); pinMode(IO7, OUTPUT);
  digitalWrite(IO0, (data >> 0) & 0x01); digitalWrite(IO1, (data >> 1) & 0x01);
  digitalWrite(IO2, (data >> 2) & 0x01); digitalWrite(IO3, (data >> 3) & 0x01);
  digitalWrite(IO4, (data >> 4) & 0x01); digitalWrite(IO5, (data >> 5) & 0x01);
  digitalWrite(IO6, (data >> 6) & 0x01); digitalWrite(IO7, (data >> 7) & 0x01);
}
void clear_io_mode() {
  pinMode(IO0, INPUT); pinMode(IO1, INPUT); pinMode(IO2, INPUT); pinMode(IO3, INPUT);
  pinMode(IO4, INPUT); pinMode(IO5, INPUT); pinMode(IO6, INPUT); pinMode(IO7, INPUT);
}
void display_buffer(){
  display.clear();
  for(int i=0;i<DISPLAY_ASCII_HEIGHT;i++){
    for(int j=0;j<DISPLAY_ASCII_WIDTH;j++){
      unsigned char tmp = char_display_buffer[DISPLAY_ASCII_WIDTH * i + j];
      if(isprint(tmp)){
        display.drawChar(j * DISPLAY_CHAR_WIDTH, i * DISPLAY_CHAR_HEIGHT, tmp, WHITE, 0x00, 1);
      }
    }
  }
  display.update();
}
void display_info(){
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println(" ASCII Graphics card");
  display.println("    [  25 x 8  ]    ");
  display.println(" Display Memory     ");
  display.println("    0x000 - 0x0C8   ");
  display.println("                    ");
  display.println("                    ");
  display.println(" Designer  Nekokami ");
  display.update();
  delay(2000);
}
void setup()
{
  init_pin();
  display.initialize();
  delay(100);
  display_info();
  system_status = 0;
  is_first = true;
}
uint32_t timer = 0;
void loop()
{
  if(HIGH == ReadCE){
    system_status = 0;
    get_data();
    if(need_update == 1 && millis()-timer > 500){
      //display.update();
      display_buffer();
      need_update = false;
      timer = millis();
    }
  }
  switch(system_status){
    case 0:
      if(LOW == ReadCE){
        address_tmp = get_address();
        system_status = 1;
        clear_io_mode();
      }
      break;
    case 1:
      if(LOW == ReadOE){
        if(address_tmp < 0x0A8)
          put_data(char_display_buffer[address_tmp]);
        else
          put_data(0xff);
        system_status = 2;
      }else if(LOW == ReadWE){
        system_status = 3;
      }
      break;
    case 2:
      if(HIGH == ReadOE)
        system_status = 4;
      break;
    case 3:
      if(HIGH == ReadWE){
        data_tmp = get_data();
        if(address_tmp < 0x0A8){
          char_display_buffer[address_tmp] = data_tmp;
          need_update = true;
        }
        system_status = 4;
      }
      break;
    case 4:
      if(HIGH == ReadCE){
        system_status = 0;
        timer = millis();
      }
      break;
    default:
      system_status = 0;
      get_data();
  }
}
