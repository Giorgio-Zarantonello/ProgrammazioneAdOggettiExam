#ifndef VEICOLOCARD_H
#define VEICOLOCARD_H

#include "type.h"
#include <QPushButton>

class VeicoloCard : public QPushButton
{
    Q_OBJECT

public:
    VeicoloCard(short int , type, QWidget *parent = nullptr);

    short int getIndice();
    type getTipo();

private:
    short int indice;
    type t;
};

#endif // VEICOLOCARD_H
