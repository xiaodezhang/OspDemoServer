#include"osp.h"
#include"commondemo.h"
#ifdef _LINUX_
#include<unistd.h>
#endif

#define OSP_AGENT_SERVER_PORT              20000

#define RUNNING_STATE                      1
#define IDLE_STATE                         0
#define EV_CLIENT_TEST_BGN                (u16)0x1111
#define SERVER_CONNECT_TEST               (EV_CLIENT_TEST_BGN+1)
#define AUTHORIZATION_NAME_SIZE            20

#define BUFFER_SIZE                       (u16)(MAX_MSG_LEN >> 1)
#define MAX_FILE_NAME_LENGTH               200

#define FILE_RECEIVE_REMOVE               (EV_CLIENT_TEST_BGN+17)
#define FILE_RECEIVE_CANCEL               (EV_CLIENT_TEST_BGN+18)
#define FILE_REMOVE_ACK                   (EV_CLIENT_TEST_BGN+19)
#define FILE_CANCEL_ACK                   (EV_CLIENT_TEST_BGN+20)

#define FILE_GO_ON                        (EV_CLIENT_TEST_BGN+24)
#define FILE_GO_ON_ACK                    (EV_CLIENT_TEST_BGN+25)


const u8 SERVER_APP_PRI                  = 80;
const u32 MAX_MSG_WAITING                = 512;

typedef struct tagSinInfo{
        s8 g_Username[AUTHORIZATION_NAME_SIZE];
        s8 g_Passwd[AUTHORIZATION_NAME_SIZE];
}TSinInfo;

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

        typedef enum tagEM_FILE_STATUS{
                GO_ON_SEND       = 0,
                RECEIVE_CANCEL   = 1,
                RECEIVE_REMOVE   = 2,
                CANCELED         = 3,
                REMOVED          = 4,
                FINISHED         = 5
        }EM_FILE_STATUS;

        EM_FILE_STATUS emFileStatus;

        TSinInfo g_tSinInfo;
        FILE *file;
        tCmdNode *m_tCmdChain;
        tCmdNode *m_tCmdDaemonChain;
        u8       file_name_path[MAX_FILE_NAME_LENGTH];

public:
        CSInstance():file(NULL),emFileStatus(GO_ON_SEND)
                     ,m_tCmdChain(NULL),m_tCmdDaemonChain(NULL){
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
        void FileNameSend(CMessage* const);
        void FileUpload(CMessage* const);
        void FileFinish(CMessage* const);
        void FileRemove(CMessage* const);
        void FileCancel(CMessage* const);
        void ReceiveRemove(CMessage* const);
        void ReceiveCancel(CMessage* const);
        void FileGoOn(CMessage* const);

};

typedef zTemplate<CSInstance,MAX_INS_NUM,CAppNoData,MAX_ALIAS_LENGTH> CSApp;
