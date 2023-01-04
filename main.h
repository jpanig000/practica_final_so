                                                            //Main
void declareHandlers();
void newClientApp(int sig);
void newClientNetwork(int sig);
                                                            //nuevoCliente
void finish(int sig);
void nuevoCliente(char type);
                                                            //accCliente
void *accCliente(void *ptr);
int clientNotAttended(int numClient, int secondPassed);
void clientAttending(int numClient);
void clientAttendedAndNetClient(int numClient);
void clientDomiciliaryRequests(int numClient);
void clientExit(int numClient, char* reason);
void clearClient(int numClient);
                                                            //accTecnico
void *accEncargado();
void manAction();
                                                            //accEncargado
void *accTecnico(struct technician tech);
void techAction(struct technician tech);

#include "globalVariables.c"
#include "accCliente.c"
#include "nuevoCliente.c"
