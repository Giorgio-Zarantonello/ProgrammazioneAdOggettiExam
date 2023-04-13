#ifndef AZIENDALE_H
#define AZIENDALE_H

#include "veicolo.h"
enum tipoCliente {liberoProfessionista = 0, azienda = 1, pubblicaAmministrazione = 2};


class Aziendale : public Veicolo
{
private :
    std::string nomeClienteNoleggio ;
    tipoCliente tC ;
    static double tariffaGiornaliera;

public:
    Aziendale();
    Aziendale(std::string, bool , unsigned int, unsigned int , std::string, tipoCliente);
    virtual ~Aziendale() = default;

    //Getters
    std::string getNomeClienteNoleggio() const ;
    unsigned int getCodCli() const;
    tipoCliente getTipoClienteAziendale() const;
    virtual double GetImportoNoleggio() const ;

    //Setters
    void setNomeClienteNoleggio(std::string);
    void setCodCliente(unsigned int);
    void setTipoCliente(tipoCliente);

    //Json

    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;

};

#endif // AZIENDALE_H
