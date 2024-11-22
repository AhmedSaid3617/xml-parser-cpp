#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "str_count.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;
    file = new QFile(fileName);
    currentFileName = fileName;
    if (!file->open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file->errorString());
        return;
    }
    setWindowTitle(fileName);
    inTextStream = new QTextStream(file);
    text = inTextStream->readAll();
    ui->textEdit->setText(text);
    file->close();
}


void MainWindow::on_actionNew_triggered()
{
    currentFileName.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionSave_triggered()
{

}


void MainWindow::on_printButton_clicked()
{
    std::cout << get_str_size(text.toStdString());
}

