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

    logFile = fopen("registroTiempos.log", "w");    // opens log file for writting (maybe changeable)

    // creating app technicians
    for (int i = 0; i < appTechsNum; i++) {
        
        struct technician newAppTech;
        newAppTech.id = i;
        newAppTech.type = 'A';

        pthread_t newThread;
        pthread_create(&newThread, NULL, accTecnico, &newAppTech);

    }
    
    // creating web technicians
    for (int i = appTechsNum; i < appTechsNum+2; i++) {

        struct technician newNetTech;
        newNetTech.id = i;
        newNetTech.type = 'N';

        pthread_t newThread;
        pthread_create(&newThread, NULL, accTecnico, &newNetTech);

    }
    
    // creating eNcaRgAdO
    pthread_t encargado;
    pthread_create(&encargado, NULL, accEncargado, NULL);

    // creating domiciliary technician
    pthread_t domTech;
    pthread_create(&domTech, NULL, accTecnicoDomiciliario, NULL);


    // // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // // CREACION TEMPORAL PARA PRUEBAS DE TECNICOS Y ENCARGADO
    // // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // //estructura tecnico red
    // struct technician prueba;
    // prueba.id = 0;
    // prueba.type = 'A';

    // pthread_t newPhread1;
    // pthread_create(&newPhread1, NULL, accTecnico, &prueba);

    // //estructura tecnico app
    // struct technician prueba1;
    // prueba1.id = 0;
    // prueba1.type = 'N';
    
    // pthread_t newPhread2;
    // pthread_create(&newPhread2, NULL, accTecnico, &prueba1);

    // pthread_t newPhread3;
    // pthread_create(&newPhread3, NULL, accEncargado, NULL);
    // //hilo encargago



    while(1){
        pause();
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

int calculaAleatorio(int min, int max) {        //calcula un num aleatorio entre min y max
    return rand() % (max-min+1) + min;
}