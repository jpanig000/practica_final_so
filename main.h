/*
*   Grupo 16
*
*   Alicia Gómez Pascual
*   Julián Paniagua González
*   Rubén Fernández González
*   Sergio González Rebollo
*/
 
#include "globalVariables.c"

//Main
void declareHandlers();
void newClientApp(int sig);
void newClientNetwork(int sig);
int calculaAleatorio(int min, int max);
void changeCustomerList();
void addAppTechs();
                                
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
void *accTecnico(void *tech);
void techAction(struct technician tech);

//accTecDom
void *accTecnicoDomiciliario();
void tecDom();

//writeLog
void writeLog(char *id, char *msg);


#include "accCliente.c"
#include "nuevoCliente.c"
#include "writeLog.c"
#include "accTecnico.c"
#include "accEncargado.c"
#include "accTecDom.c"


