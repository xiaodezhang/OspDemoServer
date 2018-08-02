#include"osp.h"
#include"server.h"
#include"list.h"

#define MAKEESTATE(state,event) ((u32)((event)<< 4 +(state)))
#define MAX_USER_NAME_LENGTH           100
#define MAX_PASSWD_LENGTH              100
#define TEST_USER_NUM           5

#define USE_CONNECT_FLAG  0
#define SYS_LOG_LEVEL_REPEAT             0

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
        u32                    wClientId;     //从属客户端
}TFileList;

//已登录客户端表
typedef struct tagClientList{
        struct list_head       tListHead;
        u32                    wClientId;     //客户端node作为id
        s8                     chUserName[MAX_USER_NAME_LENGTH+1];
}TClientList;

typedef struct tagUserList{
        struct list_head       tListHead;
        s8                     chUserName[MAX_USER_NAME_LENGTH+1];
        s8                     chPasswd[MAX_PASSWD_LENGTH+1];
        u16                    level;   //定义用户权限
}TUserList;

typedef struct tagDemoInfo{
        u32                    srcid;
        u32                    srcnode;
        s8                     fileName[MAX_FILE_NAME_LENGTH];
}TDemoInfo;

static bool CheckSign(u32 wClientId,TClientList **tClient);
static bool CheckFileIn(LPCSTR filename,TFileList **tFile);
static CSInstance* GetPendingIns();


int main(){

#ifdef _MSC_VER
        int ret = OspInit(TRUE,2501,"WindowsOspServer");
#else
        int ret = OspInit(TRUE,2501,"LinuxOspServer");
#endif

        int i,j;

        printf("demo osp server\n");
        if(!ret){
                OspPrintf(1,0,"[main]osp init failed\n");
                printf("[main]osp init failed\n");
                OspQuit();
        }
        g_cCSApp.CreateApp("OspServerApp",SERVER_APP_ID,SERVER_APP_PRI,MAX_MSG_WAITING);
        ret = OspCreateTcpNode(0,OSP_AGENT_SERVER_PORT);

        if(INVALID_SOCKET == ret){
                OspPrintf(1,0,"[main]create positive node failed,quit\n");
                printf("[main]create positive node failed,quit\n");
                OspQuit();
                return -1;
        }
        //表初始化
        INIT_LIST_HEAD(&tClientList);
        INIT_LIST_HEAD(&tFileList);
        INIT_LIST_HEAD(&tUserList);

        //用户表init
        //TODO:使用配置文件的方式init

        TUserList *tUsers[TEST_USER_NUM];
        LPCSTR names[TEST_USER_NUM] = {"Robert","Michael","William","David","GG"};
        for(i = 0;i < TEST_USER_NUM;i++){
#if THREAD_SAFE_MALLOC
                tUsers[i] = (TUserList*)malloc(sizeof(TUserList));
#else
                tUsers[i] = new TUserList();
#endif
                if(!tUsers[i]){
                        for(j = 0;j < i;j++){
#if THREAD_SAFE_MALLOC
                                free(tUsers[j]);
#else
                                delete tUsers[j];
#endif
                        }
                        OspLog(LOG_LVL_ERROR,"[main]user malloc failed\n");
                        printf("[main]user malloc failed\n");
                        OspQuit();
                        return -1;
                }
                if(strlen(names[i]) > MAX_USER_NAME_LENGTH){
                        OspLog(LOG_LVL_ERROR,"[main]user name too long\n");
                        printf("[main]user name too long\n");
                        return -1;
                }
                strcpy(tUsers[i]->chUserName,names[i]);
                strcpy(tUsers[i]->chPasswd,"admin");
                list_add(&(tUsers[i]->tListHead),&tUserList);
        }


        while(1)
                OspDelay(100);

        for(i = 0;i < TEST_USER_NUM;i++){
#if THREAD_SAFE_MALLOC
                free(tUsers[i]);
#else
                delete tUsers[i];
#endif
        }
        OspQuit();
        return 0;
}

void CSInstance::InstanceEntry(CMessage * const pMsg){

#if USE_CONNECT_FLAG 
        if(!m_bConnectedFlag){
                 OspLog(LOG_LVL_ERROR,"[InstanceEntry]disconnected\n");
                 return;
        }
#endif
#if 0
        if(!CheckSign(pMsg->srcnode,NULL)){
                 OspLog(LOG_LVL_ERROR,"[InstanceEntry]not signed,sign in first\n");
                 return;
        }
#endif

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
                OspLog(LOG_LVL_ERROR,"[InstanceEntry] can not find the EState,event:%d\nstate:%d\n"
                                ,curEvent,curState);
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
                OspLog(LOG_LVL_ERROR,"[DaemonInstanceEntry] can not find the EState,event:%d\nstate:%d\n"
                                ,curEvent,curState);
                printf("[InstanceEntry] can not find the EState\n");
        }

}

