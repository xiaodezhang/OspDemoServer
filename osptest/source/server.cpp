#include"osp.h"
#include"server.h"


CSApp g_cCSApp;

char buffer[BUFFER_SIZE];
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

        switch(curState){
                case IDLE_STATE:{
                        switch(curEvent){
                                case SERVER_CONNECT_TEST:{
                                        OspPrintf(1,0,"connect sucessfully\n");
                                }
                                break;
                                case FILE_NAME_SEND:{
                                     if(pMsg->length > MAX_FILE_NAME_LENGTH-1){
                                             OspLog(LOG_LVL_ERROR,"[InstanceEntry] file name length error\n");
                                             OspPrintf(1,0,"file name length error\n");
                                     }
                                     strcpy((char*)FileName,(const char*)pMsg->content);
                                     post(pMsg->srcid,FILE_NAME_ACK,NULL,0,pMsg->srcnode);
                                     NextState(RUNNING_STATE);
                                }
                                break;

                        }
                }
                        break;
                case RUNNING_STATE:
                        switch(curEvent){
                                case FILE_UPLOAD:{
                                     FILE *file;
                                     size_t buffer_size;

                                     if(!(file = fopen("test_file_name","wb"))){
                                             printf("open file error\n");
                                             break;
                                     }

                                     //TODO:增加缓冲
                                     buffer_size = fwrite(pMsg->content,1,sizeof(char)*pMsg->length,file);
                                   //TODO:需要增加返回信息，为客户端文件传送进度显示做依据。
                                     printf("get files\n");
                                     fclose(file);
                                }
                                break;
                        }
                        break;
                default:
                        break;
        }

        OspPrintf(1,0,"instance entry\n");
}

void CSInstance::DaemonInstanceEntry(CMessage * const pcMsg,CApp *pCApp){

	if (NULL == pcMsg) {
		OspLog(LOG_LVL_ERROR, "[CCltInstance::DaemonInstanceEntry] NULL == pcMsg.\n");
		return;
	}
	if (NULL == pCApp) {
		OspLog(LOG_LVL_ERROR, "[CCltInstance::DaemonInstanceEntry] NULL == pCApp.\n");
		return;
	}

	u32 dwcurState = CurState();
	u16 wEvent = pcMsg->event;
	CSInstance *pCSInstance = NULL;

         switch(wEvent){
                 case SIGN_IN:{
                       if(CheckAuthorization((TSinInfo*)pcMsg->content,pcMsg->length)){
                               if(OSP_OK != post(pcMsg->srcid,SIGN_IN_ACK,"succeed"
                                     ,strlen("succeed"),pcMsg->srcnode)){
                                       OspPrintf(1,0,"post back failed\n");
                                       printf("post back failed\n");
                               }
                               OspLog(SYS_LOG_LEVEL,"sign in\n");
                               OspPrintf(1,1,"sign in\n");
                       }else{
                               post(pcMsg->srcid,SIGN_IN_ACK,"failed",strlen("failed"),pcMsg->srcnode);
                               OspLog(SYS_LOG_LEVEL,"sign in failed\n");
                               OspPrintf(1,1,"sign in failed\n");
                       }
                 }
                 break;
                 case SIGN_OUT:{
printf("get sign out\n");
                      post(pcMsg->srcid,SIGN_OUT_ACK,NULL,0,pcMsg->srcnode);
                      OspLog(SYS_LOG_LEVEL,"sign out\n");
                      OspPrintf(1,1,"sign out\n");
                }
                 break;

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
