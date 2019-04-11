String json_domoticz(char* host, int httpPort , String idx){
WiFiClient client;

if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return "connection failed";
  }
  
   String url = "/json.htm?type=devices&rid="+idx;
  Serial.print("requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('OK');
  Serial.println("=======DATA ===");
  return line;
}

/////////////////// get "data" in json

String get_data(String data) {
  
  int debut = data.indexOf('[');
  debut = data.indexOf('D',debut);
  debut = data.indexOf(':',debut);
  debut = debut+3;
  int fin = data.indexOf('"',debut);
  data = data.substring(debut,fin);
  Serial.println(data); 
  return data;
}

//// get "usage" on json 
String get_usage(String data) {
  
  int debut = data.indexOf('[');
  debut = data.indexOf('U',debut);
  debut = data.indexOf('U',debut+10);
  debut = data.indexOf('U',debut+5);
  debut = data.indexOf(':',debut);
  ///Serial.println(data.substring(debut)); 
  debut = debut+3;
  int fin = data.indexOf('"',debut);
  data = data.substring(debut,fin);
  Serial.println(data); 
  return data;
}

//////////////////////
