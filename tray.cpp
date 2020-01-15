// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "tray.h"
#include "constants.h"
#include "controller.h"
#include "guihelper.h"

#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QSignalBlocker>

#include <QDebug>

Tray::Tray(std::shared_ptr<Controller> controller, QObject *parent) :
    QObject(parent),
    m_controller(controller),
    m_tray(nullptr),
    m_contextMenu(nullptr),
    m_methodGroup(nullptr),
    m_deviceGroup(nullptr),
    m_freqGroup(nullptr),
    m_uprateGroup(nullptr),
    m_amplGroup(nullptr),
    m_brightControl(nullptr),
    m_autostart(nullptr)
{
    this->createMenu();
    m_tray->setContextMenu(m_contextMenu.get());
    m_tray->setIcon(QIcon(":/res/iconWork.ico"));
    m_tray->show();
}

Tray::~Tray()
{
    if(!m_tray)
        return;

    m_tray->hide();
    delete m_tray;
}

void Tray::updateMethodsMenu()
{
    clear(m_methodGroup);
    fill(m_methodGroup, m_controller->availableCaptureMethods());
}

void Tray::updateDevicesMenu()
{
    qDebug() << __FUNCTION__ << "Not implemented";
}

void Tray::setMethod(const int method)
{
    if(!signalsBlocked())
        select(m_methodGroup, method);
}

void Tray::setDevice(const int device)
{
    if(!signalsBlocked())
        select(m_deviceGroup, device);
}

void Tray::setUpdateRate(const int uprate)
{
    if(!signalsBlocked())
        select(m_uprateGroup, uprate);
}

void Tray::setFrequency(const int freq)
{
    if(!signalsBlocked())
        select(m_freqGroup, freq);
}

void Tray::setAmplification(const int ampl)
{
    if(!signalsBlocked())
        select(m_amplGroup, ampl);
}

void Tray::setBrightControl(const bool check)
{
    if(!signalsBlocked())
    {
        QSignalBlocker block(m_brightControl);
        m_brightControl->setChecked(check);
    }
}

void Tray::setAutostart(const bool check){
    if(!signalsBlocked())
    {
        QSignalBlocker block(m_autostart);
        m_autostart->setChecked(check);
    }
}

void Tray::onTrayActivate(QSystemTrayIcon::ActivationReason reason){
    switch(reason)
    {
    case QSystemTrayIcon::Context:
        m_contextMenu->show();
        break;
    case QSystemTrayIcon::DoubleClick:
        emit this->openMainWindow();
        break;
    default:
        break;
    }
}

void Tray::createMenu(){
    if(m_tray)
        return;

    m_tray = new QSystemTrayIcon(this);
    m_contextMenu = std::make_unique<QMenu>();

    //Capture methods menu
    auto methodMenu = new QMenu(tr("Capture method"), m_contextMenu.get());
    m_methodGroup = new QActionGroup(methodMenu);
    fill(m_methodGroup, m_controller->availableCaptureMethods());
    QObject::connect(m_methodGroup, &QActionGroup::triggered, [this](QAction* action)
    {
        emit this->methodChanged(action->data().toInt());
    });

    //Capture devices menu
    auto deviceMenu = new QMenu(tr("Capture device"), m_contextMenu.get());
    m_deviceGroup = new QActionGroup(deviceMenu);
    QObject::connect(m_deviceGroup, &QActionGroup::triggered, [this](QAction* action)
    {
        emit this->deviceChanged(action->data().toInt());
    });

    //Frequency menu
    auto freqMenu = new QMenu(tr("Frequency"), m_contextMenu.get());
    m_freqGroup = new QActionGroup(freqMenu);
    fill(m_freqGroup, m_controller->availableFastFrequency());
    QObject::connect(m_freqGroup, &QActionGroup::triggered, [this](QAction* action)
    {
        emit this->frequencyChanged(action->data().toInt());
    });

    //Update rate menu
    auto uprateMenu = new QMenu(tr("Update rate"), m_contextMenu.get());
    m_uprateGroup = new QActionGroup(uprateMenu);
    fill(m_uprateGroup, m_controller->availableUprate());
    QObject::connect(m_uprateGroup, &QActionGroup::triggered, [this](QAction* action)
    {
        emit this->uprateChanged(action->data().toInt());
    });

    //Amplification menu
    auto amplMenu = new QMenu(tr("Amplification"), m_contextMenu.get());
    m_amplGroup = new QActionGroup(amplMenu);
    fill(m_amplGroup, m_controller->availableAmpl());
    QObject::connect(m_amplGroup, &QActionGroup::triggered, [this](QAction* action)
    {
        emit this->amplificationChanged(action->data().toInt());
    });

    m_brightControl = new QAction("Control brightness");
    m_brightControl->setCheckable(true);
    QObject::connect(m_brightControl, &QAction::triggered, this, &Tray::brightControlChanged);

    m_autostart = new QAction("Start on system startup");
    m_autostart->setCheckable(true);
    QObject::connect(m_autostart, &QAction::triggered, this, &Tray::autostartChanged);

    //Create main menu
    m_contextMenu->addAction(tr("Show..."), this, &Tray::openMainWindow);
    m_contextMenu->addSeparator();
    m_contextMenu->addMenu(methodMenu);
    m_contextMenu->addMenu(deviceMenu);
    m_contextMenu->addMenu(uprateMenu);
    m_contextMenu->addMenu(freqMenu);
    m_contextMenu->addMenu(amplMenu);
    m_contextMenu->addAction(m_brightControl);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_autostart);
    m_contextMenu->addAction(tr("Exit"), this, &Tray::exit);
}
