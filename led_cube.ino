#define number_of_74hc595s 8 
#define numOfRegisterPins number_of_74hc595s * 8
boolean registers[numOfRegisterPins];
int data = 9;   //pin 14 on the 75HC595
int verrou = 10;  //pin 12 on the 75HC595
int horloge = 11; //pin 11 on the 75HC595

int i,j,e,f,a,prec_a;

char animation[20];

char etage[8]={6,13,A0,A1,A2,A3,A4,A5};

int timer=100;

boolean cube[8][64];



byte vumetro[8][8];     // vu-meter
float vumetres[16];
int valor_analogic = 7; 
int strobe = 4; 
int reset = 5; 
int valeur_freq[7]; 
int hauteur=120;   // de 0 à 120


void setup(){ //******************************************************************************
              //******************************************************************************
  Serial.begin(9600);
              
  pinMode(data, OUTPUT);
  pinMode(verrou, OUTPUT);
  pinMode(horloge, OUTPUT);

  for(i=0;i<8;i++){
    pinMode(etage[i], OUTPUT);
    digitalWrite(etage[i], 0);
  }
  randomSeed(analogRead(7));    //  mode aléatoire


  pinMode(valor_analogic, INPUT);   // vu-meter
  pinMode(strobe, OUTPUT);
  pinMode(reset, OUTPUT);
  analogReference(DEFAULT);
  digitalWrite(reset, LOW);
  digitalWrite(strobe, HIGH);
  
}  //****************************************************************************************             
void clearRegisters(){
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
     registers[i] = LOW;
  } 
} 
void writeRegisters(){ 
  digitalWrite(verrou, LOW);
  for(int i = numOfRegisterPins - 1; i >=  0; i--){
    digitalWrite(horloge, LOW);
    int val = registers[i];
    digitalWrite(data, val);
    digitalWrite(horloge, HIGH);
  }
  digitalWrite(verrou, HIGH);
}
void setRegisterPin(int index, boolean value){
  registers[index] = value;
}
 
void loop(){//******************************************************************************
            //******************************************************************************
/*
cube[0][30]=1;
cube[1][8]=0;
cube[2][8]=1;
cube[3][8]=0;
cube[4][8]=1;
cube[5][8]=0;
cube[6][8]=1;
cube[7][8]=0;*/
/*for( i=0;i<64;i++)
  cube[2][i]=1;
*/


//affichage();

//total();

for(int i =0;i<20;i++)
  ani_1();
for(int i =0;i<3;i++)
  ani_2();
for(int i =0;i<20;i++)
  ani_4();

// vumetre();

//test();

}//*****************************************************************************************
void test()//*******************************************************************************
{
  for( i=0;i<64;i++)
      setRegisterPin(i, HIGH);
  digitalWrite(etage[7], 1);
  writeRegisters();


/*
  for(int i=0;i<8;i++){
            digitalWrite(etage[i], 1);
            writeRegisters();
            delay(3000);
            digitalWrite(etage[i], 0);
            writeRegisters();
        }*/
}

void clear_cube()//=========================================================================================
{
        for(i=0;i<8;i++){ 
          for( j=0;j<64;j++)
             cube[i][j]=0;
        }
}

void affichage()//=========================================================================================
{
  for(int i=0;i<8;i++){
     for(int j=0;j<64;j++)
          registers[j] = cube[i][j];
     digitalWrite(etage[i], 1);
     writeRegisters();
     digitalWrite(etage[i], 0);
   }
   delay(1);
}

void total()//=========================================================================================
{
  for(int i=0;i<8;i++){
     for(int j=0;j<64;j++)
          setRegisterPin(j, 1);
    digitalWrite(etage[i], 1);
    writeRegisters();
    digitalWrite(etage[i], 0);
   }
}

void tempo(int t)//=========================================================================================
{
  for(int i=0;i<t/10;i++)
        affichage();
}

