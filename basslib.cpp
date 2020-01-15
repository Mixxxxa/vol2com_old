// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "basslib.h"
#include "constants.h"
#include "bass.h"
#include "basswasapi.h"
#include <array>

#include <QDebug>

BassLib::BassLib(QObject *parent) :
    QObject(parent),
    m_init(false),
    m_maxValue(Colors::MAX_VALUE),
    m_bands(20),
    m_fftSamples(1024),
    m_fft(nullptr)
{
}

BassLib::~BassLib()
{
    this->deinit();
}

std::vector<std::pair<QString, int> > BassLib::availableDevices()
{
    std::vector<std::pair<QString, int> > temp;
    BASS_WASAPI_DEVICEINFO device;

    for (DWORD i = 0; BASS_WASAPI_GetDeviceInfo(i, &device); ++i)
    {
        if((device.flags&BASS_DEVICE_ENABLED) && ((device.flags&BASS_DEVICE_LOOPBACK) || (device.flags&BASS_DEVICE_INPUT)))
        {
            auto displayName = QString("%1 - %2").arg(i).arg(device.name);
            temp.push_back(std::make_pair(displayName, static_cast<int>(i)));
        }
    }

    return temp;
}

QString BassLib::deviceName(int id)
{
    BASS_WASAPI_DEVICEINFO device;

    if(BASS_WASAPI_GetDeviceInfo(static_cast<DWORD>(id), &device))
    {
        return QString(device.name);
    }
    return QString();
}

//Helper function for WASAPI BASS Lib. See BASS_WASAPI_Init docs
DWORD CALLBACK WasapiProc(void *buffer, DWORD length, void *user)
{
    Q_UNUSED(buffer)
    Q_UNUSED(length)
    Q_UNUSED(user)
    return static_cast<DWORD>(1);
}

//On Linux may cause problem. See BASS_GetDeviceInfo platform specific section
int BassLib::defaultDeviceId()
{
    BASS_WASAPI_DEVICEINFO device;
    for (DWORD i = 0; BASS_WASAPI_GetDeviceInfo(i, &device); ++i)
        if(device.flags&BASS_DEVICE_DEFAULT)
            return static_cast<int>(i);

    return -1;
}

bool BassLib::init(const int device)
{
    if(!BASS_Init(0, 44100, 0, nullptr, nullptr))
    {
        qDebug() << "BassLib init failed" << BASS_ErrorGetCode();
        BASS_Free();
        return false;
    }

    if(!BASS_WASAPI_Init(device, 0, 0, BASS_WASAPI_BUFFER, 1, 0.1f, WasapiProc, nullptr))
    {
        qDebug() << "Bass WASAPI init failed" << BASS_ErrorGetCode();
        BASS_WASAPI_Free();
        BASS_Free();
        return false;
    }

    if(!BASS_WASAPI_Start())
    {
        qDebug() << "Bass WASAPI start failed" << BASS_ErrorGetCode();
        BASS_WASAPI_Free();
        BASS_Free();
        return false;
    }

    m_fft = new float[m_fftSamples];
    m_init = true;
    qDebug() << "Bass initiated with device" << device;

    return true;
}

void BassLib::deinit()
{
    if(m_init)
    {
        BASS_WASAPI_Free();
        BASS_Free();

        delete[] m_fft;
        m_fft = nullptr;
        m_init = false;
    }
}

std::vector<uint8_t> BassLib::ftt()
{
    if(!m_init)
        return std::vector<uint8_t>();

    std::vector<uint8_t> result(m_bands);
    BASS_WASAPI_GetData(m_fft, BASS_DATA_FFT2048);
    int y = 0, b0 = 0;
    float peak;

    for (size_t x = 0; x < m_bands; ++x)
    {
        peak = 0;
        int b1 = static_cast<int>(pow(2, x*10.0/(m_bands-1)));
        if (b1 > 1023)
            b1 = 1023;
        if (b1 <= b0)
            b1 = b0+1;
        for (; b0 < b1; ++b0)
            if (peak < m_fft[1+b0])
                peak = m_fft[1+b0];

        y = static_cast<int>(sqrt(peak) * 3 * m_maxValue);

        if(y > m_maxValue)
            y = m_maxValue;
        else if (y < 0)
            y = 0;

        result[x] = static_cast<uint8_t>(y);
    }
    return result;
}

int BassLib::lastError()
{
    return BASS_ErrorGetCode();
}



