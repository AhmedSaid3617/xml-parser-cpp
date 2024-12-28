#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "consistency/consistency.h"
#include "convert/tree_to_json.h"
#include "fromat/format.h"
#include "compression/compression.h"
#include "QImageGraphVisualization.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    extracted = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    extracted = false;
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
    extracted = false;
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
    int err_line = verify(in_string.toStdString());
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
    int err_line = verify(in_string.toStdString());

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
    int err_line = verify(in_string.toStdString());

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
    string in_string_std = in_string.toStdString();
    QString out_string;
    int err_line = verify(in_string.toStdString());
    if (err_line != -1)
    {
        ui->textEdit->setText(QString(fix_file(in_string_std).c_str()));
        out_string = "Fixed the file.";
    }
    else
    {
        out_string = "File is correct.";
    }

    // TODO: Remove whitespaces but not new lines.

    ui->outputLabel->setText(out_string);
}

void MainWindow::on_actionVisualize_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    if (in_string.isEmpty())
    {
        return;
    }
    
    if (!extracted)
    {
        social_network.extract_data(in_string.toStdString());
        extracted = true;
    }

    QString out_string;
    const string most_active = social_network.get_most_active_user()->getName();
    const string most_influential = social_network.get_most_influencer_user()->getName();
    QString most_active_qs = QString(most_active.c_str());
    QString most_influential_qs = QString(most_influential.c_str());

    out_string = QString("Most Active User: %1\nMost influential user: %2").arg(most_active_qs, most_influential_qs);
    ui->outputLabel->setText(out_string);

    QPixmap pix;
    auto visitor = new QImageGraphVisualization();
    QImage image = any_cast<QImage>(social_network.accept(visitor));
    pix.convertFromImage(image);
    ui->label_pic->setPixmap(pix);
}


void MainWindow::on_actionMutual_followers_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    QStringList user_names;

    if (in_string.isEmpty())
    {
        return;
    }
    
    if (!extracted)
    {
        social_network.extract_data(in_string.toStdString());
        extracted = true;
    }

    string users_string = ui->user_text_edit->toPlainText().toStdString();

    std::istringstream iss(users_string);
    std::vector<int> user_ids;
    vector<User *> mutuals;
    int id;

    while (iss >> id)
    {
        user_ids.push_back(id);
    }
    
    try
    {
        mutuals = social_network.who_does_n_users_follow(user_ids);

        for(User* user: mutuals){
            user_names.append(user->getName().c_str());
        }
        out_string = user_names.join("\n");
        ui->outputLabel->setText(out_string);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}


void MainWindow::on_actionSuggested_followers_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    QStringList user_names;

    if (in_string.isEmpty())
    {
        return;
    }
    
    if (!extracted)
    {
        social_network.extract_data(in_string.toStdString());
        extracted = true;
    }

    string users_string = ui->user_text_edit->toPlainText().toStdString();

    std::istringstream iss(users_string);
    std::vector<int> user_ids;
    vector<User *> suggested;
    int id;

    while (iss >> id)
    {
        user_ids.push_back(id);
    }
    
    try
    {
        suggested = social_network.suggest_users_to_follow(social_network.get_user(user_ids[0]));

        for(User* user: suggested){
            user_names.append(user->getName().c_str());
        }
        out_string = user_names.join("\n");
        ui->outputLabel->setText(out_string);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}


void MainWindow::on_actionRemove_whitespaces_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    int err_line = verify(in_string.toStdString());

    if (err_line != -1)
    {
        out_string = QString("Error on line %1").arg(err_line);
        ui->outputLabel->setText(out_string);
        return;
    }

    in_string = QString(minifyXML(in_string.toStdString()).c_str());
    ui->textEdit->setPlainText(in_string);
}


void MainWindow::on_actionCompress_file_triggered()
{
    QString in_string = ui->textEdit->toPlainText();
    QString out_string;
    int err_line = verify(in_string.toStdString());

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
    text = Compress(minifyXML(ui->textEdit->toPlainText().toStdString())).c_str();
    out << text;
    file.close();

    out_string = "Compressed successfully.";
    ui->outputLabel->setText(out_string);
}


void MainWindow::on_actionDecompress_file_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    extracted = false;
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
    QString compressed_text = in.readAll();
    file.close();

    QString decompressed = QString(Decompress(compressed_text.toStdString()).c_str());
    ui->textEdit->setText(decompressed);
}

