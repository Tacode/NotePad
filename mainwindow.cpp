#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Untitled-NotePad");

    QObject::connect(ui->newAction,SIGNAL(triggered(bool)),this,SLOT(doProcessNewFile()));
    QObject::connect(ui->openAction,SIGNAL(triggered(bool)),this,SLOT(doProcessOpenFile()));
    QObject::connect(ui->saveAction,SIGNAL(triggered(bool)),this,SLOT(doProcessSaveFile()));
    QObject::connect(ui->saveAsAction,SIGNAL(triggered(bool)),this,SLOT(doProcessSaveASFile()));
    QObject::connect(ui->printAction,SIGNAL(triggered(bool)),this,SLOT(doProcessPrintFile()));
    QObject::connect(ui->exitAction,SIGNAL(triggered(bool)),this,SLOT(close()));
    QObject::connect(ui->fontAction,SIGNAL(triggered(bool)),this,SLOT(doProcessFont()));
    QObject::connect(ui->colorAction,SIGNAL(triggered(bool)),this,SLOT(doProcessColor()));
    QObject::connect(ui->dateTimeAction,SIGNAL(triggered(bool)),this,SLOT(doProcessDateTime()));
    QObject::connect(ui->copyAction,SIGNAL(triggered(bool)),ui->textEdit,SLOT(copy()));
    QObject::connect(ui->cutAction,SIGNAL(triggered(bool)),ui->textEdit,SLOT(cut()));
    QObject::connect(ui->pasteAction,SIGNAL(triggered(bool)),ui->textEdit,SLOT(paste()));
    QObject::connect(ui->selectaAllAction,SIGNAL(triggered(bool)),ui->textEdit,SLOT(selectAll()));
    QObject::connect(ui->undoAction,SIGNAL(triggered(bool)),ui->textEdit,SLOT(undo()));
    QObject::connect(ui->redoAction,SIGNAL(triggered(bool)),ui->textEdit,SLOT(redo()));
    QObject::connect(ui->aboutQt,SIGNAL(triggered(bool)),qApp,SLOT(aboutQt()));
    QObject::connect(ui->aboutWebsite,SIGNAL(triggered(bool)),this,SLOT(doProcessAboutWebsite()));
    QObject::connect(ui->aboutSoftware,SIGNAL(triggered(bool)),this,SLOT(doProcessAboutSoftware()));
    QObject::connect(ui->updataAction,SIGNAL(triggered(bool)),this,SLOT(doProcessUpdata()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::doProcessNewFile()
{
    if(ui->textEdit->document()->isModified()){
        int ret=QMessageBox::warning(this,"Warning","Do you want to save the file?",QMessageBox::Ok|QMessageBox::No,QMessageBox::Ok);
        if(ret==QMessageBox::Ok){
            this->doProcessSaveFile();
            ui->textEdit->clear();
            this->setWindowTitle("Untitled2-NotePad");
        }

    }
    else{
        ui->textEdit->clear();
        this->setWindowTitle("Untitled2-NotePad");
    }
}

void MainWindow::doProcessOpenFile()
{
    QString filename=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
    if(filename.isEmpty()){
        QMessageBox::information(this,"Error Information","Please Select The File");
        return;
    }
    QFile *file=new QFile();
    file->setFileName(filename);
    bool ok=file->open(QIODevice::ReadWrite);
    if(ok){
        QTextStream in(file);
        ui->textEdit->setText(in.readAll());
        file->close();
        delete file;
    }
    else{
        QMessageBox::information(this,"Error Information","File Open Error"+file->errorString());
        return;
    }

}

void MainWindow::doProcessSaveFile()
{
    if(SaveFileName.isEmpty()){
        this->doProcessSaveASFile();
    }
    else{
        QFile *file=new QFile();
        file->setFileName(SaveFileName);
        bool ok=file->open(QIODevice::WriteOnly);
        if(ok){
            QTextStream out(file);
            QString str=ui->textEdit->toPlainText();
            out<<str;
            out.flush();
            file->close();
            this->setWindowTitle(SaveFileName+"-NotePad");
            delete file;
        }
        else{
            QMessageBox::information(this,"Error Information","File Open Error"+file->errorString());
            return;
        }
    }
}

void MainWindow::doProcessSaveASFile()
{
    QString SaveFileName=QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath(),"FILE (*.txt);;SOURCES (*.cpp *.c);;HEADERS(*.h)");
    if(SaveFileName.isEmpty()){
        QMessageBox::information(this,"Error Information","Please Write File Name");
        return;
    }
    QFile *file=new QFile();
    file->setFileName(SaveFileName);
    bool ok=file->open(QIODevice::WriteOnly);
    if(ok){
        QTextStream out(file);
        QString str=ui->textEdit->toPlainText();
        out<<str;
        out.flush();
        file->close();
        this->setWindowTitle(SaveFileName+"-NotePad");
        delete file;
    }
    else{
        QMessageBox::information(this,"Error Information","File Open Error"+file->errorString());
        return;
    }
}

void MainWindow::doProcessPrintFile()
{
   // QPrinter *printer=new QPrinter();
    //QPrintDialog printDialog(printer, this);
    //QPrintDialog printDialog(this);


}

void MainWindow::doProcessFont()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,QFont("Arial",12),this,"Select Font");
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
    else{
        QMessageBox::information(this,"Error Information","Select Font Error");
        return;
    }
}

void MainWindow::doProcessColor()
{
    QColor color=QColorDialog::getColor(Qt::black,this,"Select Color");
    if(color.isValid()){
        ui->textEdit->setTextColor(color);
    }
    else{
        QMessageBox::information(this,"Error Information","Select Color Error");
        return;
    }


}

void MainWindow::doProcessDateTime()
{
    QDateTime current=QDateTime::currentDateTime();
    QString time=current.toString("yyyy-MM-dd hh:mm:ss");
    ui->textEdit->append(time);
}

void MainWindow::doProcessAboutWebsite()
{
    QDesktopServices::openUrl(QUrl("https://www.qt.io/"));
}

void MainWindow::doProcessAboutSoftware()
{
    About *about=new About;
    about->show();//unmodal dialog
    //about->exec() //modal dialog
}

void MainWindow::doProcessUpdata()
{
    QMessageBox msgBox;
    msgBox.setText("此版本为NotePad 1.0");
    msgBox.setInformativeText("暂无更新版本");
    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.setWindowTitle("更新信息");
    msgBox.setWindowIcon(this->windowIcon());
    msgBox.exec();
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if(ui->textEdit->document()->isModified()){
//        int ret=QMessageBox::warning(this,"Warning","Do you want to save the file?",QMessageBox::Ok|QMessageBox::No|QMessageBox::Cancel,QMessageBox::Ok);
//        if(ret==QMessageBox::Cancel){
//            event->ignore();
//        }
//        if(ret==QMessageBox::Ok){
//            this->doProcessSaveFile();
//        }
        QMessageBox msgBox;
        msgBox.setText("文本已经修改");
        msgBox.setInformativeText("您是否要保存文件?");
        msgBox.setStandardButtons(QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        msgBox.setWindowTitle("NotePad");
        msgBox.setWindowIcon(this->windowIcon());
        int ret=msgBox.exec();
        switch(ret){
            case QMessageBox::Save:
                 this->doProcessSaveFile();break;
            case QMessageBox::Discard:
                event->accept();break;
            case QMessageBox::Cancel:
                event->ignore();break;
        }
    }
    else{
        event->accept();
    }
}


