/*******************************************************************************
* ��Ȩ����(C) 2011-2015www.LomoX.hk All Rights Follow Lomox licence.
*
* �ļ�����	: lxsystemtray.h
* ��    ��	: ղ���� (mailto:zch.fly@gmail.com)
* ��������	: 2015/04/20
* ��������	:
* ��    ע	:
********************************************************************************/
#ifndef __LXSYSTEMTRAY_H__
#define __LXSYSTEMTRAY_H__

#include "lomox_global.h"
#include "lxdialogoperate.h"
#include <QSystemTrayIcon>

class LxSystemTray : public QWidget
{
	Q_OBJECT

public:
	LxSystemTray(QIcon icon, QString toolTipName = "", LxDialogBase* pLxDialogBase = NULL);
	~LxSystemTray();
	
private:
	QPointer<QSystemTrayIcon> m_ptrTrayIcon;
	QPointer<LxDialogBase> m_ptrLxDialogBase;
	QIcon m_icon;
	QString m_toolTipName;
	QPointer<QMenu> m_ptrTrayMenu;
	QMap<QString, QAction *> m_trayActions;
	bool __initSystemTray();
public slots:
	void iconActivated(QSystemTrayIcon::ActivationReason reason);

};

#endif // LXSYSTEMTRAYICON_H
