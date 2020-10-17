#ifndef NETWORK_H
#define NETWORK_H

#include <QDialog>

#include <QtNetwork/QtNetwork>
#include <QTextCodec>
#include <QUrl>


namespace Ui {
class network;
}

class network : public QDialog
{
    Q_OBJECT
public slots:
    void replyFinished(QNetworkReply *reply);
public:
    explicit network(QWidget *parent = nullptr);
    ~network();

private:
    Ui::network *ui;

    QNetworkAccessManager *manager;
};

#endif // NETWORK_H
