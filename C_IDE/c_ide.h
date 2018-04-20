#ifndef C_IDE_H
#define C_IDE_H

#include <QMainWindow>
#include <string>
#include <QProcess>

namespace Ui {
class C_IDE;
}

class C_IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit C_IDE(QWidget *parent = 0);
    ~C_IDE();

    bool readLines(std::string text);

    void readCode(std::string code);

private:
    Ui::C_IDE *ui;

    int lineNumber = 0;

    int port = 0;

    QProcess *cmd;

    void createUI();

    void error(std::string msg);

public slots:
    void refreshMem();

    void restartCode();
};

#endif // C_IDE_H
