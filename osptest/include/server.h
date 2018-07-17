#include"osp.h"
#include"commondemo.h"

#define OSP_AGENT_SERVER_PORT 20000

#define RUNNING_STATE         1
#define IDLE_STATE            0
#define EV_CLIENT_TEST_BGN           (u16)0x1111
#define SERVER_CONNECT_TEST          (EV_CLIENT_TEST_BGN+1)
#define AUTHORIZATION_NAME_SIZE      20

#define BUFFER_SIZE                  MAX_MSG_LEN
#define MAX_FILE_NAME_LENGTH         200

const u8 SERVER_APP_PRI    =            80;
const u32 MAX_MSG_WAITING  =            512;

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

        TSinInfo g_tSinInfo;
        u8      FileName[MAX_FILE_NAME_LENGTH];
        FILE *file;
        tCmdNode *m_tCmdChain;
        tCmdNode *m_tCmdDaemonChain;

public:
        CSInstance():file(NULL)
                     ,m_tCmdChain(NULL),m_tCmdDaemonChain(NULL){
                strcpy((char*)g_tSinInfo.g_Username,"admin");
                strcpy((char*)g_tSinInfo.g_Passwd,"admin");
                memset(FileName,0,sizeof(u8)*MAX_FILE_NAME_LENGTH);
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

};

typedef zTemplate<CSInstance,MAX_INS_NUM,CAppNoData,MAX_ALIAS_LENGTH> CSApp;
