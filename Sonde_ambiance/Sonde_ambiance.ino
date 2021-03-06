/*
 * Code permettant la Gestion d'une sonde d'ambiance avec une carte NodeMcuV3.0 équipée d'un module Wifi ESP8266
 * Réalisé dans le cadre du projet de Deuxième année FIP 2019
 * 
 * V1.0 : 31/01/2019
 *        Debug présent mais commentés
 * 
 */
 
#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTTYPE DHT11
#define DHTPIN 2

//Définition des variables réseau permettant la connexion au wifi et au serveur
const char* ssid = "AndroidAP";
const char* password = "arduino4ever";

const char* server = "192.168.43.47";
const char* streamId = "collect_data_ambiance.php";

//Définition du capteur et de la variable de température
DHT dht(DHTPIN,DHTTYPE,15);
int temp=0;
int hum=0;

//****Fonction d'envoi de la requête http au serveur****

void SendRequest(String temp ,String hum) {
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
  url += "&hum=";
  url += hum;
               
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" + 
               "Connection: close\r\n\r\n");

                 Serial.println(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" + 
               "Connection: close\r\n\r\n");
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
 hum = dht.readHumidity();
 
 //Envoi de la requête au serveur
 SendRequest(String(temp),String(hum));
 Serial.println("Mesures envoyées");

 //Reglage fréquence d'envoi de la requete (en ms)
 delay(120000);
}
