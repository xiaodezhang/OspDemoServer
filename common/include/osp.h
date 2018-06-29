/******************************************************************************
ģ����  : OSP
�ļ���  : osp.h
����    : OSP���ͷ�ļ�
�汾    ��KDV 4.0
******************************************************************************/
/*************************************************
ģ��汾��OSP.1.8.0.20140303
���ӹ��ܣ�������ҵ����ҵ��Osp
�޸�ȱ�ݣ���
�ύ�ˣ�������
**************************************************/
/*************************************************
ģ��汾��OSP.1.5.3.200803011
���ӹ��ܣ�VX��mstotick�޸ģ�ʹ��u64��������
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.5.2.200803011
���ӹ��ܣ�OspTaskSetPriority��SCHED_OTHER��������ȼ�ֻ��0����Ч
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.5.0.20080304
���ӹ��ܣ�����OspTaskSetPriorityByName�Ƚӿ�
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.4.4.20080303
���ӹ��ܣ����telnet���쳣���⣬NVR, BUG1048, 803
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.4.3.20080116
���ӹ��ܣ�Ospconnecttcpnode�Ĵ����޸ģ����ӵ������ڽڵ�ʱ������
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.4.2.20080109
���ӹ��ܣ�SemTakeByTime�ٽ���������,nsec=1000000���������pthread_wait_cond����
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.4.1.20080102
���ӹ��ܣ�����ȡ�����Զ�ʱ���ӿڣ�����LInux�¾��Զ�ʱ����BUG
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.3.0.20071214
���ӹ��ܣ�KDV��OSPͬKDMͬ��
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.2.5.20071211
���ӹ��ܣ�ospע�������⣬����������
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.2.4.20071211
���ӹ��ܣ�osp post�ӱ�����ȷ��APPID��Ӧ��APP��Ч
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.2.3.20070917
���ӹ��ܣ�Э����OSP,����OspTaskShow��%d Ϊ %u
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.2.2.20070828
���ӹ��ܣ�Э����OSP,����OspGetTick�ӿڣ������������ǰ����-1��ʼ�շ�����ȷ��tick����ȷ�������ֵ��׼ȷ��
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.2.1.20070823
���ӹ��ܣ�Э����OSP,����OspGetTick64�ӿڣ�����64λtick�������32λtick���������
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.1.4.20070727
���ӹ��ܣ�Э����OSP,��ȡCPU�����ʵĺ�����һЩ��̬��������������������֤����ִ���µİ�ȫ
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.1.3.20070725
���ӹ��ܣ�Э����OSP,ȥ��OSP���ź���ͳ�ƣ��ź����������ʱ���Ӧ�ó�����Ч�ʼ�����£����ȥ���ù���
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.1.1.2.20070721
���ӹ��ܣ�Э����OSP,����OspTaskShow�е�ȫ�������¼���ݵĻ��Ᵽ�����Լ�������Խ����
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/
/*************************************************
ģ��汾��OSP.KDV4.0.1.1.1.20070627
���ӹ��ܣ�Э����OSP��ʼ�汾
�޸�ȱ�ݣ���
�ύ�ˣ���һƽ
**************************************************/


#ifndef _OSP_H
#define _OSP_H

///////////////////////////////////////////////////////////////////
//	Linux ����ϵͳͷ�ļ�
///////////////////////////////////////////////////////////////////
#if (defined(_LINUX_) || defined(_IOS_PLATFORM_))
#ifdef PWLIB_SUPPORT
#include <ptlib.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>
#ifdef _IOS_PLATFORM_
#include <malloc/malloc.h>
#else
#include <malloc.h>
#endif
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/times.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <termios.h>
#include <signal.h>
#include "syslog.h"

/* 5.0�ϲ��� ����Androidƽ̨֧�� */
#if defined(_ANDROID_)
#include <sys/epoll.h>
#include <fcntl.h>
#elif (!(defined(_EQUATOR_) || defined(_IOS_PLATFORM_)))
#include <mqueue.h>
#include <sys/epoll.h>
#include <sys/resource.h>
#endif
#endif //_LINUX_

///////////////////////////////////////////////////////////////////
//	Vxworks ����ϵͳͷ�ļ�
///////////////////////////////////////////////////////////////////
#ifdef _VXWORKS_

#include <vxworks.h>
#include <tasklib.h>
#include <msgqlib.h>
#include <syslib.h>
#include <string.h>
#include <memLib.h>
#include <stdlib.h>
#include <string.h>
#include <sockLib.h>
#include <inetLib.h>
#include <stdioLib.h>
#include <strLib.h>
#include <hostLib.h>
#include <ioLib.h>
#include <assert.h>
#include <netdb.h>
#include <errno.h>
#include <sys/stat.h>
#include <taskHookLib.h>
#include <logLib.h>
//����֧��
#include "brddrvlib.h"

#endif // _VXWORKS_

///////////////////////////////////////////////////////////////////
//	Win32 ����ϵͳͷ�ļ�
///////////////////////////////////////////////////////////////////
#ifdef _MSC_VER
#pragma warning(disable:4127)
#pragma warning(disable:4996)

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#ifdef WINVER
#undef WINVER
#endif
/* vc is vs2005 and later */
#if (_MSC_VER >= 1400)
#define _WIN32_WINNT 0x0501 //support only winxp and above
#define WINVER 0x0501 //support only winxp and above
#else
#define _WIN32_WINNT 0x400
#define WINVER 0x0400
#endif

#include <malloc.h>
#include <time.h>

#ifdef _AFXDLL
#include <afx.h>
#include <afxwin.h>
#include <winsock2.h>
#else
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#endif

#include <assert.h>
#pragma comment(lib,"Ws2_32.lib")

#endif  // _MSC_VER

///////////////////////////////////////////////////////////////////
//	����ϵͳͷ�ļ������Ͷ��壩
///////////////////////////////////////////////////////////////////
#include "kdvtype.h"

///////////////////////////////////////////////////////////////////
//	����ϵͳ����������Ͷ���
///////////////////////////////////////////////////////////////////
#ifdef _LINUX_

#define TRUE                 1
#define FALSE                0

typedef void *(*LINUXFUNC)(void *);

#define SEMHANDLE            pthread_cond_t*

#define TASKHANDLE           pthread_t

#endif  // _LINUX_

#ifdef _VXWORKS_

#define SEMHANDLE            SEM_ID
#define TASKHANDLE           u32

#endif  // _VXWORKS_

#ifndef _MSC_VER
/* 5.0�ϲ��� ȥ��u64����, u64�Ѿ�������kdvtype.h��. */
//	typedef unsigned long long    u64;
#define SOCKHANDLE           int
#define SERIALHANDLE         int

#ifndef SOCKADDR
#define SOCKADDR         sockaddr
#endif
#define SOCKADDR_IN          sockaddr_in

#endif  // _MSC_VER

#ifdef _MSC_VER

#define SEMHANDLE            HANDLE
#define TASKHANDLE           HANDLE

#define SOCKHANDLE           SOCKET
#define SERIALHANDLE         HANDLE

#endif  // _MSC_VER

///////////////////////////////////////////////////////////////////
//	����ϵͳ��غ궨��
///////////////////////////////////////////////////////////////////
#ifdef _LINUX_

#define SOCKET_ERROR          (-1)
#define INVALID_SOCKET        (-1)
#define INVALID_SERIALHANDLE  (-1)

#define OSP_NO_WAIT           0
#define OSP_WAIT_FOREVER      (-1)

#endif // _LINUX_

#ifdef _VXWORKS_

#define SOCKET_ERROR          ERROR
#define INVALID_SOCKET        ERROR
#define INVALID_SERIALHANDLE  ERROR

#define OSP_NO_WAIT           NO_WAIT
#define OSP_WAIT_FOREVER      WAIT_FOREVER

#endif  // _VXWORKS_

#ifdef _MSC_VER

#define INVALID_SERIALHANDLE  INVALID_HANDLE_VALUE
#define TOspCommTimeouts      COMMTIMEOUTS
#define TOspDCB               DCB
#define TOspComStat           COMSTAT

#define OSP_NO_WAIT           ((int)0)
#define OSP_WAIT_FOREVER      ((int)-1)

#endif  // _MSC_VER

///////////////////////////////////////////////////////////////////
//	����ϵͳ�޹غ궨��
///////////////////////////////////////////////////////////////////
// for Microsoft c++
#ifdef _MSC_VER

//������
#ifndef _EQUATOR_
#pragma pack(push)
#pragma pack(1)
#endif

#define API extern "C"          __declspec(dllexport)
#define OSP_API                 __declspec(dllexport)

// for gcc
#else

#define API extern "C"
#define OSP_API

#endif  // _MSC_VER

//OSP�汾��Ϣ
#define OSPVERSION              "OSP.1.8.0.20140303"

//SockShutdown����
#define STOP_RECV             0
#define STOP_SEND             1
#define STOP_BOTH             2


//OSP�汾��
#define OSP_VERSION_ID          0x40

//δʹ��
const u8  OSPLOCAL              = 0;
//δʹ��
const u8  TCP_GATEWAY           = 255;
//δʹ��
const u16 SECONDS               = 1000;

/* 5.0�ϲ��� ԭ��ҵ���ԣ�֧��һ��osp�������osp server*/
#ifndef MULTI_LISTEN_SOCKET_SUPPORT
#define MULTI_LISTEN_SOCKET_SUPPORT 1
#endif

/* 5.0�ϲ��� ����֧�ֵ�osp server���� */
#ifdef MULTI_LISTEN_SOCKET_SUPPORT
const u32 MAX_LISTEN_SOCK_NUM       = 16;
#endif //MULTI_LISTEN_SOCKET_SUPPORT

//ͬһ������Ӧ����
/* 5.0�ϲ���  ����app����, ��512����4096, ����app������AppPool�����ĸ����ڴ� */
const u16 MAX_APP_NUM            = 4096;
//ͬһӦ�����ʵ����
const u16 MAX_INST_NUM           = 65000;
//���ʱ����
const u16 MAX_TIMER_NUM          = 5000;
//��󴮿���
const u8  MAX_SERIALPORT_NUM     = 10;

//��Ч���ⲿ����
#define INVALID_NODE             0
//���ؽ���
#define LOCAL_NODE               0

//��Ч��Ӧ�ú�
#define INVALID_APP              0
//����ȫ��Ӧ�ú�
#define LOCAL_APP                0

//��Ч��ʵ����
#define INVALID_INS              0xfffb
//����ʵ����
#define LOCAL_INS                0

//Ĭ��TCP�������ʱ����(��)
#define DEFAULT_TCP_HEARTBEAT_TIME      10
//Ĭ��TCP����������(��μ���ʧ����Ϊ�Ѿ�����)
#define DEFAULT_TCP_HEARTBEAT_NUM       3
//Ĭ��OSPϵͳ״̬��ӡʱ����(��)
#define DEFAULT_STATUS_MSGOUT_TIME      3600
//������TCP�������
#define UNDETECT_TCP_HEARTBEAT          0

#ifndef MINCHAR
#define MINCHAR                 0x80
#endif

#ifndef MAXCHAR
#define MAXCHAR                 0x7f
#endif

#ifndef MINSHORT
#define MINSHORT                0x8000
#endif

#ifndef MAXSHORT
#define MAXSHORT                0x7fff
#endif

#ifndef MINLONG
#define MINLONG                 0x80000000
#endif

#ifndef MAXLONG
#define MAXLONG                 0x7fffffff
#endif

#ifndef MAXBYTE
#define MAXBYTE                 0xff
#endif

#ifndef MAXWORD
#define MAXWORD                 0xffff
#endif

#ifndef MAXDWORD
#define MAXDWORD                0xffffffff
#endif

#ifndef _MSC_VER

//
// Provider capabilities flags.
//

#define PCF_DTRDSR        ((u32)0x0001)
#define PCF_RTSCTS        ((u32)0x0002)
#define PCF_RLSD          ((u32)0x0004)
#define PCF_PARITY_CHECK  ((u32)0x0008)
#define PCF_XONXOFF       ((u32)0x0010)
#define PCF_SETXCHAR      ((u32)0x0020)
#define PCF_TOTALTIMEOUTS ((u32)0x0040)
#define PCF_INTTIMEOUTS   ((u32)0x0080)
#define PCF_SPECIALCHARS  ((u32)0x0100)
#define PCF_16BITMODE     ((u32)0x0200)

//
// Comm provider settable parameters.
//

#define SP_PARITY         ((u32)0x0001)
#define SP_BAUD           ((u32)0x0002)
#define SP_DATABITS       ((u32)0x0004)
#define SP_STOPBITS       ((u32)0x0008)
#define SP_HANDSHAKING    ((u32)0x0010)
#define SP_PARITY_CHECK   ((u32)0x0020)
#define SP_RLSD           ((u32)0x0040)

//
// Settable baud rates in the provider.
//
#ifdef _VXWORKS_
#define BAUD_110          (u32)110
#define BAUD_300          (u32)300
#define BAUD_1200         (u32)1200
#define BAUD_2400         (u32)2400
#define BAUD_4800         (u32)4800
#define BAUD_9600         (u32)9600
#define BAUD_19200        (u32)19200
#define BAUD_38400        (u32)38400
#endif

#if defined(_LINUX_) && !defined(_EQUATOR_)
#define BAUD_300          (u32)300
#define BAUD_1200         (u32)1200
#define BAUD_2400         (u32)2400
#define BAUD_4800         (u32)4800
#define BAUD_9600         (u32)9600
#define BAUD_19200        (u32)19200
#define BAUD_38400        (u32)38400
#define BAUD_57600        (u32)57600
#define BAUD_115200       (u32)115200
#endif

// Equator��ֻ�����ò����ʣ������Ķ���������
#ifdef _EQUATOR_
// ע�⣺�������Ϊ9600
#define BAUD_110          (u16)110
#define BAUD_300          (u16)300
#define BAUD_600          (u16)600
#define BAUD_1200         (u16)1200
#define BAUD_2400         (u16)2400
#define BAUD_4800         (u16)4800
#define BAUD_9600         (u16)9600
#endif

//
// Settable Data Bits
//
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
#define DATABITS_5        (u8)5
#define DATABITS_6        (u8)6
#define DATABITS_7        (u8)7
#define DATABITS_8        (u8)8
#else
#define DATABITS_5        ((u16)0x0001)
#define DATABITS_6        ((u16)0x0002)
#define DATABITS_7        ((u16)0x0004)
#define DATABITS_8        ((u16)0x0008)
#define DATABITS_16       ((u16)0x0010)
#define DATABITS_16X      ((u16)0x0020)
#endif

//
// Settable Stop and Parity bits.
//
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
#define STOPBITS_10       (u8)1
#define STOPBITS_20       (u8)2
#else
#define STOPBITS_10       ((u16)0x0001)
#define STOPBITS_15       ((u16)0x0002)
#define STOPBITS_20       ((u16)0x0004)
#endif

#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
#define PARITY_NONE       (u8)0
#define PARITY_ODD        (u8)1
#define PARITY_EVEN       (u8)2
#define PARITY_MARK       (u8)3
#define PARITY_SPACE      (u8)4
#else
#define PARITY_NONE       ((u16)0x0100)
#define PARITY_ODD        ((u16)0x0200)
#define PARITY_EVEN       ((u16)0x0400)
#define PARITY_MARK       ((u16)0x0800)
#define PARITY_SPACE      ((u16)0x1000)
#endif
//
// DTR Control Flow Values.
//
#define DTR_CONTROL_DISABLE     0x00
#define DTR_CONTROL_ENABLE      0x01
#define DTR_CONTROL_HANDSHAKE   0x02

