#include <iostream>
#include "Respuesta.h"

using namespace std;

int main(int argc, char *argv[]) {
	int puerto = 0;
	struct Mensaje *pet, *hist;
	hist = new struct Mensaje; 

	if(argc == 2) {
		puerto = atoi(argv[1]);
	} else {
		cout << "Ingrese el comando de forma correcta" << endl;
		cout << "\t ./Servidor <puerto>";
		exit(-2);
	}

	Respuesta srv(puerto);
	unsigned int nbd = 0;
	unsigned int idProcesada = 0;
	cout << "Escuchando..." << endl;

	while(1) {
		struct Mensaje *pet = srv.getRequest();

		if (pet->operationId==1) {
			cout << "\nInicializar nbd" << endl;
			nbd = 0,
			memcpy((unsigned int *)pet->arguments, &nbd, sizeof(unsigned int));
			cout << "nbd enviado, base inicializada." << endl;
			idProcesada = pet->requestId;
		} else if (pet->operationId==2) {
			cout << "\nDeposito recibido" << endl;
			cout << "\tTipo: " << pet->messageType << endl;
			cout << "\tId: " << pet->requestId << endl;
			cout << "\tOperacion: " << pet->operationId << endl;

			int nbdCliente;
			memcpy(&nbdCliente,(unsigned int *)pet->arguments, sizeof(unsigned int));

			if(idProcesada+1 == pet->requestId) {
				idProcesada++;
				nbd += nbdCliente;
				cout << "\tSaldo actual: " << nbd << endl;
				cout << "\tnuevo saldo enviado" << endl;
			} else {
				cout << "\t*Mensaje duplicado, saldo anterior enviado" << endl;
			}
			memcpy((unsigned int *)pet->arguments, &nbd, sizeof(unsigned int));
		}

		pet->messageType=1;
		srv.sendReply(pet);
	}

	// while(1) {
	// 	pet = srv.getRequest();

	// 	if (pet->operationId==1) {
	// 		cout << "\nInicializar nbd" << endl;
	// 		nbd = 0,
	// 		memcpy(hist, pet, sizeof(struct Mensaje));
	// 		memcpy((unsigned int *)pet->arguments, &nbd, sizeof(unsigned int));
	// 		cout << "nbd enviado, base inicializada." << endl;
	// 		idProcesada = pet->requestId;
	// 	} else if (pet->operationId==2) {
	// 		cout << "\nDeposito recibido" << endl;
	// 		cout << "\tTipo: " << pet->messageType << endl;
	// 		cout << "\tId: " << pet->requestId << endl;
	// 		cout << "\tOperacion: " << pet->operationId << endl;

	// 		int nbdCliente;
	// 		memcpy(&nbdCliente,(unsigned int *)pet->arguments, sizeof(unsigned int));
			
	// 		if(pet->requestId==idProcesada+1){
	// 			idProcesada++;
	// 			nbd += nbdCliente;
	// 			cout << "\tSaldo actual: " << nbd << endl;
	// 			memcpy((unsigned int *)pet->arguments, &nbd, sizeof(unsigned int));
	// 		} else if (pet->requestId<=idProcesada) {
	// 			cout << "\tMensaje duplicado, accion ignorada" << endl;
	// 			continue;
	// 		}

	// 		memcpy(hist, pet, sizeof(struct Mensaje));
	// 		cout << "\tnuevo saldo enviado" << endl;
	// 	} else if (pet->operationId==3) {
	// 		cout << "\nSolicitud de ultimo deposito" << endl;
	// 		cout << "\tTipo: " << pet->messageType << endl;
	// 		cout << "\tId: " << pet->requestId << endl;
	// 		cout << "\tOperacion: " << pet->operationId << endl;

	// 		idProcesada = pet->requestId;
	// 		memcpy(pet, hist, sizeof(struct Mensaje));

	// 		cout << "\tnuevo saldo enviado " << *(unsigned int*)hist->arguments << endl;
	// 	}

	// 	pet->messageType=1;
		
	// 	srv.sendReply(pet);
	// }
}
