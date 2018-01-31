/*
 * Code permettant la surveillance d'une installation de chauffage avec une carte NodeMcuV3.0 équipée d'un module Wifi ESP8266
 * Réalisé dans le cadre du projet de Deuxième année FIP 2019
 * 
 * V1.0 : 31/01/2019
 *        Les informations de debug sont présentes mais commentées
 * 
 */
 
#include <ESP8266WiFi.h>

//Définition des variables réseau permettant la connexion au wifi et au serveur
const char* ssid = "AndroidAP";
const char* password = "arduino4ever";

const char* server = "192.168.43.47";
const char* streamId = "collect_data.php";

//Définition des variables de température
int temp_dep_ch=0;
int temp_ret_ch=0;
int temp_dep_pch=0;
int temp_ret_pch=0;

//****Fonction d'envoi de la requête http au serveur****

void SendRequest(String temp) {
  const int httpPort = 80;
  
  //Serial.print("Connecting to ");
  //Serial.println(server);

  WiFiClient client;
  
  if (!client.connect(server, httpPort)) 
  {
  Serial.println("connection failed");
  return;
  }

  String url = "/";
  url += streamId;
  url += "?temp=";
  url += temp;
               
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(120000);
}
//*****************************************************

void setup() {

  //Permet d'éviter le reboot intempestif de la carte
  pinMode(0,OUTPUT);
  digitalWrite(0,LOW);

  //Liaison serie permettant le debug
  Serial.begin(9600);
  delay(10);
  
  //Attente de la connexion
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  // On se connecte a reseau WiFi avec le SSID et le mot de passe precedemment configure
  WiFi.begin(ssid, password);
  
  // On sort de la boucle uniquement lorsque la connexion a ete etablie.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  
  //On indique sur le port serie l'adresse ip de l'ESP 
  Serial.println(WiFi.localIP());

  //Démarrage du capteur dht
  dht.begin();
}

//****************************************************************
void loop() {

 //Letcure de la température du capteur
 temp = dht.readTemperature();

 //Envoi de la requête au serveur
 SendRequest(String(temp));
 Serial.println("Mesure envoyée");
}