//
// RTS Control Flow Values
//
#define RTS_CONTROL_DISABLE     0x00
#define RTS_CONTROL_ENABLE      0x01
#define RTS_CONTROL_HANDSHAKE   0x02
#define RTS_CONTROL_TOGGLE      0x03

#define NOPARITY                0
#define ODDPARITY               1
#define EVENPARITY              2
#define MARKPARITY              3
#define SPACEPARITY             4

#define ONESTOPBIT              0
#define ONE5STOPBITS            1
#define TWOSTOPBITS             2

//
// Escape Functions
//

#define SETXOFF                 1       // Simulate XOFF received
#define SETXON                  2       // Simulate XON received
#define SETRTS                  3       // Set RTS high
#define CLRRTS                  4       // Set RTS low
#define SETDTR                  5       // Set DTR high
#define CLRDTR                  6       // Set DTR low
#define RESETDEV                7       // Reset device if possible
#define SETBREAK                8       // Set the device break line.
#define CLRBREAK                9       // Clear the device break line.

//
// PURGE function flags.
//
#define PURGE_TXABORT           0x0001  // Kill the pending/current writes to the comm port.
#define PURGE_RXABORT           0x0002  // Kill the pending/current reads to the comm port.
#define PURGE_TXCLEAR           0x0004  // Kill the transmit queue if there.
#define PURGE_RXCLEAR           0x0008  // Kill the typeahead buffer if there.

typedef struct {
	u32 ReadIntervalTimeout;
	u32 ReadTotalTimeoutMultiplier;
	u32 ReadTotalTimeoutConstant;
	u32 WriteTotalTimeoutMultiplier;
	u32 WriteTotalTimeoutConstant;
} TOspCommTimeouts;

typedef struct {
	u32 DCBlength;           // sizeof(DCB)
	u32 BaudRate;            // current baud rate
	u32 fBinary: 1;          // binary mode, no EOF check
	u32 fParity: 1;          // enable parity checking
	u32 fOutxCtsFlow: 1;     // CTS output flow control
	u32 fOutxDsrFlow: 1;     // DSR output flow control
	u32 fDtrControl: 2;      // DTR flow control type
	u32 fDsrSensitivity: 1;  // DSR sensitivity
	u32 fTXContinueOnXoff: 1; // XOFF continues Tx
	u32 fOutX: 1;            // XON/XOFF out flow control
	u32 fInX: 1;             // XON/XOFF in flow control
	u32 fErrorChar: 1;       // enable error replacement
	u32 fNull: 1;            // enable null stripping
	u32 fRtsControl: 2;      // RTS flow control
	u32 fAbortOnError: 1;    // abort on error
	u32 fDummy2: 17;         // reserved
	u32 wReserved;           // not currently used
	u16 XonLim;              // transmit XON threshold
	u16 XoffLim;             // transmit XOFF threshold
	u8  ByteSize;            // number of bits/Byte, 4-8
	u8  Parity;              // 0-4=no,odd,even,mark,space
	u8  StopBits;            // 0,1,2 = 1, 1.5, 2
	char XonChar;            // Tx and Rx XON character
	char XoffChar;           // Tx and Rx XOFF character
	char ErrorChar;          // error replacement character
	char EofChar;            // end of input character
	char EvtChar;            // received event character
	u16  wReserved1;         // reserved; do not use
} TOspDCB;

typedef struct {
	u32 fCtsHold : 1;
	u32 fDsrHold : 1;
	u32 fRlsdHold : 1;
	u32 fXoffHold : 1;
	u32 fXoffSent : 1;
	u32 fEof : 1;
	u32 fTxim : 1;
	u32 fReserved : 25;
	u32 cbInQue;
	u32 cbOutQue;
} TOspComStat;

#endif //#ifndef _MSC_VER

#if (defined(_MSC_VER) && (_MSC_VER > 1200)) || !defined(_MSC_VER)
/* 5.0�ϲ��� ����IP��ַ���͵Ķ���
 * windows ҪVS2010����ʹ��ipv6
*/
typedef union tagOspNetAddr {
    struct sockaddr_in		v4addr;     //ipv4��ַ
    struct sockaddr_in6		v6addr;     //ipv6��ַ
    struct sockaddr_storage staddr;     //socket��ʾ�ĵ�ַ
    //socket�޷���ʾ��˽�е�ַ����
    u8  raw_addr[sizeof(struct sockaddr_storage)];
} TOspNetAddr;
#endif

// ���ݽ��ţ�APP�źͱ���ʵ���Ź���ȫ��ʵ��ID
inline u32  MAKEIID( u16 app, u16 ins = 0 , u8 = 0 )
{
	return (app << 16) + ins;
}

// ��ID�л��Ӧ�ú�
inline u16 GETAPP( u32 GlobIID )
{
	return (u16)(GlobIID >> 16);
}

// ��ID�л�����غ�
inline u8 GETGATE( u32 = 0 )
{
	return 0;
}

// ��ID�л��ʵ����
inline u16 GETINS( u32 GlobIID )
{
	return (u16)(GlobIID);
}

// ��ID�л��ʵ���ŵĵ��ֽ�
inline u8 GETINSL( u32 GlobIID )
{
	return (u8)(GlobIID);
}

// ��ID�л��ʵ���ŵĸ��ֽ�
inline u8 GETINSH(u32 GlobIID)
{
	return (u8)(GlobIID >> 8);
}

//telnet�ն���ʾ����󳤶�
#define MAX_PROMPT_LEN              21

// OSP������
#define OSP_ERROR_BASE              0
//�����ɹ�
#define OSP_OK                      (OSP_ERROR_BASE + 0)
//����ʧ��
#define OSP_ERROR                   (OSP_ERROR_BASE + 1)
//δʹ��
#define OSPERR_SEND_FAIL            (OSP_ERROR_BASE + 2)
//����ͬ����Ϣ��ʱ
#define OSPERR_SEND_TIMEOUT         (OSP_ERROR_BASE + 3)
//ͬ����ϢӦ�𳬳�
#define OSPERR_SYNCACK_EXCEED       (OSP_ERROR_BASE + 4)
//ͬһӦ����ʵ�������Ѿ�����
#define OSPERR_ALIAS_REPEAT         (OSP_ERROR_BASE + 5)
//δʹ��
#define OSPERR_APP_REPEAT           (OSP_ERROR_BASE + 6)
//�ⲿ������Ч
#define OSPERR_NODE_INVALID         (OSP_ERROR_BASE + 7)
//������Ч
#define OSPERR_ILLEGAL_PARAM        (OSP_ERROR_BASE + 8)
//ͬ����Ϣ�Զ���Ӧ��
#define OSPERR_PEER_NOT_RESPOND     (OSP_ERROR_BASE + 9)

//�����Ϣ���� /* 5.0�ϲ��� ����ԭ��ҵ���飬 ԭ��ҵ��Ϣ��󳤶�Ϊ0x8000*/
#define MAX_MSG_LEN                 (u16)0xffff
//ʵ��������󳤶�
#define MAX_ALIAS_LEN               (u8)255
//���ͬ����ϢӦ�𳤶�
#define MAX_SYNCACK_LEN             MAX_MSG_LEN
//������ݳ���(δʹ��)
#define MAX_DATA_LEN                (MAX_MSG_LEN+MAX_ALIAS_LEN+MAX_SYNCACK_LEN)

//OSP��Ϣ����
// �첽��Ϣ
#define MSG_TYPE_ASYNC              (u16)0
// ͬ����Ϣ
#define MSG_TYPE_SYNC               (u16)1
// ͬ��Ӧ����Ϣ
#define MSG_TYPE_SYNCACK            (u16)2
// ȫ��ͬ����Ϣ
#define MSG_TYPE_GSYNC              (u16)3
// ȫ��ͬ��Ӧ����Ϣ
#define MSG_TYPE_GSYNCACK           (u16)4
// ��ʱ��Ϣ
#define MSG_TYPE_TIMEOUT            (u16)5

/* 5.0�ϲ��� ԭ��ҵ���ж��壬 raw��Ϣ����*/
#define MSG_TYPE_RAWMSG             (u16)6

//�л�ʵ��״̬��
#define NEXTSTATE(x)                NextState(x,#x)

//OSP �û��Զ�����Ϣ�¼��Ż�׼(С�ڸ�ֵ����ϢΪOSP������Ϣ���ϲ��ֹ���͸���Ϣ)
#define   OSP_USEREVENT_BASE        (u16)0x0400
//������Ϣ�¼���
#define OSPEVENT(x,y)       const u16 x = y

//δʹ��
OSPEVENT(OSP_CONFIRM,       0xff);
//�����������
OSPEVENT(OSP_POWERON,       0x100);
//δʹ��
OSPEVENT(OSP_SWITCHMASTER,  0x101);
//δʹ��
OSPEVENT(OSP_SWITCHSLAVE,   0x102);
//������޿���ʵ��
OSPEVENT(OSP_OVERFLOW,      0x103);
//δʹ��
OSPEVENT(OSP_EXCEPTION_IND, 0x104);
//δʹ��
OSPEVENT(OSP_INSNOTEXIST,   0x105);
//��Զ�˽���TCP��·�Ѷ�
OSPEVENT(OSP_DISCONNECT,    0x106);
//�㲥��Ϣȷ��Ӧ��
OSPEVENT(OSP_BROADCASTACK,  0x107);
//δʹ��
OSPEVENT(OSP_NODECLOSE,     0x108);
//�������̽����Ϣ
OSPEVENT(OSP_NETBRAECHO,    0x109);
//�������̽����Ϣȷ��Ӧ��
OSPEVENT(OSP_NETBRAECHOACK, 0x110);
//OSPж����Ϣ
OSPEVENT(OSP_QUIT,          0x120);
//����ͨ�Ų�����Ϣ
OSPEVENT(OSP_NETSTATEST,    0x121);
//����ͨ�Ų�����Ϣȷ��Ӧ��
OSPEVENT(OSP_NETSTATESTACK, 0x122);
//δʹ��
OSPEVENT(OSP_APPCONN_ACK,   0x123);


// Trc���ٱ�־
typedef enum TRCOPTION {
	// ����״̬Ǩ��
	TRCSTATE     = 1,
	// �����¼�
	TRCEVENT     = 2,
	// ���ٶ�ʱ��
	TRCTIMER     = 4,
} TRCOPTION;

//״̬ԾǨ���¼�����ʱ��������
#define TRCALL     (u16)(TRCSTATE|TRCEVENT|TRCTIMER)

// 1.1���Ժ�֧��ͬ����Ϣ
#if (defined OSP_VERSION_ID) && (OSP_VERSION_ID >= 0x11)
#define SYNCMSG
#endif

#ifdef _LINUX_
/**
 * �������紫������������
 * �κ�һ���ṹҪ�������ϴ��䣬��д��һ�������������У�
 * Ȼ��Ѵ�����������OSP����OSP������
 * ��Ҫ��ֱ��ʹ�ô���һ���ṹ
 */
class COspStream
{
public:
	//��ǰ���ݳ���
	u32 m_dwCurrSize;
	//��ǰ����
	u8 m_achData[MAX_MSG_LEN];

	COspStream()
	{
		m_dwCurrSize = 0;
		memset(m_achData, 0, sizeof(m_achData));
	}
	/* 5.0�ϲ��� ԭ��ҵ���У� ����raw��Ϣ*/
	BOOL32 IsRawMsg()
	{
		return !memcmp(m_achData , "kedacom" , 7);
	}
	u32 GetRawLen()
	{
		u32 *pLen = (u32 *)(m_achData + 7);
		return htonl(*pLen);
	}

	u32  PackElement(const u8 *pData, u32 dwLen);
	u32  ExtractElement(u8 *pData, u32 dwLen);
};

#define PackElement2(data)  PackElement((u8*)&data, sizeof(data))
#define ExtractElement2(data)   ExtractElement((u8*)&data, sizeof(data))

// OSP��Ϣͷ���ṹ
class CMessage
{
public:
	//Դ���
	u32 srcnode;
	//Ŀ�Ľ��
	u32 dstnode;
	//Ŀ��Ӧ��ʵ��
	u32 dstid;
	//ԴĿ��ʵ��
	u32 srcid;
	//��Ϣ����
	u16 type;
	//��Ϣ��
	u16 event;
	//��Ϣ�峤��
	u16 length;
	//��Ϣ��
	u8 *content;

	//���֧��ͬ����Ϣ
#ifdef SYNCMSG
	//ͬ����ϢӦ��
	u8 *output;
	//ͬ����ϢӦ�𳤶�
	u16 outlen;
	//δʹ��
	u16 expire;
#endif

	//ʵ������
	char *dstAlias;
	//ʵ����������
	u8 dstAliasLen;

	//�õ�OSP��Ϣͷ������
	static u32 GetPackedSize()
	{
		return sizeof(u32) + sizeof(u32) + sizeof(u32) + sizeof(u32) + sizeof(u16) +
			   sizeof(u16) + sizeof(u16) + sizeof(u8 *) +
#ifdef SYNCMSG
			   sizeof(u8 *) + sizeof(u16) + sizeof(u16) +
#endif
			   sizeof(char *) + sizeof(u8);
	};

	//OSP��Ϣͷ�����
	void Pack(COspStream &tStream);
	//OSP��Ϣͷ�����
	void Extract(COspStream &tStream);
};

#else
// OSP��Ϣͷ���ṹ
typedef struct CMessage {
	//Դ���
	u32 srcnode;
	//Ŀ�Ľ��
	u32 dstnode;
	//Ŀ��Ӧ��ʵ��
	u32 dstid;
	//ԴĿ��ʵ��
	u32 srcid;
	//��Ϣ����
	u16 type;
	//��Ϣ��
	u16 event;
	//��Ϣ�峤��
	u16 length;
	//��Ϣ��
	u8 *content;

	//���֧��ͬ����Ϣ
#ifdef SYNCMSG
	//ͬ����ϢӦ��
	u8 *output;
	//ͬ����ϢӦ�𳤶�
	u16 outlen;
	//δʹ��
	u16 expire;
#endif

	//ʵ������
	char *dstAlias;
	//ʵ����������
	u8 dstAliasLen;
}
//������
#if defined(_VXWORKS_) || (defined(_LINUX_) && !defined(_EQUATOR_))
__attribute__ ((packed))
#endif
CMessage;

#endif

//ʵ����Ҫ��Ϣ
typedef struct {
	u32 state;
	u16 insid;
	u16 evtrcv;
	u16 evtsnd;
} TInstInfo;

/* 5.0�ϲ��� ԭ��ҵ���нӿڣ���������Ϣ�����ڵ�Ļص� */
typedef BOOL32 (*CB_FUNC_CREATE_RAW_NODE)(int nNodeId , u16 *pwAid, u32 dwAddr , u16 wPort);

/* 5.0�ϲ��� ԭ��ҵ���нӿڣ�����app��������Ϣ�Ļص� */
typedef void (*CB_FUNC_RCV_RAW_MSG)(u32 dwContext, int nNodeId , const char *pchMsg , u32 dwLen );
//����Ӧ���пɱ�������ʵ����Ҫ��Ϣ����
#define MAX_INSTINFO_NUM           100

