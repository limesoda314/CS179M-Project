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
    this->shipDriver = new ShippingPortDriver();

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
    this->connect(ui->balancing_next_button, &QPushButton::clicked, this, &MainWindow::load_next_balance_states_clicked);
    this->connect(ui->enter_transfer_info_button, &QPushButton::clicked, this, &MainWindow::input_transfer_list_clicked);
    this->ui->Onload_offload_popup->hide();


    this->connect(ui->load_unload_submit_button, &QPushButton::clicked, this, &MainWindow::submit_transfer_list_clicked);
    this->connect(ui->add_yet_another_transfer_list_button, &QPushButton::clicked, this, &MainWindow::add_another_transfer_item_clicked);
    this->connect(ui->onload_offload_calculate_button, &QPushButton::clicked, this, &MainWindow::generate_transfer_moves_clicked);
    this->connect(ui->transfer_next_move_button, &QPushButton::clicked, this, &MainWindow::next_transfer_moves_clicked);






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

    if (this->shipDriver->getShip()->get_manifest_name().size() == 0) {
        std::cout << "Error: manifest empty."  << std::endl;
        return;
    }

    std::string ship_view = this->shipDriver->getShip()->print_ship();

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

    this->shipDriver->getShip()->load_manifest(filepath);

    std::string comment = "Opened Manifest " + this->shipDriver->getShip()->get_manifest_name() + ".txt. There are ";
    comment += std::to_string(this->shipDriver->getShip()->num_boxes());
    comment += " containers on the ship.";

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

    this->shipDriver->getShip()->load_manifest(filepath);

    std::string comment = "Opened Manifest " + this->shipDriver->getShip()->get_manifest_name() + ".txt. There are ";
    comment += std::to_string(this->shipDriver->getShip()->num_boxes());
    comment += " containers on the ship.";

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

    this->shipDriver->getShip()->load_manifest(filepath);

    std::string comment = "Opened Manifest " + this->shipDriver->getShip()->get_manifest_name() + ".txt. There are ";
    comment += std::to_string(this->shipDriver->getShip()->num_boxes());
    comment += " containers on the ship.";

    logger->logRawComment(comment);
}


// -------------------------balance - generate ship states----------------------------------------------------------------
void MainWindow::generate_balancing_states_clicked() {

    if (this->shipDriver->getShip()->get_manifest_name().size() == 0) {
        std::cout << "Error: manifest empty."  << std::endl;
        return;
    }

    this->shipDriver->balance_ship(this->GUI_balanced_list);
    this->shipDriver->getShip()->save_ship_states(this->GUI_move_save_states, this->GUI_balanced_list);

    std::reverse(this->GUI_move_save_states.begin()  , this->GUI_move_save_states.end());
    std::reverse(this->GUI_balanced_list.begin()     , this->GUI_balanced_list.end());

//    for (int i = 0; i < manifestShip->balanced_list.size(); i++) {
//        std::cout << manifestShip->balanced_list.at(i).first << ", " << manifestShip->balanced_list.at(i).second << std::endl;
//    }

    if (this->GUI_move_save_states.size() < 2) {

        this->ui->balancing_plain_text->clear();

        std::string balance_info = "Finished balancing Ship! Manifest \n";
        balance_info += this->shipDriver->getShip()->get_manifest_name();
        balance_info += "OUTBOUND.txt was written to desktop. email file.\n";
        balance_info += this->shipDriver->getShip()->print_ship();

        balance_info += "\nbalance factor: ";
        balance_info += std::to_string(this->shipDriver->getShip()->balance_score());
        balance_info += "\n";
        balance_info += this->shipDriver->getShip()->print_ship();
        this->ui->balancing_plain_text->setPlainText(QString::fromStdString(balance_info));

        QString outbound_filepath = QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

        this->shipDriver->getShip()->create_outbound(outbound_filepath.toStdString());

        std::string comment = "Finished a cycle. Manifest " + this->shipDriver->getShip()->get_manifest_name() + "OUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed.";
        logger->logRawComment(comment);
    }
    else {
        this->shipDriver->getShip()->move_num.first = this->shipDriver->getShip()->balanced_list.size()/2;
        this->shipDriver->getShip()->move_num.second = 1;
        std::string move_instru = "Now doing move number ";
        move_instru += std::to_string(this->shipDriver->getShip()->move_num.second);
        move_instru += " of ";
        move_instru += std::to_string(this->shipDriver->getShip()->move_num.first);
        move_instru += ". Move (";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-1).first);
        move_instru += ", ";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-1).second);
        move_instru += ") to (";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-2).first);
        move_instru += ", ";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-2).second);
        move_instru += ")\n";
        this->GUI_balanced_list.pop_back();
        this->GUI_balanced_list.pop_back();
        this->shipDriver->getShip()->move_num.second++;

        this->ui->balancing_next_move_text->setPlainText(QString::fromStdString(move_instru));

        int manifestsize =  this->shipDriver->getShip()->saved_states.size();

        std::string first_move = "Current Ship State\n\n";
        first_move += this->shipDriver->getShip()->saved_states.at(manifestsize-1);
        first_move += "\n------------------------------------------------------------\n\n";
        first_move += "After Moving\n";
        first_move += this->shipDriver->getShip()->saved_states.at(manifestsize-2);

        this->ui->balancing_plain_text->setPlainText(QString::fromStdString(first_move));
        this->shipDriver->getShip()->saved_states.pop_back();
        this->shipDriver->getShip()->saved_states.pop_back();
    }

    //this->ui->balancing_plain_text->clear();
    //this->ui->balancing_plain_text->setPlainText(QString::fromStdString(saved_states.at(1)));
}

