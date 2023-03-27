#ifndef __POPUP_H__
#define __POPUP_H__

#include <string>
#include <QtWidgets>

class Popup : public QWidget {
    Q_OBJECT

    private:
        std::string message;

    public:
        Popup(QWidget* parent = nullptr, int = 0, int = 0, int = 0, int = 0);
        ~Popup() {}

        void setMessage(const std::string&);
};

#endif
