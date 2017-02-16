//Omer Faruk KOC
//miniKukaV4Son_19.Nisan.2016

#include <Servo.h>

Servo servoOmuz;
Servo servoPazu;
Servo servoDirsek;
Servo servoBilek;
Servo servoParmak;

const int servoOmuzPin=3;
const int servoPazuPin=4;
const int servoDirsekPin=5;
const int servoBilekPin=6;
const int servoParmakPin=7;


const int potOmuz=A3;
const int potPazu=A2;
const int potDirsek=A1;
const int potBilek=A0;
const int potParmak=A4;

int potOmuzDurum=0;     
int potOmuzPozisyon = 0;

int potPazuDurum=0;     
int potPazuPozisyon = 0;

int potDirsekDurum=0;     
int potDirsekPozisyon = 0;

int potBilekDurum=0;     
int potBilekPozisyon = 0;

int potParmakDurum=0;     
int potParmakPozisyon = 0;      


const int kaydetButonPin=10;
const int oynatButonPin=9;

int kaydetButonDeger=0;
int oynatButonDeger=0;

int noktaKayitSayisi=0;

int omuzNoktalari[10];
int pazuNoktalari[10];
int dirsekNoktalari[10];
int bilekNoktalari[10];
int parmakNoktalari[10];

bool oynat=true;
bool durmaKontrol=true;

void setup(){
  
  servoOmuz.attach(servoOmuzPin);
  servoPazu.attach(servoPazuPin);
  servoDirsek.attach(servoDirsekPin);
  servoBilek.attach(servoBilekPin);
  servoParmak.attach(servoParmakPin);

  pinMode(kaydetButonPin,INPUT);
  pinMode(oynatButonPin,INPUT);  

  Serial.begin(9600);
} 
void loop()
{
  butonOku();
  Serial.println(noktaKayitSayisi);
}

void butonOku()
{
  kaydetButonDeger=digitalRead(kaydetButonPin);
  oynatButonDeger=digitalRead(oynatButonPin);

  if(kaydetButonDeger==HIGH)
  {
    //durmaKontrol = false;
      //Serial.println("Kaydet");
      noktaKaydet(noktaKayitSayisi);
      delay(250);
      noktaKayitSayisi++;
  }
  else
  {
    if(oynat)
    {
      //Serial.println("Oynuyooo");
      potDegerOku();
      servoCalistir();
    }
  }
  if(oynatButonDeger==HIGH)
  {
    //Serial.println("Playy");
    noktaDegerlerindenOynat(noktaKayitSayisi);
    oynat=false;
  }
}

void potDegerOku()
{
  potOmuzDurum=analogRead(potOmuz);
  potOmuzPozisyon= map(potOmuzDurum,0,1023,0,180);
  potPazuDurum=analogRead(potPazu);
  potPazuPozisyon= map(potPazuDurum,0,1023,0,180);
  potDirsekDurum=analogRead(potDirsek);
  potDirsekPozisyon= map(potDirsekDurum,0,1023,0,180);
  potBilekDurum=analogRead(potBilek);
  potBilekPozisyon= map(potBilekDurum,0,1023,0,180);
  potParmakDurum=analogRead(potParmak);
  potParmakPozisyon= map(potParmakDurum,0,1023,10,150);
}

void servoCalistir()
{
  servoOmuz.write(potOmuzPozisyon);
  servoPazu.write(potPazuPozisyon);
  servoDirsek.write(potDirsekPozisyon);
  servoBilek.write(potBilekPozisyon);
  servoParmak.write(potParmakPozisyon);
}


void noktaKaydet(int kayitSayisi)
{
  potDegerOku();
  omuzNoktalari[kayitSayisi]=potOmuzPozisyon;
  pazuNoktalari[kayitSayisi]=potPazuPozisyon;
  dirsekNoktalari[kayitSayisi]=potDirsekPozisyon;
  bilekNoktalari[kayitSayisi]=potBilekPozisyon;
  parmakNoktalari[kayitSayisi]=potParmakPozisyon;
}

void noktaDegerlerindenOynat(int donguAdimi)
{
  while(durmaKontrol)
  {
    for(int i=0 ; i<donguAdimi ; i++)
    {
      servoOmuz.write(omuzNoktalari[i]);
      delay(300);
      servoPazu.write(pazuNoktalari[i]);
      delay(300);
      servoDirsek.write(dirsekNoktalari[i]);
      delay(300);
      servoBilek.write(bilekNoktalari[i]);
      delay(300);
      servoParmak.write(parmakNoktalari[i]);
      delay(1100);
      if(i==donguAdimi)
      {
        oynat=true;
      }
    }
  }
  
}

