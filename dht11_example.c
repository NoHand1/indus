#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>


#define PIN (7)


//Auslesen der Daten
int ReadData(){


int i=0, count=0;
int data[5] = { 0 };
int buffer[40]= { 0 };


//Startsignal zur Uebertragung
pinMode(PIN,OUTPUT);
   digitalWrite(PIN,LOW);
   delay(18);
   digitalWrite(PIN,HIGH);
   delayMicroseconds(30);
pinMode(PIN,INPUT);


//Solange warten bis Low
while(digitalRead(PIN)==HIGH) delayMicroseconds( 1 );
//Antwort Sensor


while(digitalRead(PIN)==LOW) delayMicroseconds(1);
while(digitalRead(PIN)==HIGH) delayMicroseconds( 1 );


//Saten in Buffer schreiben
for(i=0; i < 40; i++)
   {
while(digitalRead(PIN)==LOW){
           delayMicroseconds(1);
       }


       //Bit high oder low
delayMicroseconds(29);
if(digitalRead(PIN)==LOW) buffer[i]=0;
else if (digitalRead(PIN)==HIGH) buffer[i]=1;
   }






// Luftfeuchtigkeit
data[0] = buffer[7] + buffer[6]*2 + buffer[5]*4 + buffer[4]*8 + buffer[3]*16 + buffer[2]*32 + buffer[1]*64 + buffer[0]*128;
data[1] = buffer[15] + buffer[14]*2 + buffer[13]*4 + buffer[12]*8 + buffer[11]*16 + buffer[10]*32 + buffer[9]*64 + buffer[8]*128;


// Temperatur
data[2] = buffer[23] + buffer[22]*2 + buffer[21]*4 + buffer[20]*8 + buffer[19]*16 + buffer[18]*32 + buffer[17]*64 + buffer[16]*128;
data[3] = buffer[31] + buffer[30]*2 + buffer[29]*4 + buffer[28]*8 + buffer[27]*16 + buffer[26]*32 + buffer[25]*64 + buffer[24]*128;


// Checksumme
data[4] = buffer[39] + buffer[38]*2 + buffer[37]*4 + buffer[36]*8 + buffer[35]*16 + buffer[34]*32 + buffer[33]*64 + buffer[32]*128;


// Nur zum Testen
for(i=0; i < 8; i++)
   {
       printf("%d", buffer[i]);
   }
   puts("");
   for(i=8; i < 16; i++)
   {
       printf("%d", buffer[i]);
   }
   puts("");
   for(i=16; i < 24; i++)
   {
       printf("%d", buffer[i]);
   }
   puts("");
   for(i=24; i < 32; i++)
   {
       printf("%d", buffer[i]);
   }
puts("");


printf("%d\n", data[0]);
printf("%d\n", data[1]);
printf("%d\n", data[2]);
printf("%d\n", data[3]);
printf("%d\n", data[4]);


printf("Temperatur: %d,%d °C, Luftfeuchtigkeit: %d,%d %%\n", data[2],data[3],data[0],data[1]);


   // Ausgabe -> vorher Checksumme überprüfen (Byte 5 == Byte 1-4)
   /*if( data[4] == (data[0]+data[1]+data[2]+data[3]) )
   {
       printf("Temperatur: %d %d   Luftfeuchtigkeit: %d %d\n", data[2],data[3],data[0],data[1]);
   }
   else
   {
       printf("Daten konnten nicht ermittelt werden!\n");
   }*/
return EXIT_SUCCESS;
}




int main ()
{
//WiringPi initialisieren
wiringPiSetup();


while(1)
   {
       ReadData();
       delay(2000);
   }


return EXIT_SUCCESS;
}
 
	return(0);
}