void MainWindow::load_next_balance_states_clicked() {

    if (this->shipDriver->getShip()->get_manifest_name().size() == 0) {
        this->ui->balancing_plain_text->setPlainText(QString::fromStdString("Error: Empty Manifest. Try loading manifest again"));
    }

    if (this->shipDriver->getShip()->saved_states.size() < 2) {
        this->ui->balancing_plain_text->clear();

        std::string balance_info = "Finished balancing Ship! Manifest \n";
        balance_info += shipDriver->getShip()->get_manifest_name();
        balance_info += "OUTBOUND.txt was written to desktop. email file.\n";
        balance_info += shipDriver->getShip()->print_ship();

        balance_info += "\nbalance factor: ";
        balance_info += std::to_string(shipDriver->getShip()->balance_score());
        balance_info += "\n";
        balance_info += shipDriver->getShip()->print_ship();
        this->ui->balancing_plain_text->setPlainText(QString::fromStdString(balance_info));

        QString outbound_filepath =
                  QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
        shipDriver->getShip()->create_outbound(outbound_filepath.toStdString());

        std::string comment = "Finished a cycle. Manifest " + shipDriver->getShip()->get_manifest_name() + "OUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed.";

        logger->logRawComment(comment);
    }
    else {
        this->ui->balancing_next_move_text->clear();

        std::string move_instru = "Now doing move number ";
        move_instru += std::to_string(shipDriver->getShip()->move_num.second);
        move_instru += " of ";
        move_instru += std::to_string(shipDriver->getShip()->move_num.first);
        move_instru += ". Move (";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-1).first);
        move_instru += ", ";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-1).second);
        move_instru += ") to (";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-2).first);
        move_instru += ", ";
        move_instru += std::to_string(this->GUI_balanced_list.at(this->GUI_balanced_list.size()-2).second);
        move_instru += ")\n";
        this->shipDriver->getShip()->move_num.second++;

        if (this->GUI_balanced_list.size() >= 2) {
            this->GUI_balanced_list.pop_back();
            this->GUI_balanced_list.pop_back();
        }


        this->ui->balancing_next_move_text->setPlainText(QString::fromStdString(move_instru));

        this->ui->balancing_plain_text->clear();
        int manifestsize =  this->shipDriver->getShip()->saved_states.size();
        std::string next_move = "Current Ship State\n\n";
        next_move += this->shipDriver->getShip()->saved_states.at(manifestsize-1);
        next_move += "\n------------------------------------------------------------\n\n";
        next_move += "After Moving\n";
        next_move += this->shipDriver->getShip()->saved_states.at(manifestsize-2);

        if (this->shipDriver->getShip()->saved_states.size() == 2) {
            next_move += "\n\nFinished! Ship balanced!";
        }

        this->ui->balancing_plain_text->setPlainText(QString::fromStdString(next_move));

        this->shipDriver->getShip()->saved_states.pop_back();
        this->shipDriver->getShip()->saved_states.pop_back();
    }
}

