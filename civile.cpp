#include "civile.h"

Civile::Civile()
{

}

Civile::Civile(std::string a,bool b,unsigned int c, unsigned int s, std::string d)
    : Veicolo(a,b,c,s) , nomeIntestatario(d) {}

Civile :: ~Civile(){}

double Civile::tariffaGiornaliera = 15;

 std::string Civile :: getNomeIntestatario() const {return nomeIntestatario;}


void Civile :: setNomeIntestatario(std::string s){
    nomeIntestatario = s;
}

void Civile::read(const QJsonObject &json)
{
    Veicolo::read(json);

    if (json.contains("nomeIntestatario") && json["nomeIntestatario"].isString())
           nomeIntestatario = json["nomeIntestatario"].toString().toStdString();

       if (json.contains("tariffaGiornaliera") && json["tariffaGiornaliera"].isDouble())
           tariffaGiornaliera = json["tariffaGiornaliera"].toDouble();
}

void Civile::write(QJsonObject &json) const
{
    Veicolo::write(json);

    json["nomeIntestatario"] = QString::fromStdString(nomeIntestatario);

    json["tariffaGiornaliera"] = (double) tariffaGiornaliera;

}


double Civile :: GetImportoNoleggio() const {
    return tariffaGiornaliera* Veicolo::getGiorniNoleggio();
}
