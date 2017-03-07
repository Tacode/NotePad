#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    MainWindow *main=new MainWindow;
    this->setWindowIcon(QIcon(main->windowIcon()));
    QMovie *movie=new QMovie(":/new/ICON/images1/lion.gif");
    ui->movieLabel->setMovie(movie);
    ui->movieLabel->setScaledContents(this);
    movie->start();


}

About::~About()
{
    delete ui;
}
