#include "../headers/MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include <QtWidgets>

#include "../headers/Logger.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->logger = new Logger(this);

    QPushButton tmp;

    // Signal/Slot connections
    this->connect(ui->loginbutton, &QPushButton::clicked, this, &MainWindow::login_button_clicked);
    this->connect(ui->add_comment_button, &QPushButton::clicked, this, &MainWindow::add_comment_clicked);
    this->connect(ui->refresh_logfile_view_output_box, &QPushButton::clicked, this, &MainWindow::refresh_logfile_output_clicked);
}

MainWindow::~MainWindow()
{
}

// TODO: review / test
void MainWindow::login_button_clicked() {
    std::cout << "login confirmation called" << std::endl;
    QString nameQString = this->ui->login_name_line_edit->text();
    std::string nameString = nameQString.toStdString();
    
    // In case of erroneous input
    if (nameString == "" || nameString.at(0) == ' ') {
        this->ui->login_confirmation_label->setText("Error: Please input a valid name.");
        return;
    }

    std::string finalString = "Currently logged in: " + nameString;
    QString finalQString = QString::fromStdString(finalString);
    this->ui->logged_in_label->setText(finalQString);
    
    std::string loginConfirmationString = "Success. User \"" + nameString + "\" logged in." + "\nAdded login information to logfile.";
    this->ui->login_confirmation_label->setText(QString::fromStdString(loginConfirmationString));  

    // Log user login information // TODO
    this->logger->logLogin(nameString);
    return;
}

// TODO finish
void MainWindow::add_comment_clicked() {
    std::cout << "add comment confirmation called" << std::endl;
    
    QString commentQString = this->ui->add_comment_text_box->toPlainText();
    std::string commentString = commentQString.toStdString();
    
    // In case of erroneous input
    if (commentString == "" || commentString.at(0) == ' ') {
        this->ui->add_comment_text_box->setPlaceholderText("Error: Please input a valid name.");
        return;
    }
    
    // clear the plain text editor
    this->ui->add_comment_text_box->setPlainText(QString::fromStdString(""));

    // set the current logger string to commentString

    this->logger->setString("Comment: \"" + commentString + "\"");

    // Log the current string within logger
    this->logger->logComment();
    return;
}

void MainWindow::refresh_logfile_output_clicked() {
    std::cout << "refresh logfile output" << std::endl;
    
    QVBoxLayout* newLayout = new QVBoxLayout();
    QPlainTextEdit* myPlainTextBox = new QPlainTextEdit();
    
    // Log to log file
    std::string folderpath = QApplication::applicationDirPath().toStdString() + "/logfiles";
    
    QDir _dir;
    
    int _dirExists = _dir.exists(QString::fromStdString(folderpath));
    
    if (!_dirExists) {
        _dir.mkdir(QString::fromStdString(folderpath));
    }
    
    std::string filepath = folderpath + "/logfile_";
    
    time_t now = time(0);
    tm *ltm = localtime(&now);
    
    filepath += std::to_string(1900 + ltm->tm_year) + ".txt";

    QString QFilePathString = QString::fromStdString(filepath); 

    QFile _file(QFilePathString);

    int _fileOpened = _file.open( QIODevice::ReadOnly );

    // Error checking
    if (!_fileOpened) {
        std::cout << "Error opening file: \"" << filepath << "\"" << std::endl;
        return;
    }
    
    std::string tot_string;
    
    QTextStream in(&_file);
    
    while (!in.atEnd()) {
        QString line = in.readLine();
        tot_string += line.toStdString() + "\n";
    }
    
    _file.close();
    
    this->ui->logfile_view_output_plaintext->setPlainText(QString::fromStdString(tot_string));
    
    return;
}
