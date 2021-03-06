#include "MainWindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QFile>
#include <QTextStream>

#include "ChatForm.h"
#include <QTextCodec>
#include <QHostInfo>
#include <QNetworkInterface>
#include "service/ChatService.h"
#include "model/User.h"
#include <QList>
#include "model/FileSender.h"
#include "model/FileReceiver.h"
#include "service/StorageService.h"
#include "model/Image.h"

bool setSkin(QApplication* const app, QString const &skinFile)
{
    QFile file(skinFile);

    if (QFile::exists(skinFile) && file.open(QIODevice::ReadOnly))
    {
        QApplication::setStyle(QStyleFactory::create("Windows"));
        QString strTemp;
        QTextStream in(&file);
        while (!in.atEnd())
        {
            strTemp.append(in.readLine());
        }
        file.close();
        app->setStyleSheet(strTemp);
    }
    else
    {
#ifdef Q_WS_MAC
        qDebug("%s: %s: File does not exist %s... setting mac style...",
               __FILE__, __FUNCTION__, qPrintable(skinFile));
        app->setStyle(new QMacStyle());
        return true;
#else
        qDebug("%s: %s: File does not exist or failed to open %s",
               __FILE__, __FUNCTION__, qPrintable(skinFile));
        return false;
#endif
    }

    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);

//    QIcon icon1(":/images/default_user_icon.png");
//    QString data = ((Image) icon1.pixmap(72,72).toImage()).toBase64Data();
//    QImage img = (QImage) Image::fromBase64Data(data);

//    img.save("D:/test.jpg");

    MainWindow *w = MainWindow::getMainWindow();
    w->show();

//    setSkin(&a ,":/skins/defaultSkin.css");

    return a.exec();
}
