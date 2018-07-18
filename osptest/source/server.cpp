#include"osp.h"
#include"server.h"

#define MAKEESTATE(state,event) ((u32)(event<< 4 +state))

CSApp g_cCSApp;

s8 buffer[BUFFER_SIZE];
int main(){

#ifdef _MSC_VER
        int ret = OspInit(TRUE,2500,"WindowsOspServer");
#else
        int ret = OspInit(TRUE,2500,"LinuxOspServer");
#endif

        printf("demo osp server\n");
        if(!ret){
                OspPrintf(1,0,"osp init fail\n");
        }
        g_cCSApp.CreateApp("OspServerApp",SERVER_APP_ID,SERVER_APP_PRI,MAX_MSG_WAITING);
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
        MsgProcess c_MsgProcess;


        if(FindProcess(MAKEESTATE(curState,curEvent),&c_MsgProcess,m_tCmdChain)){
                (this->*c_MsgProcess)(pMsg);
        }else{
                OspLog(LOG_LVL_ERROR,"[InstanceEntry] can not find the EState\n");
                printf("[InstanceEntry] can not find the EState\n");
        }

}

void CSInstance::DaemonInstanceEntry(CMessage *const pMsg,CApp *pCApp){

        if(NULL == pMsg){
                OspLog(LOG_LVL_ERROR,"[InstanceEntry] pMsg is NULL\n");
        }

        u32 curState = CurState();
        u16 curEvent = pMsg->event;
        MsgProcess c_MsgProcess;


        if(FindProcess(MAKEESTATE(curState,curEvent),&c_MsgProcess,m_tCmdDaemonChain)){
                (this->*c_MsgProcess)(pMsg);
        }else{
                OspLog(LOG_LVL_ERROR,"[InstanceEntry] can not find the EState\n");
                printf("[InstanceEntry] can not find the EState\n");
        }

}

bool CSInstance::CheckAuthorization(TSinInfo *tSinInfo,u32 dwLen){

        if(!tSinInfo || dwLen <=0 ){
                OspPrintf(1,0,"no sign info\n");
                return false;
        }

        if(0 == strcmp(g_tSinInfo.g_Username,tSinInfo->g_Username)
                        && 0 == strcmp(g_tSinInfo.g_Passwd,tSinInfo->g_Passwd)){
                OspLog(SYS_LOG_LEVEL,"user authorized\n");
                OspPrintf(1,0,"user authorized\n");
                return true;
        }else{
                OspPrintf(1,0,"username:%s\npassword:%s\n",g_tSinInfo.g_Username,g_tSinInfo.g_Passwd);
                OspLog(SYS_LOG_LEVEL,"user not authorized\n");
                OspPrintf(1,0,"user not authorized\n");
                return false;
        }
}


void CSInstance::MsgProcessInit(){

       //Daemon Instance
        RegMsgProFun(MAKEESTATE(IDLE_STATE,SIGN_IN),&CSInstance::SignIn,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,SIGN_OUT),&CSInstance::SignOut,&m_tCmdDaemonChain);


      //common Instance
        RegMsgProFun(MAKEESTATE(IDLE_STATE,FILE_NAME_SEND),&CSInstance::FileNameSend,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_UPLOAD),&CSInstance::FileUpload,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_FINISH),&CSInstance::FileFinish,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_CANCEL),&CSInstance::FileCancel,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_REMOVE),&CSInstance::FileRemove,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_REMOVE),&CSInstance::ReceiveRemove,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_CANCEL),&CSInstance::ReceiveCancel,&m_tCmdChain);
}

void CSInstance::NodeChainEnd(){

        while(m_tCmdChain){
                free(m_tCmdChain);
                m_tCmdChain = m_tCmdChain->next;
        }

        while(m_tCmdDaemonChain){
                free(m_tCmdDaemonChain);
                m_tCmdDaemonChain = m_tCmdDaemonChain->next;
        }
}

