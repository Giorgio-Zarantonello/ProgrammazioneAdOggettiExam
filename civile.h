#ifndef CIVILE_H
#define CIVILE_H

#include "veicolo.h"
#include <string>

class Civile : public Veicolo
{
private :
    std::string nomeIntestatario;
    static double tariffaGiornaliera;


public:
    Civile();
    Civile(std::string,bool,  unsigned int, unsigned int , std::string);
    virtual ~Civile() ;

    //Getters
    virtual std::string getNomeIntestatario() const ;

    unsigned int getGiorniNoleggio() const;

    virtual double GetImportoNoleggio() const ;


    //Setters
    void setNomeIntestatario(std::string);

    //Json
    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;


};

#endif // CIVILE_H
