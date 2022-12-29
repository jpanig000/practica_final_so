struct customer {   // struct representing customers
    int id;
    int isAttended; // 0 if is not
    char type;      // 'A' for app, 'N' for net
    int priority;   
    int solicited;  // 1 if they have solicited domiciliary attention
};

struct customer customerList[20];       // customers list

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