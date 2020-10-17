#include "network.h"
#include "ui_network.h"

network::network(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::network)
{
    ui->setupUi(this);

    manager=new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,
                SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl("http://www.baidu.com")));


}

network::~network()
{
    delete ui;
}


void network::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QString all=codec->toUnicode(reply->readAll());

    reply->deleteLater();
}
