#include "/home/codeleaded/System/Static/Library/CStr.h"
#include "/home/codeleaded/System/Static/Library/Networking_Event.h"


#define NET_EVENT_MSG  (NET_EVENT_START + 0)

void Net_EventClient_Proc_Connect(void* parent,Net_EventClient* c,Net_EventPackage* p){
    printf("[Net_EventServer]: Connect -> %d\n",(uint32_t)Net_Client_Id(&c->client));
    Net_EventClient_Send(c,NET_EVENT_CONNECT,NULL,0);
}
void Net_EventClient_Proc_Disconnect(void* parent,Net_EventClient* c,Net_EventPackage* p){
    printf("[Net_EventServer]: Disconnect -> %d\n",(uint32_t)Net_Client_Id(&c->client));
    Net_EventClient_Send(c,NET_EVENT_DISCONNECT,NULL,0);
}
void Net_EventClient_Proc_Msg(void* parent,Net_EventClient* c,Net_EventPackage* p){
    printf("[Net_EventServer]: Msg -> %u: '%s' (%u)\n",(uint32_t)Net_Client_Id(&c->client),(char*)p->pack.data,(uint32_t)p->pack.size);
}

char running = 1;
void* Net_EventClient_Recver(Net_EventClient* c){
    while(running){
        Net_EventClient_Update(c);
        Net_EventClient_DoAll(c,NULL);
        Thread_Sleep_M(NET_SERVER_DELAY);
    }
    return NULL;
}

int main(){
    Net_EventClient s = Net_EventClient_Make("5000","192.168.2.99",(Net_EventHandler[]){
        Net_EventHandler_New(NET_EVENT_CONNECT,     Net_EventClient_Proc_Connect),
        Net_EventHandler_New(NET_EVENT_DISCONNECT,  Net_EventClient_Proc_Disconnect),
        Net_EventHandler_New(NET_EVENT_MSG,         Net_EventClient_Proc_Msg),
        Net_EventHandler_Null()
    });

    Thread recver = Thread_New(NULL,(void*(*)(void*))Net_EventClient_Recver,&s);
    Thread_Start(&recver);

    while(running){
        char buffer[1024];
        int size = scanf("%1023s",buffer);
        
        if(CStr_Cmp(buffer,"exit")){
            running = 0;
        }else{
            Net_EventClient_Send(&s,NET_EVENT_MSG,buffer,CStr_Size(buffer) + 1);
            Thread_Sleep_M(100);
        }
    }
    
    Thread_Join(&recver);
    Net_EventClient_Free(&s);
    return 0;
}