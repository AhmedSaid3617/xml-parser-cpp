#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "consistency/consistency.h"
#include "convert/tree_to_json.h"
#include "fromat/format.h"

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
    QFile file(fileName);
    currentFileName = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionNew_triggered()
{
    currentFileName.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFileName.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        if (fileName.isEmpty())
            return;
        currentFileName = fileName;
    }
    else
    {
        fileName = currentFileName;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::on_actionCheck_for_errors_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    int err_line = check_errors(in_string.toStdString());
    if (err_line != -1)
    {
        out_string = QString("Error on line %1").arg(err_line);
    }
    else
    {
        out_string = "File is correct!";
    }

    ui->outputLabel->setText(out_string);
}

void MainWindow::on_actionFormat_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    int err_line = check_errors(in_string.toStdString());

    if (err_line != -1)
    {
        out_string = QString("Error on line %1").arg(err_line);
        ui->outputLabel->setText(out_string);
        return;
    }
    
    in_string = QString(formatXML(in_string.toStdString()).c_str());
    ui->textEdit->setPlainText(in_string);
}

void MainWindow::on_actionConvert_to_JSON_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    int err_line = check_errors(in_string.toStdString());

    if (err_line != -1)
    {
        out_string = QString("Error on line %1").arg(err_line);
        ui->outputLabel->setText(out_string);
        return;
    }
    
    QString fileName;
    // If we don't have a filename from before, get one.

    fileName = QFileDialog::getSaveFileName(this, "Save");
    if (fileName.isEmpty())
        return;
    currentFileName = fileName;

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text;
    text = xml_to_json(ui->textEdit->toPlainText().toStdString()).c_str();
    out << text;
    file.close();

    out_string = "Converted successfully.";
    ui->outputLabel->setText(out_string);

}

void MainWindow::on_actionFix_errors_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    int err_line = check_errors(in_string.toStdString());
    if (err_line != -1)
    {
        ui->textEdit->setText(QString(fix_errors(in_string.toStdString()).c_str()));
        out_string = "Fixed the file.";
    }
    else
    {
        out_string = "File is correct.";
    }

    // TODO: Remove whitespaces but not new lines.

    ui->outputLabel->setText(out_string);
}