bool CSInstance::RegMsgProFun(u32 EventState,MsgProcess c_MsgProcess,tCmdNode** tppNodeChain){

        tCmdNode *Node,*NewNode,*LNode;

        Node = *tppNodeChain;

        if(!(NewNode = (tCmdNode*)malloc(sizeof(tCmdNode)))){
                OspLog(LOG_LVL_ERROR,"[RegMsgProFun] node malloc error\n");
                return false;
        }

        NewNode->EventState = EventState;
        NewNode->c_MsgProcess = c_MsgProcess;
        NewNode->next = NULL;

        if(!Node){
                *tppNodeChain = NewNode;
                OspLog(SYS_LOG_LEVEL,"cmd chain init \n");
                return true;
        }

        while(Node){
                if(Node->EventState == EventState){
                        OspLog(LOG_LVL_ERROR,"[RegMsgProFun] node already in \n");
                        printf("[RegMsgProFun] node already in \n");
                        return false;
                }
                LNode = Node;
                Node = Node->next;
        }
        LNode->next = NewNode;

        return true;
}

bool CSInstance::FindProcess(u32 EventState,MsgProcess* c_MsgProcess,tCmdNode* tNodeChain){

        tCmdNode *Node;

        Node = tNodeChain;
        if(!Node){
                OspLog(LOG_LVL_ERROR,"[FindProcess] Node Chain is NULL\n");
                printf("[FindProcess] Node Chain is NULL\n");
                return false;
        }
        while(Node){

                if(Node->EventState == EventState){
                        *c_MsgProcess = Node->c_MsgProcess;
                        return true;
                }
                Node = Node->next;
        }

        return false;
}

void CSInstance::SignIn(CMessage *const pcMsg){

       if(!pcMsg->content || pcMsg->length <= 0){
               //通知客户端
                OspLog(LOG_LVL_ERROR,"[SignIn] pMsg is NULL\n");
                return;
       }
      //TODO:客户端状态维护
       if(CheckAuthorization((TSinInfo*)pcMsg->content,pcMsg->length)){
               if(OSP_OK != post(pcMsg->srcid,SIGN_IN_ACK,"succeed"
                     ,strlen("succeed")+1,pcMsg->srcnode)){
                       OspPrintf(1,0,"post back failed\n");
                       printf("post back failed\n");
               }
               OspLog(SYS_LOG_LEVEL,"sign in\n");
               OspPrintf(1,1,"sign in\n");
       }else{
               if(OSP_OK != post(pcMsg->srcid,SIGN_IN_ACK,"failed"
                                       ,strlen("failed")+1,pcMsg->srcnode)){
                       OspPrintf(1,0,"post back failed\n");
                       printf("post back failed\n");
               }
               OspLog(SYS_LOG_LEVEL,"sign in failed\n");
               OspPrintf(1,1,"sign in failed\n");
       }
}

void CSInstance::SignOut(CMessage* const pcMsg){

      //TODO:客户端状态维护
      if(OSP_OK != post(pcMsg->srcid,SIGN_OUT_ACK,NULL
            ,0,pcMsg->srcnode)){
              OspPrintf(1,0,"post back failed\n");
              printf("post back failed\n");
      }
      OspLog(SYS_LOG_LEVEL,"sign out\n");
      OspPrintf(1,1,"sign out\n");
}

