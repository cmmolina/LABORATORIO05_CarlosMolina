
/*
 * Universidad del Valle de Guatemala
 * Electrónica Digital 2
 * Carlos Mauricio Molina López (#21253)
 * LABORATORIO 05 - Juego de Carreras
 * 22/03/23
 */


// Definición de LEDs RGB
#define LED_R RED_LED
#define LED_G GREEN_LED
#define LED_B BLUE_LED

int buttonState = 0;          // Status del botón "Inicio de Carrera"
int buttonState1 = 0;         // Status del botón "Jugador1"
int buttonState2 = 0;         // Status del botón "Jugador2"

int carrera = 0;              // Variable que indica si la carrera ha iniciado
int cont1 = 0;                // "Jugador1" comienza en 0
int cont2 = 0;                // "Jugador2" comienza en 0


void setup() {

  //LED RGB como Output
  pinMode(LED_R, OUTPUT);   
  pinMode(LED_B, OUTPUT);   
  pinMode(LED_G, OUTPUT);   

  // LEDs de los ganadores
  pinMode(PE_5, OUTPUT);
  pinMode(PB_4, OUTPUT);

  // LEDs Jugador 1
  pinMode(PD_0, OUTPUT);
  pinMode(PD_1, OUTPUT);
  pinMode(PD_2, OUTPUT);
  pinMode(PD_3, OUTPUT);

  // LEDs Jugador 2
  pinMode(PE_1, OUTPUT);
  pinMode(PE_2, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PA_5, OUTPUT);
  
  // Inicio de Carrera
  pinMode(PB_5, INPUT);    
  
  //Jugador 1
  pinMode(PB_0, INPUT);

  //Jugador 2
  pinMode(PB_1, INPUT);
  
}

void loop() {
  
  if (carrera == 0){
    buttonState = digitalRead(PB_5);
    
    if (buttonState == 1){
    while (digitalRead(PB_5) == HIGH){       // Antirrebote "Inicio de Carrera"  
      ;
    }

    // Reiniciamos todo, preparando así un juego nuevo
    restartgame();

    // Empezamos la secuencia del semaforo en el LED RGB de la TIVA C
    secuencia_semaforo();

    // Indicamos a la variable que el juego ha empezado
    carrera = 1;
    }
    
    else if (buttonState == 0){
      ;
    }
  }

  else if (carrera == 1){

    // Leemos constantemente si los jugadores presionan uno de los botones
    buttonState1 = digitalRead(PB_0);
    buttonState2 = digitalRead(PB_1);

    // Si el "Jugador1" presiona, se suma su contador
    if (buttonState1 == 1){
      while (digitalRead(PB_0) == HIGH){     //  Antirrebote "Jugador 1"
        ;
      }
      //digitalWrite(PE_5, HIGH);
      cont1++;

      if (cont1 == 1){
        digitalWrite(PD_0, HIGH);
      }

      else if (cont1 == 2){
        digitalWrite(PD_1, HIGH);;
      }

      else if (cont1 == 3) {
        digitalWrite(PD_2, HIGH);;
      }

      else if (cont1 == 4) {
        digitalWrite(PD_3, HIGH);;
      }
      
    }

    // Si el "Jugador2" presiona, se suma su contador
    if (buttonState2 == 1){
      while (digitalRead(PB_1) == HIGH){     // Antirrebote "Jugador 2"
        ;
      }
      cont2++;

      if (cont2 == 1){
        digitalWrite(PE_1, HIGH);
      }

      else if (cont2 == 2){
        digitalWrite(PE_2, HIGH);;
      }

      else if (cont2 == 3) {
        digitalWrite(PE_3, HIGH);;
      }

      else if (cont2 == 4) {
        digitalWrite(PA_5, HIGH);;
      }
      
    }

    // Vamos a una rutina para asegurarnos si alguien ha ganado
    comparacion();
  }  
}

void comparacion(){

  // ¿Jugador 1 ganó?
  if(cont1 == 4){
     digitalWrite(PB_4, HIGH);
     carrera = 0;
     cont1 = 0;
     cont2 = 0;
     digitalWrite(LED_B, HIGH);
  }

  // ¿Jugador 2 ganó?
  else if (cont2 == 4){
    digitalWrite(PE_5, HIGH);
    carrera = 0;
    cont1 = 0;
    cont2 = 0;
    digitalWrite(LED_R, HIGH);
  }

  // ¿Nadie ha ganado todavía?
  else{
    ;
  }
}

void secuencia_semaforo(){
  // Empezamos la secuencia del semaforo 

  // Verde 
  digitalWrite(LED_G, HIGH);   // Encendemos el LED Verde
  delay(2000);                 // Esperamos 2 segundos
  digitalWrite(LED_G, LOW);    // Apagamos el LED Verde


  // Amarillo
  digitalWrite(LED_R, HIGH);   // Encendemos el LED Rojo
  digitalWrite(LED_G, HIGH);   // Encendemos el LED Verde
  delay(2000);                 // Esperamos 2 segundos
  digitalWrite(LED_R, LOW);    // Apagamos el LED Rojo
  digitalWrite(LED_G, LOW);    // Apagamos el LED Verde

  // Rojo
  digitalWrite(LED_R, HIGH);   // Encendemos el LED Rojo
  delay(2000);                 // Esperamos 2 segundos
  digitalWrite(LED_R, LOW);    // Apagamos el LED Rojo
}

void restartgame(){

  // Apagamos todos los LEDs de Hardware utilizados
  
  digitalWrite(LED_B, LOW);
  digitalWrite(LED_R, LOW);

  digitalWrite(PE_5, LOW);
  digitalWrite(PB_4, LOW);

  digitalWrite(PD_0, LOW);
  digitalWrite(PD_1, LOW);
  digitalWrite(PD_2, LOW);
  digitalWrite(PD_3, LOW);

  digitalWrite(PE_1, LOW);
  digitalWrite(PE_2, LOW);
  digitalWrite(PE_3, LOW);
  digitalWrite(PA_5, LOW);
}