void ani_1()//=========================================================================================
{


  timer=100;

while( a==prec_a ){ 
  a = random(0,15);
} 
prec_a=a;

if(a==0 || a==1 ){
  for(i=0;i<8;i++){                     // bas haut
        if(a==1 && i<7){
          for( j=0;j<64;j++)
             cube[i+1][j]=0;
        }
        for( j=0;j<64;j++)
            cube[i][j]=1;
        tempo(timer);
        if(a==0){
          for( j=0;j<64;j++)
             cube[i][j]=0;
        }
    }
} 
if(a==2 || a==3){
  for(i=7;i>=0;i--){                     // haut bas
      if(a==3 && i>0){
          for( j=0;j<64;j++)
             cube[i-1][j]=0;
      }
      for( j=0;j<64;j++)
          cube[i][j]=1;
      tempo(timer);
      if( a==2){
        for( j=0;j<64;j++)
           cube[i][j]=0;
      }
  }
}
//*******************************************************************************
if(a==4 || a==5){
  for(e=0;e<8;e++){                        // av ar
      for(i=0;i<8;i++){ 
            if(a==5 && e<7){
                for(j=e*8;j<(e+1)*8;j++)
                   cube[i][j+8]=0;
            }                    
            for(j=e*8;j<(e+1)*8;j++)
                cube[i][j]=1;
            affichage();
            if(a==4){
              for(j=e*8;j<(e+1)*8;j++)
                 cube[i][j]=0;
            }
        }
  }
} 
if(a==6 || a==7 ){
  for(e=7;e>=0;e--){                        // ar av
      for(i=0;i<8;i++){ 
            if(a==7 && e>0){
                for(j=e*8;j<(e+1)*8;j++)
                   cube[i][j-8]=0;
            }                   
            for(j=e*8;j<(e+1)*8;j++)
                cube[i][j]=1;
            affichage();
            if(a==6){
              for(j=e*8;j<(e+1)*8;j++)
                 cube[i][j]=0;
            }
        }
  }
}
//*******************************************************************************
if(a==8 || a==9 ){
  for(e=0;e<8;e++){                        // dte gch
      for(i=0;i<8;i++){ 
            if(a==9 && e<7){
                for(j=0;j<8;j++)
                   cube[i][j*8+e+1]=0;
            }                               
            for(j=0;j<8;j++)
                cube[i][j*8+e]=1;
            affichage();
            if(a==8){
              for(j=0;j<8;j++)
                 cube[i][j*8+e]=0;
            }
        }
  }
}
if(a==10 || a==11){
  for(e=7;e>=0;e--){                        // gch dte
      for(i=0;i<8;i++){ 
            if(a==11 && e>0){
                for(j=0;j<8;j++)
                   cube[i][j*8+e-1]=0;
            }                       
            for(j=0;j<8;j++)
                cube[i][j*8+e]=1;
            affichage();
            if(a==10){
              for(j=0;j<8;j++)
                 cube[i][j*8+e]=0;
            }
        }
  }
}
}

void ani_2()//=========================================================================================
{
  for(e=0;e<6;e++){
    clear_cube(); 
    for(i=0+e/2;i<8-e/2;i++)  {
      for(j=0+e/2;j<8-e/2;j++){
        cube[i][(e*8)+j]=1;
        cube[i][j*8+e]=1;
        cube[i][j*8+7-e]=1;
        cube[i][j+56-(e*8)]=1;
      }
    }
    tempo(timer);
  }

  for(e=5;e>0;e--){
    clear_cube(); 
    for(i=0+e/2;i<8-e/2;i++)  {
      for(j=0+e/2;j<8-e/2;j++){
        cube[i][(e*8)+j]=1;
        cube[i][j*8+e]=1;
        cube[i][j*8+7-e]=1;
        cube[i][j+56-(e*8)]=1;
      }
    }
    tempo(timer);
  }
  
}

void ani_3()//=========================================================================================
{
  clear_cube();
  for(e=0;e<20;e++){
    cube[random(0,8)][random(0,64)]=1;
    }
    tempo(timer);
}
void ani_4()//=========================================================================================
{
  clear_cube();
  for(e=0;e<4;e++){
    cube[7][random(0,64)]=1;
    }
    tempo(timer);
}


void vumetre() {//=========================================================================================
  
  digitalWrite(reset, HIGH);
  digitalWrite(reset, LOW);
  for (int i = 0; i < 7; i++)
  {
    digitalWrite(strobe, LOW);
    delayMicroseconds(5); 
    valeur_freq[i] = analogRead(valor_analogic);
    digitalWrite(strobe, HIGH);
  }
  
  for( i=0;i<8;i++){ 
    for( j=0;j<64;j++)
      cube[i][j]=0;
  }
          
  for (int k=0; k<8; k++)
    {
    switch (k) 
    {
      case 0:
        vumetres[k]= valeur_freq[0]/hauteur;
      break;
      case 1:
        vumetres[k]= valeur_freq[1]/hauteur;
      break;
  
      case 2:
        vumetres[k]= valeur_freq[2]/hauteur;
      break;
      case 3:
        vumetres[k]= valeur_freq[3]/hauteur;
      break;
      case 4:
        vumetres[k]= valeur_freq[4]/hauteur;
      break;
      case 5:
        vumetres[k]= valeur_freq[5]/hauteur;
      break;
      case 6:
        vumetres[k]= (valeur_freq[5]+valeur_freq[6])/2/hauteur;
      break;
      case 7:
        vumetres[k]= valeur_freq[6]/hauteur;
      break;
    }
    
      for( i=0;i<vumetres[k];i++){  
        for( j=k*8;j<(k+1)*8;j++)
          cube[i][j]=1;
      }
  }
  affichage();
}
