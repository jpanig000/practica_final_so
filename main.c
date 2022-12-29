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

    logFile = fopen("log.txt", "w");                // opens log txt for writting (maybe changeable)

    

}

void declareHandlers() {
    // parte de Rubén
}