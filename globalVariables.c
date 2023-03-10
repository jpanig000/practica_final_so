/*
*   Grupo 16
*
*   Alicia Gómez Pascual
*   Julián Paniagua González
*   Rubén Fernández González
*   Sergio González Rebollo
*/

struct customer {   // struct representing customers
    int id;         // End at even for app, odd for net
    int isAttended; // -1 if is not, 0 if atending, 1 atended
    char type;      // 'A' for app, 'N' for net
    int priority;   
    int solicited;  // -1 if the the customer cant solicity dom att, 1 if they have solicited domiciliary attention
};

struct customer *customerList;       // customers list

int techAppNum;     // type app technicians counter
int appCustNum;     // type app customers counter
int netCustNum;     // type net customers counter
int domSolsNum;     // domiciliary requests number

pthread_mutex_t mutexFile;              // mutex for file access
pthread_mutex_t mutexCustList;          // mutex for customer list access
pthread_mutex_t mutexDomRequest;        // mutex for condition condDomRequest

pthread_cond_t condDomRequest;          // condition for domiciliary requests

struct technician { // struct representing technicians
    int id;
    char type;      // 'A' for app, 'N' for net
};

FILE *logFile;       // log file