#ifndef PRINTERDEMO_H
#define PRINTERDEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_printerdemo.h"

#include <string>
#include <QTextStream>
#include <QPrinter>

class PrinterDemo : public QMainWindow
{
	Q_OBJECT

public:
	PrinterDemo(QWidget *parent = 0);
	~PrinterDemo();
	

public slots:
	void on_printAction_triggered();
	void on_printPreviewAction_triggered();
	void printDocument(QPrinter *printer);

private:
	Ui::PrinterDemoClass ui;
	QString createHTML();
	QString loadFile();
	void printHtml(QPrinter &printer, const QString &html);
	void paintContent(QPrinter &printer, const QString &html);
	void paintHtml(QPrinter &printer, const QString &html);
	
};

#endif // PRINTERDEMO_H
