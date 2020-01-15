// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "controller.h"
#include "basslib.h"
#include "serial.h"

#include <QSignalBlocker>
#include <QApplication>
#include <QSettings>
#include <QTimer>

#include <QDebug>

Controller::Controller(QSettings *settings, QObject *parent) :
    QObject(parent),
    m_settings(settings),
    m_bassLib(nullptr),
    m_timer(nullptr)
{
    //TEST
    m_bassLib = std::make_shared<BassLib>();
    m_bassLib->init(9);

    m_timer = new QTimer(this);
    m_timer->setInterval(20);
    QObject::connect(m_timer, &QTimer::timeout, [this]()
    {
        qDebug() << m_bassLib->ftt().at(0);
    });
    m_timer->start();
}

Controller::~Controller()
{
}

std::vector<std::pair<QString, int> > Controller::availableDevices()
{
    return BassLib::availableDevices();
}

std::vector<std::pair<QString, int> > Controller::availableCaptureMethods()
{
    return std::vector<std::pair<QString, int> >
    {
        std::make_pair("Color",  Constants::CAPTURE::COLOR),
        std::make_pair("Volume", Constants::CAPTURE::VOLUME)
    };
}

std::vector<std::pair<QString, int> > Controller::availableFastFrequency()
{
    return std::vector<std::pair<QString, int> >
    {
        std::make_pair("Low",    Constants::FREQ_LOW),
        std::make_pair("Middle", Constants::FREQ_MIDDLE),
        std::make_pair("High",   Constants::FREQ_HIGH)
    };
}

std::vector<std::pair<QString, int> > Controller::availableUprate()
{
    return std::vector<std::pair<QString, int> >
    {
        std::make_pair("10", 10),
        std::make_pair("20", 20),
        std::make_pair("30", 30),
        std::make_pair("30", 30),
        std::make_pair("40", 40),
        std::make_pair("50", 50),
        std::make_pair("60", 60),
        std::make_pair("90", 90),
        std::make_pair("120", 120),
        std::make_pair("144", 144),
    };
}

std::vector<std::pair<QString, int> > Controller::availableAmpl()
{
    return std::vector<std::pair<QString, int> >
    {
        std::make_pair("X2.0",  Constants::SETTINGS::AMPL200),
        std::make_pair("X1.75", Constants::SETTINGS::AMPL175),
        std::make_pair("X1.5",  Constants::SETTINGS::AMPL150),
        std::make_pair("X1.25", Constants::SETTINGS::AMPL125),
        std::make_pair("X1.0",  Constants::SETTINGS::AMPL100),
        std::make_pair("X0.75", Constants::SETTINGS::AMPL075),
        std::make_pair("X0.5",  Constants::SETTINGS::AMPL050)
    };
}

std::vector<std::pair<QString, QString> > Controller::availableLanguages()
{
    return std::vector<std::pair<QString, QString> >
    {
        std::make_pair("English", "en_US"),
        std::make_pair("Русский", "ru_RU")
    };
}

std::vector<std::pair<QString, QString> > Controller::availablePorts()
{
    return serial::availablePorts();
}