void MainWindow::input_transfer_list_clicked() {
    if (shipDriver->getShip()->get_manifest_name().size() == 0) {
        this->ui->Onload_offload_popup->hide();
        this->ui->onload_offload_textbox->clear();
        this->ui->onload_offload_textbox->setPlainText(QString::fromStdString("Please input manifest first"));
        return;
    }
    else {
        this->ui->unload_name_line->clear();
        this->ui->unload_quantity_line->clear();
        this->ui->load_name_line->clear();
        this->ui->load_mass_line->clear();
        this->ui->Onload_offload_popup->show();
    }

}


void MainWindow::submit_transfer_list_clicked() {

    QString unloadQname = this->ui->unload_name_line->text();
    std::string unloadname = unloadQname.toStdString();
    QString unloadQquantity = this->ui->unload_quantity_line->text();
    std::string unloadquantity= unloadQquantity.toStdString();
    if (unloadname.size() !=0 && unloadquantity.size() != 0) {
        // at max we have 96 containers
        if (unloadquantity.size() <=2) {
            shipDriver->getShip()->unload_names.push_back(unloadname);
            shipDriver->getShip()->unload_quantity.push_back(unloadquantity);
            std::cout << "unload quantity: " << unloadquantity << std::endl;
            std::cout << "unload name: " << unloadname << std::endl;

        }
        else {
            std::cout << "Error: Please check unload input. Quantity is greater than 99" << std::endl;
            this->ui->transfer_description_text_box->clear();
            this->ui->transfer_description_text_box->setPlainText(QString::fromStdString("Error: Please check unload input. Quantity is greater than 99"));
            return;
        }



    }

    QString loadQname = this->ui->load_name_line->text();
    std::string loadname = loadQname.toStdString();
    QString loadQmass = this->ui->load_mass_line->text();
    std::string loadmass= loadQmass.toStdString();
    if (unloadname.size() !=0 && unloadquantity.size() != 0) {
        if (loadmass.size() <= 5) {
            shipDriver->getShip()->load_mass.push_back(loadmass);
            shipDriver->getShip()->load_mass.push_back(loadmass);
            shipDriver->getShip()->load_names.push_back(loadname);
            std::cout << "load mass: " << loadmass << std::endl;
            std::cout << "load name: " <<loadname << std::endl;

        }
        else {
            std::cout << "Error: Please check load input. Mass is greater than 99999" << std::endl;
            this->ui->transfer_description_text_box->clear();
            this->ui->transfer_description_text_box->setPlainText(QString::fromStdString("Error: Please check load input. Mass is greater than 99999"));
            return;


        }

    }

    this->ui->Onload_offload_popup->hide();


}


