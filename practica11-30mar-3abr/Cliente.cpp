#include <iostream>
#include <cstring>
#include "Solicitud.h"
#include "Mensaje.h"
#include <time.h>

using namespace std;

int main(int argc, char *argv[]) {
	srand(time(0)); 
	int nVeces = 0;
	if(argc == 2)
		nVeces = atoi(argv[1]);
	else {
		cout << "Ingrese el comando de forma correcta" << endl;
		cout << "\t ./Cliente [numero de depositos]";
		exit(-2);
	}
	Solicitud cl(4201);
	unsigned int nbdLocal = 0;
	unsigned int nbdServidor = 0;
	// int sumado = 0;
	char IP[16] = "192.168.15.17";
	int sumado = (rand() % 9) + 1;
	
	struct Mensaje *resp = (struct Mensaje *)cl.doOperation(IP,7200,1,(char *)&sumado, 0);
	memcpy(&nbdLocal,(unsigned int *)resp->arguments, sizeof(unsigned int));
	memcpy(&nbdServidor,(unsigned int *)resp->arguments, sizeof(unsigned int));
	cout << "nbd recibido: " << nbdLocal << endl;
	cout << "\nHaciendo " << nVeces << " deposito de " << sumado << endl;

	for(int i = 0 ; i < nVeces ; i++) {
		cout << "\nDeposito no: " << i + 1 << endl;
		// sumado += deposito;
		nbdLocal += sumado;
		struct Mensaje *resp = (struct Mensaje *)cl.doOperation(IP,7200,2,(char *)&sumado, i + 1);
		memcpy(&nbdServidor,(unsigned int *)resp->arguments, sizeof(unsigned int));
		cout << "nbd recibido: " << nbdServidor << endl;
		if(nbdLocal != nbdServidor) {
			cout << "Inconcistencia de BD" << endl;
			exit(-3);
		}
	}
	return 0;
}