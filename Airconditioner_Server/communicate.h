#ifndef COMMUNICATE
#define COMMUNICATE
#include <QtNetwork>
class QUdpSocket;
class UdpSocket
{
private slots:
    void processPendingDatagram();
public:
    QUdpSocket *Receiver= new QUdpSocket();
    UdpSocket()
    {
       QObject::connect(Receiver,SIGNAL(readyRead()),this,SLOT(processPendingDatagram()));
    }

};
void UdpSocket::processPendingDatagram()
{
    while(this->Receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(this->Receiver->pendingDatagramSize());
        this->Receiver->readDatagram(datagram.data(),datagram.size());
        qDebug()<<datagram.data();
    }
}

#endif // COMMUNICATE

