#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>

#include "vista.h"
#include "modello.h"
#include "type.h"


class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(Modello *, QObject * parent = nullptr);

    void setView(Vista * v);

    unsigned int getSize() const;

    QString getNomeVeicolo(unsigned short) const;
    unsigned short getAnnoImmatricolazione(unsigned short)const;
    bool getStatoNoleggio(unsigned short) const;
    unsigned int getGiorniNoleggio(unsigned short) const;
    QString getNomeIntestatario(unsigned short) const;
    QString getNomeClienteNoleggio(unsigned short) const;
    unsigned int getCodiceCliente(unsigned short) const ;
    tipoCliente getTipoAziendale(unsigned short) const;

    type getTipoCliente(unsigned short) const;

    void nuovoCivile(std::string,bool,  unsigned int,unsigned int, std::string);
    void nuovoAziendale(std::string,bool,  unsigned int,unsigned int, std::string, tipoCliente);
    void cancellaVeicolo(unsigned short);
    void modificaCivile(QString,bool,  unsigned int,unsigned int, QString, short int );
    void modificaAziendale(QString,bool,  unsigned int,unsigned int, QString, tipoCliente, short int );

    unsigned int c_countVeicolo (unsigned int);
    unsigned int c_countNoleggioVeicolo (unsigned int,bool);
    unsigned int c_calcolaRicavoAnnoImm(unsigned int);

    void h_saveFile(Modello::SaveFormat,QString);
    void h_loadFile(Modello::SaveFormat,QString);

private:
    Vista * view;
    Modello * model;
};

#endif // CONTROLLER_H
