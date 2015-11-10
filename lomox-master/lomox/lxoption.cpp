/*******************************************************************************
* ��Ȩ����(C) 2010-2013 lomox caidongyun. All Rights Reserved.
*
* �ļ�����	: lxoption.cpp
* ��    ��	: �̶��S (mailto:caidongyun19@qq.com)
* ��������	: 2013/3/9
* ��������	: 
* ��    ע	: 
* ��    ��  ��ղ����(KeoJam)(mailto:zch.fly@gmail.com)
********************************************************************************/
#include "lomox_global.h"
#include "lxoption.h"


LxOption::LxOption( QObject* parent )
:QObject(parent)
{

}

LxOption::~LxOption()
{

}


QString LxOption::getStartResourceFileName()
{
	return QCoreApplication::applicationDirPath() + "/Resources/main.lx";
}

//����������Ŀ
/*
// main.lx //��Դ��
//main.html";
//lomoxdemo.html
//index.html
*/
QString LxOption::getStartUrl()
{
	QString strUrlConfg = QCoreApplication::applicationDirPath() + QString::fromUtf8("/config.ini");
	if (QFile::exists(strUrlConfg))
	{
		QSettings qsetting(strUrlConfg, QSettings::IniFormat,0);
		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/url"));
		if (!varUrl.isNull() && varUrl.isValid())
		{
			QString strUrl = varUrl.toString();
			if (!strUrl.isEmpty())
				return strUrl;
		}
	}

	QString strFilePath = QCoreApplication::applicationDirPath() + QString::fromUtf8("/Resources/");

	QString strResCab = getStartResourceFileName();
	QString strMainHtml = strFilePath + "main.html";
	QString strDemoHtml = strFilePath + "lomoxdemo.html";
	QString strIndex = strFilePath + "index.html";

	
	if (QFile::exists(strResCab))
	{
		//ע����Դ������main ����index�ڵ�
		QResource::registerResource(strResCab);
		return QString::fromLocal8Bit("qrc:/pack/main.html");

	}
	else if (QFile::exists(strMainHtml))
	{
		return strMainHtml;
	}
	else if (QFile::exists(strDemoHtml))
	{
		return strDemoHtml;
	}
	else if (QFile::exists(strIndex))
	{
		return strIndex;
	}
	return QString();
}

QString LxOption::getAppPath()
{
	return QCoreApplication::applicationDirPath();
}

QObject* LxOption::getCoreAppOption()
{
	return qApp;
}

// int LxOption::getMainWithFromCfg()
// {
// 	QString strCfgPath = getConfgPath();
// 	if (QFile::exists(strCfgPath))
// 	{
// 		QSettings qsetting(strCfgPath, QSettings::IniFormat,0);
// 		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/with"), QVariant(400));
// 		if (!varUrl.isNull() && varUrl.isValid())
// 		{
// 			return varUrl.toInt();
// 		}
// 	}
// 	return -1;
// }

// int LxOption::getMainHigthFromCfg()
// {
// 	QString strCfgPath = getConfgPath();
// 	if (QFile::exists(strCfgPath))
// 	{
// 		QSettings qsetting(strCfgPath, QSettings::IniFormat,0);
// 		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/higth"),QVariant(400));
// 		if (!varUrl.isNull() && varUrl.isValid())
// 		{
// 			return varUrl.toInt();
// 		}
// 	}
// 	return -1;
// }

QString LxOption::getConfgPath()
{
	return QCoreApplication::applicationDirPath() + QString::fromUtf8("/config.ini");
}

QString LxOption::getMainTitle()
{
	QString strConfg = QCoreApplication::applicationDirPath() + QString::fromUtf8("/config.ini");
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat,0);
		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/title"));
		if (!varUrl.isNull() && varUrl.isValid())
		{
			QString strUrl = QString::fromLocal8Bit(varUrl.toByteArray().data());
			return strUrl;
		}
	}
	return QString();
}

