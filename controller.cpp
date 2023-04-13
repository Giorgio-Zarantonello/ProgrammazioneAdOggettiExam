#include "controller.h"
#include <iostream>

Controller::Controller(Modello * m, QObject * parent)
    : QObject(parent), view(nullptr), model(m)
{
    model->popolaVettore();
}

void Controller::setView(Vista * v)
{
    view = v;
}
unsigned int Controller::getSize() const
{
    return model->getSize();
}

unsigned short Controller::getAnnoImmatricolazione(unsigned short i) const
{
    Veicolo * v = model->getVeicolo(i);

    return v->getAnnoImmatricolazione();
}

bool Controller::getStatoNoleggio(unsigned short i) const
{
    Veicolo * v = model->getVeicolo(i);
    return v->getStatoNoleggio();
}


QString Controller::getNomeVeicolo(unsigned short i) const
{
    Veicolo * v = model->getVeicolo(i);
    return QString::fromStdString(v->getNome());
}
unsigned int Controller::getGiorniNoleggio(unsigned short i) const
{
    Veicolo * v = model->getVeicolo(i);

    return v->getGiorniNoleggio();

}


tipoCliente Controller::getTipoAziendale(unsigned short i) const
{
    Aziendale* a = dynamic_cast <Aziendale*>(model->getVeicolo(i));
    return a->getTipoClienteAziendale();

}



QString Controller::getNomeIntestatario(unsigned short i) const {
    Civile* c = dynamic_cast <Civile *>(model->getVeicolo(i));
    return QString::fromStdString(c->getNomeIntestatario());

}
QString Controller::getNomeClienteNoleggio(unsigned short i) const {
    Aziendale* a = dynamic_cast <Aziendale*>(model->getVeicolo(i));
    return QString::fromStdString(a->getNomeClienteNoleggio());

}


type Controller::getTipoCliente(unsigned short i ) const
{
    type t ;

    if (dynamic_cast<Civile*>(model->getVeicolo(i))){
        t = civile;

    }
    if (dynamic_cast<Aziendale *>(model->getVeicolo(i))){
        t = aziendale ;
    }
    return t ;
}

void Controller::nuovoCivile(std::string a,bool b,unsigned int c, unsigned int s, std::string d)
{

    model->insertCivile(a, b, c, s , d);
}

void Controller::nuovoAziendale(std::string a,bool b,unsigned int c, unsigned int s, std::string d, tipoCliente tp)
{

    model->insertAziendale(a, b, c, s , d,tp);
}
void Controller::cancellaVeicolo(unsigned short i)
{
    model->togliVeicolo(i);
}

void Controller::modificaCivile(QString a ,bool b ,  unsigned int c ,unsigned int d , QString e,short int f ) {

    model->modifyCivile(a.toStdString(),b,c,d,e.toStdString(),f);
}
void Controller::modificaAziendale(QString a ,bool b ,  unsigned int c ,unsigned int d , QString e,tipoCliente tp ,short int f ) {

    model->modifyAziendale(a.toStdString(),b,c,d,e.toStdString(),tp,f);
}

unsigned int Controller::c_countVeicolo(unsigned int i)
{
    return model->countVeicolo(i);
}

unsigned int Controller::c_countNoleggioVeicolo(unsigned int i , bool s)
{
    return model->countNoleggio(i,s);
}
unsigned int Controller::c_calcolaRicavoAnnoImm(unsigned int i)
{
    return model->calcolaRicavo(i);
}

void Controller::h_saveFile(Modello::SaveFormat Json,QString s)
{

    model->saveFile(Json,s);
}

void Controller::h_loadFile(Modello::SaveFormat Json , QString s)
{
    model->loadFile(Json,s);
}
