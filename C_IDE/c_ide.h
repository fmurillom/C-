#ifndef C_IDE_H
#define C_IDE_H

#include <QMainWindow>

namespace Ui {
class C_IDE;
}

class C_IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit C_IDE(QWidget *parent = 0);
    ~C_IDE();

private:
    Ui::C_IDE *ui;

    void createUI();

public slots:
    void refreshMem();
};

#endif // C_IDE_H
