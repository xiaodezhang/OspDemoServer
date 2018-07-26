#include"osp.h"
#include"server.h"
#include"list.h"

#define MAKEESTATE(state,event) ((u32)((event)<< 4 +(state)))
#define MAX_USER_NAME_LENGTH           100
#define TEST_USER_NUM           5


CSApp g_cCSApp;

s8 buffer[BUFFER_SIZE];

struct list_head tClientList; //客户端表，一个node一个客户端
struct list_head tFileList;   //文件表
struct list_head tUserList;   //用户表

typedef struct tagFileList{
        struct list_head       tListHead;
        u8                     FileName[MAX_FILE_NAME_LENGTH];
        EM_FILE_STATUS         FileStatus;
        u16                    DealInstance;
}TFileList;

typedef struct tagClientList{
        struct list_head       tListHead;
        u16                    wClientId;   //客户端node作为id
        bool                   wSignFlag;
}TClientList;

typedef struct tagUserList{
        struct list_head       tListHead;
        s8                     chUserName[MAX_USER_NAME_LENGTH+1];
        u16                    level;   //定义用户权限
}TUserList;


static bool CheckSign(u16 wClientId,TClientList **tClient);
static bool CheckFileIn(LPCSTR filename,TFileList **tFile);


int main(){

#ifdef _MSC_VER
        int ret = OspInit(TRUE,2500,"WindowsOspServer");
#else
        int ret = OspInit(TRUE,2500,"LinuxOspServer");
#endif

        int i,j;

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
        INIT_LIST_HEAD(&tClientList);
        INIT_LIST_HEAD(&tFileList);
        INIT_LIST_HEAD(&tUserList);

        //用户表init
        //TODO:使用配置文件的方式init

        TUserList *tUsers[TEST_USER_NUM];
        LPCSTR names[TEST_USER_NUM] = {"Robert","Michael","William","David","GG"};
        for(i = 0;i < TEST_USER_NUM;i++){
                tUsers[i] = (TUserList*)malloc(sizeof(TUserList));
                if(!tUsers[i]){
                        for(j = 0;j < i;j++){
                                free(tUsers[j]);
                        }
                        OspLog(LOG_LVL_ERROR,"[main]user malloc failed\n");
                        OspQuit();
                        return -1;
                }
                if(strlen(names[i]) > MAX_USER_NAME_LENGTH){
                        OspLog(LOG_LVL_ERROR,"[main]user name too long\n");
                        return -1;
                }
                strcpy(tUsers[i]->chUserName,names[i]);
                list_add(&(tUsers[i]->tListHead),&tUserList);
        }
        while(1)
                OspDelay(100);

        for(i = 0;i < TEST_USER_NUM;i++){
                free(tUsers[i]);
        }
        OspQuit();
        return 0;
}

void CSInstance::InstanceEntry(CMessage * const pMsg){

        if(!m_bConnectedFlag){
                 OspLog(LOG_LVL_ERROR,"[InstanceEntry]disconnected\n");
                 return;
        }

        if(!CheckSign(pMsg->srcid,NULL)){
                 OspLog(LOG_LVL_ERROR,"[InstanceEntry]not signed,sign in first\n");
                 return;
        }

        if(NULL == pMsg){
                OspLog(LOG_LVL_ERROR,"[InstanceEntry]Msg is NULL\n");
                return;
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
                return;
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

void CSInstance::MsgProcessInit(){

       //Daemon Instance
        RegMsgProFun(MAKEESTATE(IDLE_STATE,SIGN_IN),&CSInstance::SignIn,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,SIGN_OUT),&CSInstance::SignOut,&m_tCmdDaemonChain);

        RegMsgProFun(MAKEESTATE(IDLE_STATE,OSP_DISCONNECT),&CCInstance::DealDisconnect,&m_tCmdDaemonChain);

        RegMsgProFun(MAKEESTATE(IDLE_STATE,FILE_RECEIVE_UPLOAD),&CSInstance::DaemonFileReceiveUpload
                        ,&m_tCmdDaemonChain);
      //common Instance
        RegMsgProFun(MAKEESTATE(IDLE_STATE,FILE_RECEIVE_UPLOAD_DEAL),&CSInstance::FileReceiveUpload,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_REMOVE),&CSInstance::ReceiveRemove,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_CANCEL),&CSInstance::ReceiveCancel,&m_tCmdChain);

        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_UPLOAD),&CSInstance::FileUpload,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_FINISH),&CSInstance::FileFinish,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_CANCEL),&CSInstance::FileCancel,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_REMOVE),&CSInstance::FileRemove,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_GO_ON),&CSInstance::FileGoOn,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_STABLE_REMOVE),&CSInstance::FileStableRemove,&m_tCmdChain);
}

