#include "printerdemo.h"
#include "ui_printerdemo.h"

#include <string>
#include <QTextStream>
#include <QPrinter>
#include <QPrinterInfo>
#include <qpainter>
#include <QPrintDialog>
#include <QPageSetupDialog>
#include <QPrintPreviewDialog>
#include <QTextDocument>
#include <QMargins>
#include <QPointF>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include <QFile>

/*
/	创建了两个槽函数：on_printAction_triggered和on_printPreviewAction_triggered
/   分别用界面上的Print和Print Review触发。
/   on_printAction_triggered和on_printPreviewAction_triggered都调用printDocument方法
/   目前打印小票用的Case 3：从本地读取html文件调用paintHtml方法打印
/
*/

PrinterDemo::PrinterDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionPrint, SIGNAL(triggered()), this, SLOT(on_printAction_triggered()));
	connect(ui.actionPrint_Review, SIGNAL(triggered()), this, SLOT(on_printPreviewAction_triggered()));
}

PrinterDemo::~PrinterDemo()
{

}

void PrinterDemo::on_printAction_triggered()
{
	QPrinter printer;
	printDocument(&printer);
}

void PrinterDemo::printDocument(QPrinter *printer)
{
	//控制台输出
	QTextStream cout(stdout, QIODevice::WriteOnly);

	//Case 1 打印字符串
	//QString str("店联");
	//QString str = QString::fromLocal8Bit("店联");
	//cout << str << endl;
	//cout << str.toLocal8Bit() << endl;
	//cout << str.toUtf8() << endl;
	//paintHtml(*printer, str);

	//Case 2 打印HTML
	//QString html = createHTML();
	//paintHtml(*printer, html);

	//Case 3 打印本地HTML文件
	QString html = loadFile();
	paintHtml(*printer, html);
}

void PrinterDemo::on_printPreviewAction_triggered()
{
	QPrinter printer;
	// 创建打印预览对话框  
	QPrintPreviewDialog preview(&printer);
	// 当要生成预览页面时，发射paintRequested()信号  
	connect(&preview, SIGNAL(paintRequested(QPrinter*)),
		this, SLOT(printDocument(QPrinter*)));
	preview.exec();

}


/*Different print solutions*/
//Print directly
void PrinterDemo::printHtml(QPrinter &printer, const QString &html)
{
	//控制台输出
	QTextStream cout(stdout, QIODevice::WriteOnly);

	//设置打印区域
	printer.setPageSize(QPrinter::Custom);
	QSizeF s = QSizeF(printer.logicalDpiX() * (58 / 25.4), printer.logicalDpiY() * (297 / 25.4));
	//QSizeF s = QSizeF(printer.logicalDpiX() * (80 / 25.4), printer.logicalDpiY() * (297 / 25.4));
	//QSizeF s = QSizeF(printer.logicalDpiX() * (30 / 25.4), printer.logicalDpiY() * (297 / 25.4));
	cout << s.width() << endl;
	cout << s.height() << endl;
	printer.setPageSizeMM(s);
	printer.setFullPage(true);
	//bool result = printer.setPageMargins(QMargins(0, 0, 0, 0));
	//cout << result << endl;
	//qreal marginLeft, marginRight, marginTop, marginBottom;
	//printer.getPageMargins(&marginLeft, &marginRight, &marginTop, &marginBottom, QPrinter::Millimeter);
	//cout << marginLeft << endl;
	//cout << marginRight << endl;
	//cout << marginTop << endl;
	//cout << marginBottom << endl;
	//cout << printer.width() << endl;
	//cout << printer.height() << endl;
	printer.setOrientation(QPrinter::Portrait);

	//设置输出方式
	printer.setOutputFormat(QPrinter::NativeFormat);
	//printer.setOutputFormat(QPrinter::PdfFormat);
	//printer.setOutputFileName("C:/Users/IBM_ADMIN/Documents/visual studio 2013/Projects/PrinterDemo/PrinterDemo/x64/Debug/print.pdf");

	QTextDocument textDocument;

	//设置字体
	QFont font = textDocument.defaultFont();
	font.setBold(false);
	font.setPointSize(10);
	textDocument.setDefaultFont(font);

	//cout << textDocument.indentWidth() << endl;
	//textDocument.setIndentWidth(0);
	//cout << textDocument.indentWidth() << endl;

	//cout << textDocument.documentMargin() << endl;
	//textDocument.setDocumentMargin(0);
	//cout << textDocument.documentMargin() << endl;

	//cout << textDocument.textWidth() << endl;
	//textDocument.setTextWidth(1000);
	//cout << textDocument.textWidth() << endl;

	textDocument.setHtml(html.toLocal8Bit());
	textDocument.print(&printer);

}

