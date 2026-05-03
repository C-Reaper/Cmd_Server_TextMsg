#include "/home/codeleaded/System/Static/Library/CStr.h"
#include "/home/codeleaded/System/Static/Library/Networking.h"


#define SIGNAL_MSG  (SIGNAL_START + 0)

void Server_Proc_Connect(void* parent,Signal s,Client* c,void* data,PackageSize size){
    printf("Server_Connect: %d\n",c->sockfd);
}
void Server_Proc_Disconnect(void* parent,Signal s,Client* c,void* data,PackageSize size){
    printf("Server_Disconnect: %d\n",c->sockfd);
}
void Server_Proc_Msg(void* parent,Signal s,Client* c,void* data,PackageSize size){
    printf("Server_Msg: %d -> '%s' (%d)\n",c->sockfd,(char*)data,size);
}

int main(){
    Server s = Server_Make(5000,10,(SignalHandler[]){
        SignalHandler_New(SIGNAL_CONNECT,(void (*)(void*,Signal,void*,void*,PackageSize))Server_Proc_Connect),
        SignalHandler_New(SIGNAL_DISCONNECT,(void (*)(void*,Signal,void*,void*,PackageSize))Server_Proc_Disconnect),
        SignalHandler_New(SIGNAL_MSG,(void (*)(void*,Signal,void*,void*,PackageSize))Server_Proc_Msg),
        SignalHandler_Null()
    });

    Server_Start_C(&s);
    Server_Start_R(&s);
    //Server_Wait(&s);

    while(1){
        char buffer[1024];
        int size = scanf("%1023s",buffer);
        if(CStr_Cmp(buffer,"exit")) break;
        
        Server_Signal_Send(&s,SIGNAL_MSG,buffer,CStr_Size(buffer) + 1);

        Thread_Sleep_M(1000);
    }

    Server_Free(&s);
    return 0;
}
