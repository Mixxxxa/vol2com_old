#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <memory>
#include <vector>
#include <utility>

#include "constants.h"

class BassLib;
class QSettings;
class QTimer;

class Controller : public QObject{
    Q_OBJECT

public:
    explicit Controller(QSettings *settings, QObject *parent = nullptr);
    ~Controller();

    static std::vector<std::pair<QString, int>> availableDevices();
    static std::vector<std::pair<QString, int>> availableCaptureMethods();
    static std::vector<std::pair<QString, int>> availableFastFrequency();
    static std::vector<std::pair<QString, int>> availableUprate();
    static std::vector<std::pair<QString, int>> availableAmpl();
    static std::vector<std::pair<QString, QString>> availableLanguages();
    static std::vector<std::pair<QString, QString>> availablePorts();

private:
    QSettings *m_settings;
    std::shared_ptr<BassLib> m_bassLib;
    QTimer *m_timer;
};

#endif // CONTROLLER_H
