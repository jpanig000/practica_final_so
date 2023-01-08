
void *accCliente(void *ptr){

    int numClient = *(int *) ptr;
    
    char name[200] = "";
    nameClient(numClient, name);
    pthread_mutex_lock(&mutexFile);
    writeLog(name,"New client.");
    pthread_mutex_unlock(&mutexFile);

    short secondPassed = 0;
    short attended;

    while(1){
        pthread_mutex_lock(&mutexCustList);
        attended = customerList[numClient].isAttended;
        pthread_mutex_unlock(&mutexCustList);

        if(attended == -1){                 //The client haven't been attended
            secondPassed = clientNotAttended(numClient, secondPassed);
        }else if(attended == 0){            //The client is being attended
            clientAttending(numClient);
        }else if(attended == 1){            //The client has been attended
            char type;
            pthread_mutex_lock(&mutexCustList);
            type = customerList[numClient].type;
            pthread_mutex_unlock(&mutexCustList);

            if(type == 'N'){                 //The net clients could request a domiciliary technician
                clientAttendedAndNetClient(numClient);
            }else{                          //The app clients exit the plataform
                clientExit(numClient, "I have been attended.");
            }
        }else{                              //There is a error
            char nombreCliente[200] = "";
            nameClient(numClient, nombreCliente);
            char mensaje[300] = "";
            sprintf(mensaje,"ERROR: wrong value, customer is attended must be -1, 0 or 1. And it is :%d.", attended);
            pthread_mutex_lock(&mutexFile);
            writeLog(nombreCliente, mensaje);
            pthread_mutex_unlock(&mutexFile);
        }

    }
}

void nameClient(int numClient, char nombre[]){
    pthread_mutex_lock(&mutexCustList);
    char typeClient = customerList[numClient].type;
    int idClient = customerList[numClient].id;
    pthread_mutex_unlock(&mutexCustList);

    sprintf(nombre,"Client%c%d",typeClient,idClient);
}

int clientNotAttended(int numClient, int secondPassed){
    int clientConduct = calculaAleatorio(1, 100);

    if(clientConduct <= 10){                // 10% find difficult the app and leaves
        clientExit(numClient, "I find difficult the app.");
    }else if(clientConduct <=15){           // 5% lost the conexion of the app
        clientExit(numClient, "I have lost conexion.");
    }else{
        if(secondPassed == 8){
            secondPassed = 0;
            if(clientConduct <= 35){        // 20% every 8 seconds is tired and leaves the app
                clientExit(numClient, "I'm tired of waiting.");
            }
        }
    }

    sleep(2);

    return secondPassed + 2;
}

void clientAttending(int numClient){
    sleep(2);                               // The client wait until the technician have end
}

void clientAttendedAndNetClient(int numClient){

    pthread_mutex_lock(&mutexCustList);
    int cSolicited = customerList[numClient].solicited;
    pthread_mutex_unlock(&mutexCustList);

    int cElection = calculaAleatorio(1, 100);

    if(30<=cElection && cSolicited!=-1){   // 30% of net clients make a domiciliary requests
       clientDomiciliaryRequests(numClient);
    }else{
        clientExit(numClient, "I don't want domiciliary attention.");
    }
}

void clientDomiciliaryRequests(int numClient){
    pthread_mutex_lock(&mutexDomRequest);
    if(domSolsNum<4){
        domSolsNum++;
        pthread_mutex_unlock(&mutexDomRequest);

        char name2[100] = "";
        nameClient(numClient, name2);
        pthread_mutex_lock(&mutexFile);
        writeLog(name2,"Waiting to be attended for a domiciliry technician.");
        pthread_mutex_unlock(&mutexFile);

        pthread_mutex_lock(&mutexCustList);
        customerList[numClient].solicited = 1;
        pthread_mutex_unlock(&mutexCustList);

        pthread_mutex_lock(&mutexDomRequest);
        if(domSolsNum == 4){
            pthread_cond_signal(&condDomRequest);
        }else{
            pthread_mutex_unlock(&mutexCustList);
        }

        pthread_mutex_lock(&mutexCustList);
        while(customerList[numClient].solicited != 0){
            pthread_mutex_unlock(&mutexCustList);
            
            pthread_cond_wait(&condDomRequest, &mutexDomRequest);

            pthread_mutex_lock(&mutexCustList);
        }

        pthread_mutex_unlock(&mutexDomRequest);
        pthread_mutex_unlock(&mutexCustList);

        char name[100] = "";
        nameClient(numClient, name);

        pthread_mutex_lock(&mutexFile);
        writeLog(name,"My domiciliary attention has been completed.");
        pthread_mutex_unlock(&mutexFile);

        clientExit(numClient, "Domiciliary attention have ended.");
    }else{
        pthread_mutex_unlock(&mutexDomRequest);
        sleep(3);
        clientDomiciliaryRequests(numClient);
    }
}


void clientExit(int numClient, char* reason){

    char name[100] = "";
    nameClient(numClient, name);

    char mensaje[100] = "Exit the app because: ";
    strcat(mensaje, reason);

    pthread_mutex_lock(&mutexFile);
    writeLog(name,mensaje);
    pthread_mutex_unlock(&mutexFile);

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