void CSInstance::NodeChainEnd(){

        tCmdNode *NextNode;

        while(m_tCmdChain){
                NextNode = m_tCmdChain->next;
                free(m_tCmdChain);
                m_tCmdChain = NextNode;
        }

        while(m_tCmdDaemonChain){
                NextNode = m_tCmdDaemonChain->next;
                free(m_tCmdDaemonChain);
                m_tCmdDaemonChain = NextNode;
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

void CSInstance::DaemonFileReceiveUpload(CMessage* const pMsg){

        u16 instCount;
        CSInstance* pIns;
        struct list_head *tFileHead;
        TFileList *tnFile;
        bool inFileList = false;

        if(!m_bConnectedFlag){
                  OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]disconnected\n");
                  return;
        }

        if(!pMsg->content || pMsg->length <= 0){
                OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]file name is NULL\n");
                //TODO:通知客户端
                return;
        }
        if(strlen((LPCSTR)pMsg->content)+1 != pMsg->length){
            OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]file name error\n");
                //TODO:通知客户端
                return;
        }
        if(pMsg->length > MAX_FILE_NAME_LENGTH-1 ||
                        pMsg->length <= 0 || !pMsg->content){
                OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload] file name error\n");
                //TODO:通知客户端
                return;
        }

        if(!CheckSign(pcMsg->srcid,NULL)){
                 OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]not signed,sign in first\n");
                //TODO:通知客户端
                 return;
        }

        //确认文件没有被其他Instance占用
        list_for_each(tFileHead,&tFileList){
                tnFile = list_entry(tClientHead,TFileList,tListHead);
                if(0 == strcmp(tnFile->FileName,pMsg->content)){
                        inFileList = true;
                        break;
                }
        }

        //TODO: 其他状态的确认
        if(inFileList && STATUS_INIT != tnFile->FileStatus){
                OspLog(SYS_LOG_LEVEL,"[DaemonFileReceiveUpload]file being used\n");
                //TODO:通知客户端文件被占用
                return;
        }

        if(access((LPCSTR)pMsg->content,F_OK) != -1){
                OspLog(SYS_LOG_LEVEL,"[DaemonFileReceiveUpload]file exists\n");
              //TODO:通知客户端文件已存在
                return;
        }

       //查找空闲实例
       g_cCSApp->wLastIdleInstID %= g_cCSApp->GetInstanceNumber();
	   instCount = g_cCSApp->wLastIdleInstID;
	   do{
               instCount++;
               pIns = g_cCSApp->GetInstance(instCount);
               if( pIns->CurState() == PENDING ) {
                    break;
               }
               instCount %= g_cCSApp->GetInstanceNumber();
	   } while( instCount != g_cCSApp->wLastIdleInstID );

	   if( instCount == g_cCSApp->wLastIdleInstID ){
               //TODO:通知客户端，没有找到空闲实例
               return;
       }
	   g_cCSApp->wLastIdleInstID = instCount;
       if(OSP_OK != post(MAKEIID(SERVER_APP_ID,instCount),FILE_RECEIVE_UPLOAD
                               ,pMsg->content ,pMsg->length)){
               OspPrintf(1,0,"[DamonFileReceiveUpload]post to pending instance failed\n");
               printf("[DamonFileReceiveUpload]post to pending instance failed\n");
               //TODO：通知客户端
               return;
       }
}

