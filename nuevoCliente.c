/*
*   Grupo 16
*
*   Alicia Gómez Pascual
*   Julián Paniagua González
*   Rubén Fernández González
*   Sergio González Rebollo
*/

void nuevoCliente(char type){

    
    int clientNum = malloc_usable_size(customerList) / sizeof(struct customer);
    
    int haveSpace = -1;    //If have no space -1, else the free space
    
    pthread_mutex_lock(&mutexCustList);
    for(int i=0; i<clientNum && haveSpace==-1; i++){
        if(customerList[i].id == 0){
            haveSpace = i;
        }
    }
    
    if(haveSpace == -1){     //No space
        pthread_mutex_unlock(&mutexCustList);

        pthread_mutex_lock(&mutexFile);
        writeLog("New Client","Can't enter, full space.");
        pthread_mutex_unlock(&mutexFile);
    }else{                  //We create the new client
        switch (type){
            case 'A':
                appCustNum++;
                customerList[haveSpace].id = (appCustNum)*2;     //Even number for app clients
                break;
            case 'N':
                netCustNum++;
                customerList[haveSpace].id = (netCustNum)*2-1;   //Odd number for net clients
                break;
            default:
                pthread_mutex_lock(&mutexFile);
                writeLog("New Client","ERROR TYPE.");
                pthread_mutex_unlock(&mutexFile);
                break;
        }
        
        customerList[haveSpace].isAttended = -1;
        customerList[haveSpace].type = type;
        customerList[haveSpace].solicited = 0;
        customerList[haveSpace].priority=calculaAleatorio(1, 10);
        pthread_t newPhread;
	    pthread_create(&newPhread, NULL, accCliente, &haveSpace);
        pthread_mutex_unlock(&mutexCustList);
    }
}
