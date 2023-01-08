#include "libs.h"
#include "main.h"


int main(int argc, char *argv[]) { // parametro 1: num clientes. // parametro 2: num tecnicos de app

    int clientNum = 20;     // número de clientes
    int techAppNum = 2;    // número de técnicos de app

    /*
        Control de parámetros
    */
    if(argc == 3) {
        if(atoi(argv[1])<1 || atoi(argv[2])<1) {
            printf("Los parámetros del programa deben ser números positivos.\n");
            return 0;
        }
        clientNum = atoi(argv[1]);
        techAppNum = atoi(argv[2]);
    } else if(argc == 2) {
        if(atoi(argv[1])<1) {
            printf("El parámetro del programa deben ser un número positivo.\n");
            return 0;
        }
        clientNum = atoi(argv[1]);
    } else if(argc == 1) {/*si no hay parámetros*/} else {
        printf("El programa solo admite dos parámetros: el número máximo de clientes y el número"); 
        printf(" de técnicos de tipo app.\n");
    }

    declareHandlers();                              // declares handlers for SIGUSR1, SIGUSR2 and SIGINT

    customerList = (struct customer *) malloc(clientNum * sizeof(struct customer));

    pthread_mutex_init(&mutexFile, NULL);           //  
    pthread_mutex_init(&mutexCustList, NULL);       // initializes all mutexs
    pthread_mutex_init(&mutexDomRequest, NULL);     //

    pthread_cond_init(&condDomRequest, NULL);       // initializes condition

    logFile = fopen("registroTiempos.log", "w");    // opens log file for writting (maybe changeable)

    // creating app technicians
    for (int i = 0; i < techAppNum; i++) {
        
        struct technician newAppTech;
        newAppTech.id = i;
        newAppTech.type = 'A';

        pthread_t newThread;
        pthread_create(&newThread, NULL, accTecnico, &newAppTech);

    }
    
    // creating web technicians
    for (int i = techAppNum; i < techAppNum+2; i++) {   // para empezar a partir de los tecnicos ya creados
                                                        //  y que la id sea única
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
    if(signal(SIGPIPE, changeCustomerList) == SIG_ERR) {
        perror("Error con SIGPIPE");
        exit(-1);
    }
    if(signal(SIGQUIT, addAppTechs) == SIG_ERR) {
        perror("Error con SIGQUIT");
        exit(-1);
    }
    //Declarador de las manejadores
}

void changeCustomerList() {

    if(signal(SIGPIPE, changeCustomerList) == SIG_ERR) {
        perror("Error con SIGPIPE");
        exit(-1);
    }

    printf("Introduzca el número de clientes permitido a partir de este momento.\n");
    int numCustomers=0;

    scanf("%d", &numCustomers);
    int tamActual = malloc_usable_size(customerList) / sizeof(struct customer);

    if(numCustomers < tamActual) {
        printf("El tamaño solo puede aumentar, no disminuir.\n");
    } else if(numCustomers == tamActual) {
        printf("Ese es el número de clientes ya permitidos actualmente. No se modifica nada.\n");
    } else {
        pthread_mutex_lock(&mutexCustList);

        struct customer *new_customerList;
        new_customerList = (struct customer *) malloc(numCustomers * sizeof(struct customer));

        memcpy(new_customerList, customerList, numCustomers * sizeof(struct customer));

        customerList = new_customerList;

        printf("Número máximo de clientes permitidos modificado.\n");

        pthread_mutex_unlock(&mutexCustList);
    }
}

void addAppTechs() {
    if(signal(SIGQUIT, addAppTechs) == SIG_ERR) {
        perror("Error con SIGQUIT");
        exit(-1);
    }

    printf("Introduzca el número de técnicos de tipo app que desee.\n");
    int new_techAppNum=0;
    scanf("%d", &new_techAppNum);

    if(new_techAppNum<=techAppNum) {
        printf("El número de técnicos de tipo app debe ser mayor que el actual.\n");
    } else {
        for(int i=techAppNum+2; i<new_techAppNum+2; i++) {
            struct technician newAppTech;
            newAppTech.id = i;
            newAppTech.type = 'A';

            pthread_t newThread;
            pthread_create(&newThread, NULL, accTecnico, &newAppTech);
        }
    }

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
    
    if(signal(SIGUSR1,SIG_IGN) == SIG_ERR){
        perror("ERROR");
        exit(-1);
    }
    
    if(signal(SIGUSR2,SIG_IGN) == SIG_ERR){
        perror("ERROR");
        exit(-1);
    }
    
    // Hago que si no han pedido el servicio tecnico domiciliario no puedan pedirlo
    pthread_mutex_lock(&mutexCustList);
    for(int i = 0; i < malloc_usable_size(customerList) / sizeof(struct customer); i++){
            if(customerList[i].solicited==0){
                customerList[i].solicited=-1;
            }
    }  
    pthread_mutex_unlock(&mutexCustList);

    //Dom tec atiende a todos los que estaban esperando
    pthread_mutex_lock(&mutexDomRequest);
    pthread_cond_signal(&condDomRequest);
    pthread_mutex_unlock(&mutexDomRequest);

    //Miro el numero de clientes
    int numC = 0;
    struct customer actual;
    do{
        numC = 0;
        sleep(1);
        for(int i = 0; i < malloc_usable_size(customerList) / sizeof(struct customer); i++){
            pthread_mutex_lock(&mutexCustList);
            actual = customerList[i];
            pthread_mutex_unlock(&mutexCustList);
            if (actual.id != 0){
                numC = 1;
            }
        }  
    }while(numC == 1); 
    free(customerList);
    kill(getpid(),SIGKILL);   
}

int calculaAleatorio(int min, int max) {        //calcula un num aleatorio entre min y max
    return rand() % (max-min+1) + min;
}
