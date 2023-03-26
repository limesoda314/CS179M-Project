#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QLayout>
#include "ShippingPortDriver.h"
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
        ShippingPortDriver* shipDriver;
        std::vector<std::pair<int, int>> GUI_balanced_list;
        std::vector<std::string> GUI_move_save_states;

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
        void generate_balancing_states_clicked();
        void load_next_balance_states_clicked();
        void input_transfer_list_clicked();
        void submit_transfer_list_clicked();
        void add_another_transfer_item_clicked();
        void generate_transfer_moves_clicked();
        void next_transfer_moves_clicked();
};
#endif // MAINWINDOW_H