void CSInstance::FileNameSend(CMessage* const pMsg){

     if(!pMsg->content || pMsg->length <= 0){
             OspLog(LOG_LVL_ERROR,"[FileNameSend]file name is NULL\n");
             //TODO:通知客户端
             return;
     }
     if(strlen((LPCSTR)pMsg->content)+1 != pMsg->length){
         OspLog(LOG_LVL_ERROR,"[FileNameSend]file name error\n");
             //TODO:通知客户端
             return;
     }
     if(pMsg->length > MAX_FILE_NAME_LENGTH-1 ||
                     pMsg->length <= 0 || !pMsg->content){
             OspLog(LOG_LVL_ERROR,"[InstanceEntry] file name error\n");
             //TODO:通知客户端
             return;
     }

     memcpy(file_name_path,pMsg->content,pMsg->length);
     if(!(file = fopen((LPCSTR)pMsg->content,"wb"))){
             //TODO:通知客户端
             OspLog(LOG_LVL_ERROR,"file open error\n");
             printf("open file error\n");
             return;
     }

     if(OSP_OK != post(pMsg->srcid,FILE_NAME_ACK,NULL
           ,0,pMsg->srcnode)){
             OspPrintf(1,0,"post back failed\n");
             printf("post back failed\n");
     }

     NextState(RUNNING_STATE);
     printf("file name send\n");
}


void CSInstance::FileUpload(CMessage* const pMsg){

     //TODO:增加缓冲
     if(pMsg->content && pMsg->length > 0){
             if(fwrite(pMsg->content,1,sizeof(s8)*pMsg->length,file)
                             != pMsg->length || ferror(file)){
                     OspLog(LOG_LVL_ERROR,"file upload write error\n");
                     //TODO:通知客户端
                     return;
             };
     }
     //TODO:需要增加返回信息，为客户端文件传送进度显示做依据。
     printf("get files\n");
     if(OSP_OK != post(pMsg->srcid,FILE_NAME_ACK,&emFileStatus
           ,sizeof(emFileStatus),pMsg->srcnode)){
             OspPrintf(1,0,"post back failed\n");
             printf("post back failed\n");
     }

}

void CSInstance::FileRemove(CMessage* const pMsg){

        if(emFileStatus < CANCELED){
                if(fclose(file) == 0){
                        OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");

                }else{
                        OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
                        //TODO：通知客户端
                        return;
                }
        }
#ifdef _LINUX_
        if(unlink((LPCSTR)file_name_path) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileRemove]file removed\n");
                if(OSP_OK != post(pMsg->srcid,FILE_REMOVE_ACK,"succeed"
                      ,strlen("succeed")+1,pMsg->srcnode)){
                        OspPrintf(1,0,"post back failed\n");
                        printf("post back failed\n");
                }
        }else{
                OspLog(LOG_LVL_ERROR,"[FileRemove]file remove failed\n");
                //TODO：通知客户端
        }
#endif
}
void CSInstance::ReceiveCancel(CMessage* const pMsg){

        emFileStatus = RECEIVE_CANCEL;
}

void CSInstance::ReceiveRemove(CMessage* const pMsg){

        emFileStatus = RECEIVE_REMOVE;
}

void CSInstance::FileCancel(CMessage* const pMsg){

        //保存为临时文件，
        if(fclose(file) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");

        }else{
                OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
                //TODO：通知客户端
                return;
        }
        emFileStatus = CANCELED;
}

void CSInstance::FileFinish(CMessage* const pMsg){

     if(pMsg->content && pMsg->length > 0){
             if(fwrite(pMsg->content,1,sizeof(s8)*pMsg->length,file)
                             != pMsg->length || ferror(file)){
                     OspLog(LOG_LVL_ERROR,"file upload write error\n");
                     NextState(IDLE_STATE);
                     if(fclose(file) == 0){
                             OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");

                     }else{
                             OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
                             //TODO：通知客户端
                     }
                     //TODO:通知客户端
                     return;
             }
     }
     OspLog(SYS_LOG_LEVEL,"file finished\n");
     if(fclose(file) == 0){
             OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");

     }else{
             OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
             //TODO：通知客户端
     }
     if(OSP_OK != post(pMsg->srcid,FILE_FINISH_ACK,NULL
           ,0,pMsg->srcnode)){
             OspPrintf(1,0,"post back failed\n");
             printf("post back failed\n");
     }
     NextState(IDLE_STATE);
     emFileStatus = FINISHED;
}