void CSInstance::SignIn(CMessage *const pcMsg){

       struct list_head *tUserHead,*tClientHead;
       TUserList *tnUser;
       TClientList *tnClient,*tClient;
       bool inClientList,inUserList;

       if(!pcMsg->content || pcMsg->length <= 0){
               //通知客户端
                OspLog(LOG_LVL_ERROR,"[SignIn] pMsg is NULL\n");
                return;
       }

       inClientList = false;
       inUserList = false;
       //查找用户表
       list_for_each(tUserHead,&tUserList){
               tnUser = list_entry(tUserHead,TUserList,tListHead);
               if(0 == strcmp(tnUser->chUserName,pcMsg->content)){
                       //允许登陆
                       tClient = (TClientList*)malloc(sizeof(TClientList));
                       if(!TClientList){
                            OspLog(LOG_LVL_ERROR,"[SignIn]client list malloc failed\n");
                            return;
                       }
                       //是否在客户端表中
                       if(!CheckSign(pcMsg->srcid,NULL)){
                               //插入客户端表
                               tClient->wClientId = pcMsg->srcid;
                               list_add(&tClient->tListHead,&tClientList);
                       }
                       inUserList = true;
                       break;
               }
       }
       if(inUserList){
               if(OSP_OK != post(pcMsg->srcid,SIGN_IN_ACK,"succeed"
                                     ,strlen("succeed")+1,pcMsg->srcnode)){
                       OspPrintf(1,0,"[SignIn]post back failed\n");
                       printf("[SignIn]post back failed\n");
                       return;
               }
       }else{
               if(OSP_OK != post(pcMsg->srcid,SIGN_IN_ACK,"failed"
                                       ,strlen("failed")+1,pcMsg->srcnode)){
                       //TODO:error deal
                       OspPrintf(1,0,"[SignIn]post back failed\n");
                       printf("[SignIn]post back failed\n");
               }
               OspLog(SYS_LOG_LEVEL,"[SignIn]sign in failed\n");
               return;
       }
       m_bConnectedFlag = true;
       OspLog(SYS_LOG_LEVEL,"[SignIn]sign in\n");
}

void CSInstance::SignOut(CMessage* const pcMsg){

        TClientList* tClient;

        if(!m_bConnectedFlag){
                  OspLog(LOG_LVL_ERROR,"[SignOut]disconnected\n");
                  return;
        }

        if(!CheckSign(pcMsg->srcid,&tClient)){
                 OspLog(LOG_LVL_ERROR,"[SignOut]not signed,sign in first\n");
                 return;
        }

        if(OSP_OK != post(pcMsg->srcid,SIGN_OUT_ACK,NULL
              ,0,pcMsg->srcnode)){
                OspPrintf(1,0,"[SignOut]post back failed\n");
                printf("[SignOut]post back failed\n");
                return;
        }

        list_del(&tClient->tListHead);
        free(tClient);
        OspLog(SYS_LOG_LEVEL,"[SignOut]sign out\n");
}

