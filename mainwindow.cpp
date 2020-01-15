// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "mainwindow.h"
#include "controller.h"
#include "guihelper.h"

#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#include <QMenu>
#include <QAction>
#include <QActionGroup>

#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(std::shared_ptr<Controller> controller, QWidget *parent) :
    QWidget(parent),
    m_controller(controller)
{
    this->createUI();
    this->show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setMethod(const int method)
{
    if(!signalsBlocked())
        select(m_methodCombo, method);
}

void MainWindow::setDevice(const int device)
{
    if(!signalsBlocked())
        select(m_captureDeviceCombo, device);
}

void MainWindow::setFrequency(const int freq)
{
    if(!signalsBlocked())
        select(m_frequencySlider, freq);
}

void MainWindow::setUpdateRate(const int uprate)
{
    if(!signalsBlocked())
        select(m_uprateSlider, uprate);
}

void MainWindow::setAmplification(const int ampl)
{
    if(!signalsBlocked())
        select(m_valueAmplGroup, ampl);
}

void MainWindow::setBrightControl(const bool check)
{
    if(!signalsBlocked())
        m_controlBrightness->setChecked(check);
}

void MainWindow::setAutostart(const bool check)
{
    if(!signalsBlocked())
        m_autoStartAction->setChecked(check);
}

void MainWindow::syncSettings()
{

}

void MainWindow::createUI()
{
    //this->setFixedSize(300, 360);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);

    //Connect group
    {
        m_firstComLabel = new QLabel(tr("Primary COM port:"));
        m_secondComLabel = new QLabel(tr("Secondary COM port:"));
        m_firstComCombo = new QComboBox();
        m_secondComCombo = new QComboBox();
        m_updateDataButton = new QPushButton("O");
        m_updateDataButton->setFlat(true);
        m_updateDataButton->setMinimumSize(40, 60);
        QGroupBox *connectGroup = new QGroupBox(tr("Connect"));
        QGridLayout *connectGridLayout = new QGridLayout(connectGroup);
        connectGridLayout->setColumnStretch(0, 4);
        connectGridLayout->setColumnStretch(1, 3);
        connectGridLayout->setColumnStretch(2, 1);
        connectGridLayout->setVerticalSpacing(10);
        connectGridLayout->addWidget(m_firstComLabel, 0, 0);
        connectGridLayout->addWidget(m_secondComLabel, 1, 0);
        connectGridLayout->addWidget(m_firstComCombo, 0, 1);
        connectGridLayout->addWidget(m_secondComCombo, 1, 1);
        connectGridLayout->addWidget(m_updateDataButton, 0, 2, 2, 1);
        mainLayout->addWidget(connectGroup, 0);

        fill(m_firstComCombo, m_controller->availablePorts());
        fill(m_secondComCombo, m_controller->availablePorts());
    }

    //Capture settings group
    {
        m_captureDeviceCombo = new QComboBox();
        fill(m_captureDeviceCombo, m_controller->availableDevices());

        m_methodCombo = new QComboBox();
        fill(m_methodCombo, m_controller->availableCaptureMethods());

        m_frequencySlider = new QSlider(Qt::Horizontal);
        m_frequencySlider->setRange(Constants::MIN_FREQUENCY, Constants::MAX_FREQUENCY);
        m_frequencySlider->setTickInterval(2);
        m_frequencySlider->setTickPosition(QSlider::TicksBelow);

        m_uprateSlider = new QSlider(Qt::Horizontal);
        m_uprateSlider->setRange(Constants::MIN_UPDATE_RATE, Constants::MAX_UPDATE_RATE);
        m_uprateSlider->setTickInterval(20);
        m_uprateSlider->setTickPosition(QSlider::TicksBelow);

        auto captureGroup = new QGroupBox(tr("Sound capture"));
        auto captureLayout = new QFormLayout(captureGroup);

        captureLayout->addRow(tr("Device:"), m_captureDeviceCombo);
        captureLayout->addRow(tr("Mode:"), m_methodCombo);
        captureLayout->addRow(tr("Sound frequency:\n(1 - 20kHz)"), m_frequencySlider);
        captureLayout->addRow(tr("Update rate:"), m_uprateSlider);
        mainLayout->addWidget(captureGroup, 1);
    }

    //Bottom buttons group
    {
        m_toggleButton = new QPushButton(tr("Start"));
        m_helpButton = new QPushButton(tr("Help"));
        m_settingsButton = new QPushButton("...");
        m_settingsButton->setMinimumSize(10,10);
        QHBoxLayout *bottomButtonsLayout = new QHBoxLayout();
        bottomButtonsLayout->addWidget(m_toggleButton, 3);
        bottomButtonsLayout->addWidget(m_helpButton, 1);
        bottomButtonsLayout->addWidget(m_settingsButton, 1);
        mainLayout->addLayout(bottomButtonsLayout, 0);
    }

    //Other settings context menu
    {
        auto otherContextMenu = new QMenu(m_settingsButton);

        auto amplificationMenu = new QMenu(tr("Amplification"), otherContextMenu);
        m_valueAmplGroup = new QActionGroup(amplificationMenu);
        fill(m_valueAmplGroup, m_controller->availableAmpl());
        otherContextMenu->addMenu(amplificationMenu);

        m_controlBrightness = otherContextMenu->addAction(tr("Control brightness"), this, &MainWindow::brightControlChanged);
        m_controlBrightness->setCheckable(true);
        otherContextMenu->addSeparator();
        m_autoStartAction = otherContextMenu->addAction(tr("Start on system startup"), this, &MainWindow::autostartChanged);
        m_autoStartAction->setCheckable(true);

        auto languageMenu = new QMenu(tr("Language"), otherContextMenu);
        m_languageGroup = new QActionGroup(languageMenu);
        fill(m_languageGroup, m_controller->availableLanguages());
        otherContextMenu->addMenu(languageMenu);

        otherContextMenu->addAction(tr("vol2com on GitHub"), this, &MainWindow::gitButtonPressed);
        otherContextMenu->addAction(tr("Help"), this, &MainWindow::helpButtonPressed);

        QObject::connect(m_settingsButton, &QPushButton::clicked, [otherContextMenu]()
        {
            otherContextMenu->exec(QCursor::pos());
        });
    }
}
