#ifndef PING_H
#define PING_H

#include <QObject>
#include <windows.h>

class CPing : public QObject
{
    Q_OBJECT
public:
    explicit CPing(QObject *parent = 0);
    ~CPing( );
    bool IcmpPing( QString& strIP );

    typedef struct {
          union {
            struct {
              u_char s_b1,s_b2,s_b3,s_b4;
            } S_un_b;
            struct {
              u_short s_w1,s_w2;
            } S_un_w;
            u_long S_addr;
          } S_un;
        } IPAddr;

    typedef struct ip_option_information {
      UCHAR  Ttl;
      UCHAR  Tos;
      UCHAR  Flags;
      UCHAR  OptionsSize;
      PUCHAR OptionsData;
    } IP_OPTION_INFORMATION, *PIP_OPTION_INFORMATION;

    typedef struct icmp_echo_reply {
          IPAddr                       Address;
          ULONG                        Status;
          ULONG                        RoundTripTime;
          USHORT                       DataSize;
          USHORT                       Reserved;
          PVOID                        Data;
          struct ip_option_information  Options;
        } ICMP_ECHO_REPLY, *PICMP_ECHO_REPLY;

    typedef HANDLE  ( WINAPI *IcmpCreateFile ) ( );
    typedef DWORD ( WINAPI *IcmpSendEcho ) (
            HANDLE IcmpHandle,
            IPAddr DestinationAddress,
            LPVOID RequestData,
            WORD RequestSize,
            PIP_OPTION_INFORMATION RequestOptions,
            LPVOID ReplyBuffer,
            DWORD ReplySize,
            DWORD Timeout
    );

    typedef BOOL ( WINAPI* ICmpCloseHandle ) ( HANDLE );

private:
    HINSTANCE hFile;
    IcmpCreateFile hIcmpCreateFile;
    ICmpCloseHandle hIcmpCloseHandle;
    IcmpSendEcho hIcmpSendEcho;
    LPVOID pReplyBuffer;
    HANDLE hIcmpFile;
    
signals:
    
public slots:
    
};

#endif // PING_H