void CSInstance::FileReceiveUpload(CMessage* const pMsg){

        TFileList *tFile;
#ifdef _LINUX_
        struct flock fl;
#endif
        memcpy(file_name_path,pMsg->content,pMsg->length);
#ifdef _LINUX_
        if(INVALID_FILEHANDLE == (file = open((LPCSTR)pMsg->content,O_WRONLY | O_CREAT))){
                //TODO:通知客户端,get the errno
                OspLog(LOG_LVL_ERROR,"[FileReceiveUpload]file open error\n");
                perror("[FileReceiveUpload]open file error\n");
                return;
        }
        fl.l_type = F_WRLCK;
        fl.l_whence = SEEK_SET;
        fl.l_start = 0;
        fl.l_len = 0; //specify 0:lock all bytes to the end of file,no matter how large
                    //the file grows
        if(fcntl(file,F_SETLK,&fl) == -1){
                if(errno == EACCES || errno == EAGAIN){//already locked
                        OspLog(LOG_LVL_ERROR,"[FileReceiveUpload]Already locked by anther process\n");
                        if(OSP_OK != post(pMsg->srcid,FILE_LOCKED,NULL
                              ,0,pMsg->srcnode)){
                                OspPrintf(1,0,"[FileReceiveUpload]post back failed\n");
                                printf("[FileReceiveUpload]post back failed\n");
                        }
                        return;
                }else{
                        OspLog(LOG_LVL_ERROR,"[FileReceiveUpload]check file locking unexpected error\n");
#if 0
                        //通知客户端
                        if(OSP_OK != post(pMsg->srcid,FILE_LOCKING_ERROR,NULL
                              ,0,pMsg->srcnode)){
                                OspPrintf(1,0,"post back failed\n");
                                printf("post back failed\n");
                        }
#endif
                        return;

                }
        }
#elif defined _MSC_VER
#endif

        if(OSP_OK != post(pMsg->srcid,FILE_RECEIVE_UPLOAD_ACK,NULL
              ,0,pMsg->srcnode)){
                OspPrintf(1,0,"[FileReceiveUpload]post back failed\n");
                printf("[FileReceiveUpload]post back failed\n");
                //TODO:资源释放
                return;
        }
        //TODO：文件注册

        tFile = (TFileList*)malloc(sizeof(TFileList));
        if(!tFileList){
                OspLog(LOG_LVL_ERROR,"[FileReceiveUpload]file malloc failed\n");
                //TODO:资源释放
                return;
        }
        strcmp(tFileList->FileName,pMsg->content);
        tFileList->FileStatus = STATUS_RECEIVE_UPLOAD;
        tFileList->DealInstance = GetInsID();
        list_add(&tFile->tListHead,&tFileList);

        NextState(RUNNING_STATE);
        emFileStatus = STATUS_RECEIVE_UPLOAD;
        printf("[FileReceiveUpload]file name send\n");
}

void CSInstance::FileUpload(CMessage* const pMsg){

     //TODO:增加缓冲
     if(pMsg->content && pMsg->length > 0){
#if 0
             if(fwrite(pMsg->content,1,sizeof(s8)*pMsg->length,file)
                             != pMsg->length || ferror(file)){
                     OspLog(LOG_LVL_ERROR,"file upload write error\n");
                     //TODO:通知客户端
                     return;
             };
#endif
#ifdef _LINUX_
             if(-1 == write(file,pMsg->content,sizeof(s8)*pMsg->length)){
                     //TODO:print errno
                     OspLog(LOG_LVL_ERROR,"file upload write error\n");
                     //TODO:通知客户端
                     return;
             }
#elif defined _MSC_VER
#endif
     }
     //TODO:需要增加返回信息，为客户端文件传送进度显示做依据。
     printf("get files\n");
     if(emFileStatus == STATUS_RECEIVE_UPLOAD){
        emFileStatus = STATUS_UPLOADING;
     }
     if(OSP_OK != post(pMsg->srcid,FILE_UPLOAD_ACK,&emFileStatus
           ,sizeof(emFileStatus),pMsg->srcnode)){
             OspPrintf(1,0,"post back failed\n");
             printf("post back failed\n");
     }
}

void CSInstance::ReceiveCancel(CMessage* const pMsg){

        OspLog(SYS_LOG_LEVEL,"[ReceiveCancel]receive cancel msg\n");
        emFileStatus = STATUS_RECEIVE_CANCEL;
}

void CSInstance::ReceiveRemove(CMessage* const pMsg){

        OspLog(SYS_LOG_LEVEL,"[ReceiveRemove]receive remove msg\n");
        emFileStatus = STATUS_RECEIVE_REMOVE;
}

