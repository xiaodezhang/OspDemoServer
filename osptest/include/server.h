#include"osp.h"
#include"commondemo.h"

#define OSP_AGENT_SERVER_PORT 20000

#define RUNNING_STATE         1
#define IDLE_STATE            0
#define EV_CLIENT_TEST_BGN           (u16)0x1111
#define SERVER_CONNECT_TEST          (EV_CLIENT_TEST_BGN+1)

const u8 SERVER_APP_PRI    =            80;
const u32 MAX_MSG_WAITING  =            512;

class CSInstance : public CInstance{
private:
        void InstanceEntry(CMessage *const);
};

typedef zTemplate<CSInstance,MAX_INS_NUM,CAppNoData,MAX_ALIAS_LENGTH> CSApp;
