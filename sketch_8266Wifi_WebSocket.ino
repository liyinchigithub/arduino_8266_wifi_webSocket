#include <ESP8266WiFi.h>
#include <WebSocketsClient.h>

// WiFi parameters to be configured
const char* ssid = "";//   wifi 账号
const char* password = "";// wifi 密码

WebSocketsClient webSocket;

void setup() {
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
   Serial.println("WiFi IPAddress:");
  Serial.println(WiFi.localIP().toString());

  // Setup WebSocket connection
  webSocket.begin("ws://192.168.31.81", 8088, "/my-websocket-endpoint");

  // Event handler
  webSocket.onEvent(webSocketEvent);

  // Start connection
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop();
}

char receivedText[256];  // 用于保存接收到的文本

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.println("[WSc] Disconnected!");
      break;
    case WStype_CONNECTED:
      Serial.println("[WSc] Connected to url: ");
      webSocket.sendTXT("Hello, WebSocket server!");// 发送内容
      break;
    case WStype_TEXT:
      Serial.println("[WSc] get text: ");
      strncpy(receivedText, reinterpret_cast<char*>(payload), sizeof(receivedText) - 1);
      receivedText[sizeof(receivedText) - 1] = '\0';  // 确保字符串以null结尾
      Serial.println(receivedText);// 接收内容
      break;
  }
}