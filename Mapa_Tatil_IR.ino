//Incluindo bibliotecas
#include <Arduino.h>
#include <WiFi.h>
#include "SinricPro.h"
#include "SinricProMotionsensor.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Adafruit_VL53L0X.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30


// set the pins to shutdown
#define SHT_LOX1 25


// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();


// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Definições da rede WiFi e do Sinric Pro
#define WIFI_SSID         "En - Servicos"                                                                           //Nome da rede Wifi
#define WIFI_PASS         "Enapervicos"                                                                     //Senha da rede Wifi
#define APP_KEY           "fecd77d1-b8fd--0e8f98d7ba9f"                                         //Chave do Sinric Pro
#define APP_SECRET        "5ca46a75-1b69-4eca-b56c-0f2cbb2f37e-0684-4e0d-8d60-7ecf04522361"    //Senha do Sinric Pro
#define MOTIONSENSOR_ID_AREA_T   "62c6f30aec232058f7615f"                                                //ID do dispositivo Sensor Área de Trabalho 
#define MOTIONSENSOR_ID_SALA_S   "62c6d0b3ad95bfbcdf37be5d"                                                //ID do dispositivo Sensor Sala de Aula Sul
#define MOTIONSENSOR_ID_SALA_L   "62c6d0dad95bfbcdf37be96"                                                //ID do dispositivo Sensor Sala de Aula Leste
#define MOTIONSENSOR_ID_ESCADA   "62b1be1dfce0b9e02e73d587"                                                //ID do dispositivo Sensor Escada
#define MOTIONSENSOR_ID_ESCADA_D   "6328701bfa39e7cce4831"                                                //ID do dispositivo Sensor Escada D

#define MOTIONSENSOR_ID_PROX   "62c6d123aec232058f761c1"                                                //ID do dispositivo Sensor Aproximação





//Define a velocidade de comunicação com o monitor do PC
#define BAUD_RATE         115200               


//Define as postas IOs do microcontrolador para conectar aos sensores
#define MOTIONSENSOR_PIN_AREA_T  16 
#define MOTIONSENSOR_PIN_SALA_S  4                   
#define MOTIONSENSOR_PIN_SALA_L  17                    
#define MOTIONSENSOR_PIN_ESCADA  5
#define MOTIONSENSOR_PIN_ESCADA_D  18

#define MOTIONSENSOR_PIN_PROX  22


bool myPowerState = true;                     
bool lastMotionState = true;
unsigned long lastChange = 5000;


bool myPowerState2 = true;                     
bool lastMotionState2 = true;
unsigned long lastChange2 = 5000;



bool myPowerState3 = true;                     
bool lastMotionState3 = true;
unsigned long lastChange3 = 5000;


bool myPowerState4 = true;                     
bool lastMotionState4 = true;
unsigned long lastChange4 = 5000;




bool myPowerState5 = true;                     
bool lastMotionState5 = true;
unsigned long lastChange5 = 30000;
unsigned long actualMillis5 = 0;
bool actualMotionState5 = true;


bool myPowerState6 = true;                     
bool lastMotionState6 = true;
unsigned long lastChange6 = 5000;
unsigned long actualMillis6 = 0;


unsigned long tempoP = 0;
unsigned int tempoA = 0;

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned long lastChangeP1 = 0;
unsigned long lastChangeP2 = 0;
unsigned long actualMillis_sensor = 0;
unsigned long actualMillis_sensor2 = 0;
int contador1 = 0; 
int contador2 = 0;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int x = 1;
int distanciaSonar = 40;                  //distancia para detectar a pessoa de frente ao sonar
unsigned long tempoPassagem = 0;





