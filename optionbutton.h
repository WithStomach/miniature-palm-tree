#ifndef OPTIONBUTTON_H
#define OPTIONBUTTON_H

#include <QPushButton>

class OptionButton : public QPushButton
{
    Q_OBJECT

public:
    OptionButton(int width, int height, QString optionName);

    QString option;

};

#endif // OPTIONBUTTON_H