//Ӧ�ó�����࣬��Ҫ���ڶ����û�Appģ��zTemplate
#if defined(PWLIB_SUPPORT) && defined(_LINUX_)
class CApp : public PThread
#else
struct OSP_API CApp
#endif
{
#if defined(PWLIB_SUPPORT) && defined(_LINUX_)
	PCLASSINFO(CApp, PThread);
#endif

public:
	//Ӧ�ý�����Ϣ����
	u32 msgIncome;
	//Ӧ���Ѵ�����Ϣ����
	u32 msgProcessed;
	//Ӧ�������д��������Ϣ����(δʹ��)
	u32 msgWaiting;
	//Ӧ�������д��������Ϣ������ֵ
	u32 msgWaitingTop;
	//�Ѽ����Ķ�ʱ��Ϣ����
	u32 timerProcessed;
	//Ӧ�����������Ϣ����
	u32 maxMsgWaiting;
	//����������������Ϣ����
	u32 msgdropped;
	//Ӧ�ñ���
	char *pAppName;

	//Ӧ��������д���
	u32 queSendId;
	//Ӧ������������
	u32 queRcvId;

	/* Ϊ֧��ͬ����Ϣ�����ӵ���Ϣ���ݶ��У����ͬ����Ϣ���ͺ�Ӧ��ʱ��Ϣ
	   ��Ӧ����Ϣ����֮ǰ��������Ϣ */
	//Ӧ�ñ������е���Ϣ����
	u32 bakQueMsgNum;
	//Ӧ�ñ�����д���
	u32 bakQueSendId;
	//Ӧ�ñ���������
	u32 bakQueRcvId;

	//Ӧ������ID
	u32 taskID;

	// ��ǰ�յ�����Ϣ
	CMessage *curMsgRcv;
	//��Ļtrc��־
	u16 scrnTraceFlag;
	//�ļ�trc��־
	u16 fileTraceFlag;
	//Ӧ��ID
	u16 appId;
	//Ӧ��ǰһ������ʵ����
	u16 wLastIdleInstID;
	// ��ǰ���͵���Ϣ��
	u16 curEvtSnd;
	//��Ļlog����
	u8 scrnLogFlag;
	//�ļ�log����
	u8 fileLogFlag;

	//Ӧ��������
	TASKHANDLE hAppTask;
	//Ӧ�������ź������
	SEMHANDLE tSemMutex;

	//Ӧ���������ȼ�
	u8 byAppPri;

	// ���ڼ�¼ʵ�����״̬���յ����ݵĻ��л���
	u8 byInstInfoHead;
	u8 byInstInfoTail;
	TInstInfo tInstInfo[MAX_INSTINFO_NUM];

	/* 5.0�ϲ��� ԭ��ҵosp���нṹ�� ����raw��Ϣ*/
	CB_FUNC_RCV_RAW_MSG m_cbMsg;
	u32                 m_dwContext;

    BOOL32 bDropFlag;

public:
#if defined(_LINUX_) && defined(PWLIB_SUPPORT)
	CApp() : PThread(200 << 10)
#else
	CApp()
#endif
	{
		msgIncome = 0;
		msgProcessed = 0;
		timerProcessed = 0;
		maxMsgWaiting = 0;
		msgdropped = 0;
		msgWaitingTop = 0;
		pAppName = NULL;
		queSendId = 0;
		queRcvId = 0;
		bakQueMsgNum = 0;
		bakQueSendId = 0;
		bakQueRcvId = 0;
		taskID = 0;
		scrnTraceFlag = 0;
		fileTraceFlag = 0;
		scrnLogFlag = 0;
		fileLogFlag = 0;
		appId = INVALID_APP;
		byAppPri = 100;
		wLastIdleInstID = 0;
		hAppTask = 0;
#ifndef _LINUX_
		tSemMutex = NULL;
#endif
		byInstInfoHead = 0;
		byInstInfoTail = 0;

		curMsgRcv = NULL;
		curEvtSnd = 0;

		/* 5.0�ϲ��� ԭ��ҵ���нṹ*/
		m_cbMsg = NULL;
		m_dwContext = 0;

		bDropFlag = FALSE;
	}

	virtual ~CApp()
	{
		scrnTraceFlag = 0;
		fileTraceFlag = 0;
		scrnLogFlag = 0;
		fileLogFlag = 0;
	}

	//����ʵ���Ų�ѯָ��ʵ��
	virtual class CInstance *GetInstance(u16 insid) = 0;
	//�趨ʵ������
	virtual BOOL32 SetInstAlias(u16 insid, const char *pAlias, u8 len) = 0;
	//���ݱ�����ѯָ��ʵ��
	virtual class CInstance *FindInstByAlias(const char *pAlias, u8 len) = 0;
	//�õ�Ӧ�����ʵ����
	virtual int GetInstanceNumber(void) = 0;
	//�õ�ʵ��������󳤶�
	virtual u8 GetMaxAliasLen(void) = 0;
	//��ʼ��ʵ��������¼��Ϣ
	virtual BOOL32  InitAliasArray(void) = 0;
	//���ʵ��������¼��Ϣ
	virtual BOOL32  ClearInstAlias(u16 insid, const char *pAlias, u8 len) = 0;

	//����Ӧ��
	// APP������ȼ�Ϊ80�����С��80��OSP��ǿ��Ϊ80���˺�, �û����Ե���OspSetAppPriority()��CApp::SetPriority()�������ȼ�.
	//�ɹ�����OSP_OK      //�����ɹ�    ʧ�ܷ���OSP_ERROR  //����ʧ��
	/* 5.0�ϲ��� �޸�char* Ϊconst char**/
	int CreateApp( const char *name, u16 aid, u8 pri, u16 queuesize = 80, u32 uStackSize = 200 << 10 );
	/* 5.0�ϲ��� ԭ��ҵosp���нӿڣ���������Ϣ�ص����� */
	void SetAppCallBack(CB_FUNC_RCV_RAW_MSG cbMsg , u32 dwContext);
	//�趨Ӧ���������ȼ�
	BOOL32 SetPriority(u8 byPrior);
	//��ѯ�������ȼ�
	u8 GetPriority(void)
	{
		return byAppPri;
	}
	//Ӧ���˳�
	void QuitApp(void);

	//Ӧ�ñ�������Ϣ�������Ӽ��ٲ�ѯ
	BOOL32 BakMsgNumInc(void);
	BOOL32 BakMsgNumDec(void);
	u32 GetBakMsgNum(void);

	//Ӧ����������Ϣ������ѯ���Ӽ���
	u32 GetMsgIncomeNum(void);
	void MsgIncomeNumInc(void);
	void MsgIncomeNumDec(void);

	//Ӧ�ô�����Ϣ��������
	void MsgProcessedNumInc(void);

	//��ѯ���������Ϣ����
	u32 GetMsgWaitingNum(void);

	//Ӧ�ñ����趨��ѯ
	void SetName(const char *pName);
	char *NameGet(void);

	//��ʱ������������
	void TimerProcessedIncrease(void);

	//�趨�ļ���Ļlog����
	void LogLevelSet(u8 file_level, u8 screen_level);
	//�趨�ļ���Ļtrc��־
	void TrcFlagSet(u16 file_flag, u16 screen_flag);

	//ʵ����Ҫ��Ϣ��ӡ
	void InstInfoShow(void);
	//ʵ����Ҫ��Ϣ����
	void InstInfoAdd(u16 ins, u32 state, u16 evtrcv, u16 evtsnd);
	//�����Ƿ�����Ϣ��־
    void DropFlagSet(BOOL32 bDropFlag);

#if defined(_LINUX_) && defined(PWLIB_SUPPORT)
	void Main(void);  // pwlib pure virtual function
#endif
};


//ʵ����ʱ����Ϣ
typedef  struct TInstTimerInfo {
	TInstTimerInfo *next ;
	u32 timerId ;
	void *timerBlkAdrr ;
} TInstTimerInfo;


/* 5.0�ϲ��� ԭ��ҵ��ʱ���ĵײ�ṹ��ʹ��ҵ�����ֱ�ӷ��ʵײ㶨ʱ��״̬ */
struct TmBlk { // ��ʱ���ƿ�
	TmBlk *suc;  // ��һ��ʱ����ƿ顣
	TmBlk *pre;  // ��һ��ʱ����ƿ顣
	u64 tick;
	u16 appId;
	u16 instId;
	u16 timerId;
	u32 param;
	u32 settedTick;
	u16 timeToLeft;
	time_t absTime;      //���Զ�ʱ��ʱʱ��
	BOOL32 bExtendMode;    //�Ƿ�ʹ����չģʽ(Ĭ�ϲ�ʹ��)
	u8  *pExtContent;    //��չ����
	u16  dwExtLength;    //��չ���ݵĳ���
};


#define  TIMERHANDLE  TmBlk*


//CInstance�������淶��
//����Osp��Ӧ�ñ���Ӹ�CInstance��������һ�������Instance�࣬
//������һ��InstanceEntry()��Ա�����ľ���ʵ��
class OSP_API CInstance
{
public:
	enum {
		//����ʵ��
		PENDING,
		//�㲥
		EACH = 0xffff,
		//�㲥��Ҫ��ȷ��Ӧ��
		EACH_ACK = 0xfffe,
		//δʹ��
		CONN_ACK = 0xfffd,
		//�ػ�ʵ��
		DAEMON = 0xfffc,
		//Ŀ��ʵ��ʵ������Ч��������Ч
		INVALID = 0xfffb
	};

public:
	//Ӧ�ú�
	u16 m_appId;
	//ʵ����
	u16 m_instId;
	//ʵ������
	char m_alias[MAX_ALIAS_LEN];
	//ʵ����������
	u8 m_aliasLen;
	//ʵ��������󳤶�
	u8 m_maxAliasLen;
	//��ǰ״̬��
	u32 m_curState;
	//��һ��״̬��
	u32 m_lastState;

public:
	//�ػ�ʵ����ں���
	virtual void DaemonInstanceEntry( CMessage *const, CApp *)
	{
		log( 0, (char *)"Osp: message received in default daemon instance of app %d.\nCheck your daemon implementation, please!\n", GetAppID() );
	}
	//ʵ����ں���
	virtual void InstanceEntry( CMessage *const pMsg) = 0;
	//ʵ����ӡ����
	virtual void InstanceDump(u32 = 0)
	{
	}
	//�ػ�ʵ����ӡ����
	virtual void DaemonInstanceDump(u32 = 0)
	{
	}
	//ʵ���˳�
	virtual void InstanceExit(void)
	{
	}

	//�趨ʵ������
	int SetAlias(const char *pchAlias, u8 len);
	//ɾ��ʵ������
	void DeleteAlias(void);
	//��ѯʵ������
	BOOL32 GetAlias(char *aliasBuf, u8 bufLen, u8 *aliasLen);
	//��ѯʵ����������
	u8 GetAliasLen(void);

	//��ѯ��һ��ʵ��״̬��
	u32         LastState();
	//��ѯ��ǰʵ��״̬��
	u32         CurState();

	//��ѯӦ�ú�
	u16         GetAppID();
	//��ѯʵ����
	u16         GetInsID();

	//��ʱ���ź���
	SEMHANDLE      m_tSemTimerList;
	//��ʱ����Ϣ����
	TInstTimerInfo  m_timerInfoListHead;

	//���붨ʱ����Ϣ
	void AddInstTimerInfo(u32 nTimerNo , void *pTimerAddr);
	//ɾ����ʱ����Ϣ
	void DelInstTimerInfo(u32 nTimerNo);
	//��ѯ��ʱ����Ϣ
	void *FindInstTimerInfo(u32 nTimerNo);
	//ɾ�����ж�ʱ����Ϣ
	void DelAllInstTimerInfo();
	/* 5.0�ϲ��� ���������ӿ�����ҵ���нӿڣ� �ṩ��ʱ���ĵײ���� */
	//������Զ�ʱ
	int SetTimer(TIMERHANDLE *pTimerHandle, u32 dwTimer, long uMilliSeconds, const void *content, u16 length );
	//ȡ����ʱ
	int KillTimer(TIMERHANDLE hTimerHandle);
protected:
	//������Զ�ʱ
	int SetTimer( u32 nTimer, long nMilliSeconds, u32 nPara = 0 );
	//���þ��Զ�ʱ
	int SetAbsTimer( u32 nTimer, u16 nYear, u8 nMon, u8 nDay, u8 nHour, u8 nMin, u8 nSec, u32 nPara = 0 );
	//ȡ����ʱ
	int KillTimer(u32 nTimerNo);
	// ȡ�����Զ�ʱ��
	int KillAbsTimer( u32 nTimerNo);
	//ʵ����ӡ,�ɵ���OspSetLogLevel�޸Ĵ�ӡ����
	void log(u8 level, char *format, ...);
	//�л�״̬��
	void NextState(u32 state, char *s = 0 );

	//�����첽��Ϣ(Ŀ��ʵ������ʵ���ű�ʶ)
	int post(u32 dstiid, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0);
	//�����첽��Ϣ(Ŀ��ʵ������ʵ��������ʶ)
	int post(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			 const void *content = 0, u16 length = 0, u32 dstnode = 0);

	//����ͬ����Ϣ(Ŀ��ʵ������ʵ���ű�ʶ)
	int send(u32 dstiid, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0,
			 void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
			 u16 timeout = 1000);
	//����ͬ����Ϣ(Ŀ��ʵ������ʵ��������ʶ)
	int send(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			 const void *content = 0, u16 length = 0, u32 dstnode = 0,
			 void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
			 u16 timeout = 1000);

	//����ͬ����ϢӦ��
	int SetSyncAck(const void *ack = NULL, u16 ackLen = 0);
	//����ͬ����ϢӦ��(����ʹ��SetSyncAck)
	int reply(const void *ack = NULL, u16 ackLen = 0);
};

//���������û�App���ģ��
class CAppNoData
{
};

//ʵ���������ٲ��Ҽ�¼����
typedef struct TInstAliasInfo {
	//ʵ������������ֵ(Ҳ�Ǵ�ŵ�λ���±�)
	u32  aliasRet;
	//��ͬ����ֵ����һ��ʵ�����λ��
	u32  nextLoc;
	//ʵ����
	u16  instId;
} TInstAliasInfo;

//Ӧ��ģ��(ģ�����Ϊʵ���ļ̳����Լ����ʵ��ʵ����)
template <class I, int maxins = 1, class A = CAppNoData, u8 maxAliasLen = 0>
class zTemplate: public CApp, public A
{
public:
	//����ʵ������
	BOOL32 SetInstAlias(u16 insid, const char *pchAlias, u8 len);
	//���ʵ��������¼��Ϣ
	BOOL32  ClearInstAlias(u16 insid, const char *pAlias, u8 len);

private:
	//�ɾֲ�ʵ���Ų���ʵ��
	CInstance *GetInstance(u16 insid);
	//�ɱ�������ʵ��
	CInstance *FindInstByAlias(const char *pchAlias, u8 len);
	//�����ͨʵ������
	int GetInstanceNumber(void);
	//�������������
	u8 GetMaxAliasLen(void);

private:
	//daemonʵ��
	I daemIns;
	//��ͨʵ����
	I insarray[maxins];

	//ʵ���������ٲ���
	//ʵ��������¼��Ϣ��ͷ��
	TInstAliasInfo instAliasArray[maxins];
	//ʵ��������¼��Ϣ���ñ���¼������ͬ��ʵ��
	TInstAliasInfo bakInstAliasArray[maxins];
	//��ǰ���ñ��м�¼��ʵ������
	u32 curBakArrayNum;

	//��ʼ��ʵ��������¼��Ϣ
	BOOL32 InitAliasArray();
	//ʵ������ת����WORD32������
	u32 AliasToWord(char *pchAlias, u8 len);
	//ȷ��ʵ��������Ϣ��������ñ����ڱ��ñ���
	BOOL32 IsInBakArray(u32 setRet);
};

