#include"osp.h"
#include"server.h"

int main(){

#ifdef _MSC_VER
        int ret = OspInit(TRUE,0,"WindowsOspServer");
#else
        int ret = OspInit(TRUE,0,"LinuxOspServer");
#endif

        if(!ret){
                OspPrintf(1,0,"osp init fail\n");
        }
        ret = OspCreateTcpNode(0,OSP_AGENT_SERVER_PORT);

        if(INVALID_SOCKET == ret){
                OspPrintf(1,0,"create positive node failed,quit\n");
                OspQuit();
                return -1;
        }
        while(1)
                OspDelay(100);

        OspQuit();
        return 0;
}

void CSInstance::InstanceEntry(CMessage * const pMsg){

        if(NULL == pMsg){
                OspLog(LOG_LVL_ERROR,"[InstanceEntry] pMsg is NULL\n");
        }

        u32 curState = CurState();
        u16 curEvent = pMsg->event;

        switch(curState){
                case IDLE_STATE:
                        break;
                case RUNNING_STATE:
                        break;
                default:
                        break;
        }

        OspPrintf(1,0,"instance entry\n");
}
