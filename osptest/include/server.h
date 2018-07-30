#include"osp.h"
#include"commondemo.h"

#ifdef _LINUX_

#include<unistd.h>
#include<fcntl.h>

#elif defined _MSC_VER

#include<Fileapi.h>

#endif

#ifdef _LINUX_

#define FILEHANDLE                    int
#define INVALID_FILEHANDLE            -1

#elif defined _MSC_VER

#define FILEHANDLE_INIT               HANDLE
#define INVALID_FILEHANDLE            INVALID_HANDLE_VALUE

#endif

#define OSP_AGENT_SERVER_PORT              20000

#define RUNNING_STATE                      1
#define IDLE_STATE                         0
#define EV_CLIENT_TEST_BGN                (u16)0x1111
#define SERVER_CONNECT_TEST               (EV_CLIENT_TEST_BGN+1)
#define AUTHORIZATION_NAME_SIZE            20

#define BUFFER_SIZE                       (u16)(MAX_MSG_LEN / 2)
#define MAX_FILE_NAME_LENGTH               200

#define FILE_RECEIVE_REMOVE               (EV_CLIENT_TEST_BGN+17)
#define FILE_RECEIVE_CANCEL               (EV_CLIENT_TEST_BGN+18)
#define FILE_REMOVE_ACK                   (EV_CLIENT_TEST_BGN+19)
#define FILE_CANCEL_ACK                   (EV_CLIENT_TEST_BGN+20)

#define FILE_GO_ON                        (EV_CLIENT_TEST_BGN+24)
#define FILE_GO_ON_ACK                    (EV_CLIENT_TEST_BGN+25)
#define FILE_LOCKED                       (EV_CLIENT_TEST_BGN+26)

#define FILE_STABLE_REMOVE                (EV_CLIENT_TEST_BGN+27)
//#define FILE_STABLE_REMOVE_ACK            (EV_CLIENT_TEST_BGN+28)


#define FILE_RECEIVE_UPLOAD_DEAL          (EV_CLIENT_TEST_BGN+31)

#define FILE_GO_ON_DEAL                   (EV_CLIENT_TEST_BGN+41)

#define FILE_STABLE_REMOVE_DEAL           (EV_CLIENT_TEST_BGN+43)



const u8 SERVER_APP_PRI                  = 80;
const u32 MAX_MSG_WAITING                = 512;

typedef struct tagSinInfo{
        s8 g_Username[AUTHORIZATION_NAME_SIZE];
        s8 g_Passwd[AUTHORIZATION_NAME_SIZE];
}TSinInfo;

typedef enum tagEM_FILE_STATUS{
                STATUS_INIT             = -1,
                //processing state
                STATUS_SEND_UPLOAD       = 0,
                STATUS_SEND_CANCEL      = 1,
                STATUS_SEND_REMOVE      = 2,
                STATUS_RECEIVE_UPLOAD   = 3,
                STATUS_RECEIVE_CANCEL   = 4,
                STATUS_RECEIVE_REMOVE   = 5,
                //stable state
                STATUS_UPLOADING        = 6,
                STATUS_CANCELLED        = 7,
                STATUS_REMOVED          = 8,
                STATUS_FINISHED         = 9 
}EM_FILE_STATUS;


class CSInstance : public CInstance{

public:
        typedef void (CSInstance::*MsgProcess)(CMessage *const pMsg); 
private:
        void DaemonInstanceEntry(CMessage *const pcMsg,CApp *pCApp);
        void InstanceEntry(CMessage *const);
        bool CheckAuthorization(TSinInfo *tSinInfo,u32 dwLen);
private:
        typedef struct tagCmdNode{
        u32         EventState;
        CSInstance::MsgProcess  c_MsgProcess;
        struct      tagCmdNode *next;
        }tCmdNode;


        EM_FILE_STATUS emFileStatus;

        TSinInfo g_tSinInfo;
//        FILE *file;
        FILEHANDLE file;
        tCmdNode *m_tCmdChain;
        tCmdNode *m_tCmdDaemonChain;
        s8       file_name_path[MAX_FILE_NAME_LENGTH];
        bool     m_bConnectedFlag;
        bool     m_bSignFlag;
        u32      m_dwDisInsID;
public:
        CSInstance():file(INVALID_FILEHANDLE),emFileStatus(STATUS_INIT)
                     ,m_tCmdChain(NULL),m_tCmdDaemonChain(NULL)
                     ,m_bConnectedFlag(false)
                     ,m_bSignFlag(false){
                strcpy((LPSTR)g_tSinInfo.g_Username,"admin");
                strcpy((LPSTR)g_tSinInfo.g_Passwd,"admin");
                memset(file_name_path,0,sizeof(u8)*MAX_FILE_NAME_LENGTH);
                MsgProcessInit();
        };
        ~CSInstance(){
                NodeChainEnd();
        }
        void MsgProcessInit();
        void NodeChainEnd();
        bool RegMsgProFun(u32,MsgProcess,tCmdNode**);
        bool FindProcess(u32,MsgProcess*,tCmdNode*);

        //注册处理函数
        void SignIn(CMessage* const);
        void SignOut(CMessage* const);
        void FileReceiveUpload(CMessage* const);
        void FileUpload(CMessage* const);
        void FileFinish(CMessage* const);
        void FileRemove(CMessage* const);
        void FileCancel(CMessage* const);
        void ReceiveRemove(CMessage* const);
        void ReceiveCancel(CMessage* const);
        void FileGoOn(CMessage* const);
        void FileStableRemove(CMessage* const);

        void notifyConnected(CMessage* const);
        void DaemonFileReceiveUpload(CMessage*const);
        void FileGoOnDeal(CMessage*const);
        void FileStableRemoveDeal(CMessage*const);

        //断链检测处理函数
        void DealDisconnect(CMessage* const);

};

typedef zTemplate<CSInstance,MAX_INS_NUM,CAppNoData,MAX_ALIAS_LENGTH> CSApp;
