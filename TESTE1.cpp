/*            Resete de Spool local SAP      */
/*		Gupo Multi 23/01/2023             */
/*	Frederico Almeida - Analista de Suporte Jr */


#include<iostream>
#include <fstream>
#include <windows.h> 

using namespace std;

int DisableFirewall(){
// Executa o comando para verificar o estado do firewall
    system("netsh advfirewall show allprofiles state > firewall_status.txt");

    // Abre o arquivo de saída
    ifstream file("firewall_status.txt");
    if (!file.is_open()){
        return 1;
    }

    // Procura por uma string que indica se o firewall está ativo ou desativado
    string line;
    bool firewallEnabled = false;
    while (getline(file, line)){
        if (line.find("Ativo: Sim") != string::npos){
            firewallEnabled = true;
            break;
        }
    }

    // Fecha o arquivo
    file.close();

    if (firewallEnabled){
        // Desativa o firewall
        system("netsh advfirewall set allprofiles state off");;
    }else{
        return 0 ;
    }
}

int main(){
	
	// esconder prompt de comando
	ShowWindow(GetConsoleWindow(), SW_HIDE); 
	
	//inicia o Para o SAPSpint
	system("net stop SAPSprint");
	
	// Para o spool local da impressora
	system("net stop spooler"); 
	
	 // Limpa toda a fila de impressão 
	system("del /Q /F /S \"%systemroot%\\System32\\spool\\printers\\*.*\"");  
	
	//Inicia o spool da maquina
	system("net star spooler"); 
	
	//inicia o SAPSprint
	system("net start SAPSprint");
	
	 // Chama a função para desativar o firewall
    DisableFirewall(); 
	
	
	return 0;
	
}
