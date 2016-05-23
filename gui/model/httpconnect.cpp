#include "httpconnect.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QObject>
#include <QSsl>
#include <QString>

HttpConnect::HttpConnect()
{

}

HttpConnect::~HttpConnect()
{

}

bool HttpConnect::downloadContent(QString urltext, contentBufferType cbtType, contentSilenceMode csmMode)
{
    url = urltext;
    this->cbt = cbtType;
    this->csm = csmMode;
    //определение способа хранения загруженных данных
    if(cbt == CBT_FILE){
        ///работа с файлом
        QFileInfo fileInfo(url.path());
        QString fileName = fileInfo.fileName();
        if (fileName.isEmpty()) //если имя по ссылке нельзя определить
            fileName = "index.html"; //делаем стандарт

        if (QFile::exists(fileName)) {
            if (QMessageBox::question(NULL, tr("HTTP"),
                                      tr("There already exists a file called %1 in "
                                         "the current directory. Overwrite?").arg(fileName),
                                      QMessageBox::Yes|QMessageBox::No, QMessageBox::No)
                == QMessageBox::No)
                return false;
            QFile::remove(fileName);
        }

        file = new QFile(fileName);
        if (!file->open(QIODevice::WriteOnly)) {
            QMessageBox::information(NULL, tr("HTTP"),
                                     tr("Unable to save the file %1: %2.")
                                     .arg(fileName).arg(file->errorString()));
            delete file;
            file = 0;
            return false;
        }
    }else{
        //qDebug() << "buffer open!";
        buffer.open(QBuffer::WriteOnly);
    }
    // schedule the request
    startRequest(url);
}

void HttpConnect::startRequest(QUrl url)
{
    //настройка ssl, бибилитеки лежат с .exe
    QSslConfiguration sslConfiguration(QSslConfiguration::defaultConfiguration());
    QNetworkRequest req;
    req.setSslConfiguration(sslConfiguration);
    req.setUrl(url);
    //запуск qnetworkreply
    reply = qnam.get(req);
    //подключим правильный сигнал-слот
    if(cbt == CBT_FILE){
        ///работа с файлом
        QObject::connect(reply, SIGNAL(finished()),
            this, SLOT(httpFileFinished()));
        QObject::connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpFileReadyRead()));
    } else {
        QObject::connect(reply, SIGNAL(finished()),
                this, SLOT(httpBufferFinished()));
        QObject::connect(reply, SIGNAL(readyRead()),
                this, SLOT(httpBufferReadyRead()));
    }
    //connect(reply, SIGNAL(downloadProgress(qint64,qint64)),
    //        this, SLOT(updateDataReadProgress(qint64,qint64)));
}

void HttpConnect::httpBufferFinished()
{
    //если по указанной ссылке стоит редирект
    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) { //и были ошибки при чтении
        buffer.reset(); //сброс буфера на 0;
        buffer.close();
        if(csm == CSM_LOUD){
            QMessageBox::information(NULL, tr("HTTP"),
                tr("Download failed: %1.")
                .arg(reply->errorString()));
        }
    } else if (!redirectionTarget.isNull()) {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl()); //получаем новый url
        if(csm == CSM_LOUD){
            //в "громком" режиме спрашиваем про редирект
            if (QMessageBox::question(NULL, tr("HTTP"),
                                  tr("Redirect to %1 ?").arg(newUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
                url = newUrl;
                reply->deleteLater();
                buffer.open(QIODevice::WriteOnly);
                buffer.seek(0);
                startRequest(url);
                return;
            }
        } else {
            //в тихом режиме - про редирект не спрашиваем.
            url = newUrl;
            reply->deleteLater();
            buffer.open(QIODevice::WriteOnly);
            buffer.seek(0);
            startRequest(url);
            return;
        }
    } else {
        //QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(QDir::currentPath()));
        //downloadButton->setEnabled(true);
    }
    reply->deleteLater();
    reply = 0;
    QString newPageContent = QString(buffer.buffer());
    QTextCodec *c = QTextCodec::codecForName("Windows-1251");
    pageContent = c->toUnicode(buffer.buffer());
    buffer.close();
    emit contentFinished(pageContent);
}

void HttpConnect::httpBufferReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (buffer.isWritable())
        buffer.write(reply->readAll());
}


void HttpConnect::httpFileFinished()
{
    //progressDialog->hide();
    file->flush();
    file->close();

    QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (reply->error()) {
        file->remove();
        QMessageBox::information(NULL, tr("HTTP"),
                                 tr("Download failed: %1.")
                                 .arg(reply->errorString()));
        //downloadButton->setEnabled(true);
    } else if (!redirectionTarget.isNull()) {
        QUrl newUrl = url.resolved(redirectionTarget.toUrl());
        if (QMessageBox::question(NULL, tr("HTTP"),
                                  tr("Redirect to %1 ?").arg(newUrl.toString()),
                                  QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
            url = newUrl;
            reply->deleteLater();
            file->open(QIODevice::WriteOnly);
            file->resize(0);
            startRequest(url);
            return;
        }
    } else {
        //QString fileName = QFileInfo(QUrl(urlLineEdit->text()).path()).fileName();
        //statusLabel->setText(tr("Downloaded %1 to %2.").arg(fileName).arg(QDir::currentPath()));
        //downloadButton->setEnabled(true);
    }

    reply->deleteLater();
    reply = 0;
    delete file;
    file = 0;
}

void HttpConnect::httpFileReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    if (file)
        file->write(reply->readAll());
}
