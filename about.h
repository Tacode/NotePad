#ifndef ABOUT_H
#define ABOUT_H
#include "mainwindow.h"
#include <QDialog>
#include <QMovie>
namespace Ui {
class About;
}

class About : public QDialog
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