/*=============================================================================
�� �� ����OspLog
��    �ܣ�ȫ��log��������������Ŀ�����Ӧ�ú�0������OspSetLogLevel(0,xx)�Ϳ���
���Ƹú����Ĵ򿪻�ر�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u8 level : [in] log level
char *format : [in] message format
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspLog(u8 level, const char *format, ...);

/*=============================================================================
�� �� ����OspMsgDumpSet
��    �ܣ�set long msg dump detail can/not be whole print, default is printf
10lines
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����BOOL32 LgMsgDumpEnbl : [in] enable or not
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspMsgDumpSet(BOOL32 LgMsgDumpEnbl);

/*=============================================================================
�� �� ����OspStatusMsgOutSet
��    �ܣ�set status message can or not be out put every timer
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����BOOL32 OutMsgEnable : [in] enable or not
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspStatusMsgOutSet(BOOL32 OutMsgEnable);

/*====================================================================
��������OspPrintf
���ܣ�����Ӧ��������ʾ����Ļ,�洢���ļ�,��������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
bScreen: �Ƿ��������Ļ,
bFile: �Ƿ�������ļ�,
szFormat: ��ʽ,
����ֵ˵����
====================================================================*/
API void OspPrintf(BOOL32 bScreen, BOOL32 bFile, const char *szFormat, ...);


/*====================================================================
��������OspTelAuthor
���ܣ�����Telnet����Ȩ�û���������(vxworks���û���������Ϊ�ջ�����ʧ��)
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
����ֵ˵����
====================================================================*/
API void OspTelAuthor(const char *szUsername = NULL , const char *szPassword = NULL );

/*=============================================================================
�� �� ����OspVerPrintf, OspVer
��    �ܣ�output compile version info to screen
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
#define  OspVerPrintf() \
OspPrintf(TRUE, TRUE, "Osp version: %s  compile time: %s %s\n", OSPVERSION, __DATE__, __TIME__)
API void ospver();

/*=============================================================================
�� �� ����OspCat
��    �ܣ�output file content to screen
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����const char*  fname : [in] file to be opened
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspCat(const char  *fname);

#ifdef _LINUX_
typedef void (*POspQuitFunc)(int);
/*====================================================================
  ��������OspRegQuitFunc
  ���ܣ�ע�������˳���������linux����Ч
  �㷨ʵ�֣�
  ����ȫ�ֱ�����
  �������˵����
    pQuitFunc   - �����˳�����
  ����ֵ˵����TRUE - ע��ɹ�
  ====================================================================*/
API BOOL32 OspRegQuitFunc( POspQuitFunc pQuitFunc );

/*====================================================================
  ��������OspRegTaskInfo
  ���ܣ�ע��������Ϣ����linux����Ч
  �㷨ʵ�֣�
  ����ȫ�ֱ�����
  �������˵����
    dwTaskId    - �����
        szName  - �������
  ����ֵ˵������
  ====================================================================*/
API void OspRegTaskInfo(u32 dwTaskId, const char *szName);

/*====================================================================
  ��������OspUnRegTaskInfo
  ���ܣ���ע��������Ϣ
  �㷨ʵ�֣�
  ����ȫ�ֱ�����
  �������˵����
    dwTaskId    - �����
  ����ֵ˵������
  ====================================================================*/
API BOOL32 OspUnRegTaskInfo(u32 dwTaskId);

/*====================================================================
  ��������OspTaskShow
  ���ܣ���ӡ������Ϣ����linux����Ч
  �㷨ʵ�֣�
  ����ȫ�ֱ�����
  �������˵����
  ����ֵ˵������
  ====================================================================*/
API void OspTaskShow();

/*====================================================================
  ��������OspRegCommand
  ���ܣ�ע�������Telnet��ִ�еĺ���(�ú�������linux����Ч��windows�²���ע��)
  �㷨ʵ�֣�
  ����ȫ�ֱ�����
  �������˵����
    szName  - Telnet�����������
    pfFunc  - ��Ӧ�ĺ���ָ��
    szUsage - ����İ�����Ϣ
  ����ֵ˵������
  ====================================================================*/
API void OspRegCommand(const char *szName, void *pfFunc, const char *szUsage);
#endif

/*=============================================================================
�� �� ����OspNodeConnTest
��    �ܣ�test a node's network connection
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 NodeId : [in] id of the node
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspNodeConnTest(u32 NodeId);

/*=============================================================================
�� �� ����OspNodeIpGet
��    �ܣ����ָ������Ip��ַ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����dwNodeId : [in] node id

 �� �� ֵ���ɹ����ؽ��IP, ʧ�ܷ���0.
=============================================================================*/
API u32 OspNodeIpGet(u32 dwNodeId);

/*=============================================================================
  �� �� ����OspNodeLocalIpGet
  ��    �ܣ���ȡ�ڵ�ı��ص�ַ
  ע    �⣺�����Ѿ����ӵ�tcp�ڵ㣬�ڱ��ش��ڶ����ַ������£���Ҫ֪���Է�ʵ�����ӵı���ip��ַ��
  �㷨ʵ�֣�
  ȫ�ֱ�����
  ��    ����dwNodeId : [in] node id

  �� �� ֵ���ɹ����ؽ��IP, ʧ�ܷ���0.
  =============================================================================*/
API u32 OspNodeLocalIpGet(u32 dwNodeId);

/*====================================================================
�������� OspInstShow
���ܣ���ʾĳ��App�е�Instance��״̬��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspInstShow(u16 aid);

/*=============================================================================
�� �� ����OspInstShowAll
��    �ܣ���ʾ����Instance��״̬��Ϣ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspInstShowAll(void);

/*=============================================================================
�� �� ����OspInstDump
��    �ܣ���ʾĳһinstance���Զ�����Ϣ�����ø�instance��dump������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����aid : [in] app id
InstId : [in] instance id, 0:��ʾ���еģ�-1:��ʾ��IDLE��
param : [in] reserved parameter
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspInstDump(u16 aid, u16 InstId, u32 param);

/*====================================================================
��������OspNodeShow
���ܣ���ʾ����Node��״̬��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspNodeShow(void);

/*=============================================================================
�� �� ����OspAppShow
��    �ܣ���ʾApp��״̬��Ϣ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspAppShow();

/*=============================================================================
�� �� ����OspDispatchShow
��    �ܣ���ʾDispatch task����Ϣ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspDispatchShow();

/*====================================================================
��������OspTimerShow
���ܣ���ʾtimer״̬��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspTimerShow(void);

/*====================================================================
��������OspLogShow
���ܣ���ʾ��־ģ��״̬
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ���:
�������˵����
����ֵ˵��: ��
====================================================================*/
API void OspLogShow(void);

/*====================================================================
��������OspMemShow
���ܣ�  ��ʾ�ڴ�����ջ����Ϣ����Ŀ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspMemShow(void);

/*=============================================================================
�� �� ����OspAppEchoTest
��    �ܣ�Application echo testing
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u16 AppId : [in] Application id
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspAppEchoTest(u16 AppId);

/*=============================================================================
�� �� ����OspAddEventDesc
��    �ܣ����ڽ��¼��������Ǽǵ���Ϣ����ϵͳ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����const char *  desc : [in]
u16 event : [in]
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspAddEventDesc (const char   *desc, u16 event);

/*=============================================================================
�� �� ����OspSendTrcOn
��    �ܣ���OSP��㷢�͸��ٱ�ʶ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspSendTrcOn();

/*=============================================================================
�� �� ����OspSendTrcOff
��    �ܣ��ر�OSP��㷢�͸��ٱ�ʶ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspSendTrcOff();

/*=============================================================================
�� �� ����OspRcvTrcOn
��    �ܣ���OSP�����ո��ٱ�ʶ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspRcvTrcOn();

/*=============================================================================
�� �� ����OspRcvTrcOff
��    �ܣ��ر�OSP�����ո��ٱ�ʶ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspRcvTrcOff();

/*====================================================================
��������OspTrcAllOn
���ܣ���OSP����Ӧ�õĸ��ٱ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspTrcAllOn(void);

/*====================================================================
��������OspTrcAllOn
���ܣ���OSP����Ӧ�õĸ��ٱ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspTrcAllOff(void);

/*=============================================================================
�� �� ����OspOpenLogFile
��    �ܣ�����־�ļ�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����const char *  name : [in] file name
u32 maxsize_KB : [in] �ļ���С����
u32 maxfiles : [in]�ļ���Ŀ����
�� �� ֵ��BOOL32 - true �ɹ�, false ʧ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspOpenLogFile(const char   *name, u32 maxsize_KB, u32 maxfiles);

/*=============================================================================
�� �� ����OspCloseLogFile
��    �ܣ��ر���־�ļ���
ע    �⣺�������OspQuit������Ҫ���øú�����
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspCloseLogFile(void);

/*=============================================================================
�� �� ����OspSetLogLevel
��    �ܣ�����һ��APP��CInstance::log�����ļ���
ע    �⣺������OspInit֮����øú���������Ч��OspInit������Ӧ�õĸñ�־��0
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����aid : [in] app id
file_level : [in] file level
screen_level : [in] screen level
if level=5, ��ô0~5 ��ӡ,  6~255 ����ӡ,����Ϊ3,��ֻ��log(0|1|2,"")
�ĵ����ܹ������
�� �� ֵ��
=============================================================================*/
API void OspSetLogLevel(u16 aid, u8 file_level, u8 screen_level);

/*====================================================================
��������OspSetFileLogLevel
���ܣ�����App���ļ���־�ȼ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����wAid App�ĵȼ�
byFileLevel: �ļ�Log�ĵȼ�
����ֵ˵����
====================================================================*/
API void OspSetFileLogLevel(u16 wAid, u8 byFileLevel);

/*====================================================================
��������OspSetScrnLogLevel
���ܣ�����App����Ļ��־�ȼ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����
uAid App�ĵȼ�
uScrnLevel: ��ĻLog�ĵȼ�
����ֵ˵����
====================================================================*/
API void OspSetScrnLogLevel(u16 wAid, u8 byScrnLevel);

/*=============================================================================
�� �� ����OspSetTrcFlag
��    �ܣ�����ÿ��Ӧ�õĸ��ٷ�Χ��Trace ��Ϊ Trace ״̬�� 1: ����Ϣ, 2: ����Ϣ
4: �趨ʱ 8:�ն�ʱ 16:״̬ԾǨ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����aid : [in] app id
file_flag : [in] trace file flag
screen_flag : [in] screen output flag
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspSetTrcFlag(u16 wAid, u16 wFileFlag, u16 wScrnFlag);

/*====================================================================
��������OspSetFileTrcFlag
���ܣ�����ĳ��Ӧ�õĸ��ٱ�־
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����uAid appl ����
uFileFlag: �ļ����ٱ���
����ֵ˵��:
====================================================================*/
API void OspSetFileTrcFlag(u16 wAid, u16 wFileFlag);

/*====================================================================
��������OspSetScrnTrcFlag
���ܣ�����ĳ��Ӧ�õĸ��ٱ�־
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����uAid application ����
uScreenFlag: ��Ļ���ٱ���
����ֵ˵��:
====================================================================*/
API void OspSetScrnTrcFlag(u16 wAid, u16 wScreenFlag);

/*=============================================================================
�� �� ����OspRegistModule
��    �ܣ���OSP�Ǽ�һ��ģ��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����(in)pchModuleName - ģ�飨.exe�ļ���������NULL��β���ַ�����
��"kdvmt.dll"��
�� �� ֵ���ɹ�����TRUE��ʧ�ܷ���FALSE
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspRegistModule(const char *szModuleName);

/*=============================================================================
�� �� ����OspSetLogEventDataLength
��    �ܣ�����ȫ�ֵ���Ϣ������ʾ�ĳ��ȡ�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u16 wLength : [in] length of log event data
�� �� ֵ��u16 previous length
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API u16 OspSetLogEventDataLength(u16);

/*=============================================================================
�� �� ����OspEnableBroadcastAck
��    �ܣ����������£��û����͹㲥��Ϣ������Ҫ�Է�����ȷ����Ϣ��ȱʡ����£�
PIS������Ϣ�ķ����߷���OSP_BROADCASTACK��Ϣ�����ǿ���ͨ���ú����޸���
��ѡ��Ƿ���OSP_BROADCASTACK���ɽ��ܽڵ�����ġ�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u16 aid : [in] ��ʾ�㲥��Ϣ�Ľ�����AID��
BOOL32 bEnable : [in] enable or not
�� �� ֵ��BOOL32 - true Succeeded, false Failed
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspEnableBroadcastAck(u16, BOOL32);

/*=============================================================================
�� �� ����OspGetNodeAddr
��    �ܣ�����Osp����ַ��������Զ��IP+Port����
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 dwNodeId : [in] ���ID
                    TOspNodeAddr* ptOspNodeAddr : [out] ����ַ
�� �� ֵ��FALSE - ��ѯ�ɹ�
                    TRUE - ��ѯʧ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2006/08/10  4.0
=============================================================================*/
typedef struct {
	u32 m_dwLocalIP;//������
	u32 m_dwPeerIP;//������
	u16 m_wLocalPort;//������
	u16 m_wPeerPort;//������
} TOspNodeAddr;
API BOOL32 OspGetNodeAddr( u32 dwNodeId , TOspNodeAddr *ptOspNodeAddr );

#if defined(_MSC_VER) || defined(_LINUX_)

//sock5����汾��
#define SOCK5_PROXY_VERSION         (u8)0x05
//�ͻ���֧�ּ�Ȩ����
#define SOCK5_PROXY_AUTHEN_NO_REQUIERD          (u8)0x00
#define SOCK5_PROXY_AUTHEN_USERNAME_PASSWORD    (u8)0x02
//�������
#define SOCK5_PROXY_SUCCESS                     (u8)0x00
#define SOCK5_PROXY_AUTHEN_NO_ACCEPTABLE        (u8)0xff
//��������
#define SOCK5_PROXY_CMD_TCP_CONNECT             (u8)0x01
#define SOCK5_PROXY_CMD_TCP_BIND                (u8)0x02
#define SOCK5_PROXY_CMD_UDP_ASSOCIATE           (u8)0x03
//�����ֶ�
#define SOCK5_PROXY_RESERVED_DATA               (u8)0x00
//��ַ����
#define SOCK5_PROXY_IPV4_ADDR                   (u8)0x01
#define SOCK5_PROXY_DOMAIN_NAME                 (u8)0x03
#define SOCK5_PROXY_IPV6_ADDR                   (u8)0x04


#define MAX_SOCK5PROXY_AUTHEN_NUM   (u8)0xff
#define MAX_SOCK5PROXY_NAME_PASS_LENGTH (u8)64
typedef struct {
	u32 m_dwProxyIP;
	u16 m_wProxyPort;
	u8 m_byAuthenNum;
	u8 m_abyAuthenMethod[MAX_SOCK5PROXY_AUTHEN_NUM];
	s8 m_achUseName[MAX_SOCK5PROXY_NAME_PASS_LENGTH + 1];
	s8 m_achPassword[MAX_SOCK5PROXY_NAME_PASS_LENGTH + 1];
} TOspSock5Proxy;

/*=============================================================================
�� �� ����OspConnectTcpNodeThroughSock5Proxy
��    �ܣ�TCP��Խsock5�������ӷ���ˣ���OspConnectTcpNode������ͬ���ϲ㲻��Ҫ����OspConnectToSock5Proxy���������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����ptOspSock5Proxy : [in] �����������Ϣ�ṹ;
          dwServerIP : [in] ������IP
          wServerPort : [in] �������˿�
          wHb: [in] �����������(��)
          byHbNum: [in] byHbNum��δ�����Ӽ��Ӧ�����Ϊ��·�ѶϿ�
          dwTimeoutMs : [in] ������ʱʱ��
          pdwLocalIP: [in,out] ��TCP����ʹ�õı���IP
�� �� ֵ��ʧ�ܷ���INVALID_NODE��
          �ɹ�����һ����̬����Ľ���, �˺��û��ɽ���������ͨ��
          �ϲ��������������OspDisconnectTcpNode���������޴���ʱ��������
-------------------------------------------------------------------------------
 �޸ļ�¼��
 ��      ��  �汾  �޸���  �޸�����
 2006/08/21  4.0   ��С��
=============================================================================*/
API int OspConnectTcpNodeThroughSock5Proxy( TOspSock5Proxy *ptOspSock5Proxy , u32 dwServerIP, u16 wServerPort,
		u16 wHb = 10, u8 byHbNum = 3 , u32 dwTimeoutMs = 0 , u32 *pdwLocalIP = NULL, u8 bySocksAuthVerion = SOCK5_PROXY_VERSION );

