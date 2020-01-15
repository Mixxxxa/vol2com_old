#ifndef CONSTANTS_H
#define CONSTANTS_H

//NOTE:
//Don't use METHOD as ENUM name. Even in namespace...

#include <QString>
#include <QObject>

namespace Constants
{
    //constexpr int METHODS_COUNT = 3;
    constexpr int MIN_FREQUENCY = 0;
    constexpr int MAX_FREQUENCY = 19;
    constexpr int MIN_UPDATE_RATE = 1;
    constexpr int MAX_UPDATE_RATE = 120;
    constexpr int MIN_AMPLIFICATION = 10;
    constexpr int MAX_AMPLIFICATION = 200;
    constexpr int FREQ_LOW = MIN_FREQUENCY + 1;
    constexpr int FREQ_MIDDLE = 10;
    constexpr int FREQ_HIGH = MAX_FREQUENCY - 1;

    enum class PROGRAMM_STATE
    {
        IDLE,
        READY,
        CONNECTING,
        WORKING
    };

    enum class ERROR_TYPE
    {
        CAPTURE_START_ERROR,        //Failed to start capture
        CAPTURE_RESTART_ERROR,      //Failed to restart with new device or method
        CAPTURE_DEVICE_ERROR,       //Device error
        CONNECT_ERROR,              //Failed to connect
        CONNECT_RESTART_ERROR,      //Failed to reconnect with new device
        CONNECT_DEVICE_ERROR,       //Connection to device lost
        UNKNOWN_ERROR               //Other errors. Need to attach info
    };

    namespace SETTINGS
    {
        //Settings name or paths in file
        constexpr auto METHOD = "method";
        constexpr auto FREQUENCY = "frequency";
        constexpr auto UPDATE_RATE = "uprate";
        constexpr auto AMPLIFICATION = "amplification";
        constexpr auto CONTROL_BRIGHTNESS = "brightness";
        constexpr auto DEVICE_TRACKING = "tracking";
        constexpr auto LANGUAGE = "locale";
        constexpr auto LAST_PRIMARY = "lastPrimary";
        constexpr auto LAST_SECONDARY = "lastSecondary";
        constexpr auto LAST_DEVICE_ID = "lastDevice";

        //Default value for settings
        constexpr auto DEFAULT_AUTORUN_LOCATION = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
        constexpr auto DEFAULT_COM_PORT = "COM0";
        constexpr int  DEFAULT_FREQUENCY = 19;
        constexpr int  DEFAULT_UPRATE = 40;
        constexpr int  DEFAULT_AMPLIFICATION = 100;
        constexpr bool DEFAULT_BRIGHTNESS_CONTROL = true;
        constexpr bool DEFAULT_TRACK_DEFAULT_DEVICE = true;

        enum AMPLIFICATION
        {
            AMPL200 = 200,
            AMPL175 = 175,
            AMPL150 = 150,
            AMPL125 = 125,
            AMPL100 = 100,
            AMPL075 = 75,
            AMPL050 = 50
        };

        enum class LOCALE
        {
            ENGLISH =0,                 //English MUST be 0, because it native programm language.
            RUSSIAN
        };
    }

    namespace COM
    {
        constexpr auto COLOR_CONNECTED = "color: rgb(0, 255, 0)";
        constexpr auto COLOR_CONNECTING = "color: rgb(255, 215, 0)";
        constexpr auto COLOR_FAILED = "color: rgb(255, 0, 0)";

        enum class PORT
        {
            NONE,
            FIRST,
            SECOND
        };

        enum class STATUS
        {
            CONNECTED,
            CONNECTING,
            FAILED,
            UNUSED
        };

        /*struct portsInfo
        {
            portsInfo(const QString &firstPort = "COM0", const Constants::COM::STATUS &firstStatus = Constants::COM::UNUSED,
                         const QString &secondPort = "COM0", const Constants::COM::STATUS &secondStatus = Constants::COM::UNUSED) :
                firstName(firstPort), secondName(secondPort),
                firstStatus(firstStatus), secondStatus(secondStatus){}

            QString firstName;
            QString secondName;
            Constants::COM::STATUS firstStatus;
            Constants::COM::STATUS secondStatus;
        };*/
    }

    namespace CAPTURE
    {
        enum TYPE
        {
            COLOR,
            VOLUME
        };
    }
}

namespace Colors
{
    constexpr int MIN_VALUE = 0;
    constexpr int MAX_VALUE = 255;

    constexpr int BRIGHTNESS_CONTROL_THRESHOLD = 110;
    constexpr int RED_TO_YELLOW_TOP = 254;
    constexpr int RED_TO_YELLOW_BOTTOM = 178;
    constexpr int YELLOW_TO_GREEN_TOP = 177;
    constexpr int YELLOW_TO_GREEN_BOTTOM = 127;
    constexpr int GREEN_TO_LIGHTBLUE_TOP = 126;
    constexpr int GREEN_TO_LIGHTBLUE_BOTTOM = 76;
    constexpr int LIGHTBLUE_TO_BLUE_TOP = 75;
    constexpr int LIGHTBLUE_TO_BLUE_BOTTOM = 45;
    constexpr int BLUE_TO_PURPLE_TOP = 44;
    constexpr int BLUE_TO_PURPLE_BOTTOM = 1;
}

Q_DECLARE_METATYPE(Constants::ERROR_TYPE)
Q_DECLARE_METATYPE(Constants::CAPTURE::TYPE)
Q_DECLARE_METATYPE(Constants::PROGRAMM_STATE)

#endif // CONSTANTS_H
