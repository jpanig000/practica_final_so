//Escribe en el archivo con identificador id y mensaje
void writeLog(char *id, char *msg){
    time_t now = time(0);
    struct tm *tlocal = localtime(&now);
    char stnow[25];
    strftime(stnow, 25, "%y/%m/%d %H:%M:%S", tlocal); 
 
    // Escribimos en el log

    logFile = fopen("registroTiempos.log", "a");
    fprintf(logFile, "[%s] %s: %s\n", stnow, id, msg);
    fclose(logFile); 
}
