#include "../headers/Logger.h"

// constructors
Logger::Logger() {
    this->logString = "";
    this->myMainWindow = nullptr;
    this->createLogfileDirAndFile();
}

Logger::Logger(MainWindow* myMainWindow) {
    this->logString = "";
    this->myMainWindow = myMainWindow;
    this->createLogfileDirAndFile();
}

Logger::Logger(std::string str, MainWindow* myMainWindow) {
    this->logString = str;
    this->myMainWindow = myMainWindow;
    this->createLogfileDirAndFile();
}

void Logger::logLogin(std::string uname) const {

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

    int _fileOpened = _file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );

    // Error checking
    if (!_fileOpened) {
        std::cout << "Error opening file: \"" << filepath << "\"" << std::endl;
        return;
    }

    QTextStream fout(&_file);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDate currDate = currentDateTime.date();
    QTime currTime = currentDateTime.time();
    QTimeZone currTZ = currentDateTime.timeZone();

    // output correct time, date, and user.
    if (currentDateTime.isDaylightTime()) {
        fout << "[" << currTZ.id() << " (DST)] ";
    }
    else {
        fout << "[" << currTZ.id() << "] ";
    }
    fout << currDate.month() << "/" << currDate.day() << "/" << currDate.year();
    fout << " (" << currTime.hour() << ":" << currTime.minute() << ":" << currTime.second() << ") - ";
    fout << "User " << QString::fromStdString(uname) << " logged in.\n";
    
    _file.close();
    return;
}

void Logger::logComment() const {
    if (this->logString == "" || this->logString.at(0) == ' ') {
        // Do nothing, don't want to log comment 
        // unless it follows proper structure
        std::cout << "Error: invalid comment, shouldn't even be called right now." << std::endl;
        return;
    }

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

    int _fileOpened = _file.open( QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append );

    // Error checking
    if (!_fileOpened) {
        std::cout << "Error opening file: \"" << filepath << "\"" << std::endl;
        return;
    }

    QTextStream fout(&_file);

    QDateTime currentDateTime = QDateTime::currentDateTime();
    QDate currDate = currentDateTime.date();
    QTime currTime = currentDateTime.time();
    QTimeZone currTZ = currentDateTime.timeZone();

    // output correct time, date, and user.
    if (currentDateTime.isDaylightTime()) {
        fout << "[" << currTZ.id() << " (DST)] ";
    }
    else {
        fout << "[" << currTZ.id() << "] ";
    }

    fout << currDate.month() << "/" << currDate.day() << "/" << currDate.year();
    fout << " (" << currTime.hour() << ":" << currTime.minute() << ":" << currTime.second() << ")";
    fout << " - " << QString::fromStdString(this->logString) << "\n";
    
    _file.close();
    return;
}

void Logger::createLogfileDirAndFile() const {
    return;
}