void CSInstance::FileGoOn(CMessage* const pMsg){

#ifdef _LINUX_

     struct flock fl;
     if(INVALID_FILEHANDLE == (file = open((LPCSTR)file_name_path,O_WRONLY | O_APPEND))){
             //TODO:通知客户端
             OspLog(LOG_LVL_ERROR,"file open error\n");
             perror("open file error\n");
             return;
     }
     fl.l_type = F_WRLCK;
     fl.l_whence = SEEK_SET;
     fl.l_start = 0;
     fl.l_len = 0; //specify 0:lock all bytes to the end of file,no matter how large
                 //the file grows
     if(fcntl(file,F_SETLK,&fl) == -1){
             if(errno == EACCES || errno == EAGAIN){//already locked
                     OspLog(LOG_LVL_ERROR,"Already locked by anther process\n");
                     if(OSP_OK != post(pMsg->srcid,FILE_LOCKED,NULL
                           ,0,pMsg->srcnode)){
                             OspPrintf(1,0,"post back failed\n");
                             printf("post back failed\n");
                     }
                     return;
             }else{
                     perror("FileGoOn\n");
                     OspLog(LOG_LVL_ERROR,"[FileGoOn]check file locking unexpected error\n");
#if 0
                     //通知客户端
                     if(OSP_OK != post(pMsg->srcid,FILE_LOCKING_ERROR,NULL
                           ,0,pMsg->srcnode)){
                             OspPrintf(1,0,"post back failed\n");
                             printf("post back failed\n");
                     }
#endif
                     return;

             }
     }
#elif defined _MSC_VER
#endif

        if(OSP_OK != post(pMsg->srcid,FILE_GO_ON_ACK,NULL
              ,0,pMsg->srcnode)){
                OspPrintf(1,0,"post back failed\n");
                printf("post back failed\n");
                return;
        }
#if 0
        if(!(file = fopen((LPCSTR)file_name_path,"ab"))){
                //TODO:通知客户端
                OspLog(LOG_LVL_ERROR,"file open error\n");
                printf("open file error\n");
                return;
        }
#endif

        emFileStatus = STATUS_UPLOADING;
}

void CSInstance::FileRemove(CMessage* const pMsg){

        TFileList* tFile;
#ifdef _LINUX_
        if(-1 == close(file)){//record locks removed
                OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
                //get the errno
                //TODO：通知客户端
                return;
        }
        OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");
        if(unlink((LPCSTR)file_name_path) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileRemove]file removed\n");
                if(OSP_OK != post(pMsg->srcid,FILE_REMOVE_ACK
                                    ,NULL,0,pMsg->srcnode)){
                        OspPrintf(1,0,"[FileRemove]post back failed\n");
                        printf("[FileRemove]post back failed\n");
                }
        }else{
                OspLog(LOG_LVL_ERROR,"[FileRemove]file remove failed\n");
                //TODO：通知客户端
                return;
        }

#elif defined _MSC_VER_
#endif
        if(!CheckFileIn(file_name_path,&tFile)){
                OspLog(LOG_LVL_ERROR,"[FileRemove]file not in list\n");//客户端文件状态错误？
                //TODO:error deal
                return;
        }
        emFileStatus = STATUS_REMOVED;
        list_del(&tFile->tListHead);
        free(tFile);
        NextState(IDLE_STATE);
}

void CSInstance::FileStableRemove(CMessage* const pMsg){

        TFileList* tFile;

#ifdef _LINUX_
        if(unlink((LPCSTR)file_name_path) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileRemove]file removed\n");
                emFileStatus = STATUS_REMOVED;
                if(OSP_OK != post(pMsg->srcid,FILE_STABLE_REMOVE_ACK
                                    ,NULL,0,pMsg->srcnode)){
                        OspPrintf(1,0,"[FileRemove]post back failed\n");
                        printf("[FileRemove]post back failed\n");
                }
        }else{
                OspLog(LOG_LVL_ERROR,"[FileRemove]file remove failed\n");
                //TODO：通知客户端
        }
#elif defined _MSC_VER_
#endif
        if(!CheckFileIn(file_name_path,&tFile)){
                OspLog(LOG_LVL_ERROR,"[FileRemove]file not in list\n");//客户端文件状态错误？
                //TODO:error deal
                return;
        }
        list_del(&tFile->tListHead);
        free(tFile);

        NextState(IDLE_STATE);
}

void CSInstance::FileCancel(CMessage* const pMsg){

        //保存为临时文件，
#if 0
        if(fclose(file) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileCancel]file closed\n");

        }else{
                OspLog(LOG_LVL_ERROR,"[FileCancel]file close failed\n");
                //TODO：通知客户端
                return;
        }
