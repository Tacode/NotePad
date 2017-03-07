#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "about.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QTextStream>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QFontDialog>
#include <QColorDialog>
#include <QDateTime>
#include <QApplication>
#include <QDesktopServices>
#include <QUrl>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString SaveFileName;
private slots:
    void doProcessNewFile();
    void doProcessOpenFile();
    void doProcessSaveFile();
    void doProcessSaveASFile();
    void doProcessPrintFile();
    void doProcessFont();
    void doProcessColor();
    void doProcessDateTime();
    void doProcessAboutWebsite();
    void doProcessAboutSoftware();
    void doProcessUpdata();
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
