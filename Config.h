#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

//PINES DE LA PIERNA IZQUIERDA
const int PIN_L_HIP = D5;
const int PIN_L_KNEE = D6;
const int PIN_L_ANKLE = D7;

//LIMITES DE SEGURIDAD

const int L_HIP_MIN = 0;
const int L_HIP_MAX = 100;

const int L_KNEE_MIN = 0;
const int L_KNEE_MAX = 100;

const int L_ANKLE_MIN = 5;
const int L_ANKLE_MAX = 165;

//POSICIONES INICIALES
const int L_HIP_START = 40;
const int L_KNEE_START = 10;
const int L_ANKLE_START = 100;
#endif