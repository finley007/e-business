/*******************************************************************************
* ��Ȩ����(C) 2011-2015www.LomoX.hk All Rights Follow Lomox licence.
*
* �ļ�����	: lxsystemtray.cpp
* ��    ��	: ղ���� (mailto:zch.fly@gmail.com)
* ��������	: 2015/04/20
* ��������	:
* ��    ע	:
********************************************************************************/
#include "lxsystemtray.h"

LxSystemTray::LxSystemTray(QIcon icon, QString toolTipName, LxDialogBase* pLxDialogBase)
{
	m_icon = icon;
	m_ptrLxDialogBase = pLxDialogBase;
	m_toolTipName = toolTipName;
	this->setParent((QWidget*)(pLxDialogBase->getCoreDialog()));
	__initSystemTray();
}

LxSystemTray::~LxSystemTray()
{

}
bool LxSystemTray::__initSystemTray()
{
	setObjectName("LxSystemTray");
	m_ptrTrayIcon = new QSystemTrayIcon(this);
	m_ptrTrayIcon->setIcon(m_icon);
	m_ptrTrayIcon->setToolTip(m_toolTipName);
	m_ptrTrayMenu = new QMenu(this);

	QAction *action = new QAction(QString::fromLocal8Bit("����"), this);
	action->setIcon(QIcon(QCoreApplication::applicationDirPath()+"/Resources/hide.ico"));
	m_ptrTrayMenu->addAction(action);
	connect(action, SIGNAL(triggered()), m_ptrLxDialogBase, SLOT(showMinimized()));
	m_trayActions.insert(QString::fromLocal8Bit("����"), action);

	action = new QAction(QString::fromLocal8Bit("��С��"), this);
	action->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/Resources/mini.ico"));
	m_ptrTrayMenu->addAction(action);
	connect(action, SIGNAL(triggered()), m_ptrLxDialogBase, SLOT(showMinimized()));
	m_trayActions.insert(QString::fromLocal8Bit("��С��"), action);

	action = new QAction(QString::fromLocal8Bit("���"), this);
	action->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/Resources/max.ico"));
	m_ptrTrayMenu->addAction(action);
	connect(action, SIGNAL(triggered()), m_ptrLxDialogBase, SLOT(showMaximized()));
	m_trayActions.insert(QString::fromLocal8Bit("���"), action);

	action = new QAction(QString::fromLocal8Bit("��ԭ"), this);
	action->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/Resources/normal.ico"));
	m_ptrTrayMenu->addAction(action);
	connect(action, SIGNAL(triggered()), m_ptrLxDialogBase, SLOT(showNormal()));
	m_trayActions.insert(QString::fromLocal8Bit("��ԭ"), action);

	m_ptrTrayMenu->addSeparator();
	action = new QAction(QString::fromLocal8Bit("�˳�"), this);
	action->setIcon(QIcon(QCoreApplication::applicationDirPath() + "/Resources/close.ico"));
	m_ptrTrayMenu->addAction(action);
	connect(action, SIGNAL(triggered()), m_ptrLxDialogBase, SLOT(close()));
	m_trayActions.insert(QString::fromLocal8Bit("�˳�"), action);

	m_ptrTrayIcon->setContextMenu(m_ptrTrayMenu);

	//ͼ�����¼�
	connect(m_ptrTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

	m_ptrTrayIcon->show();
	return true;
}

void LxSystemTray::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	//������̨ͼ��ִ����Ӧ�¼�  
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
		m_ptrLxDialogBase->showNormal();
		break;
	case QSystemTrayIcon::DoubleClick:
		m_ptrLxDialogBase->showNormal();
		break;
// 	case QSystemTrayIcon::MiddleClick:
// 		showMessage("����м���");
// 		break;
	default:
		break;
	}
}