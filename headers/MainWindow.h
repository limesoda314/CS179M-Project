#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLayout>

class Logger;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        Logger* logger;
        
    private:
        Ui::MainWindow *ui;
    
    private slots:
        void login_button_clicked();
        void add_comment_clicked();
        void refresh_logfile_output_clicked();
};
#endif // MAINWINDOW_H
