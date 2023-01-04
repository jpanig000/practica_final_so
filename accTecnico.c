                                                            //principal function 
void *accTecnico(struct technician tech){
    
    int counter = 1;
    
    while(1){
        techAction(tech);
        if(tech.type = 'A'){
            if(counter == 5){
                sleep(5);
            }
        }else{
            if(counter == 6){
                sleep(5);
            }
        }
    }
}

techAction(struct technician tech){
    struct customer next;
    next.id = 0;
    next.isAttended = -1;
    next.priority = 0;
    
    do{
        pthread_mutex_lock(&mutexCustList);

                                                            //seleccionar el siguiente cliente
            for(int i = 0; i < sizeof(customerList)/sizeof(struct customer); i++){
                struct customer actual = customerList[i];
                if (actual.id != 0 && actual.isAttended == -1 && actual.type == tech.type){
                    if (actual.priority > next.priority){
                        next = actual;
                    }else if(actual.id < next.id) {
                        next = actual;
                    }
                }
            }
        pthread_mutex_unlock(&mutexCustList);
        
        if (next.id != 0){
            sleep(1);
        }
    }while(next.id == 0);
    
                                                            //cambiar condición a atendiendo
    pthread_mutex_lock(&mutexCustList);
        next.isAttended == 0;
    pthread_mutex_unlock(&mutexCustList);

                                                            //calcular numero aleatorio para tipo de atencion
    int atencion = 1; //numAleatorio(0-100);
    
    //escribir en log que se inicia la atencion
    pthread_mutex_lock(&mutexFile);
        writeLog("tech" + tech.type + tech.id, "the tech of type %s starts the attention to client %s", tech.type, client.id);
    pthread_mutex_unlock(&mutexFile);                                                        
                                                            //dormir tiempo de atencion
    if(atencion > 0 && atencion < 10){
        sleep(0);// numAleatorio(2-6));                     //error de identificacion
    }else if(atencion > 10 && atencion < 20){
        sleep(0);// numAleatorio(1-2));                     //compañia equivocada
    }else if(atencion > 20 && atencion < 100){
        sleep(0);// numAleatorio(1-4));                     //todo en regla
    }
    
    //escribir en log que finaliza la atencion
    
    //escribir en log motivo de finalización
    
                                                            //cambiar atendido
    pthread_mutex_lock(&mutexCustList);
        next.isAttended == 0;
    pthread_mutex_unlock(&mutexCustList);

}