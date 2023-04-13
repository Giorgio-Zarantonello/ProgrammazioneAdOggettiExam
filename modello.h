#ifndef MODELLO_H
#define MODELLO_H

#include<vector>
#include "veicolo.h"
#include "aziendale.h"
#include "civile.h"

class Modello
{
private:

    std::vector<Veicolo *> vett;

public:
    enum SaveFormat {
           Json
       };

    Modello();
    unsigned int getSize() const;
    unsigned int getAnnoImmatricolazione() const;

    bool getStatoNoleggio() const;

    Veicolo* getVeicolo(unsigned int) const;
    Civile*  getCivile(unsigned int) const;

    void popolaVettore();

    void resetVett();
    void togliVeicolo(unsigned short);
    void insertCivile(std::string ,bool , unsigned int ,unsigned int , std::string );
    void insertAziendale(std::string ,bool, unsigned int , unsigned int , std::string ,tipoCliente );
    void modifyCivile(std::string ,bool , unsigned int ,unsigned int , std::string,unsigned int);
    void modifyAziendale(std::string ,bool, unsigned int , unsigned int , std::string ,tipoCliente,unsigned int);



    unsigned int countVeicolo(unsigned int);
    unsigned int countNoleggio(unsigned int,bool);
    unsigned int calcolaRicavo(unsigned int);


    void loadFile(SaveFormat saveFormat,QString s);
    void saveFile(SaveFormat saveFormat,QString s) const ;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

};
#endif // MODELLO_H