//Paint
void PrinterDemo::paintContent(QPrinter &printer, const QString &html)
{
	//控制台输出
	QTextStream cout(stdout, QIODevice::WriteOnly);

	QPainter painter;
	/*printer.setPageSize(QPrinter::Custom);
	QSizeF s = QSizeF(printer.logicalDpiX() * (58 / 25.4), printer.logicalDpiY() * (297 / 25.4));
	cout << s.width() << endl;
	cout << s.height() << endl;
	printer.setPageSizeMM(s);*/
	painter.begin(&printer);

	// Find the dimensions of the text on each page.
	qreal width = 0.0;
	qreal height = 0.0;
	QFont font;
	font.setBold(true);
	font.setPointSize(200);
	font = QFont(font, painter.device());
	QFontMetricsF fontMetrics(font);
	QRectF rect = fontMetrics.boundingRect(html.toLocal8Bit());
	width = rect.width();
	height = rect.height();

	cout << printer.pageRect().width() << endl;
	cout << printer.pageRect().height() << endl;
	qreal xScale = printer.pageRect().width() / width;
	qreal yScale = printer.pageRect().height() / height;
	qreal scale = qMin(xScale, yScale);

	//painter.translate(printer.pageRect().width() / 2.0, printer.pageRect().height() / 2.0);
	painter.scale(scale, scale);
	painter.setBrush(QBrush(Qt::black));

	//qreal x = -width / 2.0;
	//qreal y = -height / 2.0;
	qreal x = 0;
	qreal y = 2 * height;

	painter.setFont(font);
	QString content = QString::fromLocal8Bit("一九七九年，那是一个春天，有\n一个老人在中国的南海边");
	painter.drawText(QPointF(x, y), content.toLocal8Bit());
	painter.end();

}

//Paint HTML
void PrinterDemo::paintHtml(QPrinter &printer, const QString &html)
{
	QList <QPrinterInfo> plist = QPrinterInfo::availablePrinters();

	printer.setFullPage(true);

	//计算在打印机的DPI下，58mm对应的点数
	int dpi = printer.logicalDpiX();
	int width = 58 * (dpi*1.0 / 25.4);//58mm

	//用html来布局
	//使用QWebPage来解析并输出解析后的文档到打印机
	QWebPage page;
	page.mainFrame()->setHtml(html);

	QWebFrame *frame = page.mainFrame();
	frame->setTextSizeMultiplier(1.4);

	//设置网页视口大小，因为我在html文档中用相对大小布局的
	page.setViewportSize(QSize(width, frame->findFirstElement("body").geometry().height()));

	//将网页通过painter打印出来
	QPainter painter(&printer);
	frame->render(&painter);
}

/*Load source string*/
//Create html directly
QString PrinterDemo::createHTML() 
{
	QString htmlString = QString("<table><tr><th>Month</th><th>Savings</th></tr><tr><td>January</td><td>$100</td></tr></table>");
	return htmlString;
}

//Obtain local file
QString PrinterDemo::loadFile() 
{
	//控制台输出
	QTextStream cout(stdout, QIODevice::WriteOnly);

	QFile file("E:\\project\\finley\\e-business\\lomox-master\\Finley's doc\\design\\打印单设计\\order.html");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return -1;
	}
	QTextStream textInput(&file);
	QString lineStr;
	while (!textInput.atEnd())
	{
		textInput.setCodec("utf-8");
		lineStr.append(textInput.readLine());
	}
	cout << lineStr << endl;
	return lineStr;
}
