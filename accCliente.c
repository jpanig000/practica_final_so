
void *accCliente(void *ptr){

    int numClient = *(int *) ptr;
    
    char name[200] = "";
    nameClient(numClient, name);
    pthread_mutex_lock(&mutexFile);
    writeLog(name,"Nuevo cliente.");
    pthread_mutex_unlock(&mutexFile);

    short secondPassed = 0;
    short attended;

    while(1){
        pthread_mutex_lock(&mutexCustList);
        attended = customerList[numClient].isAttended;
        pthread_mutex_unlock(&mutexCustList);

        if(attended == -1){
            secondPassed = clientNotAttended(numClient, secondPassed);
        }else if(attended == 0){
            clientAttending(numClient);
        }else{
            char type;
            pthread_mutex_lock(&mutexCustList);
            type = customerList[numClient].type;
            pthread_mutex_unlock(&mutexCustList);
            if(attended == 1 && (type = 'N')){
                clientAttendedAndNetClient(numClient);
            }else{
                clientExit(numClient, "Ya he sido atendido.");
            }
        }

    }
}

void nameClient(int numClient, char nombre[]){
    pthread_mutex_lock(&mutexCustList);
    char typeClient = customerList[numClient].type;
    int idClient = customerList[numClient].id;
    pthread_mutex_unlock(&mutexCustList);
    
    sprintf(nombre,"Cliente%c%d",typeClient,idClient);
}

int clientNotAttended(int numClient, int secondPassed){
    int clientConduct = 1/*aleatorio 1-100*/;

    if(clientConduct <= 10){            // 10% find difficult the app and leaves
        clientExit(numClient, "Me parece dificil la aplicación.");
    }else if(clientConduct <=15){       // 5% lost the conexion of the app
        clientExit(numClient, "Perdida de conexión.");
    }else{
        if(secondPassed == 8){
            secondPassed = 0;
            if(clientConduct <= 35){    // 20% every 8 seconds is tired and leaves the app
                clientExit(numClient, "Me cansé de esperar.");
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
    if( 30 <= 1/*aleatorio 1-30*/ ){     // 30% of net clients make a domiciliary requests
       clientDomiciliaryRequests(numClient);
    }else{
        clientExit(numClient, "No quiero atención domiciliaria.");
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
        writeLog(name2,"Espero a ser atendido por atencion domiciliaria");
        pthread_mutex_unlock(&mutexFile);

        pthread_mutex_lock(&mutexCustList);
        customerList[numClient].solicited = 1;
        pthread_mutex_unlock(&mutexCustList);

        pthread_mutex_lock(&mutexDomRequest);
        if(domSolsNum == 4){
            pthread_mutex_unlock(&mutexCustList);
            pthread_cond_signal(&condDomRequest);
        }else{
            pthread_mutex_unlock(&mutexCustList);
        }

        pthread_mutex_lock(&mutexCustList);
        while(customerList[numClient].solicited == 0){
            pthread_mutex_unlock(&mutexCustList);
            pthread_cond_wait(&condDomRequest, &mutexDomRequest);
            pthread_mutex_lock(&mutexCustList);
        }
        pthread_mutex_unlock(&mutexCustList);

        char name[100] = "";
        nameClient(numClient, name);

        pthread_mutex_lock(&mutexFile);
        writeLog(name,"Mi atencion ha finalizado");
        pthread_mutex_unlock(&mutexFile);

        clientExit(numClient, "Atención domiciliaria finalizada.");
    }else{
        pthread_mutex_unlock(&mutexDomRequest);
        sleep(3);
        clientDomiciliaryRequests(numClient);
    }
}


void clientExit(int numClient, char* reason){

    char name[100] = "";
    nameClient(numClient, name);

    char mensaje[100] = "se va de la aplicacion por el motivo: ";
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