#include <iostream>
#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "Solicitud.h"
#include "Mensaje.h"
#include <sys/time.h>

using namespace std;

Solicitud::Solicitud(int port){
	socketlocal = new SocketDatagrama(port);  	
}

char* Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments,int numSol){
    struct Mensaje men;
    men.messageType=0;
    men.requestId=numSol;
    memcpy(men.IP,IP,sizeof(char)*16);//men.IP=IP;  
    men.puerto=puerto;
    men.operationId=operationId;
    memcpy(men.arguments, arguments,sizeof(char)*TAM_MAX_DATA);

	PaqueteDatagrama p1((char *)&men,sizeof(men),IP,puerto);

    time_t segundos = 2;
    suseconds_t microsegundos =  5000;
    int enviado, enviado1 ;
    int nEnviado = 0, nEnviado1 = 0;

    if (operationId==2) {
        cout << "\tTipo: " << men.messageType << endl;
        cout << "\tId: " << men.requestId << endl;
        cout << "\tOperacion: " << men.operationId << endl;
    }
    
    // Peticiones iniciales
    do {
        socketlocal->envia(p1);
	    while(true) {
            enviado = socketlocal->recibeTimeout(p1,segundos,microsegundos);
            if((unsigned int)numSol == ((struct Mensaje *)p1.obtieneDatos())->requestId){
                break;
            }
        }
        if(enviado != -1)
            break;
        else
            nEnviado++;
    } while (nEnviado < 7);

    if(nEnviado == 7) {
        // cout << "Se han agotado el numero posible de intentos" << endl;
        cout << "Solicitando ultimo deposito...\n";
        men.operationId = 3;
        PaqueteDatagrama p1((char *)&men,sizeof(men),IP,puerto);

        cout << "\tTipo: " << ((struct Mensaje*)p1.obtieneDatos())->messageType << endl;
        cout << "\tId: " << ((struct Mensaje*)p1.obtieneDatos())->requestId << endl;
        cout << "\tOperacion: " << ((struct Mensaje*)p1.obtieneDatos())->operationId << endl;

        do {
            socketlocal->envia(p1);
            while(true) {
                enviado1 = socketlocal->recibeTimeout(p1,segundos,microsegundos);
                if(1 == ((struct Mensaje *)p1.obtieneDatos())->messageType) {
                    break;
                }
            }
            if(enviado1 != -1) {
                //cout << "\tTipo: " << ((struct Mensaje*)p1.obtieneDatos())->messageType << endl;
                //cout << "\tId: " << ((struct Mensaje*)p1.obtieneDatos())->requestId << endl;
                //cout << "\tOperacion: " << ((struct Mensaje*)p1.obtieneDatos())->operationId << endl;
                //cout << "\tSaldo: " << *(unsigned int*)((struct Mensaje*)p1.obtieneDatos())->arguments << endl;
                return p1.obtieneDatos();
            } else
                nEnviado1++;
        } while (nEnviado1 < 7);
    }
    if (nEnviado1==7) {
        cout << "Se han agotado el numero posible de intentos" << endl;
        exit(-1);
    }

	return p1.obtieneDatos();
}
