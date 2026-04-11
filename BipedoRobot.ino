#include "Config.h"
#include "Leg.h"

// Instanciamos la pierna
Leg leftLeg;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando WEMOS D1 R2...");

  leftLeg.begin();
  delay(2000);
}

void loop() {
  Serial.println("Prueba de flexión de cadera (porcentaje)...");
  leftLeg.hip.setPercentage(20);
  delay(1000);
  leftLeg.hip.setPercentage(80);
  delay(1000);

  Serial.println("Volviendo a la normalidad...");
  leftLeg.resetToStart();
  delay(2000);

  Serial.println("Prueba de estrés de rodilla (ángulos exactos)...");
  leftLeg.knee.setAngle(90);
  delay(1000);
  leftLeg.knee.setAngle(L_KNEE_START); // Vuelve al inicio seguro
  
  delay(3000); // Pausa de 3 segundos y repite el ciclo
}