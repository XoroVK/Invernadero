#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Credenciales de la red WiFi
const char* ssid = "Galaxy S24 Ultra";              // Cambia esto por tu SSID
const char* password = "1234567890";           // Cambia esto por tu contraseña

// Configuración del servidor MQTT
const char* mqtt_server = "broker.emqx.io";      // Dirección del broker MQTT
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (256) // Aumentar el tamaño del buffer para más datos
char msg[MSG_BUFFER_SIZE];

// Definir el nuevo tópico
const char* nuevo_topico = "invernadero/01"; // Cambia el nombre del tópico aquí

void setup_wifi() {
    delay(10);
    Serial.println();
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi conectado");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje Enviado [");
    Serial.print(topic);
    Serial.print("] ");
    for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Intentando conexión MQTT...");
        String clientId = "ESP8266Client-";
        clientId += String(random(0xffff), HEX);
        if (client.connect(clientId.c_str())) {
            Serial.println("conectado");
            // Publicar un mensaje de bienvenida
            client.publish(nuevo_topico, "Invernadero Conectado");
            client.subscribe("inTopic");
        } else {
            Serial.print("Falla, rc=");
            Serial.print(client.state());
            Serial.println(" intenta de nuevo en 5 segundos");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    unsigned long now = millis();
    if (now - lastMsg > 2500) {
        lastMsg = now;

        // Leer datos del Arduino Nano a través de Serial
        String sensorData = "";
        if (Serial.available()) {
            sensorData = Serial.readStringUntil('\n'); // Lee hasta el salto de línea
        }

        // Publicar los datos si están disponibles
        if (sensorData.length() >= 0) {
            Serial.print("Datos recibidos: ");
            Serial.println(sensorData);
             snprintf(msg, MSG_BUFFER_SIZE, "%s", sensorData.c_str());
            Serial.print("Mensaje publicado: ");
            Serial.println(msg);
            client.publish(nuevo_topico, msg); // Publicar en el nuevo tópico
        }
    }
}