void MainWindow::add_another_transfer_item_clicked() {
    // save state
    QString unloadQname = this->ui->unload_name_line->text();
    std::string unloadname = unloadQname.toStdString();
    QString unloadQquantity = this->ui->unload_quantity_line->text();
    std::string unloadquantity= unloadQquantity.toStdString();
    if (unloadname.size() !=0 && unloadquantity.size() != 0) {
        if (unloadquantity.size() <=2) {
            shipDriver->getShip()->unload_names.push_back(unloadname);
            shipDriver->getShip()->unload_quantity.push_back(unloadquantity);
            std::cout << "unload quantity: " << unloadquantity << std::endl;
            std::cout << "unload name: " << unloadname << std::endl;
        }
        else {
            std::cout << "Error: Please check unload input. Quantity is greater than 99" << std::endl;
            this->ui->transfer_description_text_box->clear();
            this->ui->transfer_description_text_box->setPlainText(QString::fromStdString("Error: Please check unload input. Quantity is greater than 99"));
            return;
        }

    }

    QString loadQname = this->ui->load_name_line->text();
    std::string loadname = loadQname.toStdString();
    QString loadQmass = this->ui->load_mass_line->text();
    std::string loadmass= loadQmass.toStdString();
    if (unloadname.size() !=0 && unloadquantity.size() != 0) {
        if (loadmass.size() <= 5) {
            shipDriver->getShip()->load_mass.push_back(loadmass);
            shipDriver->getShip()->load_mass.push_back(loadmass);
            shipDriver->getShip()->load_names.push_back(loadname);
            std::cout << "load mass: " << loadmass << std::endl;
            std::cout << "load name: " <<loadname << std::endl;
        }
        else {
            std::cout << "Error: Please check load input. Mass is greater than 99999" << std::endl;
            this->ui->transfer_description_text_box->clear();
            this->ui->transfer_description_text_box->setPlainText(QString::fromStdString("Error: Please check load input. Mass is greater than 99999"));
            return;

        }

    }
    this->ui->unload_name_line->clear();
    this->ui->unload_quantity_line->clear();
    this->ui->load_name_line->clear();
    this->ui->load_mass_line->clear();

    this->ui->Onload_offload_popup->show();

}

void MainWindow::generate_transfer_moves_clicked() {

    if (shipDriver->getShip()->get_manifest_name().size() == 0) {
        std::cout << "Error: manifest empty."  << std::endl;
        return;
    }
    if (shipDriver->getShip()->unload_names.size() == 0 && shipDriver->getShip()->load_names.size() == 0) {
        std::cout << "Error: no moves to calculate" << std::endl;
        return;
    }

    //
    shipDriver->getShip()->create_transfer_list(this->shipDriver->getShip()->transfer_moves);
    shipDriver->getShip()->save_ship_states(this->shipDriver->getShip()->transfer_moves);

    std::reverse(shipDriver->getShip()->transfer_moves.begin(), shipDriver->getShip()->transfer_moves.end());
    std::reverse(shipDriver->getShip()->saved_states.begin(), shipDriver->getShip()->saved_states.end());


    if (shipDriver->getShip()->saved_states.size() < 2) {
        std::string transfer_info = "Finished Unloading and Loading! Manifest \n";
        transfer_info += shipDriver->getShip()->get_manifest_name();
        transfer_info += "OUTBOUND.txt was written to desktop. email file.\n";
        transfer_info += shipDriver->getShip()->print_ship();
        this->ui->onload_offload_textbox->setPlainText(QString::fromStdString(transfer_info));
        this->ui->transfer_update_coords_text->clear();
        this->ui->transfer_update_coords_text->setPlainText(QString::fromStdString("No more moves!"));

        QString outbound_filepath =
                  QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
        shipDriver->getShip()->create_outbound(outbound_filepath.toStdString());
        std::string comment = "Finished a cycle. Manifest " + shipDriver->getShip()->get_manifest_name() + "OUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed.";

        logger->logRawComment(comment);
    }
    else {
        shipDriver->getShip()->move_num.first = shipDriver->getShip()->transfer_moves.size() / 2;
        shipDriver->getShip()->move_num.second = 1;
        std::string move_instru = "Now doing move number ";
        move_instru += std::to_string(shipDriver->getShip()->move_num.second);
        move_instru += " of ";
        move_instru += std::to_string(shipDriver->getShip()->move_num.first);
        move_instru += ". Move (";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-1).first);
        move_instru += ", ";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-1).second);
        move_instru += ") to (";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-2).first);
        move_instru += ", ";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-2).second);
        move_instru += ")\n";
        shipDriver->getShip()->transfer_moves.pop_back();
        shipDriver->getShip()->transfer_moves.pop_back();
        shipDriver->getShip()->move_num.second++;


        this->ui->transfer_update_coords_text->setPlainText(QString::fromStdString(move_instru));


        int manifestsize =  this->shipDriver->getShip()->saved_states.size();

        std::string first_move = "Current Ship State\n\n";
        first_move += this->shipDriver->getShip()->saved_states.at(manifestsize-1);
        first_move += "\n------------------------------------------------------------\n\n";
        first_move += "After Moving\n";
        first_move += this->shipDriver->getShip()->saved_states.at(manifestsize-2);

        this->ui->onload_offload_textbox->setPlainText(QString::fromStdString(first_move));
        this->shipDriver->getShip()->saved_states.pop_back();
        this->shipDriver->getShip()->saved_states.pop_back();
    }

    //this->ui->balancing_plain_text->clear();
    //this->ui->balancing_plain_text->setPlainText(QString::fromStdString(saved_states.at(1)));
}


