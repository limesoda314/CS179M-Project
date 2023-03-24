#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLayout>
<<<<<<< HEAD
#include "Ship.h"
=======
#include <QVBoxLayout>
>>>>>>> ea1f3fc70dc18dcb294d36d066efa1ce15282a4d

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
        void load_manifest_clicked();
};
#endif // MAINWINDOW_H
