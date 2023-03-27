#include "../headers/Popup.h"

void Popup::setMessage(const std::string& s) {
    this->message = s;
}

Popup::Popup(QWidget* parent, int x, int y, int w, int h)
: QWidget(parent) {
    this->setGeometry(x, y, w, h);
}
