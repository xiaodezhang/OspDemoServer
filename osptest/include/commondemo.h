#ifndef _COMMON_DEMO_H
#define _COMMON_DEMO_H

const u16 SERVER_APP_ID   = 2;
const int MAX_INS_NUM     = 512;
const u8 MAX_ALIAS_LENGTH = 20;

#define  C_S_MSG_BGN   0x7777

#define  C_S_POST_MSG_REQ    (C_S_MSG_BGN + 1)
#define  S_C_POST_MSG_ACK    (C_S_MSG_BGN + 2)

#define  C_S_SEND_MSG_REQ    (C_S_MSG_BGN + 3)
#define  S_C_SEND_MSG_ACK    (C_S_MSG_BGN + 4)

#define  C_S_RAW_MSG_REQ     (C_S_MSG_BGN + 5)
#define  S_C_RAW_MSG_ACK     (C_S_MSG_BGN + 6)

#define  C_S_POST_ALIAS_REQ  (C_S_MSG_BGN + 7)
#define  S_C_POST_ALIAS_ACK  (C_S_MSG_BGN + 8)

#define  C_S_SEND_ALIAS_REQ  (C_S_MSG_BGN + 9)
#define  S_C_SEND_ALIAS_ACK  (C_S_MSG_BGN + 10)

#define  C_S_TEST_REQ        (C_S_MSG_BGN + 11)
#define  S_C_TEST_ACK        (C_S_MSG_BGN + 12)


#define  LOG_LVL_ERROR      1
#define  LOG_LVL_WARNING    2
#define  LOG_LVL_KEY        3
#define  LOG_LVL_DETAIL     4

#endif /*_COMMON_DEMO_H*/