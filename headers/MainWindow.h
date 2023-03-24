#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLayout>
#include "Ship.h"
#include <QVBoxLayout>

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
        Ship *manifestShip;
        
    private:
        Ui::MainWindow *ui;
    
    private slots:
        void login_button_clicked();
        void add_comment_clicked();
        void refresh_logfile_output_clicked();
        void refresh_view_ship_clicked();
        void load_manifest_balance_clicked();
        void load_manifest_status_clicked();
        void load_manifest_onload_clicked();
};
#endif // MAINWINDOW_H