/*=============================================================================
�� �� ����OspConnectToSock5Proxy
��    �ܣ���sock5�������������TCP��·��UDP��Խsock5��������Ƚ���һ��TCP��·��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����ptOspSock5Proxy : [in] �����������Ϣ�ṹ
          dwTimeoutMs : [in] ������ʱʱ��
�� �� ֵ��ʧ�ܷ���INVALID_SOCKET��
          �ɹ����������ͨ�ŵ�TCP Socket���ɽ�һ������OspUdpAssociateThroughSock5Proxy����UDP Associate��
          �ɸ��ã���Ҫ�ϲ�ά����TCP���ӣ���·����Чʱ��Udp AssociateҲӦ��Ϊ��Ч��
          �������������OspDisconnectFromSock5Proxy��
-------------------------------------------------------------------------------
 �޸ļ�¼��
 ��      ��  �汾  �޸���  �޸�����
 2006/08/21  4.0   ��С��
=============================================================================*/
API SOCKHANDLE OspConnectToSock5Proxy( TOspSock5Proxy *ptOspSock5Proxy , u32 dwTimeoutMs = 0 , u8 bySocksAuthVerion = SOCK5_PROXY_VERSION);

/*=============================================================================
�� �� ����OspUdpAssociateThroughSock5Proxy
��    �ܣ�UDP��Խsock5����
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����hSocket : [in] OspConnectToSock5Proxy���ص�socket(�ɸ���);
          dwLocalIP : [in] �����շ�socket IP���Ա����������������ݴ�Խ��������
          wLocaPort : [in] �����շ�socket �˿ڣ��Ա����������������ݴ�Խ��������
          pdwProxyMapIP : [out] ���������ӳ��IP��������
          pwProxyMapPort : [out] ���������ӳ��˿ڣ�������
          dwTimeoutMs : [in] ������ʱʱ��
�� �� ֵ��ʧ�ܷ���FALSE��
          �ɹ�����TRUE
-------------------------------------------------------------------------------
 �޸ļ�¼��
 ��      ��  �汾  �޸���  �޸�����
 2006/08/21  4.0   ��С��
=============================================================================*/
API BOOL32 OspUdpAssociateThroughSock5Proxy( SOCKHANDLE hSocket , u32 dwLocalIP, u16 wLocalPort ,
		u32 *pdwProxyMapIP, u16 *pwProxyMapPort , u32 dwTimeoutMs = 0 );

/*=============================================================================
�� �� ����OspDisConnectFromSock5Proxy
��    �ܣ��Ͽ���sock5������������UDP Associate��TCP����
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����hSocket : [in] OspConnectToSock5Proxy���ص�socket;
�� �� ֵ��ʧ�ܷ���FALSE��
          �ɹ�����TRUE
-------------------------------------------------------------------------------
 �޸ļ�¼��
 ��      ��  �汾  �޸���  �޸�����
 2006/08/21  4.0   ��С��
=============================================================================*/
API BOOL32 OspDisConnectFromSock5Proxy( SOCKHANDLE hSocket );

#endif

/* 5.0�ϲ��� ԭ��ҵosp���нӿڣ� ����һ��raw��Ϣosp server */
/*=============================================================================
�� �� ����OspCreateTcpNode
��    �ܣ�����һ��TCP�ڵ㡣���Ժ�����ڵ���Ա����ӡ���ʹ��6682��Ϊport������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 dwAddr : [in] reserved
u16 wPort : [in] which port to use
bTcpNodeReuse:[in]������node�˳���˿��Ƿ����������û�������������ռ��
�� �� ֵ��int - If no error occurs, CreateTcpNode returns a descriptor
referencing the new socket. Otherwise, a value of
INVALID_SOCKET is returned.
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspCreateTcpNode(u32 dwAddr, u16 wPort, BOOL32 bTcpNodeReuse = FALSE , CB_FUNC_CREATE_RAW_NODE cb_setappid = NULL);

/*=============================================================================
�� �� ����OspConnectTcpNode
��    �ܣ��ڵ�ַuIpv4Addr�Ͷ˿�uTcpPort�����ӷ�����, �����ö���������.
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����g_Osp
��    ����uIpv4Addr : [in] �������IP��ַ,
wTcpPort : [in] ������������˿ں�,
wHb: [in] �����������(��),
byHbNum: [in] byHbNum��δ�����Ӽ��Ӧ�����Ϊ��·�ѶϿ�,
dwTimeOutMs: [in] �����dwTimeOutMs���������Ӳ��ɹ�, ���س���. ȱʡֵ0,
��ʾȡconnect��ʱ��ȱʡʱ��(75s).  �ò���Ŀǰ����VxWorks����Ч.
pdwLocalIP: [out] ��ǰ�������õ�IP��ַ

 �� �� ֵ���ɹ�����һ����̬����Ľ���, �˺��û��ɽ���������ͨ��.
 ʧ�ܷ���INVALID_NODE.
 -------------------------------------------------------------------------------
 �޸ļ�¼��
 ��      ��  �汾  �޸���  �޸�����
 2003/03/12  2.0
=============================================================================*/
API int OspConnectTcpNode(u32 dwIpv4Addr, u16 wTcpPort, u16 wHb = 10, u8 byHbNum = 3, u32 dwTimeoutMs = 0, u32 *pdwLocalIP = NULL , u16 wAid = 0);

/* 5.0�ϲ��� ԭ��ҵosp���нӿ� */
/*=============================================================================
  �� �� OspConnectTcpNodeEx
  ��    �ܣ��ڵ�ַuIpv4Addr�Ͷ˿�uTcpPort�����ӷ�����, �����ö���������.
            ���ض˿ڰ󶨷�Χ��wMinPort~wMaxPort��
  ע    �⣺
  �㷨ʵ�֣�
  ȫ�ֱ�����g_Osp
  ��    ����uIpv4Addr : [in] �������IP��ַ,
  uTcpPort : [in] ������������˿ں�,
  uHb: [in] �����������(��),
  uHbNum: [in] uHbNum��δ�����Ӽ��Ӧ�����Ϊ��·�ѶϿ�.
  dwTimeOutMs: [in] �����dwTimeOutMs���������Ӳ��ɹ�, ���س���. ȱʡֵ0.
  pdwLocalIP: [out] ��ǰ�������õ�IP��ַ
  wMinPort:[in] ָ�����ذ󶨶˿ڷ�Χ����Сֵ
  wMaxPort:[in] ָ�����ذ󶨶˿ڷ�Χ�����ֵ
  ����󶨶˿���Сֵ�����ֵ��Ϊ0����ʾ���ѡ��˿ڣ�����

  �� �� ֵ���ɹ�����һ����̬����Ľ���, �˺��û��ɽ���������ͨ��.
  ʧ�ܷ���INVALID_NODE.
  =============================================================================*/
API int OspConnectTcpNodeEx(u32 dwIpv4Addr, u16 wTcpPort, u16 wHb, u8 byHbNum,
							u32 dwTimeOutMs, u32 *pdwLocalIP, u16 wMinPort, u16 wMaxPort, u16 wAid = 0);

/*=============================================================================
�� �� ����OspSetHBParam
��    �ܣ����ý��Ķ���������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����dwNodeID: ����,
wHb: ��·�������(����Ϊ��λ),
byHbNum: �������ping��uHbNum��û��Ӧ��, �����Ͽ�.

 �� �� ֵ���ɹ�����TRUE, ʧ�ܷ���FALSE.
 -------------------------------------------------------------------------------
 �޸ļ�¼��
 ��      ��  �汾  �޸���  �޸�����
 2003/06/5   2.1
=============================================================================*/
API BOOL32 OspSetHBParam(u32 dwNodeID, u16 wHb, u8 byHbNum);

/*=============================================================================
�� �� ����OspNodeDiscCBReg
��    �ܣ�������node�����ж�ʱ��֪ͨ��appid��InstId
ע    �⣺Ŀǰ֧��֪ͨ���ʵ����ÿ�ε��øú�������ָֻ֪ͨ��ʵ����������ע���
����������֪ͨʵ�����������
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����dwNodeId : [in] node id
wAppId : [in] application id
wInsId : [in] instance id
�� �� ֵ���ɹ�����OSP_OK��ʧ�ܲμ�������
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspNodeDiscCBReg(u32 dwNodeId, u16 wAppId, u16 wInsId);

/*=============================================================================
�� �� ����OspNodeDiscCBRegQ
��    �ܣ�������node�����ж�ʱ��֪ͨ��appid��InstId
ע    �⣺ÿ�ε��ô˺�����������һ��Ҫ֪ͨ��ʵ�������Ǵﵽ������
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����dwNodeId : [in] node id
wAppId : [in] application id
wInsId : [in] instance id
�� �� ֵ���ɹ�����OSP_OK��ʧ�ܲμ�������
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspNodeDiscCBRegQ(u32 dwNodeId, u16 wAppId, u16 wInsId);

/*=============================================================================
�� �� ����OspNodeDelDiscCB
��    �ܣ�ɾ����node�����ж�ʱ��֪ͨ��appid��InstId
ע    �⣺ÿ�ε��ô˺�������ɾ��һ��Ҫ֪ͨ��ʵ����
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����dwNodeId : [in] node id
wAppId : [in] application id
wInsId : [in] instance id
�� �� ֵ���ɹ�����OSP_OK��ʧ�ܲμ�������
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspNodeDelDiscCB(u32 dwNodeId, u16 wAppId, u16 wInsId);

/*=============================================================================
�� �� ����OspDisconnectTcpNode
��    �ܣ��Ͽ���һ��node�ϵ����ӡ�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u8 node_id : [in] node id
�� �� ֵ��BOOL32 - true Succeeded, false Failed
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspDisconnectTcpNode(u32 nodeId);

/* 5.0�ϲ��� ԭ��ҵosp�Ľӿڣ� ֧��һ�����̴������osp server */
/*=============================================================================
�� �� ����OspCloseTcpNode
��    �ܣ��ر�һ���׽��ֵļ�������Ӧ��OspCreateTcpNode��������(Ŀǰ��linux����Ч)��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����int nSocketFd : [in] �׽�����������һ��ΪOspCreateTcpNode�ķ���ֵ
�� �� ֵ��BOOL32 - true Succeeded, false Failed
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspCloseTcpNode(int nSocketFd);

#ifdef _LINUX_
/*=============================================================================
�� �� ����OspDisconnectAllTcpNode
��    �ܣ�ֹͣ��ǰ�ļ���,���Ͽ����ϴ���ȫ������(Ŀǰ��linux����Ч)��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2006/12/06  1.0   �޽���
=============================================================================*/
API BOOL32 OspDisconnectAllTcpNode(void);
#endif

/*=============================================================================
�� �� ����OspIsValidTcpNode
��    �ܣ��ж�һ��TCP�ڵ��Ƿ���Ч��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 node_id : [in] node id
�� �� ֵ��BOOL32 - Valid or not
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspIsValidTcpNode (u32 node_id);

/*====================================================================
��������OspIsNodeCheckEnable
���ܣ��ж�ָ��������·��⹦���Ƿ����á�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspIsNodeCheckEnable(u32 dwNodeId);

/*====================================================================
��������OspEnableNodeCheck
���ܣ�����ָ��������·��⹦�ܡ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspEnableNodeCheck(u32 dwNodeId);

/*====================================================================
��������OspDisableNodeCheck
���ܣ�����ָ��������·��⹦�ܡ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspDisableNodeCheck(u32 dwNodeId);

/*====================================================================
��������OspSetAppPriority
���ܣ�����App�ĵ������ȼ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����wAppId -- Ŀ��App��,
byPrior -- ���ȼ�.

 ����ֵ˵�����ɹ�, ����TRUE; ʧ��, ����FALSE.
====================================================================*/
API BOOL32 OspSetAppPriority(u16 wAppId, u8 byPrior);

/*====================================================================
��������OspGetAppPriority
���ܣ����ָ��App�ĵ������ȼ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����wAppId -- (in)Ŀ��App��,
pbyPrior -- (out)���ȼ�.

 ����ֵ˵�����ɹ�, ����TRUE; ʧ��, ����FALSE.
====================================================================*/
API BOOL32 OspGetAppPriority(u16 wAppId, u8 *pbyPrior);

/*=============================================================================
�� �� ����OspIsLocalHost
��    �ܣ��ж��Ƿ��Ǳ���IP����OspIsLocalHost( inet_addr( "127.0.0.1" ) );
ע    �⣺�������Windows��ʹ�ñ������������ȵ���OspInit������WSAStartup��
������Ч�ʽϵͣ���Ҫ�ظ����á�
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 dwIP : [in] ��Ҫ�жϵ�IP
�� �� ֵ��BOOL32    �Ƿ�Ϊ����IP
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspIsLocalHost( u32 dwIP );

/*=============================================================================
�� �� ����OspPost
��    �ܣ������첽��Ϣ
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 dstid : [in] destination info
u16 event : [in] OSP_ event
const void* content : [in] message data
u16 length : [in] sizeof content in u8s
u32 dstnode : [in] destionation socket node
u32 srcGlobIID : [in] source info
u32 srcnode : [in] source node
BOOL32 bDroppable : [in] drop the message when message queue full
int timout : [in] message send timeout
�� �� ֵ��int - 0 Succeeded, others Failed
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspPost(u32 dstid, u16 event, const void *content = 0, u16 length = 0,
				u32 dstnode = 0, u32 srciid = MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE, int timeout = 2000);

/* used only in C++ environment */
//�������޸�, ��Ӳ���timeout, Ĭ��ֵ2��
int OspPost(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			const void *content = 0, u16 length = 0, u32 dstnode = 0, u32 srciid = MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE, int timout = 2000);

/*=============================================================================
�� �� ����OspSend
��    �ܣ�ȫ��ͬ����Ϣ����
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u32 dstid : [in] destination info
u16 event : [in] OSP_ event
const void* content : [in] message data
u16 length : [in] sizeof content in u8s
u32 dstnode : [in] destionation socket node
u32 srcGlobIID : [in] source info
u32 srcnode : [in] source node
BOOL32 bDroppable : [in] drop the message when message queue full
�� �� ֵ��int - 0 Succeeded, others Failed
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspSend(u32 dstiid, u16 event, const void *content = 0, u16 length = 0, u32 dstnode = 0,
				u32 srciid = MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE,
				void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
				u16 timeout = 1000);

/* used only in C++ environment */
int OspSend(const char *dstalias, u8 aliaslen, u16 dstapp, u16 event,
			const void *content = 0, u16 length = 0, u32 dstnode = 0,
			u32 srciid = MAKEIID(INVALID_APP, INVALID_INS), u32 srcnode = INVALID_NODE,
			void *ackbuf = NULL, u16 ackbuflen = 0, u16 *realacklen = NULL,
			u16 timeout = 1000);

/*====================================================================
��������IsOspInitd
���ܣ��ж�OSP�Ƿ��ѳ�ʼ������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����OSP�ѳ�ʼ��������TRUE�����򷵻�FALSE.
====================================================================*/
API BOOL32 IsOspInitd(void);

