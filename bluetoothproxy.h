#ifndef BLUETOOTHPROXY_H
#define BLUETOOTHPROXY_H

#include <QDialog>
#include <QObject>

#include <QtBluetooth/qbluetoothlocaldevice.h>
#include <qbluetoothaddress.h>
#include <qbluetoothdevicediscoveryagent.h>
#include <qbluetoothlocaldevice.h>
#include <qbluetoothsocket.h>
#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QWidget>
#include <QListWidgetItem>
#include <QMessageBox>



namespace Ui {
class BluetoothProxy;
}

//搜索蓝牙要开启定位
class BluetoothProxy : public QDialog
{
    Q_OBJECT

public:
    explicit BluetoothProxy(QWidget *parent = nullptr);
    ~BluetoothProxy();
    void openBlueTeeth();
    void closeBlueTeeth();
    void findDevices();
    void sendData(char* _arr,int len);
    QByteArray readData();
    bool connected(){return is_connected;};
public slots:
    void addBlueToothDevicesToList(const QBluetoothDeviceInfo&);
    void readBluetoothDataEvent();
    void bluetoothConnectedEvent();
    void bluetoothDisconnectedEvent();
    void findFinish();

private slots:
    void on_pushButton_open_clicked();

    void on_pushButton_close_clicked();

    void on_pushButton_find_clicked();
    void on_list_itemActivated(QListWidgetItem *item);

    void on_pushButton_break_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::BluetoothProxy *ui;

    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothLocalDevice *localDevice;
    QBluetoothSocket *socket;
    QByteArray blueReadArray;
    bool is_find_finished;
    bool is_connected;
    bool checkPermission();

};

#endif // BLUETOOTHPROXY_H
