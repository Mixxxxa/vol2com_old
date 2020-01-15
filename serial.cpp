// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "serial.h"

#include <QSerialPortInfo>
#include <QSerialPort>
#include <QByteArray>
#include <QDebug>

serial::serial(QObject *parent) :
    QObject(parent),
    m_serial(nullptr)
{
}

serial::~serial()
{
    this->disconnectFromDevice();
}

std::vector<std::pair<QString, QString> > serial::availablePorts()
{
    std::vector<std::pair<QString, QString> > temp;
    for(const auto& port : QSerialPortInfo::availablePorts())
    {
        if((port.vendorIdentifier() != 0) && (port.productIdentifier() != 0))
        {
            auto displayText = QString("%1 - %2").arg(port.portName()).arg(port.description());
            temp.push_back(std::make_pair(displayText, port.portName()));
        }
        else
        {
            temp.push_back(std::make_pair(port.portName(), port.portName()));
        }
    }
    return temp;
}

//Trying to connect to device with name "port"
bool serial::connectToDevice(const QString &port){
    if(m_serial){
        return false;
    }

    m_serial = new QSerialPort(this);
    m_serial->setPortName(port);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);

    if(m_serial->open(QIODevice::ReadWrite))
    {
        QObject::connect(m_serial, &QSerialPort::errorOccurred, [=](QSerialPort::SerialPortError error)
        {
            qDebug() << "SERIAL ERROR: " << error;
        });
        return true;
    }
    else
    {
        delete m_serial;
        m_serial = nullptr;
        return false;
    }
}

void serial::disconnectFromDevice()
{
    if(m_serial)
    {
        m_serial->close();
        delete m_serial;
        m_serial = nullptr;
    }
}

void serial::sendData(const QByteArray &data)
{
    if(m_serial)
        m_serial->write(data);
}

void serial::sendData(const QString &data)
{
    if(m_serial)
        m_serial->write(data.toLocal8Bit());
}