/*=============================================================================
�� �� ����OspInit
��    �ܣ�initialize OSP module
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����TelNetEnable : [in] start telnet.exe
          TelNetPort : [in] osp telnet server port
          pchModuleName : [in] process module name��maxlength = 63
�� �� ֵ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
#define MAX_MODULE_NAME_LENGTH 63
API BOOL32 OspInit(BOOL32 TelNetEnable = FALSE, u16 TelNetPort = 0, const char *pchModuleName = NULL, u32 dwMaxNodeNum = 512, u32 dwMaxDispatchMsg = 1024 );

/*====================================================================
��������OspQuit
���ܣ��˳�OSP�����ñ�������APP������ʵ����InstanceExit�������˳�ʵ����
�Ͽ�����OSP��㣬��������OSP�������APP��Ȼ�󷵻ء�OSP�˳�֮��
����OSP���񽫲���ʹ�á�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspQuit(void);

/*=============================================================================
�� �� ����OspSetPrompt
��    �ܣ������ն���ʾ��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API BOOL32 OspSetPrompt(const char *prompt);

/*====================================================================
��������OspStopScrnLog
���ܣ���ͣ��Ļ��־���.
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵������

 ����ֵ˵������.
====================================================================*/
API void OspStopScrnLog(void);

/*====================================================================
��������OspResumeScrnLog
���ܣ��ָ���Ļ��־���.
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵������

 ����ֵ˵������.
====================================================================*/
API void OspResumeScrnLog(void);

/*=============================================================================
�� �� ����OspGetLocalID
��    �ܣ�����ȫ�ֱ��
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��int - ����ȫ�ֱ��
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API int OspGetLocalID(); // ����ȫ�ֱ��

/*=============================================================================
�� �� ����OspEventDesc
��    �ܣ�������Ϣ������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u16 wEventID : [in]��Ϣ��ID
�� �� ֵ��const char *  ��Ϣ�������������ϢID��Ч���߸���Ϣû�������ַ���������
ֵ��ΪNULL��
-------------------------------------------------------------------------------
�޸ļ�¼��
��   ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API const char *OspEventDesc( u16 wEventID );

/*=============================================================================
�� �� ����OspEventDescShow
��    �ܣ���ʾ��Ϣ������
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����u16 wEventID : [in]��Ϣ��ID
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void OspEventDescShow( u16 wEventID );

/*=============================================================================
�� �� ����osphelp
��    �ܣ�inline help function of OSP module
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����const char * pszTopic : [in] which topic's help infomation to be shown
�� �� ֵ��void
-------------------------------------------------------------------------------
�޸ļ�¼��
��      ��  �汾  �޸���  �޸�����
2002/05/23  1.0
=============================================================================*/
API void osphelp(void);

/*====================================================================
��������OspSemBCreate
���ܣ�����һ����Ԫ�ź���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(out)ptSemHandle ���ص��ź������

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
API BOOL32 OspSemBCreate(SEMHANDLE *ptSemHandle);

/*====================================================================
��������OspSemCCreate
���ܣ����������ź���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(out)ptSemHandle �ź���������ز�����
(in)initcount ��ʼ������
(in)MaxSemCount ������

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
API BOOL32 OspSemCCreate(SEMHANDLE *ptSemHandle, u32 initcount, u32 MaxSemCount);

/*====================================================================
��������OspSemDelete
���ܣ�ɾ���ź���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(in)tSemHandle ��ɾ���ź����ľ��

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
API  BOOL32 OspSemDelete(SEMHANDLE tSemHandle );

/* 5.0�ϲ��� ԭ��ҵosp���нӿ� */
/*====================================================================
��������OspSetNodeAppId
���ܣ�Ϊ�ڵ����ù���appid
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(in)nNodeId �����õĽڵ��
             (in) ���õ�appid

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
API BOOL32 OspSetNodeAppId(int nNodeId, u16 wAid);

/*====================================================================
��������OspSemTake
���ܣ��ź���p����������ź��������ã�����������ʵ����������(APP)
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(in)tSemHandle �ź������

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
API BOOL32  OspSemTake(SEMHANDLE tSemHandle );

/*====================================================================
��������OspSemTakeByTime
���ܣ�����ʱ���ź���p���������ź��������ã���ʱ������dwtime����󣬳�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(in)tSemHandle �ź������, (in)dwtime ��ʱ���(��msΪ��λ)

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
API BOOL32 OspSemTakeByTime(SEMHANDLE tSemHandle, u32 dwtime);

/*====================================================================
��������OspSemGive
���ܣ��ź���v����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(in)tSemHandle �ź������

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE.
====================================================================*/
API BOOL32 OspSemGive(SEMHANDLE tSemHandle );

/*====================================================================
��������OspTaskCreate
���ܣ�������ִ��һ������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
#ifdef _LINUX_
API TASKHANDLE OspTaskCreate(LINUXFUNC pvTaskEntry, const char *szName, u8 byPriority, u32 dwStacksize, u32 dwParam, u16 wFlag, u32 *puTaskID = NULL);
#else
API TASKHANDLE OspTaskCreate(void *pvTaskEntry, const char *szName, u8 byPriority, u32 dwStacksize, u32 dwParam, u16 wFlag, u32 *puTaskID = NULL);
#endif


/*====================================================================
  ��������OspTaskSetAffinity
  ���ܣ�
  ��װ
  �㷨ʵ�֣�����ѡ�
  ����ȫ�ֱ�����
  �������˵����hTaskHandle:windows�µ��߳�/���̵ľ����hTaskId:�󶨵��߳�/����/�����ID��
                dwCpuId:��󶨵�CPU(��0��ʼ����,��εݼ�)
                byTaskType���󶨵��߳�/����/��������ͣ�0--�̣߳�1-���̣�����-���񣩣�linux��Ĭ��0����
                pdwPreviousBind�����֮ǰ�ý���/�߳�/���񱻰󶨵�ĳCPU����᷵�ظ�CPU�ţ���Solaris����Ч��
  ����ֵ˵�����ɹ�����TRUE, ʧ�ܷ���FALSE.
  ====================================================================*/
#ifdef _MSC_VER
API BOOL32 OspTaskSetAffinity( TASKHANDLE hTaskHandle, u32 dwCpuId, u8 byTaskType = 0, u32 *pdwPreviousBind = NULL);
#else
API BOOL32 OspTaskSetAffinity( u64 hTaskId, u32 dwCpuId, u8 byTaskType = 0, u32 *pdwPreviousBind = NULL);
#endif

/* 5.0�ϲ��� ����raw��Ϣ�Ľӿ� */
API int OspPostRaw(int nNodeId , const void *content , u32 dwLen);

/*====================================================================
��������OspTaskExit
���ܣ��˳��������������˳�֮ǰ�û�Ҫע���ͷű�����������ڴ桢�ź�������Դ��
��װWindows��ExitThread(0)��vxWorks��taskDelete(0)��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskExit(void);

/*====================================================================
��������OspTaskTerminate
���ܣ�ǿ����ָֹ������
��װWindows��ExitThread()��vxWorks��taskDelete()��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����handle--��ɱ�����handle

 ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskTerminate(TASKHANDLE handle);

/*====================================================================
��������OspTaskSuspend
���ܣ�����ǰ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskSuspend(TASKHANDLE handle = 0);

/*====================================================================
��������OspTaskResume
���ܣ�����ǰ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskResume(TASKHANDLE handle);

/*====================================================================
��������OspTaskSetPriority
���ܣ��ı���������ȼ���

 �㷨ʵ�֣�����ѡ�
 ����ȫ�ֱ�����
 �������˵����

  ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskSetPriority(TASKHANDLE taskHandle, u8 newPriority, int newSchedPolicy = 0);

/*====================================================================
��������OspTaskGetPriority
���ܣ������������ȼ���

 �㷨ʵ�֣�����ѡ�
 ����ȫ�ֱ�����
 �������˵����

  ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskGetPriority(TASKHANDLE taskHandle, u8 *puPri, int *SchedPolicy = NULL);

/*====================================================================
��������OspSetTaskPriorityByName
���ܣ�ͨ��������������������ȼ�linux����Ч

 �㷨ʵ�֣�����ѡ�
 ����ȫ�ֱ�����
 �������˵����

  ����ֵ˵����
====================================================================*/
API void OspSetTaskPriorityByName(s8 *name , u8 priority, int newSchedPolicy = 0);

//���������, Linux��ʹ�õ�����task nice���ȼ��Ľӿ�.
//����ӿڿ���ȥ��, ���漰������Ѷ��һЩҵ�������޸�, ��ʱ�ȱ���. ���������پ���.
/*====================================================================
��������OspSetTaskNiceByName
���ܣ�ͨ�����������������ʱ��Ƭ��С��linux����Ч
 �㷨ʵ�֣�����ѡ�
 ����ȫ�ֱ�����
 �������˵����

  ����ֵ˵����
====================================================================*/
API void OspSetTaskNiceByName(s8 *name , int nice);

/*====================================================================
��������OspSetTaskPriorityByName
���ܣ�ͨ����������ȡ��������ȼ�

 �㷨ʵ�֣�����ѡ�
 ����ȫ�ֱ�����
 �������˵����

  ����ֵ˵����
====================================================================*/
API void OspGetTaskPriorityByName(s8 *name , u8 *priority, int *newSchedPolicy = NULL);

/*====================================================================
��������OspTaskSelfHandle
���ܣ���õ�������ľ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API TASKHANDLE OspTaskSelfHandle(void);

/*====================================================================
��������OspTaskSelfHandle
���ܣ���õ��������ID
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API u32 OspTaskSelfID(void);

/*====================================================================
��������OspTaskHandleVerify
���ܣ��ж�ָ�������Ƿ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspTaskHandleVerify(TASKHANDLE handle);

/*====================================================================
��������OspTaskSafe
���ܣ������������񲻱��Ƿ�ɾ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspTaskSafe(void);

/*====================================================================
��������OspTaskUnsafe
���ܣ��ͷŵ��������ɾ��������ʹ�õ���������Ա���ȫɾ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API void OspTaskUnsafe(void);

/*====================================================================
��������OspTaskDelay
���ܣ�������ʱ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����uMseconds--��ʱ���(ms)

 ����ֵ˵����
====================================================================*/
#define OspDelay                      OspTaskDelay

API void OspTaskDelay(u32 dwMseconds);

/*====================================================================
��������OspCreateMailbox
���ܣ�������Ϣ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
//�������޸�szName����, ��char*��Ϊconst char*
API BOOL32 OspCreateMailbox(const char *szName, u32 dwMsgNumber, u32 dwMsgLength , u32 *puQueueIDRead, u32 *puQueueIDWrite);

/*====================================================================
��������OspCloseMailbox
���ܣ��ر�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����uQueueIDRead, uQueueIDWrite--����Ķ���д���

 ����ֵ˵����
====================================================================*/
API void OspCloseMailbox(u32 dwQueueIDRead, u32 dwQueueIDWrite);

/*====================================================================
������      ��OspSndMsg
����        �������䷢��Ϣ
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵����tQueueID: ����ID,
lpMsgBuf: ����ָ��,
len: ����,
timeout: ��ʱֵ(ms). Windows�¸ò�����Ч, ��������һֱ����ֱ���пյ�buffer.
VxWorks��, ȱʡΪ2��;
OSP_NO_WAIT(0): ��������������;
OSP_WAIT_FOREVER(-1): ����������ֱ���пյ�buffer.

 ����ֵ˵��  ���ɹ�����TRUE, ʧ�ܻ�ʱ����FALSE.
====================================================================*/
API BOOL32 OspSndMsg(u32 tQueueID, const char *lpMsgBuf, u32 len, int timeout = 2000);

/*====================================================================
������      ��OspRcvMsg
����        ������������Ϣ
�㷨ʵ��    ��
����ȫ�ֱ�������
�������˵����
OSTOKEN tQueueID    ����ID
u32  dwTimeout   ��ʱ(����)
LPVOID *lpMsgBuf    ������Ϣ����ָ��
����ֵ˵��  ��
====================================================================*/
API BOOL32 OspRcvMsg(u32 tQueueID, u32  dwTimeout, char *lpMsgBuf, u32 len, u32 *pLenRcved);

/*====================================================================
��������OspClkRateGet
���ܣ��õ�tick���ȣ�n ticks/sec
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API u32 OspClkRateGet();

/*====================================================================
��������OspTickGet
���ܣ�ȡ�õ�ǰ��tick��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API u32 OspTickGet();


/*====================================================================
��������OspTickGet64
���ܣ�ȡ�õ�ǰ��tick��,64���ȣ�����������
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API u64 OspTickGet64();



API void OspCpuShow();

//CPU��Ϣ
typedef struct {
	// ���аٷֱȣ�0��100
	u8 m_byIdlePercent;
} TOspCpuInfo;

/*====================================================================
��������OspGetCpuInfo
���ܣ�ȡ�õ�ǰ��CPU��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptCpuInfo���û�CPU��Ϣ�ṹ
����ֵ˵����ΪTRUEʱ��ʾ��ȡ��Ϣ�ɹ��������ʾʧ��
====================================================================*/
API BOOL32 OspGetCpuInfo( TOspCpuInfo *ptCpuInfo );

//�ڴ���Ϣ
typedef struct {
	//�����ڴ��С(KByte)
	u32 m_dwPhysicsSize;
	//��ʹ���ڴ�(KBytes)
	u32 m_dwAllocSize;
	//�����ڴ�(KBytes)
	u32 m_dwFreeSize;
} TOspMemInfo;

/*====================================================================
��������OspGetMemInfo
���ܣ�ȡ�õ�ǰ��Mem��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptMemInfo���û�MEM��Ϣ�ṹ
����ֵ˵����ΪTRUEʱ��ʾ��ȡ��Ϣ�ɹ��������ʾʧ��
====================================================================*/
API BOOL32 OspGetMemInfo( TOspMemInfo *ptMemInfo );

//ʱ����Ϣ
typedef struct {
	//��(2006)
	u16 m_wYear;
	//��(1--12)
	u16 m_wMonth;
	//��(1--31)
	u16 m_wDay;
	//ʱ(0--23)
	u16 m_wHour;
	//��(0--59)
	u16 m_wMinute;
	//��(0--59)
	u16 m_wSecond;
} TOspTimeInfo;

/*====================================================================
��������OspGetTimeInfo
���ܣ�ȡ�õ�ǰ��Time��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptTimeInfo��ϵͳtime��Ϣ�ṹ
����ֵ˵����ΪTRUEʱ��ʾ��ȡ��Ϣ�ɹ��������ʾʧ��
====================================================================*/
API BOOL32 OspGetTimeInfo( TOspTimeInfo *ptTimeInfo );

/*====================================================================
��������OspSetTimeInfo
���ܣ����õ�ǰ��Time��Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����ptTimeInfo��ϵͳtime��Ϣ�ṹ
����ֵ˵����ΪTRUEʱ��ʾ��ȡ��Ϣ�ɹ��������ʾʧ��
====================================================================*/
API BOOL32 OspSetTimeInfo( TOspTimeInfo *ptTimeInfo );

//���̷�����Ϣ
typedef struct {
	//���̷�����С(MByte)
	u32 m_dwPhysicsSize;
	//��ʹ�ô��̷�����С(MBytes)
	u32 m_dwUsedSize;
	//���ô��̷�����С(MBytes)
	u32 m_dwFreeSize;
} TOspDiskInfo;
//���̷�����󳤶�
#define MAX_PARTION_NAME_LENGTH     255
/*====================================================================
��������OspGetDiskInfo
���ܣ�ȡ�õ�ǰ�Ĵ��̷�����Ϣ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����s8 *pchPartionName�� ������
                    win32 : "c:"
                    Vxworks : "/ata0/"
                    Linux : "/"
              ptDiskInfo��ϵͳ���̷�����Ϣ�ṹ
����ֵ˵����ΪTRUEʱ��ʾ��ȡ��Ϣ�ɹ��������ʾʧ��
====================================================================*/
API BOOL32 OspGetDiskInfo( s8 *pchPartionName , TOspDiskInfo *ptDiskInfo );

