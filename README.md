# Invernadero
Componentes Principales
Arduino Nano: Lee los valores de los sensores y controla el relé.
NodeMCU (ESP8266): Se conecta a WiFi y envía los datos recibidos del Arduino al servidor MQTT.
Relé y Bomba de 12V: El relé se activa cuando los valores de humedad están por debajo de un umbral, encendiendo la bomba de 12V para irrigar.
Sensores de Humedad del Suelo: Se utilizan cinco sensores analógicos para medir la humedad del suelo en diferentes ubicaciones del invernadero.
Sensores DHT: Dos sensores (DHT11 y DHT22) miden la temperatura y la humedad del aire, uno interno y otro externo.
Node-RED: Herramienta de programación visual para la automatización del flujo de datos.
Funciones del Código
Arduino Nano
Lectura de Sensores:

Sensores de Humedad del Suelo: Lee los valores de cinco sensores analógicos conectados a los pines A0 a A4, que indican el nivel de humedad del suelo. Los valores se mapean a un rango del 0 al 100.
Sensores DHT: Lee la temperatura y la humedad del aire del sensor DHT interno y externo.
Control de Relé:

Si alguno de los sensores de humedad del suelo registra valores por debajo del 30%, el Arduino activa el relé para encender la bomba de riego.
Formato de Datos:

Los datos se empaquetan en una lista en el formato [sensor1, sensor2, sensor3, sensor4, sensor5, humedadInterna, tempInterna, humedadExterna, tempExterna, estadoRele] y se envían al ESP8266 vía comunicación serial.
NodeMCU (ESP8266)
Conexión a WiFi y MQTT:

Se conecta a la red WiFi y al servidor MQTT para transmitir los datos.
Recepción y Publicación de Datos:

Lee los datos del Arduino vía serial y los envía al servidor MQTT bajo el tópico invernadero/01.
Gestión de Paquetes de Datos:

El ESP8266 verifica que los datos recibidos estén completos antes de enviarlos. Si los datos están incompletos, espera el siguiente paquete para evitar errores en la publicación.
Node-RED
Instalación:

Instalar Node-RED en un servidor local o en la nube siguiendo las instrucciones de instalación.
Configuración:

Agregar un nodo de entrada MQTT que se suscriba al tópico invernadero/01 para recibir los datos del ESP8266.
Procesar los datos recibidos utilizando nodos como function, debug, y chart para visualizarlos.
Visualización:

Crear un tablero (dashboard) en Node-RED para visualizar en tiempo real las lecturas de los sensores y el estado del relé.
Configurar notificaciones o alertas en caso de que los niveles de humedad del suelo estén por debajo del umbral definido.
Requisitos de Instalación
Instalar librerías:

PubSubClient para MQTT.
DHT para los sensores de temperatura y humedad.
Node-RED.
Configuración de Red:

Modificar ssid y password en el código del ESP8266 para adaptarse a la red WiFi.
Configurar el servidor MQTT en mqtt_server.
Uso
Conectar el Arduino Nano y el ESP8266 según el esquema de conexión.
Compilar y cargar el código en ambos dispositivos.
Iniciar Node-RED y configurar los flujos para recibir y procesar los datos.
Monitorear los datos enviados a través del servidor MQTT y visualizarlos en Node-RED para obtener información en tiempo real del estado del invernadero.
