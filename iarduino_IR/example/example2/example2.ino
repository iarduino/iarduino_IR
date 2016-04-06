// Библиотека iarduino_IR для работы arduino с ИК приёмопередатчиками, разработана интернет магазином http://iarduino.ru
// Приём данных с ИК-пультов осуществляется через Trema ИК-приёмник http://iarduino.ru/shop/Sensory-Datchiki/ik-priemnik-trema-modul.html
// К 13 выводу подключен Trema зелёный светодиод http://iarduino.ru/shop/Expansion-payments/svetodiod---zelenyy-trema-modul.html
// Для удобства подключения предлагаем воспользоваться Trema Shield http://iarduino.ru/shop/Expansion-payments/trema-shield.html

// Подключаем библиотеку:
#include <iarduino_IR.h>                          // подключаем библиотеку для работы с ИК-приёмопередатчиком

// Объявляем переменные и константы:
iarduino_IR    IR(2);                             // объявляем переменную для работы с ИК-приёмником (номер цифрового вывода к которому подключён ИК приёмник = 2)
const uint8_t  PIN_LED   = 13;                    // указываем номер вывода arduino, к которому подключён светодиод
      uint32_t SEC_START = 0;                     // количество микросекунд в момент включения светодиода

void setup(){
  Serial.begin(9600);                             // открываем последовательный порт на скорости 9600 бод
  IR.begin();                                     // инициализация ИК приёмника
  pinMode(PIN_LED, OUTPUT);                       // устанавливаем режим работы вывода подключённого к светодиоду, как "выход"
}
void loop(){
  if(IR.check(true)){                             // если принят информационный пакет или пакеты повтора
    Serial.print(F("Code = "));
    Serial.print(IR.data,HEX);
    Serial.print(F(", Length = "));
    Serial.print(IR.length);
    Serial.println(F(" bits."));
    if(IR.data==0xFF30CF){SEC_START = micros();}  // если принятые данные соответствуют кнопке «1», то сохраняем количество микросекунд
  }
  if(SEC_START>micros()){SEC_START=0;}            // произошло переполнение micros()
  if(micros()<200000){delay(200);}                // ждём 200 мс после переполнение micros()
  digitalWrite(PIN_LED, SEC_START>(micros()-200000)?HIGH:LOW); // вкл/выкл светодиод
}