void MainWindow::next_transfer_moves_clicked() {

    if (shipDriver->getShip()->get_manifest_name().size() == 0) {
        std::cout << "Error: manifest empty."  << std::endl;
        return;
    }

    if (shipDriver->getShip()->saved_states.size() < 2) {
        std::string transfer_info = "Finished Unloading and Loading! Manifest \n";
        transfer_info += shipDriver->getShip()->get_manifest_name();
        transfer_info += "OUTBOUND.txt was written to desktop. email file.\n";
        transfer_info += shipDriver->getShip()->print_ship();
        this->ui->onload_offload_textbox->setPlainText(QString::fromStdString(transfer_info));
        this->ui->transfer_update_coords_text->clear();
        this->ui->transfer_update_coords_text->setPlainText(QString::fromStdString("No more moves!"));

        QString outbound_filepath =
                  QString("%1/").arg(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
        shipDriver->getShip()->create_outbound(outbound_filepath.toStdString());
        std::string comment = "Finished a cycle. Manifest " + shipDriver->getShip()->get_manifest_name() + "OUTBOUND.txt was written to desktop, and a reminder pop-up to operator to send file was displayed.";

        logger->logRawComment(comment);
    }
    else {

        std::string move_instru = "Now doing move number ";
        move_instru += std::to_string(shipDriver->getShip()->move_num.second);
        move_instru += " of ";
        move_instru += std::to_string(shipDriver->getShip()->move_num.first); //size
        move_instru += ". Move (";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-1).first);
        move_instru += ", ";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-1).second);
        move_instru += ") to (";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-2).first);
        move_instru += ", ";
        move_instru += std::to_string(shipDriver->getShip()->transfer_moves.at(this->shipDriver->getShip()->transfer_moves.size()-2).second);
        move_instru += ")\n";
        shipDriver->getShip()->transfer_moves.pop_back();
        shipDriver->getShip()->transfer_moves.pop_back();
        shipDriver->getShip()->move_num.second++;


        this->ui->transfer_update_coords_text->setPlainText(QString::fromStdString(move_instru));


        int manifestsize =  this->shipDriver->getShip()->saved_states.size();

        std::string first_move = "Current Ship State\n\n";
        first_move += this->shipDriver->getShip()->saved_states.at(manifestsize-1);
        first_move += "\n------------------------------------------------------------\n\n";
        first_move += "After Moving\n";
        first_move += this->shipDriver->getShip()->saved_states.at(manifestsize-2);

        this->ui->onload_offload_textbox->setPlainText(QString::fromStdString(first_move));
        this->shipDriver->getShip()->saved_states.pop_back();
        this->shipDriver->getShip()->saved_states.pop_back();
    }

    //this->ui->balancing_plain_text->clear();
    //this->ui->balancing_plain_text->setPlainText(QString::fromStdString(saved_states.at(1)));
}




