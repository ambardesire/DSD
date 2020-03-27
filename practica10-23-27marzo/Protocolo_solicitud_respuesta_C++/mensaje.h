#ifndef __mensaje__
#define __mensaje__

#define TAM_MAX_DATA 4000

//Definicion de identificadores para operaciones permitidas

#define suma 1

//Definicion del formato de mensaje

struct mensaje {
    int messageType;        //0 = Solicitud, 1 = Respuesta
    unsigned int requestId; //Identificador del mensaje
    char IP[16];
    int puerto;
    int operationId;        //Identificador del mensaje
    char arguments[TAM_MAX_DATA];
};

#endif
