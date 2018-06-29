#include"osp.h"
#include"commondemo.h"

class CSInstance : public CInstance{
private:
        void InstanceEntry(CMessage *const);
};

typedef zTemplate<CSInstance,MAX_INS_NUM,CAppNoData,MAX_ALIAS_LENGTH> CSApp;
