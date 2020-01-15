#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "constants.h"

#include <QWidget>
#include <QSignalBlocker>
#include <memory>

class Controller;
class QGroupBox;
class QComboBox;
class QLabel;
class QPushButton;
class QSlider;
class QGridLayout;
class QVBoxLayout;
class QHBoxLayout;
class QMessageBox;
class QMenu;
class QAction;
class QActionGroup;
class QHideEvent;
class QCloseEvent;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(std::shared_ptr<Controller> controller, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setMethod(const int method);
    void setDevice(const int device);
    void setFrequency(const int freq);
    void setUpdateRate(const int uprate);
    void setAmplification(const int ampl);
    void setBrightControl(const bool check);
    void setAutostart(const bool check);

    void syncSettings();

signals:
    void methodChanged(const int method);
    void deviceChanged(const int device);
    void frequencyChanged(const int frequency);
    void uprateChanged(const int uprate);
    void amplificationChanged(const int amplification);
    void brightControlChanged(const bool check);
    void autostartChanged(const bool check);

    void helpButtonPressed();
    void gitButtonPressed();
    void languageChanged(const QString &langCode);

    void start(const QString &com1, const QString &com2, const int deviceId);
    void stop();
    void hideWindow();
    void exit();
    void updateDeviceList();

private:
    void createUI();

    std::shared_ptr<Controller> m_controller;

    QLabel *m_firstComLabel;
    QLabel *m_secondComLabel;
    //QLabel *m_uprateLabel;
    QComboBox *m_firstComCombo;
    QComboBox *m_secondComCombo;
    QComboBox *m_methodCombo;
    QComboBox *m_captureDeviceCombo;
    QPushButton *m_updateDataButton;
    QPushButton *m_toggleButton;
    QPushButton *m_helpButton;
    QPushButton *m_settingsButton;
    QSlider *m_frequencySlider;
    QSlider *m_uprateSlider;
    QActionGroup* m_valueAmplGroup;
    QActionGroup* m_languageGroup;
    QAction *m_autoStartAction;
    QAction *m_controlBrightness;
};

#endif // MAINWINDOW_H
