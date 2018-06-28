#ifndef MYTHREAD
#define MYTHREAD
#include <QThread>
#include <QString>
#include <QHostAddress>
//#include <QtNetwork>

class QUdpSocket;
class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = 0);
    void run();
    void stop();

    //void printMessage();
    //void setMessage(QString Message);
signals:
protected:
    void communicate();

public:
    void processPendingDatagram();
    void MessageDealing(QString Message,QHostAddress address,quint16 port);
	QString bind_ip_room(QString,QString);

private:
    bool stopped ;
    //QString Message;
    QUdpSocket *Receiver;
private slots:
	void send_5(int b);
};

#endif // MYTHREAD

