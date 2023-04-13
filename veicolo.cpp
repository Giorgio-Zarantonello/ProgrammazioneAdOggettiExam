#include "veicolo.h"

Veicolo::Veicolo()
{

}

Veicolo::Veicolo(std::string n,bool b , unsigned int i, unsigned int k) : nome(n),statoNoleggio(b), annoImmatricolazione(i), giorniNoleggio(k) {}



std::string Veicolo::getNome() const
{
    return nome;
}

unsigned int Veicolo::getGiorniNoleggio() const
{
    return giorniNoleggio;
}
unsigned short Veicolo::getAnnoImmatricolazione() const
{
    return annoImmatricolazione;
}

void Veicolo::read(const QJsonObject &json)
{
    if (json.contains("nome") && json["nome"].isString())
           nome = json["nome"].toString().toStdString();

       if (json.contains("statoNoleggio") && json["statoNoleggio"].isBool())
           statoNoleggio = json["statoNoleggio"].toBool();

       if (json.contains("annoImmatricolazione") && json["annoImmatricolazione"].isDouble())
           annoImmatricolazione = json["annoImmatricolazione"].toInt();

       if (json.contains("giorniNoleggio") && json["giorniNoleggio"].isDouble())
           giorniNoleggio = json["giorniNoleggio"].toInt();
}

void Veicolo::write(QJsonObject &json) const
{

    json["nome"] = QString::fromStdString(nome);
    json["statoNoleggio"] = (bool) statoNoleggio;
    json["annoImmatricolazione"] = (int) annoImmatricolazione;
    json["giorniNoleggio"] = (int) giorniNoleggio;

}


bool Veicolo::getStatoNoleggio() const { return statoNoleggio ; }

void Veicolo::setNome(std::string n)
{
    nome = n;
}

void Veicolo::setStatoNoleggio(bool b){ statoNoleggio=b;}

void Veicolo::setGiorniNoleggio(unsigned int a){ giorniNoleggio=a;}
void Veicolo::setAnnoImmatricolazione(unsigned int a){ annoImmatricolazione=a;}

