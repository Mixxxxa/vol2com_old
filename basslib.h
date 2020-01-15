#ifndef SPECTRE_H
#define SPECTRE_H

#include <QObject>

class BassLib : public QObject{
    Q_OBJECT

public:
    explicit BassLib(QObject *parent = nullptr);
    ~BassLib();

    static std::vector<std::pair<QString, int> > availableDevices();
    static QString deviceName(int id);
    static int defaultDeviceId();

public slots:
    bool init(const int device);
    void deinit();
    int lastError();    
    std::vector<uint8_t> ftt();

private:
    bool m_init;
    const int m_maxValue;
    const unsigned m_bands;
    const unsigned m_fftSamples;
    float *m_fft;
};

#endif // SPECTRE_H
