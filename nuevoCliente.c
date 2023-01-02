#include "main.h"

void nuevoCliente(char type){

    /*
            NO FUNCIONA AÚN EL CÓDIGO
    */
    if(1){
        printf("Aqui se crearía un nuevo cliente.\n");
        return 0;
    }

    int clientNum = 20;
    short haveSpace = 0;    //If have no space 0, else the free space
    phread_mutex_lock(&mutexCustList);
    for(int i=0; i<clientNum && haveSpace==0; i++){
        if(customerList[i].id == 0){
            haveSpace = i;
        }
    }
    if(haveSpace == 0){     //No space
        phread_mutex_unlock(&mutexCustList);
        // Logger -> No hay espacio
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
            printf("ERROR");
            // Logger -> Error, tipo de cliente erroneo
            break;
        }

        customerList[haveSpace].isAttended = -1;
        customerList[haveSpace].type = type;
        customerList[haveSpace].solicited = 0;
        customerList[haveSpace].priority=/*aleatorio 1-10*/;
        pthread_t newPhread;
	    pthread_create(&newPhread, NULL, accCliente, &haveSpace);
        phread_mutex_unlock(&mutexCustList);
    }
}
