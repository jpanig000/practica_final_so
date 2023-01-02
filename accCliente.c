#include "main.h"

void *accCliente(void *ptr){

    /*
            NO FUNCIONA AÚN EL CÓDIGO
    */
    if(1){
        printf("Aqui se ejecutaría las acciones de un cliente con id %d.\n", customerList[*(int *)ptr].id);
        return 0;
    }

    // Logger -> hora entrada + tipo de cliente
    // "Nuevo cliente tipo %c", customerList[*(int *)ptr].type


    short secondPassed = 0;
    short attended;

    while(1){
        pthread_mutex_lock(&mutexCustList);
        attended = customerList[*(int *)ptr].isAttended;
        pthread_mutex_unlock(&mutexCustList);

        if(attended == -1){
            secondPassed = clientNotAttended(*(int *)ptr, secondPassed);
        }else if(attended == 0){
            clientAttending(*(int *)ptr);
        }else if(attended == 1 && (customerList[*(int *)ptr].type = 'N')){
            clientAttendedAndNetClient(*(int *)ptr);
        }else{
            clientExit(*(int *)ptr)
        }

    }
}

int clientNotAttended(int numClient, int secondPassed){
    int clientConduct = /*aleatorio 1-100*/;

    if(clientConduct <= 10){            // 10% find difficult the app and leaves
        clientExit(numClient);
    }else if(clientConduct <=15){       // 5% lost the conexion of the app
        clientExit(numClient);
    }else{
        if(secondPassed == 8){
            secondPassed = 0;
            if(clientConduct <= 35){    // 20% every 8 seconds is tired and leaves the app
                clientExit(numClient);
            }
        }
    }

    sleep(2);

    return secondPassed + 2;
}

void clientAttending(int numClient){
    sleep(2);                           // The client wait until the technician have end
}

void clientAttendedAndNetClient(int numClient){
    if( 30 <= /*aleatorio 1-30*/ ){     // 30% of net clients make a domiciliary requests
       clientDomiciliaryRequests(numClient);
    }else{
        clientExit(numClient);
    }
}

void clientDomiciliaryRequests(int numClient){

    pthread_mutex_lock(&mutexDomRequest);

    if(domSolsNum<4){
        domSolsNum++;
        pthread_mutex_unlock(&mutexDomRequest);

        // Logger -> Espero a ser atendido por atencion domiciliaria

        pthread_mutex_lock(&mutexCustList);
        customerList[numClient].solicited = 1;
        pthread_mutex_unlock(&mutexCustList);

        pthread_mutex_lock(&mutexDomRequest);
        if(domSolsNum == 4){
            pthread_mutex_unlock(&mutexCustList);
            signal(condDomRequest);
        }else{
            pthread_mutex_unlock(&mutexCustList);
        }

        pthread_mutex_lock(&mutexCustList);
        while(customerList[numClient].solicited == 0){
            pthread_mutex_unlock(&mutexCustList);
            wait(condDomRequest);
            pthread_mutex_lock(&mutexCustList);
        }
        pthread_mutex_unlock(&mutexCustList);

        // Logger -> Su atencion ha finalizado

    }else{
        pthread_mutex_unlock(&mutexDomRequest);
        sleep(3);
        clientDomiciliaryRequests(numClient);
    }
}


void clientExit(int numClient){
    // Logger -> Se va el cliente %d, num
    clearClient(numClient);
    pthread_exit(NULL);
}

void clearClient(int numClient){
    pthread_mutex_lock(&mutexCustList);

    customerList[numClient].id = 0;
    customerList[numClient].isAttended = -1;
    customerList[numClient].type = ' ';
    customerList[numClient].priority = 0;
    customerList[numClient].solicited = 0;

    pthread_mutex_unlock(&mutexCustList);
}