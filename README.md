## 1. Visión General de la Arquitectura

El diseño sigue un enfoque "de abajo hacia arriba" (Bottom-Up). En lugar de tener un archivo principal gigante que controle los pines físicos y haga las matemáticas al mismo tiempo, delegamos las responsabilidades en capas.

La regla principal del proyecto es la abstracción: el archivo principal (`.ino`) no necesita saber en qué pin está conectado un servo ni cuáles son sus límites físicos; solo necesita decir "Mueve la pierna izquierda".

---

## 2. Dependencias de Clases (Quién lee a quién)

Para entender cómo se conectan los archivos, debes mirarlos en este orden jerárquico:

* **Nivel 0: `Config.h` (El Archivo Maestro)**
    No depende de nadie. Es un archivo de texto plano que contiene constantes globales (pines, límites, posiciones iniciales). Todos los demás archivos consultan este para conocer las "reglas físicas" del robot.
* **Nivel 1: `Joint.h` y `Joint.cpp` (La Articulación)**
    Depende de la librería nativa `<Servo.h>`. Representa un (1) solo servomotor físico. Su única responsabilidad es mover ese motor y, lo más importante, bloquear cualquier movimiento que exceda los límites de seguridad para no partir las piezas 3D.
* **Nivel 2: `Leg.h` y `Leg.cpp` (La Pierna)**
    Depende de `Joint` y de `Config.h`. Es un "gestor" que agrupa internamente tres objetos `Joint` (Cadera, Rodilla y Tobillo). Al instanciar una pierna, automáticamente nacen sus tres articulaciones.
* **Nivel 3: `BipedoRobot.ino` (El Cerebro)**
    Depende de `Leg`. Es el punto de entrada del programa. Su trabajo es armar la coreografía. Llama a métodos de alto nivel y no maneja variables de hardware directamente.

---

## 3. Flujo de Ejecución (El Ciclo de Vida)

Cuando enciendes el WEMOS D1 R2, el código se ejecuta con esta secuencia exacta:

1.  **Creación:** El archivo `.ino` crea un objeto global llamado `leftLeg`. Al nacer, este objeto lee el archivo `Config.h` y pre-configura sus tres articulaciones con los pines y límites correctos.
2.  **Inicialización (`setup`):** El `.ino` llama a `leftLeg.begin()`. Este comando viaja hacia abajo: la pierna le dice a la cadera, rodilla y tobillo que ejecuten su propio `.begin()`. En este instante, los servos se encienden (usando `attach`) y viajan automáticamente a su posición inicial segura (`START`).
3.  **Bucle Principal (`loop`):** El programa entra en un ciclo infinito. El cerebro envía comandos de movimiento. Puede hacerlo de dos formas:
    * Por porcentaje (`setPercentage`): Útil para movimientos abstractos donde `0` es el mínimo físico y `100` es el máximo físico.
    * Por ángulo directo (`setAngle`): Útil para posiciones matemáticas exactas (ej. 90 grados).
4.  **Filtro de Seguridad:** Cada vez que el `.ino` pide un movimiento, el archivo `Joint.cpp` intercepta el comando. Si el cerebro pide ir al grado 190, pero el límite es 100, `Joint.cpp` anula el 190, impone el 100 y ejecuta el movimiento, salvando al robot de autodestruirse.

---

## 4. Guía de Modificación (Dónde tocar sin romper nada)

Si trabajas en equipo, es vital que todos sepan qué archivos modificar según lo que quieran lograr. 

### Cambiar conexiones físicas, calibración o proteger piezas
**Solo debes modificar `Config.h`.**
Si conectan el tobillo a otro pin, si descubren que el servo choca contra el plástico a los 160 grados, o si la posición inicial de reposo quedó chueca, cambian los valores aquí. Al recompilar, todo el programa absorberá las nuevas reglas automáticamente sin tocar la lógica.

### Crear nuevas rutinas de prueba o coreografías
**Solo debes modificar `BipedoRobot.ino`.**
Aquí es donde programas los tiempos, pausas (`delay`) y secuencias de movimiento. Puedes jugar libremente con las funciones `setPercentage()`, `setAngle()` y `resetToStart()`. Gracias a la capa de seguridad de `Joint`, es imposible que rompas el robot desde este archivo, sin importar qué números escribas.

### Cambiar el comportamiento de fondo de los motores
**Solo debes modificar `Joint.cpp`.**
Si en el futuro deciden que los servos se mueven muy agresivamente y quieren agregar matemáticas para suavizar las curvas de aceleración (interpolación), ese código matemático se escribe exclusivamente dentro del método `setAngle()` o `setPercentage()` de esta clase.

### Agregar la pierna derecha
**Debes modificar `Config.h` y el `.ino`.**
1. En `Config.h`, clonas el bloque de variables de la pierna izquierda pero con nombres nuevos (ej. `PIN_R_HIP`, `R_HIP_MAX`, etc.).
2. En el `.ino`, creas una nueva instancia debajo de la anterior: `Leg rightLeg;`. Nota: Tendrás que adaptar temporalmente `Leg.cpp` para que acepte qué pierna es (izquierda o derecha) y lea las constantes correctas, o pasarle los pines por parámetro al crearla.