//////////////////////////////////////////////////////////////////////
//	�׽��ַ�װ���û�ʹ���׽���ǰ�����ȵ���SockInit()���׽��ֿ���г�ʼ����
//	ʹ����֮������Ҫ����SockCleanup()�ͷŶ��׽��ֿ��ʹ�á�����vxWorks��
//	Windows�Ĺر��׽��ֵĺ�����ͬ�������ڵ���socket��connect�Ⱥ���ʱ������
//	ֵ����Ҳ��һ����OSPҲ�����˱�Ҫ�ķ�װ��ԭ���Ǳ�����Windows�»���һ�¡�
/////////////////////////////////////////////////////////////////////

/*====================================================================
��������SockInit
���ܣ��׽��ֳ�ʼ������װWindows�µ�WSAStartup��vxWorks�·���TRUE
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
API BOOL32 SockInit(void);

/*====================================================================
��������SockShutdown
���ܣ��Ը�ƽ̨shutdown�ļ򵥷�װ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����hSock--Ҫ�������׽��֣�
              dwMode--����ģʽ, ��ȡֵΪSTOP_SEND, STOP_RECV��STOP_BOTH

����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
API BOOL32 SockShutdown(SOCKHANDLE hSock, u32 uMode);

/*====================================================================
��������SockClose
���ܣ��ر��׽��֣���װwindows�µ�closesocket��vxworks�µ�close.
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����tSock--���ر��׽��ֵľ��������socketʱ���أ���

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
API BOOL32 SockClose(SOCKHANDLE tSock);

/*====================================================================
��������SockCleanup
���ܣ��׽������٣���װwindows��WSACleanup��vxWorks�·���TRUE
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵�����ɹ�����TRUE��ʧ�ܷ���FALSE
====================================================================*/
API BOOL32 SockCleanup(void);

// ���ڷ�װ����Windows���ڲ�������Ϊ׼����VxWorks���ṩ��Ӧ����
/*====================================================================
��������OspSerialOpen
���ܣ���ָ���Ĵ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵�����ɹ����ش򿪴��ڵľ����ʧ�ܷ���INVALID_SERIALHANDLE
====================================================================*/
API SERIALHANDLE OspSerialOpen(u8 port);

/*====================================================================
��������OspSerialClose
���ܣ��ر�ָ���Ĵ���
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspSerialClose(SERIALHANDLE hCom);

/*====================================================================
��������OspSerialRead
���ܣ���ָ���Ĵ��ڶ�����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspSerialRead(SERIALHANDLE hCom, char *pchBuf, u32 dwu8sToRead, u32 *puu8sRead);

/*====================================================================
��������OspSerialWrite
���ܣ���ָ���Ĵ���д����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspSerialWrite(SERIALHANDLE hCom, char *pchBuf, u32 dwu8sToWrite, u32 *puu8sWrite);

/*====================================================================
��������OspSetCommTimeouts
���ܣ����ô��ڳ�ʱ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspSetCommTimeouts(SERIALHANDLE hCom, TOspCommTimeouts *ptCommTimeouts);

/*====================================================================
��������OspGetCommState
���ܣ���ô���״̬
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspGetCommState(SERIALHANDLE hCom, TOspDCB *ptDCB);

/*====================================================================
��������OspSetCommState
���ܣ����ô���״̬
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspSetCommState(SERIALHANDLE hCom, TOspDCB *ptDCB);

/*====================================================================
��������OspEscapeCommFunction
���ܣ�ʹ�ô�����չ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspEscapeCommFunction(SERIALHANDLE hCom, u32 dwFunc);

/*====================================================================
��������OspPurgeComm
���ܣ���������δ�����ݣ���ֹ���ڶ�д����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspPurgeComm(SERIALHANDLE hCom, u32 dwFlags);

/*====================================================================
��������OspClearCommError
���ܣ���Windows��ClearCommError��ͬ
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspClearCommError(SERIALHANDLE hCom, u32 *pdwErrors, TOspComStat *ptStat);

/*====================================================================
��������OspGetCommTimeouts
���ܣ�ȡ�ô򿪴��ڵĳ�ʱ����
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵����
====================================================================*/
API BOOL32 OspGetCommTimeouts(SERIALHANDLE hCom, TOspCommTimeouts *ptCommTimeouts);

/*====================================================================
��������OspAgentStart
���ܣ�����һ��Osp���Դ���, ���а���һ�����Է�����APP��һ���ͻ���APP, ����
��Ҫ��ͬ��APP��, ��Ϣ������̶���һ����.
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����(in)port -- �˿ں�, ��������APP��������ڵ����øö˿ڴ���֮

 ����ֵ˵����
====================================================================*/
API int OspAgentStart(u16 port);

/*====================================================================
��������OspAllocMem
���ܣ����ڴ���з����ڴ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����size: ��������ڴ���С��

 ����ֵ˵�����ɹ�����ָ����䵽���ڴ���ָ�룬ʧ�ܷ���NULL.
====================================================================*/
API void *OspAllocMem(size_t size);

/*====================================================================
��������OspFreeMem
���ܣ��ͷ����ȷ�����ڴ��
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����token: ָ����ͷŵ��ڴ���ָ�롣

 ����ֵ˵������.
====================================================================*/
API void OspFreeMem(void *token);

/*====================================================================
��������OspSetPriRealTime
���ܣ��Ѷ�ʱ������Ϣ���͵�������ߵ���ϵͳnet���񻹸ߵ����ȼ�
�㷨ʵ�֣�����ѡ�
����ȫ�ֱ�����
�������˵����

 ����ֵ˵������.
====================================================================*/
API void OspSetPriRealTime();

/*=============================================================================
�� �� ����OspAddrListGet
��    �ܣ���ȡ������ַ������
ע    �⣺�������Windows��ʹ�ñ������������ȵ���OspInit������WSAStartup��
������Ч�ʽϵͣ���Ҫ�ظ����á�
�㷨ʵ�֣�
ȫ�ֱ�����
��    ���� u32   adwIP[] : [in/out]�û���������ڵ�ַ�����ݵ�������׵�ַ
u16   wNum : [in]�û����������Ĵ�С
�� �� ֵ�� ���ر�����ַ���е�ַ����������ʱ����0
=============================================================================*/
API u16  OspAddrListGet(u32 adwIPList[], u16 wNum);

/* 5.0�ϲ��� ԭ��ҵosp���нӿ� */
/*=============================================================================
�� �� ����OspGetTelServerPort
��    �ܣ���ȡtelnet server�Ķ˿ں�.
ע    �⣺���û������telnet server, ����û�г�ʼ��Osp, ����-1
�㷨ʵ�֣�N/A
ȫ�ֱ�����N/A
��    ����N/A
�� �� ֵ�� ����telnet server��listen�˿ں�, ���û������, ����-1
=============================================================================*/
API s32 OspGetTelServerPort();

/*=============================================================================
�� �� ����OspPton
��    �ܣ�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��
=============================================================================*/
API s32 OspPton(s32 af, const char *src, void *dst);

/*=============================================================================
�� �� ����OspNtop
��    �ܣ�
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����
�� �� ֵ��
=============================================================================*/
API const char *OspNtop(s32 af, const void *src, char *dst, u32 size);

#if (defined(_MSC_VER) && (_MSC_VER > 1200)) || !defined(_MSC_VER)

#define OSP_IS_VALID_LOCAL_ADDR(netaddr)   \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 && (netaddr)->v6addr.sin6_port)))

#define OSP_IS_VALID_REMOTE_ADDR(netaddr)    \
    ((netaddr) &&   \
    (((netaddr)->v4addr.sin_family == AF_INET &&    \
        (netaddr)->v4addr.sin_addr.s_addr && (netaddr)->v4addr.sin_port) || \
    ((netaddr)->v6addr.sin6_family == AF_INET6 &&   \
        (netaddr)->v6addr.sin6_port)))

