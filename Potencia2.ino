//----------------------------------------------------------------------------------------
// PROGRAMA PARA PROYECTO: 
// FECHA DE MODIFICACION:
//----------------------------------------------------------------------------------------
// CONFIGURACION DE LAS ENTRADAS ANALOGICAS DE 8 BITS 
// PARA MAYOR VELOCIDAD DE LECTURA
//----------------------------------------------------------------------------------------

#define mysize 200

unsigned long mytime[mysize];
byte Voltaje1[mysize];
byte Corriente1[mysize];
byte Voltaje2[mysize];
byte Corriente2[mysize];
byte Voltaje3[mysize];
byte Corriente3[mysize];
byte ADMUX0;
byte ADMUX1;
byte ADMUX2;
byte ADMUX3;
byte ADMUX4;
byte ADMUX5;

void setup()
{
  Serial.begin(115200);
 
  //Prescaler
  //ADPS2 - ADPS1 - ADPS0 - Division Factor
  //0        - 0       - 0        ->2
  //0        - 0       - 1        ->2
  //0        - 1       - 0        ->4
  //0        - 1       - 1        ->8
  //1        - 0       - 0        ->16
  //1        - 0       - 1        ->32
  //1        - 1       - 0        ->64
  //1        - 1       - 1        ->128
  ADCSRA|= (1<<ADPS2)|(0<<ADPS1)|(1<<ADPS0);  //Prescaler=32
 
  //Free running mode
  ADCSRB|=(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
 
  // Configuracion para Entrada A0
  // MUX4  MUX3  MUX2  MUX1  MUX0
  //    0     0     0     0     0
  ADMUX0|=(1<<ADLAR)|(0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(0<<MUX0);

  // Configuracion para Entrada A1
  // MUX4  MUX3  MUX2  MUX1  MUX0
  //    0     0     0     0     1
  ADMUX1|=(1<<ADLAR)|(0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(0<<MUX1)|(1<<MUX0);

  //Configuración para entrada A2
  // MUX4  MUX3  MUX2  MUX1  MUX0
  //    0     0     0     1     0
  ADMUX2| =(1<<ADLAR)|(0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(0<<MUX0);

  //Configuración para entrada A3
  // MUX4  MUX3  MUX2  MUX1  MUX0
  //    0     0     0     1     1
  ADMUX3| =(1<<ADLAR)|(0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(0<<MUX2)|(1<<MUX1)|(1<<MUX0);

  //Configuración para entrada A4
  // MUX4  MUX3  MUX2  MUX1  MUX0
  //    0     0     1     0     0
  ADMUX4| = (1<<ADLAR)|(0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(0<<MUX0);

  //Configuración para entrada A5
  // MUX4  MUX3  MUX2  MUX1  MUX0
  //    0     0     1     0     1
  ADMUX5| = (1<<ADLAR)|(0<<REFS1)|(1<<REFS0)|(0<<MUX3)|(1<<MUX2)|(0<<MUX1)|(1<<MUX0);

}
void loop()
{
  // -----------------------------------------------------------------------------
  // Toma de muestras de Voltaje y Corriente Instantáneos
  // -----------------------------------------------------------------------------
  for (int i=0; i<mysize;i++)
  {
    mytime[i]=micros();
    
    ADMUX=ADMUX0;                       // Selecciona Entrada A0
    Voltaje1[i]=analogReadFast();        // Muestra de Voltaje Instantaneo
            
    ADMUX=ADMUX1;                       // Selecciona Entrada A1
    Corriente1[i]=analogReadFast();      // Muestra de Corriente Instantanea

    ADMUX=ADMUX2;                       // Selecciona Entrada A2
    Voltaje2[i]=analogReadFast();        // Muestra de Voltaje Instantaneo
            
    ADMUX=ADMUX3;                       // Selecciona Entrada A3
    Corriente2[i]=analogReadFast();      // Muestra de Corriente Instantanea

    ADMUX=ADMUX4;                       // Selecciona Entrada A4
    Voltaje3[i]=analogReadFast();        // Muestra de Voltaje Instantaneo
            
    ADMUX=ADMUX5;                       // Selecciona Entrada A5
    Corriente3[i]=analogReadFast();      // Muestra de Corriente Instantanea
  }


  // -----------------------------------------------------------------------------
  // Envío de información por el puerto serie
  // -----------------------------------------------------------------------------
  Serial.println("D");
  for (int i=0; i<mysize;i++)
  {
    Serial.print(mytime[i]);
    Serial.print("/");
    Serial.print(Voltaje1[i],DEC);
    Serial.print("/");
    //Serial.print('\n');
    Serial.print(Corriente1[i],DEC);
    Serial.println("/");
    Serial.print('\n');

    Serial.print(mytime[i]);
    Serial.print("/");
    Serial.print(Voltaje2[i],DEC);
    Serial.print("/");
    //Serial.print('\n');
    Serial.print(Corriente2[i],DEC);
    Serial.println("/");
    Serial.print('\n');

    Serial.print(mytime[i]);
    Serial.print("/");
    Serial.print(Voltaje3[i],DEC);
    Serial.print("/");
    //Serial.print('\n');
    Serial.print(Corriente3[i],DEC);
    Serial.println("/");
    //Serial.print('\n');

  } 
 // -----------------------------------------------------------------------------
}

//Función para leer 8 bits
int analogReadFast()
{
  ADCSRA|=(1<<ADSC);
  // ADSC is cleared when the conversion finishes
  while (bit_is_set(ADCSRA, ADSC));
       return ADCH;
}

