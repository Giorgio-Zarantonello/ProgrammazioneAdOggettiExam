#include "modello.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QTextStream>

#include <iostream>





Modello::Modello() : vett(0U) {}

unsigned int Modello::getSize() const
{
    return vett.size();

}
Veicolo * Modello::getVeicolo(unsigned int i) const
{
    return vett[i];
}


void Modello::popolaVettore()
{
    Veicolo* p1 = new Civile("alfa romeo 156", true, 2001, 30, "Paolo Bitta");
    Veicolo* p2 = new Aziendale("ford escort", false , 2020 , 25, "edile srl",  liberoProfessionista);
    Veicolo* p3 = new Civile("volkswagen Golf", false, 2012 , 15, "Andrea Rossi");
    Veicolo* p4 = new Civile("alfa romeo 156", true, 2010, 17, "Paolo Bitta");
    Veicolo* p5 = new Aziendale("ford ka", true , 2020, 12 , "edile srl", azienda);
    Veicolo* p6 = new Civile("volkswagen Golf", true, 2018, 40, "Andrea Rossi");
    Veicolo* p7 = new Aziendale("ford escort", false , 2020 , 25, "edile srl",  liberoProfessionista);
    Veicolo* p8 = new Civile("volkswagen Golf", false, 2012 , 15, "Andrea Rossi");
    Veicolo* p9 = new Civile("alfa romeo 156", true, 2010, 17, "Paolo Bitta");
    Veicolo* p10= new Aziendale("ford ka", true , 2020, 12 , "edile srl", pubblicaAmministrazione);
    Veicolo* p11= new Civile("volkswagen Golf", true, 2018, 40, "Andrea Rossi");
    vett.push_back(p1);
    vett.push_back(p2);
    vett.push_back(p3);
    vett.push_back(p4);
    vett.push_back(p5);
    vett.push_back(p6);
    vett.push_back(p7);
    vett.push_back(p8);
    vett.push_back(p9);
    vett.push_back(p10);
    vett.push_back(p11);

}

void Modello::resetVett()
{

    std::vector<Veicolo *> temp(0U);
    vett = temp;
}
void Modello::togliVeicolo(unsigned short i)
{
    std::vector<Veicolo *>::iterator it = vett.begin();
    for (unsigned int j=0; j<i; j++) {
        ++it;
    }
    vett.erase(it);
}

void Modello::insertCivile(std::string a,bool b,unsigned int c, unsigned int s, std::string d)
{
    Civile * civile = new Civile(a, b, c, s, d);
    vett.push_back(civile);
}

void Modello::insertAziendale(std::string n,bool e, unsigned int p,unsigned int k, std::string s,  tipoCliente z)
{
    Aziendale * aziendale = new Aziendale(n, e, p, k, s,z);
    vett.push_back(aziendale);
}

void Modello::modifyCivile(std::string n,bool e, unsigned int p,unsigned int k, std::string o,unsigned int i){

    Civile * v = dynamic_cast<Civile*>(getVeicolo(i));
    v->setNome(n);
    v->setStatoNoleggio(e);
    v->setGiorniNoleggio(k);
    v->setAnnoImmatricolazione(p);
    v->setNomeIntestatario(o);
}

void Modello::modifyAziendale(std::string n,bool e, unsigned int p,unsigned int k, std::string o,tipoCliente tc,unsigned int i){
    Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
    v->setNome(n);
    v->setStatoNoleggio(e);
    v->setAnnoImmatricolazione(p);
    v->setGiorniNoleggio(k);
    v->setNomeClienteNoleggio(o);
    v->setTipoCliente(tc);
}

unsigned int Modello::countVeicolo(unsigned int j)
{
    unsigned int count = 0 ;
    switch (j) {
    case 1:
        for (unsigned int i = 0 ; i < getSize() ; i++ ){
            Civile * v = dynamic_cast<Civile*>(getVeicolo(i));
            if (v){
                count++;
            }}
        return count;
    case 2:
        for (unsigned int i = 0 ; i < getSize() ; i++ ){
            Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
            if (v){
                if (v->getTipoClienteAziendale() == liberoProfessionista)
                    count++;
            }
        }

        return count;

    case 3:
        for (unsigned int i = 0 ; i < getSize() ; i++ ){
            Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
            if (v){
                Aziendale* k = static_cast<Aziendale*>(v);
                if (k->getTipoClienteAziendale() == azienda)
                    count++;
            }
        }

        return count;
        break;
    case 4:
        for (unsigned int i = 0 ; i < getSize() ; i++ ){
            Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
            if (v){
                Aziendale* k = static_cast<Aziendale*>(v);
                if (k->getTipoClienteAziendale() == pubblicaAmministrazione)
                    count++;
            }
        }

        return count;
        break;
    default:
        break;
    }
}