bool LxOption::getNeedShowMainNcFrame()
{
	QString strConfg = getConfgPath();;
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat,0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/mainframe"));

		if (!varValue.isNull() && varValue.isValid() )
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

bool LxOption::getNeedShowChildNcFrame()
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat,0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/childframe"));

		if (!varValue.isNull() && varValue.isValid() )
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

bool LxOption::getMainWindowStaysOnTopHint()
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat,0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/maintop"));

		if (!varValue.isNull() && varValue.isValid())
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

//add by KeoJam 2015-04-19 �����Ӵ����Ƿ���ʾ��������
bool LxOption::getChildWindowStaysOnTopHint()
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat, 0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/childtop"));

		if (!varValue.isNull() && varValue.isValid())
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

//add by KeoJam 2015-04-19 �����Ƿ����ô��ڸ��ӹ�ϵ
bool LxOption::getDialogsRelationShip()
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat, 0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/dialogsrelation"));

		if (!varValue.isNull() && varValue.isValid())
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

//add by KeoJam 2015-04-19 �����Ƿ����ô���ϵͳ����
bool LxOption::getNeedSystemTray()
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat, 0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/systemtray"));

		if (!varValue.isNull() && varValue.isValid())
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

QString LxOption::getSystemTrayIconName()
{
	QString strConfg = QCoreApplication::applicationDirPath() + QString::fromUtf8("/config.ini");
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat, 0);
		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/trayicon"));
		if (!varUrl.isNull() && varUrl.isValid())
		{
			QString strUrl = QString::fromLocal8Bit(varUrl.toByteArray().data());
			return strUrl;
		}
	}
	return QString();
}

bool LxOption::getValueFromIni(QString strKey, bool &bValue)
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat,0);
		QVariant varValue = qsetting.value(strKey);

		if (!varValue.isNull() && varValue.isValid())
		{
			int nValue = varValue.toInt();
			bValue = nValue != 0 ? true : false;
			return true;
		}
	}
	return false;
}

bool LxOption::getLoadHrefInCurrentMainDialog()
{
	bool bRes = false;//Ĭ���Լ�����
	if (getValueFromIni(QString::fromLocal8Bit("/maindialog/hrefincurrent"), bRes))//ȡ�ɹ����óɹ��Ľ��
	{
		return bRes;
	}
	return bRes;//Ĭ�ϵ�
}

bool LxOption::getLoadHrefInCurrentChildDialog()
{
	bool bRes = false;//Ĭ���Լ�����
	if (getValueFromIni(QString::fromLocal8Bit("/childdialog/hrefincurrent"), bRes))//ȡ�ɹ����óɹ��Ľ��
	{
		return bRes;
	}
	return bRes;//Ĭ�ϵ�
}


//add by KeoJam 2015-04-19 �����Ƿ����ô��ڼ���ʱ�� ��ͼ��
bool LxOption::getNeedShowLoadingGif()
{
	QString strConfg = getConfgPath();
	if (QFile::exists(strConfg))
	{
		QSettings qsetting(strConfg, QSettings::IniFormat, 0);
		QVariant varValue = qsetting.value(QString::fromLocal8Bit("/cfg/showloadinggif"));

		if (!varValue.isNull() && varValue.isValid())
		{
			int nValue = varValue.toInt();
			return nValue != 0 ? true : false;
		}
	}

	return false;
}

int LxOption::getLoadingGifWidth()
{
	QString strCfgPath = getConfgPath();
	if (QFile::exists(strCfgPath))
	{
		QSettings qsetting(strCfgPath, QSettings::IniFormat,0);
		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/loadinggifwidth"),QVariant(400));
		if (!varUrl.isNull() && varUrl.isValid())
		{
			return varUrl.toInt();
		}
	}
	return -1;
}
int LxOption::getLoadingGifHeight()
{
	QString strCfgPath = getConfgPath();
	if (QFile::exists(strCfgPath))
	{
		QSettings qsetting(strCfgPath, QSettings::IniFormat, 0);
		QVariant varUrl = qsetting.value(QString::fromLocal8Bit("/cfg/loadinggifheight"), QVariant(400));
		if (!varUrl.isNull() && varUrl.isValid())
		{
			return varUrl.toInt();
		}
	}
	return -1;
}