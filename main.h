void newClientApp(int sig);
void newClientNetwork(int sig);
void finish(int sig);
void nuevoCliente(char type);
void *accCliente(void *ptr);
int clientNotAttended(int numClient, int secondPassed);
void clientAttending(int numClient);
void clientAttendedAndNetClient(int numClient);
void clientDomiciliaryRequests(int numClient);
void clientExit(int numClient, char* reason);
void clearClient(int numClient);
void declareHandlers();

#include "globalVariables.c"
#include "accCliente.c"
#include "nuevoCliente.c"
