#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "./MainWindow.h"

#include <QApplication>
#include <QFile>
#include <QDir>
#include <windows.h>

#include <iostream>
#include <string.h>
#include <fstream>
#include <filesystem>

#include <sys/stat.h>

class Logger {

    private:
        std::string logString;
        MainWindow* myMainWindow;

    public:
        Logger();
        Logger(MainWindow*);
        Logger(std::string, MainWindow*);

        // setters
        void setString(std::string logString) { this->logString = logString; };

        // getters
        std::string getString() const { return this->logString; }

        void logLogin(std::string) const;
        void logComment() const;
        void logRawComment(std::string);

    private:
        void createLogfileDirAndFile() const;
};

#endif // LOGGER.H
