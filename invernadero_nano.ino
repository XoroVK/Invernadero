#include <DHT.h>

#define DHTPIN2 7        // Pin del sensor DHT11 interno
#define DHTPIN1 6        // Pin del sensor DHT22 externo
#define DHTTYPE DHT22    // Tipo de sensor DHT interno
#define RELAY_PIN 4      // Pin del relé

DHT interno(DHTPIN2, DHTTYPE);
DHT externo(DHTPIN1, DHTTYPE);

#define sensor1 A0 
#define sensor2 A1 
#define sensor3 A2 
#define sensor4 A3 
#define sensor5 A4 

int estado_rele = 0;

void setup() {
    Serial.begin(115200);  // Inicializa la comunicación serial
    interno.begin();
    externo.begin();
    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW);
}

void loop() {
    // Mapeo y lectura de los sensores
    int valor1 = map(analogRead(sensor1), 0, 1023, 100, 0);
    int valor2 = map(analogRead(sensor2), 0, 1023, 100, 0);
    int valor3 = map(analogRead(sensor3), 0, 1023, 100, 0);
    int valor4 = map(analogRead(sensor4), 0, 1023, 100, 0);
    int valor5 = map(analogRead(sensor5), 0, 1023, 100, 0); 

    // Activar o desactivar el relé basado en las lecturas
    if (valor1 < 30 || valor2 < 30 || valor3 < 30 || valor4 < 30 || valor5 < 30) {
        digitalWrite(RELAY_PIN, HIGH);
        estado_rele = 1;
    } else {
        digitalWrite(RELAY_PIN, LOW);
        estado_rele = 2;
    }

    // Lecturas del sensor DHT interno
    float hi = interno.readHumidity(); 
    float ti = interno.readTemperature(); 
    // Lecturas del sensor DHT externo
    float he = externo.readHumidity(); 
    float te = externo.readTemperature(); 

    // Comprobación y manejo de errores en el sensor interno
    if (isnan(hi) || isnan(ti)) {
        Serial.println("Error al leer del sensor DHT interno");
        hi = 0.0;  // Valor por defecto en caso de error
        ti = 0.0;
    }

    // Comprobación y manejo de errores en el sensor externo
    if (isnan(he) || isnan(te)) {
        Serial.println("Error al leer del sensor DHT externo");
        he = 0.0;  // Valor por defecto en caso de error
        te = 0.0;
    }

    // Enviar los datos con delimitadores de inicio y fin

    Serial.print(valor1);
    Serial.print(", ");
    Serial.print(valor2);
    Serial.print(", ");
    Serial.print(valor3);
    Serial.print(", ");
    Serial.print(valor4);
    Serial.print(", ");
    Serial.print(valor5);
    Serial.print(", ");
    Serial.print(hi);
    Serial.print(", ");
    Serial.print(ti);
    Serial.print(", ");
    Serial.print(he);
    Serial.print(", ");
    Serial.print(te);
    Serial.print(", ");
    Serial.print(estado_rele);
    Serial.println(" ");



    delay(2500);  // Aumentar el tiempo de delay para garantizar procesamiento
}
