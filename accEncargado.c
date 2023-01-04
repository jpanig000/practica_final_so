                                                            //principal function 
void *accEncargado(){
    
    while(1){
        manAction();
    }

}

manAction(){
    struct customer next;
    next.id = 0;
    next.isAttended = -1;
    next.priority = 0;
    
    do{
        pthread_mutex_lock(&mutexCustList);

                                                            //seleccionar el siguiente cliente
                                                            //primero busca clientes de tipo red
            for(int i = 0; i < sizeof(customerList)/sizeof(struct customer); i++){
                struct customer actual = customerList[i];
                if (actual.id != 0 && actual.isAttended == -1){

                    if (next.type == 'N'){
                        if (actual.priority > next.priority){
                        next = actual;
                        }else if(actual.id < next.id) {
                        next = actual;
                        }    
                    }
                }
            }
                                                            //en caso de no encontrar clientes de red busca clientes de app
            if (next.id != 0){
                for(int i = 0; i < sizeof(customerList)/sizeof(struct customer); i++){
                    struct customer actual = customerList[i];
                    if (actual.id != 0 && actual.isAttended == -1){

                        if (next.type == 'A'){
                            if (actual.priority > next.priority){
                            next = actual;
                            }else if(actual.id < next.id) {
                            next = actual;
                            }    
                        }
                    }
                }
            }                                                            
            
        pthread_mutex_unlock(&mutexCustList);
        
        if (next.id != 0){
            sleep(3);
        }
    }while(next.id == 0);
    
                                                            //cambiar condición a atendiendo
    pthread_mutex_lock(&mutexCustList);
        next.isAttended == 0;
    pthread_mutex_unlock(&mutexCustList);

                                                            //calcular numero aleatorio para tipo de atencion
    int atencion = 1; //numAleatorio(0-100);
    
    //escribir en log que se inicia la atencion
                                                            
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