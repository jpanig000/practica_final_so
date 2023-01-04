                                                            //Main
void declareHandlers();
void newClientApp(int sig);
void newClientNetwork(int sig);
                                                            //nuevoCliente
void finish(int sig);
void nuevoCliente(char type);
                                                            //accCliente
void *accCliente(void *ptr);
void nameClient(int numClient, char nombre[]);
int clientNotAttended(int numClient, int secondPassed);
void clientAttending(int numClient);
void clientAttendedAndNetClient(int numClient);
void clientDomiciliaryRequests(int numClient);
void clientExit(int numClient, char* reason);
void clearClient(int numClient);
                                                            //accEncargado
void *accEncargado();
void manAction();
                                                            //accTecnico
void *accTecnico(struct technician tech);
void techAction(struct technician tech);
                                                            //accTecDom
void *accTecnicoDomiciliario();
void tecDom();
                                                            //writeLog
void writeLog(char *id, char *msg);

#include "globalVariables.c"
#include "accCliente.c"
#include "nuevoCliente.c"
#include "writeLog.c"
#include "accTecnico.c"
#include "accEncargado.c"
#include "accTecDom.c"


