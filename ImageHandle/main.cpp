#include "mainwindow.h"
#include "header.h"


//日志生成
void LogMsgOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
 {
    // 加锁
       static QMutex mutex;
       mutex.lock();

       QByteArray localMsg = msg.toLocal8Bit();

       QString strMsg("");
       switch(type)
       {
       case QtDebugMsg:
           strMsg = QString("Debug:     ");
           break;
       case QtInfoMsg:
           strMsg = QString("Info:      ");
           break;
       case QtWarningMsg:
           strMsg = QString("Warning:   ");
           break;
       case QtCriticalMsg:
           strMsg = QString("Critical:  ");
           break;
       case QtFatalMsg:
           strMsg = QString("Fatal:     ");
           abort();            //终止程序
           //break;

       }

       // 设置输出信息格式
       QString strDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
       QString strMessage = QString("%1 DateTime:%2 Message:%3      File:%4 Line:%5 Function:%6")
               .arg(strMsg).arg(strDateTime).arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);

       // 输出信息至文件中（读写、追加形式）
       QFile file("log.txt");
       file.open(QIODevice::ReadWrite | QIODevice::Append);
       QTextStream stream(&file);
       stream << strMessage << "\r\n";
       cout << QString(localMsg.constData()).toStdString() << endl;
       file.flush();
       file.close();

       // 解锁
       mutex.unlock();
 }


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(LogMsgOutput);

    qDebug("This is a debug message.");
    qWarning("This is a warning message.");
    qInfo("This is a info message.");

    MainWindow w;
    w.show();
    return a.exec();
}
