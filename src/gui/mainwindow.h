#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>

#include "graph/SocialNetwork.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionCheck_for_errors_triggered();

    void on_actionFormat_triggered();

    void on_actionConvert_to_JSON_triggered();

    void on_actionFix_errors_triggered();

    void on_actionVisualize_triggered();

    void on_actionMutual_followers_triggered();

    void on_actionSuggested_followers_triggered();

    void on_actionRemove_whitespaces_triggered();

    void on_actionCompress_file_triggered();

    void on_actionDecompress_file_triggered();

    void on_post_search_button_clicked();

    void on_topic_search_button_clicked();

private:
    Ui::MainWindow *ui;
    QString currentFileName;
    SocialNetwork social_network;
    bool extracted;
};
#endif // MAINWINDOW_H
