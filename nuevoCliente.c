
void nuevoCliente(char type){

    
    int clientNum = sizeof(customerList)/sizeof(struct customer);

    int haveSpace = -1;    //If have no space -1, else the free space
    
    pthread_mutex_lock(&mutexCustList);
    for(int i=0; i<clientNum && haveSpace==-1; i++){
        if(customerList[i].id == 0){
            haveSpace = i;
        }
    }
    
    if(haveSpace == -1){     //No space
        pthread_mutex_unlock(&mutexCustList);
        printf("Espacio lleno, no se puede atender a mas clientes.\n");
        printf("Logger -> No hay espacio\n");
    }else{                  //We create the new client
        switch (type){
        case 'A':
            appCustNum++;
            customerList[haveSpace].id = (appCustNum)*10 + 0;   //End at 0 for app clients
            break;
        case 'N':
            netCustNum++;
            customerList[haveSpace].id = (netCustNum)*10 + 1;   //End at 1 for net clients
            break;
        default:
            printf("Logger -> Error, tipo de cliente erroneo\n");
            break;
        }
        
        customerList[haveSpace].isAttended = -1;
        customerList[haveSpace].type = type;
        customerList[haveSpace].solicited = 0;
        customerList[haveSpace].priority=1/*aleatorio 1-10*/;
        pthread_t newPhread;
	    pthread_create(&newPhread, NULL, accCliente, &haveSpace);
        pthread_mutex_unlock(&mutexCustList);
    }
}