void CSInstance::MsgProcessInit(){

       //Daemon Instance
        RegMsgProFun(MAKEESTATE(IDLE_STATE,SIGN_IN),&CSInstance::SignIn,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,SIGN_OUT),&CSInstance::SignOut,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,OSP_DISCONNECT),&CSInstance::DealDisconnect,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,FILE_RECEIVE_UPLOAD),&CSInstance::DaemonFileReceiveUpload
                        ,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,FILE_GO_ON),&CSInstance::FileGoOn,&m_tCmdDaemonChain);
        RegMsgProFun(MAKEESTATE(IDLE_STATE,FILE_STABLE_REMOVE),&CSInstance::FileStableRemove,&m_tCmdDaemonChain);


      //common Instance
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_UPLOAD_DEAL),&CSInstance::FileReceiveUpload,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_REMOVE),&CSInstance::ReceiveRemove,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_RECEIVE_CANCEL),&CSInstance::ReceiveCancel,&m_tCmdChain);

        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_UPLOAD),&CSInstance::FileUpload,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_FINISH),&CSInstance::FileFinish,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_CANCEL),&CSInstance::FileCancel,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_REMOVE),&CSInstance::FileRemove,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_GO_ON_DEAL),&CSInstance::FileGoOnDeal,&m_tCmdChain);
        RegMsgProFun(MAKEESTATE(RUNNING_STATE,FILE_STABLE_REMOVE_DEAL),&CSInstance::FileStableRemoveDeal,&m_tCmdChain);
}

void CSInstance::NodeChainEnd(){

        tCmdNode *tmpNode;

        while(m_tCmdChain){
                tmpNode = m_tCmdChain->next;
#if THREAD_SAFE_MALLOC
                free(m_tCmdChain);
#else
                delete m_tCmdChain;
#endif
                m_tCmdChain = tmpNode;
        }

        while(m_tCmdDaemonChain){
                tmpNode = m_tCmdChain->next;
#if THREAD_SAFE_MALLOC
                free(m_tCmdDaemonChain);
#else
                delete m_tCmdDaemonChain;
#endif
                m_tCmdDaemonChain = tmpNode;
        }
}

bool CSInstance::RegMsgProFun(u32 EventState,MsgProcess c_MsgProcess,tCmdNode** tppNodeChain){

        tCmdNode *Node,*NewNode,*LNode;

        Node = *tppNodeChain;

#if THREAD_SAFE_MALLOC
        if(!(NewNode = (tCmdNode*)malloc(sizeof(tCmdNode)))){
#else
        if(!(NewNode = new tCmdNode())){
#endif
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

        TFileList *tnFile;
        TDemoInfo tDemoInof;
        CSInstance *ins;

#if USE_CONNECT_FLAG 
        if(!m_bConnectedFlag){
                  OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]disconnected\n");
                  return;
        }
#endif

        if(!pMsg->content || pMsg->length <= 0){
                OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]file name is NULL\n");
                //TODO:通知客户端
                return;
        }

        if(pMsg->length > MAX_FILE_NAME_LENGTH-1 ||
                        pMsg->length <= 0 || !pMsg->content){
                OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload] file name error\n");
                //TODO:通知客户端
                return;
        }

        if(!CheckSign(pMsg->srcnode,NULL)){
                 OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]not signed,sign in first\n");
                //TODO:通知客户端
                 return;
        }

        //确认文件没有被其他Instance占用
        //TODO: 其他状态的确认
        if(CheckFileIn((LPCSTR)pMsg->content,&tnFile)){
                if(STATUS_FINISHED != tnFile->FileStatus 
                                && STATUS_REMOVED != tnFile->FileStatus){
                        OspLog(SYS_LOG_LEVEL,"[DaemonFileReceiveUpload]file being operated:%s\n",
                                        pMsg->content);
                        //TODO:通知客户端文件被其他任务占用
                        return;

                }else{

                        //TODO:同一用户操作
                        if(tnFile->wClientId != pMsg->srcnode){
                               OspLog(SYS_LOG_LEVEL,"[DaemonFileReceiveUpload]file being used by another client\n");

                        //TODO:通知客户端文件被其他客户端占用
                               return;
                        }
                }
        }

        if(access((LPCSTR)pMsg->content,F_OK) != -1){
                OspLog(SYS_LOG_LEVEL,"[DaemonFileReceiveUpload]file exists\n");
              //TODO:通知客户端文件已存在
#if 0
                return;
#endif
        }

       //查找空闲实例
       if(!(ins = GetPendingIns())){
                OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]no pending instance\n");
                return;
       }
       tDemoInof.srcid = pMsg->srcid;
       tDemoInof.srcnode = pMsg->srcnode;
       strcpy(tDemoInof.fileName,(LPCSTR)pMsg->content);

       //立刻指定非空闲，防止再被其他任务查询到
       ins->m_curState = RUNNING_STATE;
       ins->m_bSignInFlag = true;

       if(OSP_OK != post(MAKEIID(SERVER_APP_ID,ins->GetInsID()),FILE_RECEIVE_UPLOAD_DEAL
                               ,&tDemoInof,sizeof(TDemoInfo))){
               OspPrintf(1,0,"[DamonFileReceiveUpload]post to pending instance failed\n");
               printf("[DamonFileReceiveUpload]post to pending instance failed\n");
               //TODO：通知客户端
               return;
       }

        //加入文件表
       if(!tnFile){
               tnFile = new TFileList();
               if(!tnFile){
                    OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]file list malloc error\n");
                    return;
               }
               list_add(&tnFile->tListHead,&tFileList);
       }
       strcpy((LPSTR)tnFile->FileName,(LPCSTR)pMsg->content);
       tnFile->FileStatus = STATUS_RECEIVE_UPLOAD;
       tnFile->DealInstance = ins->GetInsID();
       tnFile->wClientId = pMsg->srcnode;
       if(!CheckFileIn((LPCSTR)tnFile->FileName,NULL)){
               OspLog(LOG_LVL_ERROR,"[DaemonFileReceiveUpload]file is not in list:%s\n",tnFile->FileName);
               return;
       }
       OspLog(SYS_LOG_LEVEL,"[DaemonFileRecevieUpload]daemon receive upload\n");

}

