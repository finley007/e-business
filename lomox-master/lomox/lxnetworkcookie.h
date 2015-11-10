/*******************************************************************************
* ��Ȩ����(C)
*
* �ļ�����	: networkcookie.h
* ��    ��	: �̶��S (mailto:caidongyun19@qq.com)
* ��������	: 2011-6-30
* ��������	: 
* ��    ע	: 
********************************************************************************/
#ifndef __NETWORKCOOKIE_H__
#define __NETWORKCOOKIE_H__
#include <QtNetwork/QNetworkCookie>
#include <QNetworkCookieJar>
class LxNetWorkCookies : public QNetworkCookieJar
{
	Q_OBJECT
public:
    LxNetWorkCookies (QString path, QObject *parent = 0);  
    ~LxNetWorkCookies (); 
    QList<QNetworkCookie> cookiesForUrl ( const QUrl & url ) const;//����ָ��url��cookie
    bool setCookiesFromUrl ( const QList<QNetworkCookie> & cookieList, const QUrl & url );// дcookie��ʱ�����õ�

	bool SaveCookie();//���浽�Լ�ָ���ĵط���δ����

private:
	QString file; 
};

#endif // end of __NETWORKCOOKIE_H__
