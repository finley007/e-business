/*******************************************************************************
* ��Ȩ����(C) 2010-2013 caidongyun. All Rights Reserved.
*
* �ļ�����	: lxpluginbase.h
* ��    ��	: �̶��S (mailto:caidongyun19@qq.com)
* ��������	: 2013/4/23
* ��������	: 
* ��    ע	: 
********************************************************************************/
#ifndef __LXPLUGINBASE_H__
#define __LXPLUGINBASE_H__


class LxPluginBase : public QObject
{
public:
	LxPluginBase(QObject* parent):QObject(parent){}
	virtual LxPluginBase(){}

};


#endif // end of __LXPLUGINBASE_H__