/*=============================================================================
 �� �� ����OSP_SET_NETADDR_ADDR
 ��    �ܣ�IPV4�����ֽ����ַ���õ�TNetAddr�ṹ��
 ע    �⣺ֻ����IPV4������ĵ�ַ��ʱ
 �㷨ʵ�֣�
 ȫ�ֱ�����
 ��    ����netaddr: TOspNetAddr�ṹ��
           type: AF_INET(ipv4) ���� AF_INET6(ipv6)
           address: u32�������ַ
 �� �� ֵ��
=============================================================================*/
#define OSP_SET_NETADDR_ADDR(netaddr, type, address)    \
    do {    \
        switch(type) {    \
        case AF_INET:   \
            (netaddr)->v4addr.sin_family = (type);      \
            (netaddr)->v4addr.sin_addr.s_addr = (address);   \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/*=============================================================================
 �� �� ����OSP_GET_NETADDR_ADDR
 ��	  �ܣ���ȡTNetAddr�ṹ���е������ֽ����ַ��address,
           ��ȡTNetAddr�ṹ���е�type��type
 ע	  �⣺
 �㷨ʵ�֣�
 ȫ�ֱ�����
 ��    ����netaddr: TOspNetAddr�ṹ��
           type: ������͵�ָ��
           address: ��ŵ�ַ��ָ��

 �� �� ֵ��
=============================================================================*/
#define OSP_GET_NETADDR_ADDR(netaddr, type, address)    \
	do {	\
		switch((netaddr)->staddr.ss_family) {	  \
		case AF_INET:	\
			*(type) = (netaddr)->v4addr.sin_family;		\
			*(address) = (netaddr)->v4addr.sin_addr.s_addr;	 \
			break;		\
		case AF_INET6:	\
			*(type) = (netaddr)->v6addr.sin6_family; 	\
			break;	\
		default:	\
			break;	\
		}	\
	} while(0)

/*=============================================================================
  �� �� ����OSP_SET_NETADDR_ADDR_STR
  ��    �ܣ�����ַ�ַ������õ�netaddr�ṹ��
  ע    �⣺
  �㷨ʵ�֣�
  ȫ�ֱ�����
  ��    ����netaddr: TOspNetAddr�ṹ��
		   type: AF_INET(ipv4) ���� AF_INET6(ipv6)
		   address: ��ַ�ַ���ָ��

 �� �� ֵ��
=============================================================================*/
#define OSP_SET_NETADDR_ADDR_STR(netaddr, type, address)    \
    do {    \
        switch(type) {      \
        case AF_INET:       \
            (netaddr)->v4addr.sin_family = (type);      \
            if (address)    \
                OspPton(type, address, &((netaddr)->v4addr.sin_addr.s_addr));\
            else        \
                (netaddr)->v4addr.sin_addr.s_addr = INADDR_ANY;    \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            if (address)    \
                OspPton(type, address, &((netaddr)->v6addr.sin6_addr.s6_addr));  \
            else    \
                memcpy(&(netaddr)->v6addr.sin6_addr, &in6addr_any, sizeof(in6addr_any));  \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/*=============================================================================
  �� �� ����OSP_GET_NETADDR_ADDR_STR
  ��    �ܣ���ȡTNetAddr�ṹ���еĵ�ַ�ַ�����address,
            ��ȡTNetAddr�ṹ���е�type��type
  ע    �⣺
  �㷨ʵ�֣�
  ȫ�ֱ�����
  ��    ����netaddr: TOspNetAddr�ṹ��
		   type: ������͵�ָ��
		   address: ��ַ�ַ���ָ��
		   size: address��ַ�ĳ���

 �� �� ֵ��
=============================================================================*/
#define OSP_GET_NETADDR_ADDR_STR(netaddr, type, address, size)    \
	do {	\
		if (type)    \
		    *(type) = (netaddr)->staddr.ss_family;		\
		switch((netaddr)->staddr.ss_family) {		\
		case AF_INET:		\
			if (address)	\
				OspNtop((s32)type, &((netaddr)->v4addr.sin_addr.s_addr), address, size);\
			break;		\
		case AF_INET6:	\
			if (address)	\
				OspNtop((s32)type, &((netaddr)->v6addr.sin6_addr.s6_addr), address, size);  \
			break;	\
		default:	\
			break;	\
		}	\
	} while(0)

/*=============================================================================
  �� �� ����OSP_SET_NETADDR_PORT
  ��    �ܣ��ṩ������˿ں����õ�TNetAddr ��
  ע    �⣺
  �㷨ʵ�֣�
  ȫ�ֱ�����
  ��    ����netaddr: TOspNetAddr�ṹ��
		   type: AF_INET(ipv4) ���� AF_INET6(ipv6)
            port:������˿ں�

 �� �� ֵ��
=============================================================================*/
#define OSP_SET_NETADDR_PORT(netaddr, type, port)    \
    do {    \
        switch(type) {    \
        case AF_INET:   \
            (netaddr)->v4addr.sin_family = (type);      \
            (netaddr)->v4addr.sin_port = htons(port);   \
            break;      \
        case AF_INET6:  \
            (netaddr)->v6addr.sin6_family = (type);     \
            (netaddr)->v6addr.sin6_port = htons(port);  \
            break;  \
        default:    \
            break;  \
        }   \
    } while(0)

/*=============================================================================
  �� �� ����OSP_GET_NETADDR_PORT
  ��    �ܣ���ȡTNetAddr�ṹ���ж˿ںŵ�port
		   ��ȡTNetAddr�ṹ���е�type��type
  ע    �⣺
  �㷨ʵ�֣�
  ȫ�ֱ�����
  ��    ����netaddr: TOspNetAddr�ṹ��
		   type: ������͵�ָ��
		   port: ���������˿ںŵ�ָ��

 �� �� ֵ��
=============================================================================*/
#define OSP_GET_NETADDR_PORT(netaddr, type, port)    \
	do {	\
		if (type)    \
		    *(type) = (netaddr)->staddr.ss_family;    \
		switch((netaddr)->staddr.ss_family) {	  \
		case AF_INET:	\
			if (port)   \
			    *(port) = ntohs((netaddr)->v4addr.sin_port);	\
			break;		\
		case AF_INET6:	\
			if (port)   \
			    *(port) = ntohs((netaddr)->v6addr.sin6_port);	\
			break;	\
		default:	\
			break;	\
		}	\
	} while(0)

#endif

//ϵͳ���Ʋ���
#define OSP_ETHERNET_ADAPTER_MAX_IP 16          /*ÿ���ӿ�������ַ����*/
#define OSP_ETHERNET_ADAPTER_MAX_NUM 32         /*ÿ���豸���ӿ���*/
#define OSP_ETHERNET_ADAPTER_NAME_LENGTH 64 /*ÿ���ӿ�������󳤶�*/
#define OSP_ETHERNET_ADAPTER_MAC_LENGTH 6       /*�ӿڵ�MAC��ַ����*/

//����״̬,��Ӧ��TOSPEthernetAdapterInfo �ṹ��nState�ֶ�
#define OSP_ETHERNET_ADAPTER_UNKNOWN 0
#define OSP_ETHERNET_ADAPTER_UP 1
#define OSP_ETHERNET_ADAPTER_DOWN 2

/* ����������Ϣ */
typedef struct {
	u32 nId;                                        /*������*/
	u32 nState;                                     /*����״̬*/
	u8  achName[OSP_ETHERNET_ADAPTER_NAME_LENGTH];      /*������*/
	u8  achDescription[OSP_ETHERNET_ADAPTER_NAME_LENGTH];   /*������Ϣ����*/
	u8  achMacAddr[OSP_ETHERNET_ADAPTER_MAC_LENGTH];        /*���������ַ*/
	u32 nIpNum;                                     /*��ַ����*/
	u32 anIp[OSP_ETHERNET_ADAPTER_MAX_IP];              /*��ַ*/
} TOSPEthernetAdapterInfo;

/* ���������Ϣ */
typedef struct {
	u32 nNum;                                                       /*��������*/
	TOSPEthernetAdapterInfo atEthernetAdapter[OSP_ETHERNET_ADAPTER_MAX_NUM];/*������Ϣ*/
} TOSPEthernetAdapterInfoAll;


/*=============================================================================
�� �� ����OspGetEthernetAdapterInfoAll
��    �ܣ���ȡ��ϵͳ������̫��������Ϣ
ע    �⣺�������Windows��ʹ�ñ������������ȵ���OspInit������WSAStartup��
������Ч�ʽϵͣ���Ҫ�ظ����á�
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����TEthernetAdapterInfoAll ��������Ϣ�ṹ���ο����ݽṹ�Ķ���
�� �� ֵ�� TRUE/ FALSE �ɹ�/ʧ��
=============================================================================*/
API BOOL32 OspGetEthernetAdapterInfoAll(TOSPEthernetAdapterInfoAll *ptEthernetAdapterInfoAll);

/*=============================================================================
�� �� ����OspGetEthernetAdapterInfo
��    �ܣ����������Ż�ȡ������Ϣ
ע    �⣺�������Windows��ʹ�ñ������������ȵ���OspInit������WSAStartup��
������Ч�ʽϵͣ���Ҫ�ظ����á�
�㷨ʵ�֣�
ȫ�ֱ�����
��    ����nEthAdapterId �������0-ETHERNET_ADAPTER_MAX_NUM�����֧��16������
            TEthernetAdapterInfo ��������Ϣ�ṹ
�� �� ֵ��TRUE/FALSE  �ɹ�/ʧ��
=============================================================================*/
API BOOL32 OspGetEthernetAdapterInfo(u32 nEthAdapterId, TOSPEthernetAdapterInfo *ptEthernetAdapterInfo);






/*=============================================================================
�� �� ����OspSetMemCheck
��    �ܣ���ȡ�ڴ��ַ����
ע    �⣺
�㷨ʵ�֣�
ȫ�ֱ�����
��    ���� u32 * pdwCheckMem :  Ҫ�����ڴ��ַ
u32 dwCheckValue ��  ��������ֵ
BOOL32  bEqual ����������Ϊ��ʱ����ʾҪ�����ڴ��ַ���ݲ���������ֵʱ��Ҫ�澯
��������Ϊ��ʱ����ʾҪ�����ڴ��ַ���ݵ�������ֵʱ��Ҫ�澯
�� �� ֵ�� �ɹ�����TRUE, ʧ�ܷ���FALSE.
=============================================================================*/
API BOOL32  OspSetMemCheck(u32 *pdwCheckMem, u32 dwCheckValue, BOOL32  bEqual);

/* ������Ա������ģ�����Ա������ʵ�� */
template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTemplate<I, maxins, A, maxAliasLen>::InitAliasArray()
{
	for(int i = 0; i < maxins; i++) {
		instAliasArray[i].instId = 0xFFFF;
		instAliasArray[i].aliasRet = 0;
		instAliasArray[i].nextLoc = 0xFFFF;

		bakInstAliasArray[i].instId = 0xFFFF;
		bakInstAliasArray[i].aliasRet = 0;
		bakInstAliasArray[i].nextLoc = 0xFFFF;
	}
	curBakArrayNum = 0;

	return TRUE;
}

template <class I, int maxins, class A, u8 maxAliasLen>
u32 zTemplate<I, maxins, A, maxAliasLen>::AliasToWord(char *pchAlias, u8 len)
{
	u32  ret = 0;
	for(u8 i = 0; i < len; i++ ) {
		ret =  (ret << 5) + ret + (*(pchAlias + i));
	}

	ret = ret & (maxins - 1);
	return  ret;
}

template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTemplate<I, maxins, A, maxAliasLen>::IsInBakArray(u32  setRet)
{
	/*���ȼ��������*/
	if(instAliasArray[setRet].instId == 0xFFFF) {  /*�����������λ�û�û�б�ռ��*/
		return FALSE;     /*���ʵ����ŵ���������*/
	} else {     /*�����������λ�û��Ѿ���ռ��*/
		return TRUE;   /*���ʵ����ŵ�bak�����еĿ���λ��*/
	}
}

template <class I, int maxins, class A, u8 maxAliasLen>
int zTemplate<I, maxins, A, maxAliasLen>::GetInstanceNumber(void)
{
	return maxins;
}

template <class I, int maxins, class A, u8 maxAliasLen>
u8 zTemplate<I, maxins, A, maxAliasLen>::GetMaxAliasLen(void)
{
	return maxAliasLen;
}

template <class I, int maxins, class A, u8 maxAliasLen>
CInstance *zTemplate<I, maxins, A, maxAliasLen>::GetInstance(u16 insid)
{
	if(insid == CInstance::DAEMON)
		return &daemIns;

	if((insid > 0) && (insid <= maxins))
		return &insarray[insid - 1];

	return NULL;
}

template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTemplate<I, maxins, A, maxAliasLen>::SetInstAlias(u16 insid, const char *pchAlias, u8 len)
{
	u32  dwCycTime = 0;

	/*�ȰѼ�¼��Ϣ������ٲ���������*/
	if(insid != CInstance::DAEMON) {
		u32 setRet = AliasToWord((char *)pchAlias, len);    /*ͨ��������������ֵ*/
		if(setRet >= maxins)
			return FALSE;

		BOOL32  isBak = IsInBakArray(setRet);   /*ȷ�����λ��*/
		if( isBak == FALSE) {   /*�������������*/
			instAliasArray[setRet].aliasRet = setRet;
			instAliasArray[setRet].instId = insid;
			instAliasArray[setRet].nextLoc = 0xFFFF;   /*��ʼ��*/
		} else {     /*�����bak������*/
			u32 loc = curBakArrayNum;
			/*�����ݼ�¼��bak������Ӧλ����*/
			for(loc = 0; loc < maxins; loc++) {
				if(bakInstAliasArray[loc].instId == 0xFFFF)
					break;
			}
			if(loc >= maxins) {
				return FALSE;
			}

			bakInstAliasArray[loc].aliasRet = setRet;
			bakInstAliasArray[loc].instId = insid;
			bakInstAliasArray[loc].nextLoc = 0xFFFF;   /*��ʼ��*/

			/*����ͬ����ֵ�����ݿ���������*/
			if(instAliasArray[setRet].nextLoc == 0xFFFF) { /*����������δ����*/
				instAliasArray[setRet].nextLoc = loc;   /*ָ��bak�����д��λ��*/
			} else {
				TInstAliasInfo *tempAlias = &bakInstAliasArray[instAliasArray[setRet].nextLoc];
				if(tempAlias == NULL)
					return FALSE;

				dwCycTime = 0;
				while(tempAlias->nextLoc != 0xFFFF) {
					if(tempAlias->nextLoc >= maxins)
						return FALSE;

					tempAlias = &bakInstAliasArray[tempAlias->nextLoc];
					if(tempAlias == NULL)
						return FALSE;

					dwCycTime++;
					if(dwCycTime > maxins) {
						OspPrintf(TRUE, FALSE, "SetInstAlias() return Cycle as dwCycTime=%d\n", dwCycTime);
						return FALSE;
					}
				}

				tempAlias->nextLoc = loc; /*�ҵ�bak���������һ����ͬ����ֵ��λ��*/
			}

			curBakArrayNum++;     /*bak�����Ÿ�������*/
		}
	}

	CInstance *pIns = GetInstance(insid);
	if( pIns != NULL && len <= maxAliasLen) {
		CInstance *pOtherIns = FindInstByAlias(pchAlias, len);
		if( (pOtherIns != NULL) && (pOtherIns->GetInsID() != pIns->GetInsID()) ) {
			return FALSE;
		}
		memcpy(pIns->m_alias, pchAlias, len);
		pIns->m_aliasLen = len;
		//return pIns->SetAlias(pchAlias, len);
	}
	return TRUE;
}

template <class I, int maxins, class A, u8 maxAliasLen>
CInstance *zTemplate<I, maxins, A, maxAliasLen>::FindInstByAlias(const char *pchAlias, u8 len)
{
	/* �ȿ��Ƿ���Daemonʵ�� */
	u8   aliasLen = 0;
	u32  dwCycTime = 0;

	if(maxAliasLen < len) {
		return NULL;
	}

	char aliasBuf[MAX_ALIAS_LEN];
	memset(aliasBuf, 0, MAX_ALIAS_LEN);

	CInstance *pIns = GetInstance(CInstance::DAEMON);
	if(pIns != NULL &&
	   pIns->GetAlias(aliasBuf, maxAliasLen, &aliasLen)) {
		if( (aliasLen == len) &&
			(memcmp(aliasBuf, pchAlias, len) == 0) ) {
			return pIns;
		}
	}

	/* �ٿ��Ƿ���ͨʵ�� */
	TInstAliasInfo *tempAlias = NULL;
	u32  setRet = AliasToWord((char *)pchAlias, len);
	/*�Ȳ���������*/
	if(setRet >= maxins)
		return NULL;

	tempAlias = &instAliasArray[setRet];
	if(tempAlias == NULL)
		return NULL;

	pIns = GetInstance(tempAlias->instId);
	if((pIns != NULL) && (pIns->GetAlias(aliasBuf, maxAliasLen, &aliasLen))) {
		if( (aliasLen == len) && (memcmp(aliasBuf, pchAlias, len) == 0) ) {
			return pIns;
		}
	}
	/*�ٲ���bak����*/
	do {
		if((tempAlias == NULL) || (tempAlias->nextLoc >= maxins))
			return NULL;

		tempAlias = &bakInstAliasArray[tempAlias->nextLoc];
		if(tempAlias == NULL)
			return NULL;

		CInstance *pIns = GetInstance(tempAlias->instId);
		if((pIns != NULL) && (pIns->GetAlias(aliasBuf, maxAliasLen, &aliasLen))) {
			if((aliasLen == len) && (memcmp(aliasBuf, pchAlias, len) == 0)) {
				return pIns;
			}
		}

		dwCycTime++;
		if(dwCycTime > maxins) {
			OspPrintf(TRUE, FALSE, "FindInstByAlias() return Cycle as dwCycTime=%d\n", dwCycTime);
			return NULL;
		}
	} while(tempAlias->nextLoc != 0xFFFF);

	return NULL;
}

/*���ʵ��������¼��Ϣ*/
template <class I, int maxins, class A, u8 maxAliasLen>
BOOL32 zTemplate<I, maxins, A, maxAliasLen>::ClearInstAlias(u16 insid, const char *pAlias, u8 len)
{
	u32  dwCycTime = 0;

	if((maxAliasLen < len) || (insid == CInstance::DAEMON)) {
		return FALSE;
	}

	u32 setRet = AliasToWord((char *)pAlias, len);    /*ͨ��������������ֵ*/
	if(setRet >= maxins)
		return FALSE;

	/*�Ȳ��������飬�ٲ��ұ�������*/
	if(instAliasArray[setRet].instId == insid) {
		if(instAliasArray[setRet].nextLoc == 0xFFFF) { /*����������δ����*/
			instAliasArray[setRet].aliasRet = 0;       /*��ʼ��*/
			instAliasArray[setRet].instId = 0xFFFF;
			instAliasArray[setRet].nextLoc = 0xFFFF;
		} else {
			TInstAliasInfo *tempAlias = &instAliasArray[setRet];
			if(tempAlias == NULL)
				return FALSE;

			if(tempAlias->nextLoc >= maxins)
				return FALSE;

			TInstAliasInfo *relocAlias = &bakInstAliasArray[tempAlias->nextLoc];
			if(relocAlias == NULL)
				return FALSE;

			dwCycTime = 0;
			while(relocAlias->nextLoc != 0xFFFF) {
				tempAlias->aliasRet = relocAlias->aliasRet;    //����һ���¼��Ϣ��䱾���¼��Ϣ
				tempAlias->instId = relocAlias->instId;

				if(relocAlias->nextLoc >= maxins)
					return  FALSE;

				tempAlias = relocAlias;         //λ���Ƶ���һ��
				relocAlias = &bakInstAliasArray[relocAlias->nextLoc];
				if(relocAlias == NULL)
					return  FALSE;

				dwCycTime++;
				if(dwCycTime > maxins) {
					OspPrintf(TRUE, FALSE, "ClearInstAlias(1) return Cycle as dwCycTime=%d\n", dwCycTime);
					return FALSE;
				}
			}

			tempAlias->aliasRet = relocAlias->aliasRet;    //�ѵ����һ���¼��Ϣ��
			tempAlias->instId = relocAlias->instId;
			tempAlias->nextLoc = 0xFFFF;

			relocAlias->aliasRet = 0;      //������һ���¼��
			relocAlias->instId = 0xFFFF;
			relocAlias->nextLoc = 0xFFFF;

			curBakArrayNum--;     /*bak�����Ÿ�������*/
		}
	} else {
		if(instAliasArray[setRet].nextLoc == 0xFFFF) { /*����������δ����*/
			return  FALSE;
		} else {
			TInstAliasInfo *tempAlias = &bakInstAliasArray[instAliasArray[setRet].nextLoc];
			if(tempAlias == NULL)
				return FALSE;

			TInstAliasInfo *relocAlias = &(instAliasArray[setRet]);

			dwCycTime = 0;
			while(tempAlias->instId != insid) {
				relocAlias = tempAlias;

				if(tempAlias->nextLoc != 0xFFFF) {
					if(tempAlias->nextLoc >= maxins)
						return  FALSE;

					tempAlias = &bakInstAliasArray[tempAlias->nextLoc];
					if(tempAlias == NULL)
						return FALSE;

					dwCycTime++;
					if(dwCycTime > maxins) {
						OspPrintf(TRUE, FALSE, "ClearInstAlias(2) return Cycle as dwCycTime=%d\n", dwCycTime);
						return FALSE;
					}
				} else {
					return  FALSE;
				}
			}

			/*�ҵ�bak�����ж�Ӧʵ����¼λ�ã������λ�õļ�¼ֵ���Ѽ�¼������������*/
			if(tempAlias->nextLoc == 0xFFFF) {
				if(relocAlias != NULL)
					relocAlias->nextLoc = 0xFFFF;

				tempAlias->aliasRet = 0;     //��λ��Ϊ������ֵ�����һλ�ã�ֱ�����
				tempAlias->instId = 0xFFFF;
			} else {
				relocAlias = &bakInstAliasArray[tempAlias->nextLoc];
				if(relocAlias == NULL)
					return FALSE;

				dwCycTime = 0;
				while(relocAlias->nextLoc != 0xFFFF) {
					tempAlias->aliasRet = relocAlias->aliasRet;    //����һ���¼��Ϣ��䱾���¼��Ϣ
					tempAlias->instId = relocAlias->instId;

					if(relocAlias->nextLoc >= maxins)
						return  FALSE;

					tempAlias = relocAlias;         //λ���Ƶ���һ��
					relocAlias = &bakInstAliasArray[relocAlias->nextLoc];
					if(relocAlias == NULL)
						return  FALSE;

					dwCycTime++;
					if(dwCycTime > maxins) {
						OspPrintf(TRUE, FALSE, "ClearInstAlias(3) return Cycle as dwCycTime=%d\n", dwCycTime);
						return FALSE;
					}
				}

				tempAlias->aliasRet = relocAlias->aliasRet;    //�ѵ����һ���¼��Ϣ��
				tempAlias->instId = relocAlias->instId;
				tempAlias->nextLoc = 0xFFFF;

				relocAlias->aliasRet = 0;      //������һ���¼��
				relocAlias->instId = 0xFFFF;
				relocAlias->nextLoc = 0xFFFF;
			}

			curBakArrayNum--;     /*bak�����Ÿ�������*/
		}
	}

	return  TRUE;
}

#if defined(_MSC_VER) && !defined(_EQUATOR_)
#pragma pack(pop)
#endif

#endif // _OSP_H
