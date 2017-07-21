/**
 * Projetos Arduino
 * 
 * @author diego patriota
 * @link https://github.com/diegopatriota
 * 19/05/2016 
 */

//inclusão de biblioteca
#include <SPI.h>
#include <Ethernet.h>
#include <sha1.h>
#include "mysql.h"

//endereço MAC 
byte mac_addr[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress server_addr(172, 0, 0, 1); //endereço do servidor do BD
char user[] = "root"; //usuário do BD
char password[] = ""; //senha do BD
Connector conexao;
String buf;
char query[128];
char caracter;
void setup() {
	Serial.begin(9600);
	Ethernet.begin(mac_addr);
	delay(1000);
	Serial.println("Conectando ao servidor...");
	if(conexao.mysql_connect(server_addr, 3306, user, password))
		delay(500);
	else
		Serial.println("A conexão falhou.");
}
void loop(){
	if(Serial.available() > 0){ 
		caracter= Serial.read(); 
		grava_dados();
    }

	delay(500);
}
void grava_dados() { 
	buf = "Insert into banco.tabela (DadoRecebido) Values ('"+ String(caracter) +"')";
	buf.toCharArray(query, 128);
	conexao.cmd_query(query);
	Serial.println("Dado gravado com sucesso!");
}
