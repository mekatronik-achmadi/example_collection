#ifndef HELLO_H
#define HELLO_H

#include <QMainWindow>

class hello : public QObject
{
    Q_OBJECT

public:
    hello();
    ~hello();

private slots:
    void to_quit(void);
};

#endif // HELLO_H
