#ifndef SERIAL_H
#define SERIAL_H

#include <QObject>

class QSerialPort;
class QByteArray;

class serial : public QObject
{
    Q_OBJECT

public:
    explicit serial(QObject *parent = nullptr);
    ~serial();

    static std::vector<std::pair<QString, QString> > availablePorts();

signals:
    void connected();
    void disconnected();

public slots:
    bool connectToDevice(const QString &port);
    void disconnectFromDevice();

    void sendData(const QByteArray &data);
    void sendData(const QString &data);

private:
    QSerialPort *m_serial;
};

#endif // SERIAL_H
