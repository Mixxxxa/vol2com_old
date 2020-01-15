#ifndef ABSTRACTCAPTUREMETHOD_H
#define ABSTRACTCAPTUREMETHOD_H

#include <QObject>
#include <memory>
#include "basslib.h"

class CaptureMethodBase : public QObject{
    Q_OBJECT

public:
    explicit CaptureMethodBase(std::shared_ptr<BassLib> lib, QObject *parent = nullptr) :
        QObject(parent),
        m_bass(lib) {}
    virtual ~CaptureMethodBase();

public slots:
    virtual bool start(const int device) = 0;
    virtual void stop() = 0;
    virtual int  currentValue(const int param =0) = 0;
    virtual int  lastError() = 0;

signals:
    void started();
    void stopped();
    void error();

private:
    std::shared_ptr<BassLib> m_bass;

};

#endif // ABSTRACTCAPTUREMETHOD_H
