#ifndef ETDONGLE_H
#define ETDONGLE_H
#include "../dongle.h"
#include "ET199_32.h"

class DONGLESHARED_EXPORT CETDongle : public CDongle
{
public:
    explicit CETDongle( bool bVerify, QObject* parent = NULL );
    ~CETDongle( );

public:
    virtual bool GetHID( QString& strHID );
    virtual bool Administrator( );
    virtual bool IsAdminHID( QString& strHID );
    virtual void Reopen( );
    virtual void GetAllHids( QStringList& lstHids );
    virtual void GetCurrentDate( QDate& dtDate );
    virtual bool JudgeTime( );

private:
    typedef DWORD WINAPI ( *MyETEnum ) ( OUT ET_CONTEXT *pETContextList, IN OUT DWORD *pdwDeviceCount );
    typedef DWORD WINAPI ( *MyETOpen ) ( IN OUT ET_CONTEXT *pETCtx );
    typedef DWORD WINAPI ( *MyETOpenEx ) ( IN OUT ET_CONTEXT *pETCtx, IN ET_OPENINFO *pETOpenInfo );
    typedef DWORD WINAPI ( *MyETClose ) ( IN ET_CONTEXT *pETCtx );
    typedef DWORD WINAPI ( *MyETControl ) ( IN CONST ET_CONTEXT *pETCtx, IN DWORD dwCtlCode,
                                                                              IN CONST VOID *pInBuffer, IN DWORD dwInBufferLen,
                                                                              OUT VOID *pOutBuffer, IN DWORD dwOutBufferLen,
                                                                              OUT DWORD *pdwBytesReturned );
    typedef DWORD WINAPI ( *MyETFormatErrorMessage ) ( IN DWORD dwRet, OUT LPSTR lpszMessage, IN DWORD dwMsgBufLen );

    MyETEnum DongleEnum;
    MyETOpen DongleOpen;
    MyETOpenEx DongleOpenEx;
    MyETClose DongleClose;
    MyETControl DongleControl;
    MyETFormatErrorMessage DongleErrorMsg;
    ET_CONTEXT* pETContext;

protected:
    virtual void InitApiPointer( );
    virtual void GetApiPointer( );
    virtual void DongleDetection( bool bVerifyDate = true );
    virtual void DongleTimerOpen(  );

private:
    inline void EmitDongleException( QString strMsg, bool bExit, bool bRetry );
    inline void ResoveException( PVOID pFunc, QString strFuncName );
    inline void FunctionException( DWORD dwRet );
    bool OpenETDongle( );
    bool VerifyDongle( ET_CONTEXT* pContext );
    bool VerifyDate( ET_CONTEXT *pContext );

    BOOL GetDongleType( CETDongle::DongleType& eType, ET_CONTEXT *pContext );

    inline void FillAdminHash( );
    inline bool ContainAdminHID( );
    bool ExclusiveOpen( ET_CONTEXT *pContext );
};

#endif // ETDONGLE_H
