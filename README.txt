Para la compilación del programa es necesario ejecutar el siguiente comando en el directorio 
gcc -o main main.c -lpthread
Una vez compilado la siguiente instrucción ejecuta el programa
Donde args1 y args2 deben ser enteros y corresponden a el número máximo de clientes y el número de técnicos de tipo app (no es necesario introducir parametros)
./main args1 args2

El proceso responde a las siguientes señales:
SIGUSR1: añade un cliente de tipo app
SIGUSR2: añade un cliente de tipo red 

SIGPIPE: permite aumentar el tamaño de la lista de clientes 
SIGQUIT: permite añadir técnicos de tipo app hasta el número especificado

SIGINT: finaliza el proceso de forma ordenada. No permite añadir más clientes, atiende a los restantes,  envia al técnico de atención domiciliaria y termina.
