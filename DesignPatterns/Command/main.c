#include "debug.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>

#define CAST_Command(pCmd)  (Command *) pCmd

typedef struct _Command Command;//Forward declare
struct _Command{
    unsigned int  id;
    void  (*execute)(Command *);
};

typedef void (*tFpCmdHandler)(Command *);

typedef struct _CommandC CommandC;//Forward declare
struct _CommandC{
    Command command;
    int Data_C;
};



typedef struct _Invoker{
    int     iAddCmd;
    Command *aCmd[10];
    void (*call)();
}Invoker;


void Invoker_call(Invoker *pInvoker) {
    __pBegin
    int i = 0;
    for(i = 0; i < 10; i++){
        if(pInvoker->aCmd[i] != NULL){
            print_err("aCmd[%d] != NULL\n", i);
            pInvoker->aCmd[i]->execute(pInvoker->aCmd[i]);
        }
    }
    __pEnd
}

void Invoker_init(Invoker *pInvoker){
    __pBegin
    pInvoker->iAddCmd   = 0;
    pInvoker->call      = Invoker_call;
    int i;    
    for(i=0; i < 10; i++){
        pInvoker->aCmd[i] = NULL;
    }
    __pEnd
}
void Invoker_addCmd(Invoker *pInvoker, Command *pCmd){
    __pBegin
    print_dbg("pCmd = 0x%x\n", pCmd);
    pInvoker->aCmd[pInvoker->iAddCmd++] = pCmd;
    __pEnd
}

void CommandA_execute(Command *pCmd){
    print_dbg("CommandA_execute\n");
    print_dbg("id = %d\n", pCmd->id);
}
void CommandB_execute(Command *pCmd){
    print_dbg("CommandB_execute\n"); 
    print_dbg("id = %d\n", pCmd->id);
}
void CommandC_execute(CommandC *pCmd){
    print_dbg("CommandC_execute\n"); 
    print_dbg("id       = %d\n", pCmd->command.id);
    print_dbg("Data_C   = %d\n", pCmd->Data_C);
    
}

// void Command_setHandle(Command *pCommandA, void (*handler)(Command *)){
void Command_setHandle(Command *pCommandA, tFpCmdHandler handler){
    pCommandA->execute = handler;
}
int main(int argc, char const *argv[])
{
    Command *pCommandA  = (Command *)malloc(sizeof(Command));
    Command_setHandle(pCommandA,CommandA_execute);
    pCommandA->id = 1;
    
    Command *pCommandB  = (Command *)malloc(sizeof(Command));
    Command_setHandle(pCommandB, CommandB_execute);
    pCommandB->id = 2;
    
    CommandC *pCommandC  = (CommandC *)malloc(sizeof(CommandC));
    Command_setHandle(pCommandC, (tFpCmdHandler)CommandC_execute);
    pCommandC->command.id = 3;
    pCommandC->Data_C = 1111;
    
    Invoker *pInvoker = (Invoker *)malloc(sizeof(Invoker));
    Invoker_init(pInvoker);
   
    /* 
     * TODO: here to add cmd */
    Invoker_addCmd(pInvoker, pCommandA); 
    Invoker_addCmd(pInvoker, pCommandB); 
    Invoker_addCmd(pInvoker, CAST_Command(pCommandC)); 
    
    Invoker_call(pInvoker);
    
    
    return 0;
}