/**
 * @file ceSerial.h
 * @brief ceSerial communication class for Windows and Linux (header)
 *
 * @details Original works and credits: https://github.com/yan9a/serial
 *
 * @addtogroup SERIAL
 * @{
 */

#ifndef CESERIAL_H
#define CESERIAL_H

#if defined(_WIN64) || defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__) || defined(__CYGWIN__)
    #define ceWINDOWS
#elif defined(linux) || defined(__linux) || defined(__linux__)
    #define ceLINUX
#endif

#include <string>

#ifdef ceWINDOWS
    #include <windows.h>
#endif

class ceSerial {
    char rxchar;
    std::string port;
    long baud;
    long dsize;
    char parity;
    float stopbits;

#ifdef ceWINDOWS
    HANDLE hComm; //handle
    OVERLAPPED osReader;
    OVERLAPPED osWrite;
    BOOL fWaitingOnRead;
    COMMTIMEOUTS timeouts_ori;
#else
    long fd; //serial_fd
#endif

public:
    static void Delay(unsigned long ms);
    ceSerial();
    ceSerial(std::string Device, long BaudRate, long DataSize, char ParityType, float NStopBits);
    ~ceSerial();
    long Open(void);
    void Close();

    char ReadChar(bool& success);
    bool WriteChar(char ch);
    bool Write(char *data);
    bool Write(char *data,long n);

    bool IsOpened();
#ifdef ceWINDOWS
    void SetPortWin(std::string Port);
#else
    void SetPort(std::string Port);
#endif
    std::string GetPort();
    void SetBaudRate(long baudrate);
    long GetBaudRate();

    bool SetRTS(bool value);
    bool SetDTR(bool value);
    void SetDataSize(long nbits);
    void SetParity(char p);
    void SetStopBits(float nbits);
};

#endif

/** @} */
