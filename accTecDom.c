void *accTecnicoDomiciliario(){
    
    while(1){
        tecDom();
    }

}

void tecDom(){
    
    //Si no se cumple la condicion se queda bloqueado
    pthread_mutex_lock(&mutexDomRequest);
    
    pthread_cond_wait(&condDomRequest,&mutexDomRequest);
    
    pthread_mutex_unlock(&mutexDomRequest);
    
    
    //Guardamos en el log que comienza la atencion
    pthread_mutex_lock(&mutexFile);
    
    writeLog("tecDom"," has begun the domiciliary attention");
    
    pthread_mutex_unlock(&mutexFile);
    
    
    for(int i = 0; i < 4; i++){
        
        struct customer next;
        next.id = 0;
        
        //Posicion para buscar en los clientes cuales esperan por la atencion
        int pos = 0; 
        
        pthread_mutex_lock(&mutexCustList);
        
        do{
            struct customer actual = customerList[pos];
            if(actual.solicited == 1){
                next = actual;
            }
            pos = pos + 1;
            if(pos == 20){
                pos = 0;
            }    
        }while(next.id == 0);
        
        pthread_mutex_unlock(&mutexCustList);
        
        
        //Descansa un segundo por cada cliente
        sleep(1);
        
        
        //Escribe en el log que ha atendido al cliente
        pthread_mutex_lock(&mutexFile);
        
        //Concateno la cadena con el id del cliente 
        char dest[30] = "has served the client";
        char anad[10];
        int num = next.id;
        sprintf(anad, "%d", num);
        strcat(dest, anad);
        
        writeLog("tecDom", dest);
        
        pthread_mutex_unlock(&mutexFile);
        
        
        //Poner flag de solicitud a 0
        pthread_mutex_lock(&mutexCustList);
        
        actual.solicited == 1;
        
        pthread_mutex_unlock(&mutexCustList);
    }
    
    
    //Pone el contador de solicitudes a 0
    pthread_mutex_lock(&mutexDomRequest);
    
    domSolsNum = 0;
    
    pthread_mutex_unlock(&mutexDomRequest);
    
    
    
    //Guardamos en el log que se ha finalizado la solicitud domiciliaria    
    pthread_mutex_lock(&mutexFile);
    
    writeLog("tecDom"," has finished the domiciliary attention");
    
    pthread_mutex_unlock(&mutexFile);
    
    
    //Avisa a los que han terminado que la solicitud actual ha finalizado
    pthread_mutex_lock(&mutexDomRequest);

    pthread_cond_signal(&condDomRequest);
    
    pthread_mutex_unlock(&mutexDomRequest);
    
}
