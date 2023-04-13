#ifndef DIALOG_H
#define DIALOG_H

#include "type.h"
#include "veicolocard.h"


#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QRadioButton>
#include <QSpinBox>
#include <QComboBox>


class Controller;
class Vista;

class Dialog : public QDialog
{
    Q_OBJECT

    friend Vista;


private slots :
    void creaCivile();
    void creaAziendale();
    void modificaCivile();
    void modificaAziendale();

private :
    Controller* controller;
    Vista* vista;
    short int indiceVeicolo;

    QFormLayout * layout;

    QLineEdit * modelloVeicolo;
    QSpinBox* giorniNoleggio;
    QLineEdit* nomeIntestatario;
    QSpinBox * annoImmVeicolo;
    QSpinBox * codiceCliente;
    QLineEdit * m_tipoCliente;

    VeicoloCard * nuovoV;

    QRadioButton * boolNoleggioY;
    QRadioButton * boolNoleggioN;
    QRadioButton * tALP;
    QRadioButton * tAA;
    QRadioButton * tAPA;


public:
    Dialog(Controller *, Vista *, type, short int, QWidget * parent = nullptr);

};

#endif // DIALOG_H