//Chave Enable
const int PIN_habilitar = 23;
int estado_habilitar = 0;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Função para verificar os 5 sensores IRs
void handleMotionsensor() {

  //Para sensor da Área de Trabalho
  //if (!myPowerState) return;                                                        //Se o dispositivo estiver desligado... não faça nada

  unsigned long actualMillis = millis();
  if (actualMillis - lastChange > 5000){          

  bool actualMotionState = !digitalRead(MOTIONSENSOR_PIN_AREA_T);                     //Ler o estado real do sensor de movimento

  
  
  if (actualMotionState != lastMotionState) {                                       //Se o estado mudou
    Serial.printf("Motion %s\r\n", actualMotionState?"detected":"not detected");
    lastMotionState = actualMotionState;                                            //Atualizar último estado conhecido
    lastChange = actualMillis;                                                      //Atualizar o tempo de debounce
    
    
    SinricProMotionsensor &myMotionsensor = SinricPro[MOTIONSENSOR_ID_AREA_T];        //Obter dispositivo sensor da Área de Trabalho
    myMotionsensor.sendMotionEvent(actualMotionState);                              //Altera o estado do sensor no Sinric Pro
  }
}  

  //Para sensor da Sala Sul
  //if (!myPowerState2) return;                                               

  unsigned long actualMillis2 = millis();
  if (actualMillis2 - lastChange2 > 5000){                                   

  bool actualMotionState2 = !digitalRead(MOTIONSENSOR_PIN_SALA_S);                     

  
  
  if (actualMotionState2 != lastMotionState2) {                                      
    Serial.printf("Motion2 %s\r\n", actualMotionState2?"detected":"not detected");
    lastMotionState2 = actualMotionState2;                                           
    lastChange2 = actualMillis2;                                                     
    
    
    SinricProMotionsensor &myMotionsensor2 = SinricPro[MOTIONSENSOR_ID_SALA_S];        
    myMotionsensor2.sendMotionEvent(actualMotionState2);
  }
  }


  //Para sensor da Sala Leste
  // if (!myPowerState3)return;                                                  

  unsigned long actualMillis3 = millis();
  if (actualMillis3 - lastChange3 > 5000) {                                

  bool actualMotionState3 = !digitalRead(MOTIONSENSOR_PIN_SALA_L);                     

  
  
  if (actualMotionState3 != lastMotionState3) {                                      
    Serial.printf("Motion3 %s\r\n", actualMotionState3?"detected":"not detected");
    lastMotionState3 = actualMotionState3;                                           
    lastChange3 = actualMillis3;                                                     
    
    
    SinricProMotionsensor &myMotionsensor3 = SinricPro[MOTIONSENSOR_ID_SALA_L];        
    myMotionsensor3.sendMotionEvent(actualMotionState3);
  }

  }



  //Para sensor da Escada
  //if (!myPowerState4) return;                                                 

  unsigned long actualMillis4 = millis();
  if (actualMillis4 - lastChange4 > 5000) {                                

  bool actualMotionState4 = !digitalRead(MOTIONSENSOR_PIN_ESCADA);                     

  
  
  if (actualMotionState4 != lastMotionState4) {                                      
    Serial.printf("Motion4 %s\r\n", actualMotionState4?"detected":"not detected");
    lastMotionState4 = actualMotionState4;                                           
    lastChange4 = actualMillis4;                                                     
    
    
    SinricProMotionsensor &myMotionsensor4 = SinricPro[MOTIONSENSOR_ID_ESCADA];        
    myMotionsensor4.sendMotionEvent(actualMotionState4);
  }

  }
  

   //Para sensor da Escada D
  //if (!myPowerState6) return;                                                  

  unsigned long actualMillis6 = millis();
  if (actualMillis6 - lastChange6 > 5000) {                                   

  bool actualMotionState6 = !digitalRead(MOTIONSENSOR_PIN_ESCADA_D);                     

  
  
  if (actualMotionState6 != lastMotionState6) {                                      
    Serial.printf("Motion6 %s\r\n", actualMotionState6?"detected":"not detected");
    lastMotionState6 = actualMotionState6;                                           
    lastChange6 = actualMillis6;                                                     
    
    
    SinricProMotionsensor &myMotionsensor6 = SinricPro[MOTIONSENSOR_ID_ESCADA_D];        
    myMotionsensor6.sendMotionEvent(actualMotionState6);
  }
  }
 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Função para executar quando altera estado no aplicativo da Amazon

//Para da Área de Trabalho
bool onPowerState(const String &deviceId, bool &state) {
  Serial.printf("Device %s turned %s (via SinricPro) \r\n", deviceId.c_str(), state?"on":"off");
  myPowerState = state;
  delay(200);
  return true; 
}


//Para o sensor Sala Sul
bool onPowerState2(const String &deviceId2, bool &state2) {
  Serial.printf("Device 2 %s turned %s (via SinricPro) \r\n", deviceId2.c_str(), state2?"on":"off");
  myPowerState2 = state2;  
  delay(200);
  return true; 
}


//Para o sensor da Sala Leste
bool onPowerState3(const String &deviceId3, bool &state3) {
  Serial.printf("Device 3 %s turned %s (via SinricPro) \r\n", deviceId3.c_str(), state3?"on":"off");
  myPowerState3 = state3;
  delay(200);
  return true; 
}


//Para o sensor da Escada
bool onPowerState4(const String &deviceId4, bool &state4) {
  Serial.printf("Device 4 %s turned %s (via SinricPro) \r\n", deviceId4.c_str(), state4?"on":"off");
  myPowerState4 = state4;
  delay(200);
  return true; 
}

//Para o sensor da Escada D
bool onPowerState6(const String &deviceId6, bool &state6) {
  Serial.printf("Device 6 %s turned %s (via SinricPro) \r\n", deviceId6.c_str(), state6?"on":"off");
  myPowerState6 = state6;
  delay(200);
  return true; 
}


//Para o sensor de Proximidade
bool onPowerState5(const String &deviceId5, bool &state5) {
  Serial.printf("Device 5 %s turned %s (via SinricPro) \r\n", deviceId5.c_str(), state5?"on":"off");
  myPowerState5 = state5;
  delay(200);
  return true; 
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Configurações gerais. Essa função é obrigatória no IDE do Arduino
void setup() {
  //Seta a velocidade de comunicação com o monitor serial do PC
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");

  //Seta os pinos IOs do microcontrolador com os pinos dos sensores
  pinMode(MOTIONSENSOR_PIN_AREA_T, INPUT);
  pinMode(MOTIONSENSOR_PIN_SALA_S, INPUT);
  pinMode(MOTIONSENSOR_PIN_SALA_L, INPUT);
  pinMode(MOTIONSENSOR_PIN_ESCADA, INPUT);
  pinMode(MOTIONSENSOR_PIN_ESCADA_D, INPUT);

  pinMode(MOTIONSENSOR_PIN_PROX, INPUT);
  

 

  pinMode(PIN_habilitar, INPUT);
  
  setupWiFi();
  setupSinricPro();



    Serial.println("Adafruit VL53L0X test");
  if (!lox1.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 


  
}





//Configuração da rede WiFi
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Connecting");
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
  }
  IPAddress localIP = WiFi.localIP();
  Serial.printf("connected!\r\n[WiFi]: IP-Address is %d.%d.%d.%d\r\n", localIP[0], localIP[1], localIP[2], localIP[3]);
}

//Configuração do Sinric Pro
void setupSinricPro() {
  //Adicionar sensores
  SinricProMotionsensor& myMotionsensor = SinricPro[MOTIONSENSOR_ID_AREA_T];
  SinricProMotionsensor& myMotionsensor2 = SinricPro[MOTIONSENSOR_ID_SALA_S];
  SinricProMotionsensor& myMotionsensor3 = SinricPro[MOTIONSENSOR_ID_SALA_L];
  SinricProMotionsensor& myMotionsensor4 = SinricPro[MOTIONSENSOR_ID_ESCADA];
  SinricProMotionsensor& myMotionsensor6 = SinricPro[MOTIONSENSOR_ID_ESCADA_D];

  SinricProMotionsensor& myMotionsensor5 = SinricPro[MOTIONSENSOR_ID_PROX];

  //Definir função de retorno de chamada para o dispositivo quando há mudança via aplicativo
  myMotionsensor.onPowerState(onPowerState);
  myMotionsensor2.onPowerState(onPowerState2);
  myMotionsensor3.onPowerState(onPowerState3);
  myMotionsensor4.onPowerState(onPowerState4);
  myMotionsensor6.onPowerState(onPowerState6);


  myMotionsensor5.onPowerState(onPowerState5);
  

  //Se tá conectado com Sinric Pro e inicializa com a chave e senha
  SinricPro.onConnected([](){ Serial.printf("Connected to SinricPro\r\n"); });
  SinricPro.onDisconnected([](){ Serial.printf("Disconnected from SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void loop() {

  //Chama a função para verificar se foi acionado os sensores IRs
  handleMotionsensor();

  //Monitora as alterações de estado no Sinric Pro
  SinricPro.handle();


 

///////////////////////////////////////////////////////////////////////////////////////////////////
  VL53L0X_RangingMeasurementData_t measure1;
  Serial.print("Reading a measurement... ");
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!

  if (measure1.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure1.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }
///////////////////////////////////////////////////////////////////////////////////////////////////
  
  //Seta a variável "actualMillis5" com o tempo interno do microcontrolador
  actualMillis5 = millis();

  //Verifica se passou 30 segundos da ultima detecção de movimento

  if (actualMillis5 - lastChange5 >= 10000){    
    
  //Mostra no monitor do PC        
  Serial.println("passou");  
  
  //Verifica o pino Enable
   estado_habilitar = digitalRead(PIN_habilitar);

   
   delay(100);
  if (measure1.RangeMilliMeter <= 600    && estado_habilitar == LOW )
      {   
        Serial.println("Detectado");    
         actualMotionState5 = true;
                
      }
   else{
    actualMotionState5 = false;
   }
    

  
  
  //Se houve uma mudança da distância do obstáculo com o limiar de 40cm
  if (actualMotionState5 != lastMotionState5 ) {         
    lastMotionState5 = actualMotionState5;                                          //Atualizar último estado conhecido
    lastChange5 = actualMillis5;                                                    //Atualizar o tempo de debounce

    
      SinricProMotionsensor &myMotionsensor5 = SinricPro[MOTIONSENSOR_ID_PROX];      //Obter dispositivo sensor de movimento
      myMotionsensor5.sendMotionEvent(actualMotionState5);                           //Altera o estado do sensor no Sinric Pro
    }
    
  }
  
 

  
  
  
}







    
  
