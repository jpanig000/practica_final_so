#include "libs.h"
#include "main.h"


int main(int argc, char *argv[]) {

    int clientNum = 20;     // número de clientes
    int appTechsNum = 2;    // número de técnicos de app

    /*
        Control de parámetros
    */
    if(argc == 3) {
        if(atoi(argv[1])<1 || atoi(argv[2])<1) {
            printf("Los parámetros del programa deben ser números positivos.\n");
            return 0;
        }
        clientNum = atoi(argv[1]);
        appTechsNum = atoi(argv[2]);
    } else if(argc == 2) {
        if(atoi(argv[1])<1) {
            printf("El parámetro del programa deben ser un número positivo.\n");
            return 0;
        }
        clientNum = atoi(argv[1]);
    } else if(argc == 1) {} else {
        printf("El programa solo admite dos parámetros: el número máximo de clientes y el número"); 
        printf(" de técnicos de tipo app.\n");
    }

    declareHandlers();                              // declares handlers for SIGUSR1, SIGUSR2 and SIGINT

    pthread_mutex_init(&mutexFile, NULL);           //  
    pthread_mutex_init(&mutexCustList, NULL);       // initializes all mutexs
    pthread_mutex_init(&mutexDomRequest, NULL);     //

    pthread_cond_init(&condDomRequest, NULL);       // initializes condition

    logFile = fopen("registroTiempos.log", "w");                // opens log txt for writting (maybe changeable)

    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //CREACION TEMPORAL PARA PRUEBAS DE TECNICOS Y ENCARGADO
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    //estructura tecnico red
    struct technician prueba;
    prueba.id = 0;
    prueba.type = 'A';
    //hilo tecnico app

    //estructura tecnico app
    struct technician prueba1;
    prueba1.id = 0;
    prueba1.type = 'N';
    //hilo tecnico red

    //hilo encargago



    while(1){
        sleep(1);
    }

}

void declareHandlers() {
    if(signal(SIGUSR1, newClientApp) == SIG_ERR){
        perror("Error con SIGUSR1");
        exit(-1);
    }
    if(signal(SIGUSR2, newClientNetwork) == SIG_ERR){
        perror("Error con SIGUSR2");
        exit(-1);
    }
    if(signal(SIGINT, finish) == SIG_ERR){
        perror("Error con SIGINT");
        exit(-1);
    }
    //Declarador de las manejadores
}

void newClientApp(int sig){                         //New client with problems with the app                       
    if(signal(SIGUSR1, newClientApp) == SIG_ERR){
        perror("Error con SIGUSR1");
        exit(-1);
    }
    //Empieza un nuevo cliente con problemas en la app
    nuevoCliente('A');
    
}

void newClientNetwork(int sig){                     //New client with problems with network
    if(signal(SIGUSR2, newClientNetwork) == SIG_ERR){
        perror("Error con SIGUSR2");
        exit(-1);
    }
    //Empieza un nuevo cliente con problemas en la red
    nuevoCliente('N');
    
}

void finish(int sig){                               //Finish the program                           
    if(signal(SIGINT, finish) == SIG_ERR){
        perror("Error con SIGINT");
        exit(-1);
    }
    
    //Finaliza todos los clientes en cola, ya no permite tener nuevas solicitudes
    
}