void CSInstance::FileReceiveUpload(CMessage* const pMsg){


        TFileList *tnFile;
        TDemoInfo *tDemoInof;

        tDemoInof = (TDemoInfo*)pMsg->content;
        strcpy(file_name_path,(LPCSTR)tDemoInof->fileName);

        if(!m_bSignInFlag){
                return;
        }

        if(!CheckFileIn((LPCSTR)file_name_path,&tnFile)){
                OspLog(LOG_LVL_ERROR,"[FileReceiveUpload]file is not in list:%s\n",file_name_path);
                return;
        }

#ifdef _LINUX_
        struct flock fl;
        if(INVALID_FILEHANDLE == (file = open((LPCSTR)file_name_path,O_WRONLY | O_CREAT))){
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

        emFileStatus = STATUS_UPLOADING;
        if(OSP_OK != post(tDemoInof->srcid,FILE_UPLOAD_ACK,&emFileStatus
              ,sizeof(emFileStatus),tDemoInof->srcnode)){
                OspPrintf(1,0,"[FileReceiveUpload]post back failed\n");
                printf("[FileReceiveUpload]post back failed\n");
                return;
        }
#if 0
        //文件注册
#if THREAD_SAFE_MALLOC
        tFile = (TFileList*)malloc(sizeof(TFileList));
#else
        tFile = new TFileList();
#endif
        if(!tFile){
                OspLog(LOG_LVL_ERROR,"[FileReceiveUpload]file list item malloc failed\n");
                //TODO:资源释放
                return;
        }
        strcpy((LPSTR)tFile->FileName,(LPCSTR)file_name_path);
        tFile->FileStatus = STATUS_RECEIVE_UPLOAD;
        tFile->DealInstance = GetInsID();
        list_add(&tFile->tListHead,&tFileList);

#endif
        emFileStatus = STATUS_UPLOADING;
        tnFile->FileStatus = STATUS_UPLOADING;
        OspLog(SYS_LOG_LEVEL,"[FileReceiveUpload]send upload ack\n");
}

void CSInstance::FileUpload(CMessage* const pMsg){

        if(!m_bSignInFlag){
                return;
        }
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
                     OspLog(LOG_LVL_ERROR,"[FileUpload]file upload write error\n");
                     //TODO:通知客户端
                     return;
             }
#elif defined _MSC_VER
#endif
     }
     //TODO:需要增加返回信息，为客户端文件传送进度显示做依据。
     printf("get files\n");
#if 0
     if(emFileStatus == STATUS_RECEIVE_UPLOAD){
        emFileStatus = STATUS_UPLOADING;
     }
#endif
     if(OSP_OK != post(pMsg->srcid,FILE_UPLOAD_ACK,&emFileStatus
           ,sizeof(emFileStatus),pMsg->srcnode)){
             OspPrintf(1,0,"[FileUpload]post back failed\n");
             return;
     }
//     OspLog(SYS_LOG_LEVEL_REPEAT,"[FileUpload]Get data,send upload ack\n");
}

