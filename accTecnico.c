#include "globalVariables.c"

//principal function 
void *accTecnico(struct technician tech){
    techAction(tech);
}

//selects the acction to perform according to the tipe of the received technician
void techAction(struct technician tech){
    if (tech.type == 'A'){
        appTech();
    }else{
        netTech();
    }
}