#endif
#ifdef _LINUX_
     if(-1 == close(file)){//record locks removed
             OspLog(LOG_LVL_ERROR,"[FileCancel]file close failed\n");
             //get the errno
             //TODO：通知客户端
             return;
     }
     OspLog(SYS_LOG_LEVEL,"[FileCancel]file closed\n");
#elif defined _MSC_VER_
#endif

        emFileStatus = STATUS_CANCELLED;
        if(OSP_OK != post(pMsg->srcid,FILE_CANCEL_ACK
                            ,&emFileStatus,sizeof(emFileStatus),pMsg->srcnode)){
                OspPrintf(1,0,"[FileCancel]post back failed\n");
                printf("[FileCancel]post back failed\n");
        }
}

void CSInstance::FileFinish(CMessage* const pMsg){

     if(pMsg->content && pMsg->length > 0){
#if 0
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
#endif
#ifdef _LINUX_
             if(-1 == write(file,pMsg->content,sizeof(s8)*pMsg->length)){
                     //TODO:print errno
                     OspLog(LOG_LVL_ERROR,"[FileFinish] write error\n");
                     NextState(IDLE_STATE);
                     //TODO:close file
                     //TODO:通知客户端
                     return;
             }
#elif defined _MSC_VER
#endif

     }
     OspLog(SYS_LOG_LEVEL,"file finished\n");
#if 0
     if(fclose(file) == 0){
             OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");

     }else{
             OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
             //TODO：通知客户端
     }
#endif
#ifdef _LINUX_
     if(-1 == close(file)){//record locks removed
             OspLog(LOG_LVL_ERROR,"[FileFinish]file close failed\n");
             //get the errno
             //TODO：通知客户端
             return;
     }
     OspLog(SYS_LOG_LEVEL,"[FileFinish]file closed\n");
#elif defined _MSC_VER_
#endif
     if(OSP_OK != post(pMsg->srcid,FILE_FINISH_ACK,NULL
           ,0,pMsg->srcnode)){
             OspPrintf(1,0,"post back failed\n");
             printf("post back failed\n");
     }
     NextState(IDLE_STATE);
     emFileStatus = STATUS_FINISHED;
}

void CCInstance::DealDisconnect(CMessage* const pMsg){

#if 1
        struct list_head *tClientHead;
        TClientList *tnClient;

        //TODO:断开之后状态需要回收
        list_for_each(tClientHead,&tClientList){
                tnClient = list_entry(tClientHead,TClientList,tListHead);
                free(tnClient);
        }
        m_bConnectedFlag = false;

        //TODO：断点续传
        if(file){
                if(fclose(file) == 0){
                        OspLog(SYS_LOG_LEVEL,"[FileRemovelAck]file closed\n");
                        file = NULL;
                }else{
                        OspLog(LOG_LVL_ERROR,"[FileRemoveAck]file close failed\n");
                        return;
                }
        }
        //需要配合文件的关闭回收
        emFileStatus = STATUS_INIT;
        NextState(IDLE_STATE);
        m_dwDisInsID = 0;
        m_wFileSize = 0;
        m_wUploadFileSize = 0;
        //m_wServerPort = SERVER_PORT;
        OspLog(SYS_LOG_LEVEL,"[DealDisconnect]disconnected\n");
#endif

}

static bool CheckSign(u16 wClientId,TClientList **tClient){

        struct list_head *tClientHead;
        TClientList *tnClient;
        bool inClientList = false;

        list_for_each(tClientHead,&tClientList){
                tnClient = list_entry(tClientHead,TClientList,tListHead);
                if(tnClient->wClientId == wClientId){
                        inClientList = true;
                        break;
                }
        }
        if(tClient){
                *tClient = tnClient;
        }
        return inClientList;
}

static bool CheckFileIn(LPCSTR filename,TFileList **tFile){

        struct list_head *tFileHead;
        TFileList *tnFile;
        bool inFileList = false;

        list_for_each(tFileHead,&tFileList){
                tnFile = list_entry(tFileHea,TFileList,tListHead);
                if(0 == strcmp(tnFile->FileName,filename)){
                        inFileList = true;
                        break;
                }
        }
        if(tFile){
                *tFile = tnFile;
        }
        return inFileList;
}
