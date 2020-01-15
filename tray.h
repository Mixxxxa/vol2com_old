#ifndef TRAY_H
#define TRAY_H

#include <QObject>
#include <QSystemTrayIcon>
#include <memory>

class QMenu;
class QActionGroup;
class QAction;
class Controller;

class Tray : public QObject{
    Q_OBJECT

public:
    Tray(std::shared_ptr<Controller> controller, QObject *parent=nullptr);
    ~Tray();

public slots:
    void updateMethodsMenu();
    void updateDevicesMenu();

    void setMethod(const int method);
    void setDevice(const int device);
    void setFrequency(const int freq);
    void setUpdateRate(const int uprate);
    void setAmplification(const int ampl);
    void setBrightControl(const bool check);
    void setAutostart(const bool check);

signals:
    void methodChanged(const int method);
    void deviceChanged(const int device);
    void frequencyChanged(const int frequency);
    void uprateChanged(const int uprate);
    void amplificationChanged(const int amplification);
    void brightControlChanged(const bool check);
    void autostartChanged(const bool check);

    void openMainWindow();
    void exit();

private slots:
    void onTrayActivate(QSystemTrayIcon::ActivationReason reason);

private:
    void createMenu();

    std::shared_ptr<Controller> m_controller;
    QSystemTrayIcon *m_tray;
    std::unique_ptr<QMenu> m_contextMenu;

    QActionGroup *m_methodGroup;
    QActionGroup *m_deviceGroup;
    QActionGroup *m_freqGroup;
    QActionGroup *m_uprateGroup;
    QActionGroup *m_amplGroup;
    QAction *m_brightControl;
    QAction *m_autostart;
};

#endif // TRAY_H
