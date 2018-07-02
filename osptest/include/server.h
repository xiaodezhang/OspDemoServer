#include"osp.h"
#include"commondemo.h"

#define OSP_AGENT_SERVER_PORT 20000

#define RUNNING_STATE         1
#define IDLE_STATE            0

class CSInstance : public CInstance{
private:
        void InstanceEntry(CMessage *const);
};

typedef zTemplate<CSInstance,MAX_INS_NUM,CAppNoData,MAX_ALIAS_LENGTH> CSApp;
