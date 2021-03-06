
#include <WiFi.h>
WiFiClient client;

const char* ssid     = "UNE_HFC_4390";
const char* password = "Jad3s3R02o2o";

//HOST o URL de su aplicación web sin http
const char* host ="gitelectiva.herokuapp.com";
const int httpPort = 80; // puerto web por defecto: 80

void setup() {
 Serial.begin(115200);
  delay(10);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a:\t");
  Serial.println(ssid); 
 
  // Esperar a que nos conectemos
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(200);
   Serial.print('.');
  }
 
  // Mostrar mensaje de exito y dirección IP asignada
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID()); 
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
  

  if(!client.connect(host,httpPort)){
    Serial.println("Conexion fallida");  
  }
  else{
    Serial.print("Conectado a la aplicación :");
    Serial.println(host);
    String tabla = "Motor_view";
    String motor = "motor1";
    float corriente = random(100,3000)/10;
    float voltaje = random(1000,2500)/10;
    sendPost(corriente, voltaje, tabla, motor);
    
  }
}

// the loop function runs over and over again forever
void loop() {
if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    for(;;)
      ;
  }

}

void sendPost(float voltaje, float corriente, String tabla, String motor){
  //Creamos la direccion para luego usarla
  String dato = "voltaje=" + String(voltaje)+ "&corriente=" + String(corriente) + "&tabla=" + String(tabla) + "&motor=" + String(motor);

  // Solicitud de tipo post para enviar al servidor 
  client.println("POST /guardardato HTTP/1.1");
  client.println("Host: gitelectiva.herokuapp.com");
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(dato.length());
  client.println();
  client.println(dato);
  Serial.println("Respuesta: ");
}
