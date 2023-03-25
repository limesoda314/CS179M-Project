#include "../headers/MainWindow.h"
#include "ui_MainWindow.h"
#include <iostream>
#include <QtWidgets>

#include "../headers/Logger.h"
#include "../headers/Ship.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->logger = new Logger(this);
    this->manifestShip = new Ship();

    QPushButton tmp;

    // Signal/Slot connections
    this->connect(ui->loginbutton, &QPushButton::clicked, this, &MainWindow::login_button_clicked);
    this->connect(ui->add_comment_button, &QPushButton::clicked, this, &MainWindow::add_comment_clicked);
    this->connect(ui->refresh_logfile_view_output_box, &QPushButton::clicked, this, &MainWindow::refresh_logfile_output_clicked);
    this->connect(ui->onload_offload_load_manifest, &QPushButton::clicked, this, &MainWindow::load_manifest_onload_clicked);
    this->connect(ui->balancing_manifest_button, &QPushButton::clicked, this, &MainWindow::load_manifest_balance_clicked);
    this->connect(ui->manifest_status_load_manifest_button, &QPushButton::clicked, this, &MainWindow::load_manifest_status_clicked);
    this->connect(ui->manifest_status_view_ship_button, &QPushButton::clicked, this, &MainWindow::refresh_view_ship_clicked);
    this->connect(ui->balancing_start_button, &QPushButton::clicked, this, &MainWindow::generate_balancing_states_clicked);

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

    // set the current logger string to commentString

    this->logger->setString("Comment: \"" + commentString + "\"");

    // Log the current string within logger
    this->logger->logComment();
    return;
}

void MainWindow::refresh_logfile_output_clicked() {
    std::cout << "refresh logfile output" << std::endl;
    
//    QVBoxLayout* newLayout = new QVBoxLayout();
//    QPlainTextEdit* myPlainTextBox = new QPlainTextEdit();
    
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

// --------------------------manifest status - print current ship---------------------------------
void MainWindow::refresh_view_ship_clicked() {
    std::cout << "refresh ship" << std::endl;

//    QVBoxLayout* newLayout = new QVBoxLayout();
//    QPlainTextEdit* myPlainTextBox = new QPlainTextEdit();

    if (manifestShip->get_manifest_name().size() == 0) {
        std::cout << "Error: manifest empty."  << std::endl;
        return;
    }

    std::string ship_view = manifestShip->print_ship();

    this->ui->manifest_status_view_ship_text->setPlainText(QString::fromStdString(ship_view));

    return;
}
// ---------------------------balance - load manifest----------------------------------

void MainWindow::load_manifest_balance_clicked() {
    std::cout << "load manifest clicked" << std::endl;
    QString filepathQ = this->ui->balancing_manifest_path->text();
    std::string filepath = filepathQ.toStdString();

    if (filepath == "" || filepath.at(0) == ' ') {
        this->ui->balancing_manifest_path->setPlaceholderText("Error: Please input a valid filepath.");
        return;
    }

    this->manifestShip->load_manifest(filepath);

    std::string comment = "Uploaded Manifest " + manifestShip->get_manifest_name() + ".txt";

    logger->logRawComment(comment);
}

// ----------------------------manifest status - load manifest---------------------------------------------------
void MainWindow::load_manifest_status_clicked() {
    std::cout << "load manifest clicked" << std::endl;
    QString filepathQ = this->ui->manifest_status_manifest_path->text();
    std::string filepath = filepathQ.toStdString();

    if (filepath == "" || filepath.at(0) == ' ') {
        this->ui->manifest_status_manifest_path->setPlaceholderText("Error: Please input a valid filepath.");
        return;
    }

    this->manifestShip->load_manifest(filepath);

    std::string comment = "Uploaded Manifest " + manifestShip->get_manifest_name() + ".txt";

    logger->logRawComment(comment);
}

// ---------------------------load/unload - load manifest----------------------------------
void MainWindow::load_manifest_onload_clicked() {
    std::cout << "load manifest clicked" << std::endl;
    QString filepathQ = this->ui->onload_offload_manifest_path->text();
    std::string filepath = filepathQ.toStdString();

    if (filepath == "" || filepath.at(0) == ' ') {
        this->ui->onload_offload_manifest_path->setPlaceholderText("Error: Please input a valid filepath.");
        return;
    }

    this->manifestShip->load_manifest(filepath);

    std::string comment = "Uploaded Manifest " + manifestShip->get_manifest_name() + ".txt";

    logger->logRawComment(comment);
}


// -------------------------balance - generate ship states----------------------------------------------------------------
void MainWindow::generate_balancing_states_clicked() {

    if (manifestShip->get_manifest_name().size() == 0) {
        std::cout << "Error: manifest empty."  << std::endl;
        return;
    }
    std::vector<std::string> saved_states;

    manifestShip->save_ship_states(saved_states, manifestShip->balance_list());

    this->ui->balancing_plain_text->setPlainText(QString::fromStdString(saved_states.at(0)));

    //this->ui->balancing_plain_text->clear();
    //this->ui->balancing_plain_text->setPlainText(QString::fromStdString(saved_states.at(1)));

}

