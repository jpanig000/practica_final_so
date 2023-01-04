void *accTecnicoDomiciliario(){
    
    while(1){
        tecDom();
    }

}

tecDom(){
    
    //Si no se cumple la condicion se queda bloqueado
    pthread_mutex_lock(&mutexDomRequest);
    
    pthread_cond_wait(&condDomRequest,&mutex);
    
    pthread_mutex_unlock(&mutexDomRequest);
    
    
    //Guardamos en el log que comienza la atencion
    writeLog("tecDom"," ha comenzado la atencion domiciliaria");
    
    for(int i = 0; i < 4; i++){
        
        pthread_mutex_lock(&mutexCustList);
        //Descansa un segundo por cada cliente
        sleep(1);
        
        writeLog(""," ha atendido al cliente");
        
        //Poner flag de solicitud a 0
        pthread_mutex_unlock(&mutexCustList);
    }
    
    //Pone el contador de solicitudes a 0
    pthread_mutex_lock(&mutexDomRequest);
    
    domSolsNum = 0;
    
    pthread_mutex_unlock(&mutexDomRequest);
    
    
    
    //Guardamos en el log que se ha finalizado la solicitud domiciliaria    
    
    //Avisa a los que han terminado que la solicitud actual ha finalizado
    pthread_mutex_lock(&mutexDomRequest);

    pthread_cond_signal(&condDomRequest,&mutex);
    
    pthread_mutex_unlock(&mutexDomRequest);
    
}
