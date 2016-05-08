#ifndef HTTPCONNECT_H
#define HTTPCONNECT_H

#include <QNetworkAccessManager>
#include <QUrl>
#include <QFile>
#include <QObject>
#include <QBuffer>

enum contentBufferType {CBT_FILE, CBT_BUFFER};
enum contentSilenceMode {CSM_SILENCE, CSM_LOUD};

class HttpConnect : public QObject
{
    Q_OBJECT
public:
    HttpConnect();
    ~HttpConnect();
private:
    //параметры запуска
    contentBufferType cbt;
    contentSilenceMode csm;
    //сеть
    QUrl url;                   //строка запроса
    QNetworkAccessManager qnam; //менеджер
    QNetworkReply *reply;       //ответ
    //переменные хранения данных
    QFile *file;
    QBuffer buffer;
    QString pageContent;
    //
    void startRequest(QUrl url);
public slots:
    bool downloadContent(QString urltext, contentBufferType cbtType, contentSilenceMode csmMode);
private slots:
    void httpFileFinished();
    void httpFileReadyRead();
    void httpBufferFinished();
    void httpBufferReadyRead();
signals:
    void contentFinished(QString);
};

#endif // HTTPCONNECT_H
