struct customer {
    int id;
    int isAttended; // 0 if is not
    char type;      // 'A' for app, 'N' for net
    int priority;   
    int solicited;  // 1 if they have solicited domiciliary attention
};

struct customer customerList[20];

int appCustNum = 0;
int netCustNum = 0;
int domiciliarySolsNum = 0;

pthread_mutex_t mutexFile;
pthread_mutex_t mutexCustList;
pthread_mutex_t mutexSolicitudes;

pthread_cond_t condSolicitudes;

struct technician
{
    pid_t pid;
    char type;      // 'A' for app, 'N' for net
};

FILE logFile;