unsigned int Modello::countNoleggio (unsigned int j,bool s){
    unsigned int count = 0 ;
    switch (s) {
    case true:
        switch (j) {
        case 1:
            for (unsigned int i = 0 ; i < getSize() ; i++ ){
                Civile * v = dynamic_cast<Civile*>(getVeicolo(i));
                if (v)
                    if (v->getStatoNoleggio() == true){
                        count++;
                    }}
            return count;
        case 2:
            for (unsigned int i = 0 ; i < getSize() ; i++ ){
                Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
                if (v){
                    if (v->getTipoClienteAziendale() == liberoProfessionista && v->getStatoNoleggio() == true)
                        count++;
                }
            }

            return count;

        case 3:
            for (unsigned int i = 0 ; i < getSize() ; i++ ){
                Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
                if (v){
                    Aziendale* k = static_cast<Aziendale*>(v);
                    if (k->getTipoClienteAziendale() == azienda && v->getStatoNoleggio() == true)
                        count++;
                }
            }

            return count;
            break;
        case 4:
            for (unsigned int i = 0 ; i < getSize() ; i++ ){
                Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
                if (v){
                    Aziendale* k = static_cast<Aziendale*>(v);
                    if (k->getTipoClienteAziendale() == pubblicaAmministrazione && v->getStatoNoleggio() == true)
                        count++;
                }
            }

            return count;
            break;
        default:
            break;
        }
        break;
    case false:
        switch (j) {
        case 1:
            for (unsigned int i = 0 ; i < getSize() ; i++ ){
                Civile * v = dynamic_cast<Civile*>(getVeicolo(i));
                if (v)
                    if (v->getStatoNoleggio() == false){
                        count++;
                    }}
            return count;
        case 2:
            for (unsigned int i = 0 ; i < getSize() ; i++ ){
                Aziendale * v = dynamic_cast<Aziendale*>(getVeicolo(i));
                if (v){
                    if (v->getStatoNoleggio() == false)
                        count++;
                }
            }

            return count;
        }

        return count;

    default:
        break;
    }
}

unsigned int Modello::calcolaRicavo(unsigned int a)
{
    unsigned int sum = 0 ;
    for (unsigned int i = 0 ; i < getSize() ; i++ ){
        Veicolo* v = getVeicolo(i);
        if(v->getAnnoImmatricolazione() == a && v->getStatoNoleggio() == true ) sum += v->GetImportoNoleggio();
    }
    return sum;
}



void Modello::read(const QJsonObject &json)
{
    if (json.contains("vett") && json["vett"].isArray()) {
        QJsonArray vettArray = json["vett"].toArray();
        vett.clear();
        for (int vettIndex = 0; vettIndex < vettArray.size(); ++vettIndex) {
            QJsonObject vettObject = vettArray[vettIndex].toObject();
            Veicolo* v;
            if(!vettObject.contains("tipoCliente")) v = new Civile();

            else v = new Aziendale();
            v->read(vettObject);
            vett.push_back(v);
        }
    }
}

void Modello::write(QJsonObject &json) const
{
    QJsonArray vettArray;
    for (const Veicolo *v: vett) {
        QJsonObject vettObject;
        v->write(vettObject);
        vettArray.push_back(vettObject);
    }
    json["vett"] = vettArray;
}


void Modello::loadFile(Modello::SaveFormat saveFormat,QString s)
{

    QFile loadFile(s);

    loadFile.open(QIODevice::ReadOnly);

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());
    loadFile.close();

}

void Modello::saveFile(Modello::SaveFormat saveFormat,QString s) const
{   

    QFile saveFile(s) ;

    saveFile.open(QIODevice::WriteOnly);

    QJsonObject gameObject;

    write(gameObject);

    saveFile.write(QJsonDocument(gameObject).toJson());

    saveFile.close();

}


