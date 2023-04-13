#ifndef VEICOLO_H
#define VEICOLO_H

#include <string>
#include <QJsonObject>


class Veicolo
{

private:
    std::string nome;
    bool statoNoleggio;
    unsigned int annoImmatricolazione;
    unsigned int giorniNoleggio;

public:
    Veicolo();
    Veicolo(std::string,bool, unsigned int, unsigned int);
    virtual ~Veicolo() = default;

    //Setters
    void setNome(std::string);
    void setStatoNoleggio(bool);
    void setGiorniNoleggio(unsigned int);
    void setAnnoImmatricolazione(unsigned int);


    //Getters
    std::string getNome() const;
    bool getStatoNoleggio() const ;
    unsigned int getGiorniNoleggio() const;
    unsigned short getAnnoImmatricolazione() const;
    virtual double GetImportoNoleggio() const = 0 ;



    //Json
    virtual void read(const QJsonObject &json);
    virtual void write(QJsonObject &json) const;


};

#endif // VEICOLO_H
