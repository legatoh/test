#include <winsock2.h>
#include "game.h"

int Connect(){
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        return ERROR_CON;
    }
    else{

    }
}
