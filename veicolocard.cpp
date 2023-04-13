#include "veicolocard.h"

VeicoloCard::VeicoloCard(short int i, type t, QWidget *parent) : QPushButton(parent), indice(i) , t(t) {}
short int VeicoloCard::getIndice()
{
    return indice;
}

type VeicoloCard::getTipo()
{
    return t;
}