void CSInstance::FileFinish(CMessage* const pMsg){


     TFileList* tFile;
     if(pMsg->content && pMsg->length > 0){
#if 0
             if(fwrite(pMsg->content,1,sizeof(s8)*pMsg->length,file)
                             != pMsg->length || ferror(file)){
                     OspLog(LOG_LVL_ERROR,"file upload write error\n");
                     NextState(IDLE_STATE);
                     if(fclose(file) == 0){
                             OspLog(SYS_LOG_LEVEL,"[FileFinish]file closed\n");

                     }else{
                             OspLog(LOG_LVL_ERROR,"[FileFinish]file close failed\n");
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
#if 0
     if(fclose(file) == 0){
             OspLog(SYS_LOG_LEVEL,"[FileFinish]file closed\n");

     }else{
             OspLog(LOG_LVL_ERROR,"[FileFinish]file close failed\n");
             //TODO：通知客户端
     }
#endif
#ifdef _LINUX_
     if(-1 == close(file)){//record locks removed
             OspLog(LOG_LVL_ERROR,"[FileFinish]file close failed\n");
             //get the errno
             //TODO：通知客户端
     }
     file = INVALID_FILEHANDLE;
     OspLog(SYS_LOG_LEVEL,"[FileFinish]file closed\n");
#elif defined _MSC_VER_
#endif
     if(!CheckFileIn((LPCSTR)file_name_path,&tFile)){
             OspLog(LOG_LVL_ERROR,"[FileFinish]file not in list\n");//客户端文件状态错误？
             //TODO:error deal
             return;
     }
     tFile->FileStatus = STATUS_FINISHED;
#if 0
     list_del(&tFile->tListHead);
#if THREAD_SAFE_MALLOC
     free(tFile);
#else
     delete tFile;
#endif

#endif

     if(OSP_OK != post(pMsg->srcid,FILE_FINISH_ACK,NULL
           ,0,pMsg->srcnode)){
             OspPrintf(1,0,"post back failed\n");
             printf("post back failed\n");
     }
     NextState(IDLE_STATE);
     emFileStatus = STATUS_FINISHED;

     OspLog(SYS_LOG_LEVEL,"[FileFinish]file finished\n");
}

void CSInstance::ReceiveCancel(CMessage* const pMsg){

        TFileList *tFile;

        if(!pMsg->content || pMsg->length<=0){
                OspLog(LOG_LVL_ERROR,"[ReceiveCancel]msg is NULL\n");
                return;
        }
        strcpy(file_name_path,(LPCSTR)pMsg->content);
        if(!CheckFileIn((LPCSTR)pMsg->content,&tFile)){
                OspLog(LOG_LVL_ERROR,"[ReceiveCancel]file not in list\n");
                //TODO:error deal
                //通知客户端
                return;
        }
        if(tFile->DealInstance != GetInsID()){
                OspLog(LOG_LVL_ERROR,"[ReceiveCancel]get error instance\n");
                //TODO:error deal
                //通知客户端
                return;
        }

        if(tFile->FileStatus == STATUS_RECEIVE_CANCEL){
               OspLog(SYS_LOG_LEVEL,"[ReceiveCancel]wait for cancelling\n");
               return;
        }

#if 0
        if(tFile->FileStatus >= STATUS_RECEIVE_UPLOAD &&
                        tFile->FileStatus <= STATUS_RECEIVE_REMOVE){
                if(OSP_OK != post(MAKEIID(GetAppID(),GetInsID()),FILE_RECEIVE_CANCEL
                               ,pMsg->content,pMsg->length)){
                        OspLog(LOG_LVL_ERROR,"[ReceiveCancel] post error\n");
                        return;
                }
        }
#endif
        if(tFile->FileStatus != STATUS_UPLOADING){
                 OspLog(LOG_LVL_ERROR,"[ReceiveCancel]file not uploading\n");
                 //通知客户端
                 return;
        }

        emFileStatus = STATUS_RECEIVE_CANCEL;
        tFile->FileStatus = STATUS_RECEIVE_CANCEL;
        OspLog(SYS_LOG_LEVEL,"[ReceiveCancel]receive cancel msg\n");
}

void CSInstance::ReceiveRemove(CMessage* const pMsg){

        TFileList *tFile;

        if(!pMsg->content || pMsg->length <= 0){
                OspLog(LOG_LVL_ERROR,"[ReceiveRemove]msg is NULL\n");
                return;
        }
        strcpy(file_name_path,(LPCSTR)pMsg->content);
        if(!CheckFileIn((LPCSTR)file_name_path,&tFile)){
                OspLog(LOG_LVL_ERROR,"[ReceiveRemove]file not in list\n");
                //TODO:error deal
                //通知客户端
                return;
        }
        if(tFile->DealInstance != GetInsID()){
                OspLog(LOG_LVL_ERROR,"[ReceiveRemove]get error instance\n");
                //TODO:error deal
                //通知客户端
                return;
        }

        if(tFile->FileStatus == STATUS_RECEIVE_REMOVE){
               OspLog(SYS_LOG_LEVEL,"[ReceiveRemove]wait for removing\n");
               return;
        }

#if 0
        if(tFile->FileStatus >= STATUS_RECEIVE_UPLOAD &&
                        tFile->FileStatus <= STATUS_RECEIVE_REMOVE){
                if(OSP_OK != post(MAKEIID(GetAppID(),GetInsID()),FILE_RECEIVE_REMOVE
                               ,pMsg->content,pMsg->length)){
                        OspLog(LOG_LVL_ERROR,"[ReceiveRemove] post error\n");
                        return;
                }
        }
#endif

        if(tFile->FileStatus != STATUS_UPLOADING){
                 OspLog(LOG_LVL_ERROR,"[ReceiveRemove]file not uploading\n");
                 //通知客户端
                 return;
        }

        tFile->FileStatus = STATUS_RECEIVE_REMOVE;
        emFileStatus = STATUS_RECEIVE_REMOVE;
        OspLog(SYS_LOG_LEVEL,"[ReceiveRemove]receive remove msg\n");
}


void CSInstance::FileGoOn(CMessage* const pMsg){

        CSInstance *ins;
        TDemoInfo tDemoInfo;
        TFileList *tnFile;

        if(!pMsg->content || pMsg->length <= 0){
                OspLog(LOG_LVL_ERROR,"[FileGoOn]file name is NULL\n");
                //TODO:通知客户端
                return;
        }

        if(pMsg->length > MAX_FILE_NAME_LENGTH-1 ||
                        pMsg->length <= 0 || !pMsg->content){
                OspLog(LOG_LVL_ERROR,"[FileGoOn] file name error\n");
                //TODO:通知客户端
                return;
        }

        if(!CheckSign(pMsg->srcnode,NULL)){
                 OspLog(LOG_LVL_ERROR,"[FileGoOn]not signed,sign in first\n");
                //TODO:通知客户端
                 return;
        }

        if(!CheckFileIn((LPCSTR)pMsg->content,&tnFile)){
                 OspLog(LOG_LVL_ERROR,"[FileGoOn]file is not in the list\n");
                 return;
        }

        if(tnFile->wClientId != pMsg->srcnode){
                 OspLog(LOG_LVL_ERROR,"[FileGoOn]file being used by another client\n");
                 return;
        }

        if(tnFile->FileStatus == STATUS_RECEIVE_GO_ON){
               OspLog(SYS_LOG_LEVEL,"[FileGoOn]wait for going on\n");
               return;
        }

#if 0
        if(tnFile->FileStatus >= STATUS_RECEIVE_UPLOAD &&
                        tnFile->FileStatus <= STATUS_RECEIVE_REMOVE){
                return;
                //TODO:msg node info need to be send
#if 0
                if(OSP_OK != post(MAKEIID(GetAppID(),GetInsID()),FILE_GO_ON
                               ,pMsg->content,pMsg->length)){
                        OspLog(LOG_LVL_ERROR,"[ReceiveCancel] post error\n");
                        return;
                }
#endif
        }

#endif
        if(tnFile->FileStatus != STATUS_CANCELLED){
                OspLog(LOG_LVL_ERROR,"[FileGoOn]file status error\n");
                //TODO:error deal
                return;
        
        }

        ins = GetPendingIns();
        if(!ins){
                 OspLog(LOG_LVL_ERROR,"[FileGoOn]no pending instance,wait...\n");
                 return;
        }

        tDemoInfo.srcid = pMsg->srcid;
        tDemoInfo.srcnode = pMsg->srcnode;
        strcpy((LPSTR)tDemoInfo.fileName,(LPCSTR)pMsg->content);
        ins->m_curState = RUNNING_STATE;
        ins->m_bSignInFlag = true;
        if(OSP_OK != post(MAKEIID(SERVER_APP_ID,ins->GetInsID()),FILE_GO_ON_DEAL
                                ,&tDemoInfo,sizeof(tDemoInfo))){
                OspPrintf(1,0,"[FileGoOn]post back failed\n");
                printf("[FileGoOn]post back failed\n");
                return;
        }
        tnFile->FileStatus = STATUS_RECEIVE_GO_ON;
        tnFile->DealInstance = ins->GetInsID();
        OspLog(SYS_LOG_LEVEL,"[FileGoOn]receive go on\n");
}

void CSInstance::FileGoOnDeal(CMessage* const pMsg){

#ifdef _LINUX_
     struct flock fl;
     TFileList *tFile;
     TDemoInfo *tDemoInfo;

     tDemoInfo = (TDemoInfo*)pMsg->content;

     if(!m_bSignInFlag){
             OspLog(LOG_LVL_ERROR,"[FileGoOnDeal]not sign in\n");
     }

     strcpy(file_name_path,(LPCSTR)tDemoInfo->fileName);
     if(!CheckFileIn((LPCSTR)tDemoInfo->fileName,&tFile)){
             OspLog(LOG_LVL_ERROR,"[FileGoOnDeal]file not in list\n");//客户端文件状态错误？
             //TODO:error deal
             return;
     }

     if(INVALID_FILEHANDLE == (file = open((LPCSTR)tDemoInfo->fileName,O_WRONLY | O_APPEND))){
             //TODO:通知客户端
             OspLog(LOG_LVL_ERROR,"[FileGoOnDeal]file open error\n");
             perror("[FileGoOnDeal]open file error\n");
             return;
     }
     fl.l_type = F_WRLCK;
     fl.l_whence = SEEK_SET;
     fl.l_start = 0;
     fl.l_len = 0; //specify 0:lock all bytes to the end of file,no matter how large
                 //the file grows
     if(fcntl(file,F_SETLK,&fl) == -1){
             if(errno == EACCES || errno == EAGAIN){//already locked
                     OspLog(LOG_LVL_ERROR,"[FileGoOnDeal]Already locked by anther process\n");
#if 0
                     if(OSP_OK != post(pMsg->srcid,FILE_LOCKED,NULL
                           ,0,pMsg->srcnode)){
                             OspPrintf(1,0,"post back failed\n");
                             printf("post back failed\n");
                     }
#endif
                     return;
             }else{
                     OspLog(LOG_LVL_ERROR,"[FileGoOnDeal]check file locking unexpected error\n");
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

        emFileStatus = STATUS_UPLOADING;
        if(OSP_OK != post(tDemoInfo->srcid,FILE_UPLOAD_ACK,&emFileStatus
              ,sizeof(emFileStatus),tDemoInfo->srcnode)){
                OspPrintf(1,0,"[FileGoOnDeal]post back failed\n");
                printf("[FileGoOnDeal]post back failed\n");
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

        tFile->FileStatus = STATUS_UPLOADING;
        NextState(RUNNING_STATE);
        OspLog(SYS_LOG_LEVEL,"[FileGoOnDeal]send upload ack\n");
}


void CSInstance::FileRemove(CMessage* const pMsg){

        TFileList* tFile;
        bool stableFlag = false;
#ifdef _LINUX_
        if(-1 == close(file)){//record locks removed
                OspLog(LOG_LVL_ERROR,"[FileRemove]file close failed\n");
                //get the errno
                //TODO：通知客户端
                return;
        }
        file = INVALID_FILEHANDLE;

        OspLog(SYS_LOG_LEVEL,"[FileRemove]file closed\n");
        if(unlink((LPCSTR)file_name_path) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileRemove]file removed\n");
                if(OSP_OK != post(pMsg->srcid,FILE_REMOVE_ACK
                                    ,&stableFlag,sizeof(stableFlag),pMsg->srcnode)){
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
        if(!CheckFileIn((LPCSTR)file_name_path,&tFile)){
                OspLog(LOG_LVL_ERROR,"[FileRemove]file not in list\n");//客户端文件状态错误？
                //TODO:error deal
                return;
        }
        emFileStatus = STATUS_REMOVED;
        tFile->FileStatus = STATUS_REMOVED;
#if 0
        list_del(&(tFile->tListHead));
#if THREAD_SAFE_MALLOC
        free(tFile);
#else
        delete tFile;
#endif
#endif

        NextState(IDLE_STATE);
        OspLog(SYS_LOG_LEVEL,"[FileRemove]file removed\n");
}

void CSInstance::FileStableRemoveDeal(CMessage* const pMsg){

        TFileList* tFile;
        bool stableFlag = true;
        TDemoInfo *tDemoInfo;

        tDemoInfo = (TDemoInfo*)pMsg->content;

        if(!m_bSignInFlag){
                OspLog(LOG_LVL_ERROR,"[FileStableRemoveDeal] not sign in\n");
        }

        strcpy((LPSTR)file_name_path,(LPCSTR)tDemoInfo->fileName);
#ifdef _LINUX_
        if(unlink((LPCSTR)file_name_path) == 0){
                OspLog(SYS_LOG_LEVEL,"[FileStableRemoveDeal]file removed\n");
                emFileStatus = STATUS_REMOVED;
                if(OSP_OK != post(tDemoInfo->srcid,FILE_REMOVE_ACK
                                    ,&stableFlag,sizeof(stableFlag),tDemoInfo->srcnode)){
                        OspPrintf(1,0,"[FileStableRemoveDeal]post back failed\n");
                        printf("[FileStableRemoveDeal]post back failed\n");
                }
        }else{
                OspLog(LOG_LVL_ERROR,"[FileStableRemoveDeal]file remove failed\n");
                //TODO：通知客户端
        }
#elif defined _MSC_VER_
#endif
        if(!CheckFileIn((LPCSTR)tDemoInfo->fileName,&tFile)){
                OspLog(LOG_LVL_ERROR,"[FileStableRemoveDeal]file not in list\n");//客户端文件状态错误？
                //TODO:error deal
                return;
        }
        tFile->FileStatus = STATUS_REMOVED;
#if 0
        list_del(&(tFile->tListHead));
#if THREAD_SAFE_MALLOC
        free(tFile);
#else
        delete tFile;
#endif
#endif
        NextState(IDLE_STATE);
        OspLog(SYS_LOG_LEVEL,"[FileStableRemoveDeal]file removed\n");
}

void CSInstance::FileStableRemove(CMessage* const pMsg){

        CSInstance *ins;
        TDemoInfo tDemoInfo;
        TFileList *tnFile;

        if(!pMsg->content || pMsg->length <= 0){
                OspLog(LOG_LVL_ERROR,"[FileStableRemove]file name is NULL\n");
                //TODO:通知客户端
                return;
        }

        if(pMsg->length > MAX_FILE_NAME_LENGTH-1 ||
                        pMsg->length <= 0 || !pMsg->content){
                OspLog(LOG_LVL_ERROR,"[FileStableRemove] file name error\n");
                //TODO:通知客户端
                return;
        }

        if(!CheckSign(pMsg->srcnode,NULL)){
                 OspLog(LOG_LVL_ERROR,"[FileStableRemove]not signed,sign in first\n");
                //TODO:通知客户端
                 return;
        }

        if(!CheckFileIn((LPCSTR)pMsg->content,&tnFile)){
                 OspLog(LOG_LVL_ERROR,"[FileStableRemove]file is not in the list\n");
                 return;
        }

        if(tnFile->wClientId != pMsg->srcnode){
                 OspLog(LOG_LVL_ERROR,"[FileStableRemove]file being used by another client\n");
                 return;
        }

        if(tnFile->FileStatus == STATUS_RECEIVE_REMOVE){
               OspLog(SYS_LOG_LEVEL,"[FileStableRemove]wait for going on\n");
               return;
        }

#if 0
        if(tnFile->FileStatus >= STATUS_RECEIVE_UPLOAD &&
                        tnFile->FileStatus <= STATUS_RECEIVE_REMOVE){
                return;
                //TODO:msg node info need to be send
#if 0
                if(OSP_OK != post(MAKEIID(GetAppID(),GetInsID()),FILE_STABLE_REMOVE
                               ,pMsg->content,pMsg->length)){
                        OspLog(LOG_LVL_ERROR,"[FileStableRemove] post error\n");
                        return;
                }
#endif
        }
#endif

        if(tnFile->FileStatus == STATUS_REMOVED){
               OspLog(SYS_LOG_LEVEL,"[FileStableRemove]file already removed\n");
               return;
        }

        if(tnFile->FileStatus != STATUS_CANCELLED 
                        && tnFile->FileStatus != STATUS_FINISHED){
                OspLog(LOG_LVL_ERROR,"[FileStableRemove]file status error\n");
                //TODO:error deal
                return;
        
        }

        ins = GetPendingIns();
        if(!ins){
                 OspLog(LOG_LVL_ERROR,"[FileStableRemove]no pending instance,wait...\n");
                 return;
        }

        tDemoInfo.srcid = pMsg->srcid;
        tDemoInfo.srcnode = pMsg->srcnode;
        strcpy((LPSTR)tDemoInfo.fileName,(LPCSTR)pMsg->content);

        ins->m_curState = RUNNING_STATE;
        ins->m_bSignInFlag = true;
        if(OSP_OK != post(MAKEIID(SERVER_APP_ID,ins->GetInsID()),FILE_STABLE_REMOVE_DEAL
                                ,&tDemoInfo,sizeof(tDemoInfo))){
                OspPrintf(1,0,"[FileStableRemove]post back failed\n");
                printf("[FileStableRemove]post back failed\n");
                return;
        }
        OspLog(SYS_LOG_LEVEL,"[FileStableRemove]receive stable remove\n");

}

void CSInstance::FileCancel(CMessage* const pMsg){

        TFileList* tFile;

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
        file = INVALID_FILEHANDLE;

        OspLog(SYS_LOG_LEVEL,"[FileCancel]file closed\n");
#elif defined _MSC_VER_
#endif

        if(!CheckFileIn((LPCSTR)file_name_path,&tFile)){
                OspLog(LOG_LVL_ERROR,"[FileCancel]file not in list,file name:%s\n"
                                ,file_name_path);//客户端文件状态错误？
                //TODO:error deal
                return;
        }

        if(OSP_OK != post(pMsg->srcid,FILE_CANCEL_ACK
                            ,&emFileStatus,sizeof(emFileStatus),pMsg->srcnode)){
                OspPrintf(1,0,"[FileCancel]post back failed\n");
                printf("[FileCancel]post back failed\n");
                //TODO:状态回收
                return;
        }
        tFile->FileStatus = STATUS_CANCELLED;
        emFileStatus = STATUS_CANCELLED;

        NextState(IDLE_STATE);
        OspLog(SYS_LOG_LEVEL,"[FileCancel]file cancelled\n");
}


void CSInstance::DealDisconnect(CMessage* const pMsg){

        //断开之后状态回收
        struct list_head *tClientHead,*tFileHead,*templist;
        TClientList *tnClient;
        TFileList *tnFile;
        u32 dwsrcnode;
        CSInstance *pIns;

        if(pMsg->length <= 0 || !pMsg->content){
                OspLog(LOG_LVL_ERROR,"[DealDisconnect]msg is NULL\n");
                return;
        }
        memcpy(&dwsrcnode,pMsg->content,pMsg->length);

        //删除文件表中相关文件，关闭文件描述符，释放instance
        list_for_each_safe(tFileHead,templist,&tFileList){
                tnFile = list_entry(tFileHead,TFileList,tListHead);
                if(tnFile->wClientId == dwsrcnode){
                       OspLog(SYS_LOG_LEVEL,"[DealDisconnect]del from file list:%s\n",tnFile->FileName);
                       pIns = (CSInstance*)((CApp*)&g_cCSApp)->GetInstance(tnFile->DealInstance);
                       if(!pIns){
                               OspLog(LOG_LVL_ERROR,"[DealDisconnect]get ins error\n");
                               continue;
                       }
                       if(pIns->file != INVALID_FILEHANDLE){
#if _LINUX_
                               if(-1 == close(file)){
                                        OspLog(LOG_LVL_ERROR,"[DealDisconnect]file close failed\n");
                                        perror("[DealDisconnect]:");
                               }
                               file = INVALID_FILEHANDLE;
#endif
                       }

                       if(!pIns){
                               OspLog(LOG_LVL_ERROR,"[DealDisconnect]get instance error\n");
                               return;
                       }
                       pIns->m_bSignInFlag = false;
                       pIns->m_curState = IDLE_STATE;
                       pIns->emFileStatus = STATUS_INIT;
                       list_del(&(tnFile->tListHead));
#if THREAD_SAFE_MALLOC
                       free(tnFile);
#else
                       delete tnFile;
#endif
                }
        }

        //删除客户端表中相关客户端
        list_for_each_safe(tClientHead,templist,&tClientList){
                tnClient = list_entry(tClientHead,TClientList,tListHead);
                if(tnClient->wClientId == dwsrcnode){
                       list_del(&(tnClient->tListHead));
#if THREAD_SAFE_MALLOC
                       free(tnClient);
#else
                       delete tnClient;
#endif
                }
        }
#if USE_CONNECT_FLAG 
        m_bConnectedFlag = false;
#endif

        //TODO：断点续传
        //去除断链注册
        if(OSP_OK != OspNodeDelDiscCB(dwsrcnode,SERVER_APP_ID,CInstance::DAEMON)){
               OspLog(LOG_LVL_ERROR,"[DealDisconnect]del discb failed\n");
               return;
        }

        //需要配合文件的关闭回收
        //m_wServerPort = SERVER_PORT;
        OspLog(SYS_LOG_LEVEL,"[DealDisconnect]disconnected\n");
}

static bool CheckSign(u32 wClientId,TClientList **tClient){

        struct list_head *tClientHead;
        TClientList *tnClient = NULL;
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
        TFileList *tnFile = NULL;
        bool inFileList = false;

        list_for_each(tFileHead,&tFileList){
                tnFile = list_entry(tFileHead,TFileList,tListHead);
                if(0 == strcmp((LPCSTR)tnFile->FileName,filename)){
                        inFileList = true;
                        break;
                }
        }
        if(tFile){
                *tFile = tnFile;
        }
        return inFileList;
}

static CSInstance* GetPendingIns(){

       u16 instCount;
       CSInstance* pIns;

       g_cCSApp.wLastIdleInstID %= MAX_INS_NUM;
	   instCount = g_cCSApp.wLastIdleInstID;
	   do{
               instCount++;
               pIns = (CSInstance*)((CApp*)&g_cCSApp)->GetInstance(instCount);
               if( pIns->CurState() == CInstance::PENDING ) {
                    break;
               }
               instCount %= MAX_INS_NUM;
	   } while( instCount != g_cCSApp.wLastIdleInstID );

	   if( instCount == g_cCSApp.wLastIdleInstID ){
               //TODO:通知客户端，没有找到空闲实例
               return NULL;
       }
	   g_cCSApp.wLastIdleInstID = instCount;
       return pIns;
}


void CSInstance::SignIn(CMessage *const pMsg){

       struct list_head *tUserHead,*tClientHead;
       TUserList *tnUser;
       TClientList *tnClient,*tClient;
       bool inUserList;
       u16 wClientAck = 0;

       if(!pMsg->content || pMsg->length <= 0){
               //通知客户端
                OspLog(LOG_LVL_ERROR,"[SignIn] pMsg is NULL\n");
                wClientAck = -1;
                goto post2client;
       }
       
       inUserList = false;
       //查找用户表
       list_for_each(tUserHead,&tUserList){
               tnUser = list_entry(tUserHead,TUserList,tListHead);
               if(0 == strcmp((LPCSTR)tnUser->chUserName,(LPCSTR)pMsg->content)){
                       //允许登陆
#if THREAD_SAFE_MALLOC
                       tClient = (TClientList*)malloc(sizeof(TClientList));
#else
                       tClient = new TClientList();
#endif
                       if(!tClient){
                            OspLog(LOG_LVL_ERROR,"[SignIn]client list malloc failed\n");
                            wClientAck = -2;
                            goto post2client;
                       }
                       //是否在客户端表中
                       if(!CheckSign(pMsg->srcnode,NULL)){
                               //插入客户端表
                               tClient->wClientId = pMsg->srcnode;
                               printf("srcnode:%d\ndstnode:%d\n",pMsg->srcnode,pMsg->dstnode);
                               list_add(&tClient->tListHead,&tClientList);
                       }
                       inUserList = true;
                       break;
               }
       }
       if(!inUserList){
               wClientAck = -3;
               OspLog(SYS_LOG_LEVEL,"[SignIn]sign in failed\n");
               goto post2client;
       }

#if USE_CONNECT_FLAG 
       m_bConnectedFlag = true;
#endif

        //断链注册
       if(OSP_OK !=OspNodeDiscCBRegQ(pMsg->srcnode,SERVER_APP_ID,CInstance::DAEMON)){
           OspLog(LOG_LVL_ERROR,"[SignIn]regis disconnect error\n");
           wClientAck = -4;
               goto post2client;
       }
       OspLog(SYS_LOG_LEVEL,"[SignIn]sign in\n");

post2client:
       if(OSP_OK != post(pMsg->srcid,SIGN_IN_ACK,&wClientAck,sizeof(wClientAck),pMsg->srcnode)){
               OspLog(SYS_LOG_LEVEL,"[SignIn]post back:%d\n",wClientAck);
       }
       return;
}

void CSInstance::SignOut(CMessage* const pMsg){

        TClientList* tClient;
        struct list_head *tFileHead,*templist;
        TFileList *tnFile;
        CSInstance *pIns;
        u16 wClientAck = 0;

#if USE_CONNECT_FLAG 
        if(!m_bConnectedFlag){
                  OspLog(LOG_LVL_ERROR,"[SignOut]disconnected\n");
                  return;
        }

#endif
        if(!CheckSign(pMsg->srcnode,&tClient)){
                 OspLog(LOG_LVL_ERROR,"[SignOut]not signed,sign in first\n");
                 wClientAck = -1;
                 goto post2client;
        }

        if(OSP_OK !=OspNodeDelDiscCB(pMsg->srcnode,SERVER_APP_ID,CInstance::DAEMON)){
                 OspLog(LOG_LVL_ERROR,"[SignOut]del discb failed\n");
        }

        list_for_each_safe(tFileHead,templist,&tFileList){
                tnFile = list_entry(tFileHead,TFileList,tListHead);
                if(tnFile->wClientId == pMsg->srcnode){
                       pIns = (CSInstance*)((CApp*)&g_cCSApp)->GetInstance(tnFile->DealInstance);
                       if(!pIns){
                               OspLog(LOG_LVL_ERROR,"[SignOut]get ins error\n");
                               continue;
                       }
                       if(tnFile->FileStatus == STATUS_UPLOADING){
                                tnFile->FileStatus = STATUS_CANCELLED;
//                                pIns->emFileStatus = STATUS_CANCELLED;
                                pIns->m_curState = IDLE_STATE;
                                if(INVALID_FILEHANDLE != pIns->file){
                                        if(close(pIns->file) == -1){
                                                OspLog(LOG_LVL_ERROR,"[SignOut]file close failed\n");
                                        }else{
                                                OspLog(SYS_LOG_LEVEL,"[SignOut]file closed\n");
                                        }
                                        file = INVALID_FILEHANDLE;
                                }
                                continue;
                        }

                        if(tnFile->FileStatus >= STATUS_CANCELLED)
                                continue;

                        tnFile->FileStatus = STATUS_INIT;
                        pIns->m_curState = IDLE_STATE;
                        pIns->emFileStatus = STATUS_INIT;
                        pIns->m_bSignInFlag = false;
                        if(pIns->file){
                                if(close(pIns->file) == -1){
                                        OspLog(LOG_LVL_ERROR,"[SignOut]file close failed\n");
                                }else{
                                        OspLog(SYS_LOG_LEVEL,"[SignOut]file closed\n");
                                }
                                pIns->file = INVALID_FILEHANDLE;
                        }
                }
        }

        list_del(&(tClient->tListHead));
#if THREAD_SAFE_MALLOC
        free(tClient);
#else
        delete tClient;
#endif
        OspLog(SYS_LOG_LEVEL,"[SignOut]sign out\n");

post2client:
        if(OSP_OK != post(pMsg->srcid,SIGN_OUT_ACK,&wClientAck
              ,sizeof(wClientAck),pMsg->srcnode)){
                OspPrintf(1,0,"[SignOut]post back failed\n");
        }
        return;
}

