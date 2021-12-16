#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>

namespace Ui {
class app;
}

class app : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit app(QWidget *parent = 0);
    ~app();
    
private:
    Ui::app *ui;

    QProcess process;

    QString avr_path;
    QString avr_arg_core;
    QString avr_arg_tool;
    QString avr_arg_port;
    QString avr_arg_load;

    QString stlink_path;
    QString stlink_arg_action;
    QString stlink_arg_load;
    QString stlink_arg_size;

    QString stflash_path;
    QString stflash_arg_action;
    QString stflash_arg_load;
    QString stflash_arg_size;
    QString stflash_arg_serial;
    QString stflash_arg_verify;

private slots:
    void processOnGoing(void);
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void processError(QProcess::ProcessError error);

    void app_quit(void);
    void app_help(void);
    void app_about(void);

    void avr_browse(void);
    void avr_write(void);
    void avr_erase(void);
    void avr_test(void);

    void stlink_browse(void);
    void stlink_write(void);
    void stlink_erase(void);

    void stflash_browse(void);
    void stflash_write(void);
    void stflash_erase(void);
    void stflash_test(void);

};

#endif // APP_H
