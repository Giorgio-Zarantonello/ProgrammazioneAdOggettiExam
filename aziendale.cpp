#include "aziendale.h"

Aziendale::Aziendale()
{

}

Aziendale::Aziendale(std::string n,bool i , unsigned int k, unsigned int a , std::string b, tipoCliente d)
    : Veicolo(n,i,k,a), nomeClienteNoleggio(b),tC(d){}

double Aziendale :: tariffaGiornaliera = 29.99;


tipoCliente Aziendale:: getTipoClienteAziendale() const { return tC;}

void Aziendale::setNomeClienteNoleggio(std::string n){
    nomeClienteNoleggio = n ;
}



void  Aziendale::setTipoCliente(tipoCliente tc) {tC = tc;}

void Aziendale::read(const QJsonObject &json)
{
    Veicolo::read(json);
    if (json.contains("nomeClienteNoleggio") && json["nomeClienteNoleggio"].isString())
           nomeClienteNoleggio = json["nomeClienteNoleggio"].toString().toStdString();

       if (json.contains("tipoCliente") && json["tipoCliente"].isDouble())
           switch (json["tipoCliente"].toInt()) {
           case 0:
               tC = liberoProfessionista;

               break;
           case 1:
               tC = azienda;

               break;
           case 2:
               tC = pubblicaAmministrazione;

               break;
           default:
               break;
           }


       if (json.contains("tariffaGiornaliera") && json["tariffaGiornaliera"].isDouble())
           tariffaGiornaliera = json["tariffaGiornaliera"].toInt();
}

void Aziendale::write(QJsonObject &json) const
{
    Veicolo::write(json);

    json["nomeClienteNoleggio"] = QString::fromStdString(nomeClienteNoleggio);

    json["tipoCliente"] = (int) tC;

    json["tariffaGiornaliera"] = (double) tariffaGiornaliera;



}

double Aziendale :: GetImportoNoleggio() const {
    return tariffaGiornaliera * Veicolo::getGiorniNoleggio();
}

std::string Aziendale:: getNomeClienteNoleggio() const {
    return nomeClienteNoleggio;
}
