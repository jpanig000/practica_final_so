#include "libs.h"
#include "main.h"


int main(int argc, char *argv[]) {

    pthread_mutex_init(&mutexFile, NULL);
    pthread_mutex_init(&mutexCustList, NULL);
    pthread_mutex_init(&mutexSolicitudes, NULL);

    pthread_cond_init(&condSolicitudes, NULL);

}