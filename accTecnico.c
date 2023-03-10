/*
*   Grupo 16
*
*   Alicia Gómez Pascual
*   Julián Paniagua González
*   Rubén Fernández González
*   Sergio González Rebollo
*/

                                                            //principal function 
void *accTecnico(void *techPointer){
    
    struct technician tech = *(struct technician *) techPointer;
    int counter = 0;
    
    while(1){
        techAction(tech);
        counter++;
        if(tech.type == 'A'){
            if(counter == 5){
                counter = 0;
                sleep(5);
            }
        }else{
            if(counter == 6){
                counter = 0;
                sleep(5);
            }
        }
    }
}

void techAction(struct technician tech){
    struct customer next;
    next.id = 0;
    next.isAttended = -1;
    next.priority = 0;
    
    int numNext = -1;

    do{
        pthread_mutex_lock(&mutexCustList);

                                                            //seleccionar el siguiente cliente
            for(int i = 0; i < malloc_usable_size(customerList) / sizeof(struct customer); i++){
                struct customer actual = customerList[i];
                if (actual.id != 0 && actual.isAttended == -1 && actual.type == tech.type){
                    if (actual.priority > next.priority){
                        next = actual;
                        numNext = i;
                    }else if(actual.priority == next.priority && actual.id < next.id) {
                        next = actual;
                        numNext = i;
                    }
                }
            }
        if (next.id == 0){
            pthread_mutex_unlock(&mutexCustList);
            sleep(1);
        }
    }while(next.id == 0);
    
                                                            //cambiar condición a atendiendo
    
        customerList[numNext].isAttended = 0;
    pthread_mutex_unlock(&mutexCustList);

                                                            //calcular numero aleatorio para tipo de atencion
    int atencion = calculaAleatorio(1, 100);
    
                                                            //escribir en log que se inicia la atencion

    char id[100];
    char number[] = "";
    
    sprintf(id,"Tech%c%d",tech.type,tech.id);
    
    char idCli[100] = "";

    sprintf(idCli,"%d.",next.id);

    char message[] = "The tech starts attending to client ";

    strcat(message, idCli);

    pthread_mutex_lock(&mutexFile);
        writeLog(id, message);
    pthread_mutex_unlock(&mutexFile); 

                                                            //dormir tiempo de atencion
    int fin;
    if(atencion > 0 && atencion <= 10){
        fin = 0;
        sleep(calculaAleatorio(2, 6));                     //error de identificacion
    }else if(atencion > 10 && atencion <= 20){
        fin = 1;
        pthread_mutex_lock(&mutexCustList);
            customerList[numNext].solicited = -1;          //the customer can´t solicity dom att
        pthread_mutex_unlock(&mutexCustList);

        sleep(calculaAleatorio(1, 2));                     //compañia equivocada
    }else if(atencion > 20 && atencion <= 100){
        fin = 2;
        sleep(calculaAleatorio(1,4));                     //todo en regla
    }
    
                                                            //escribir en log que finaliza la atencion

    char message1[] = "The tech finalized the attention to client ";
    strcat(message1, idCli);

    pthread_mutex_lock(&mutexFile);
        writeLog(id, message1);
    pthread_mutex_unlock(&mutexFile); 
    
                                                            //escribir en log motivo de finalización
    
    char message2[] = "The action finalized because ";
    if(fin == 0){
        strcat(message2, "it was an autentication error.");
    }else if(fin == 1){
        strcat(message2, "the customer has the wrong company.");
    }else if(fin == 2){
        strcat(message2, "the customer was atended correctly.");
    }
    

    pthread_mutex_lock(&mutexFile);
        writeLog(id, message2);
    pthread_mutex_unlock(&mutexFile); 

                                                            //cambiar atendido
    pthread_mutex_lock(&mutexCustList);
        customerList[numNext].isAttended = 1;
    pthread_mutex_unlock(&mutexCustList);
    
}