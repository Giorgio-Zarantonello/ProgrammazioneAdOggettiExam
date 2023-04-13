#include "dialog.h"
#include "controller.h"
#include "aziendale.h"



Dialog::Dialog(Controller * c, Vista * v, type t, short int i, QWidget * parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint), controller(c), vista(v), indiceVeicolo(i)
{
    layout = new QFormLayout();
    modelloVeicolo = new QLineEdit("");
    layout->addRow("Modello Veicolo:", modelloVeicolo);

    QGroupBox * noleggioAttivo = new QGroupBox();
    boolNoleggioY = new QRadioButton((tr("&Si")));
    boolNoleggioN = new QRadioButton((tr("&No")));
    boolNoleggioY->setChecked(true);
    QHBoxLayout *box = new QHBoxLayout;
    box->addWidget(boolNoleggioY);
    box->addWidget(boolNoleggioN);
    noleggioAttivo->setLayout(box);
    layout->addRow("Stato Noleggio:", noleggioAttivo);
    annoImmVeicolo = new QSpinBox();
    annoImmVeicolo->setRange(2000,2022);
    layout->addRow("Anno Immatricolazione Veicolo:", annoImmVeicolo);
    giorniNoleggio = new QSpinBox();
    giorniNoleggio->setRange(0,100);
    layout->addRow("Giorni Noleggio Veicolo:", giorniNoleggio);
    if (t == civile)
    {
        setWindowTitle(tr("Nuovo Noleggio Veicolo Civile"));
        nomeIntestatario = new QLineEdit("");
        layout->addRow("Nome Intestatario:", nomeIntestatario);
        if (indiceVeicolo == -1) {
            nuovoV = new VeicoloCard(-1 , t);
            nuovoV->setText("Crea Veicolo");
            layout->addRow(nuovoV);
            connect(nuovoV, SIGNAL(clicked()), this, SLOT(creaCivile()));
        }
        else {
            nuovoV = new VeicoloCard(indiceVeicolo, t);
            layout->addRow(nuovoV);
            nuovoV->setText("Modifica Veicolo Civile");

            connect(nuovoV, SIGNAL(clicked()), this, SLOT(modificaCivile()));
        }
        setLayout(layout);
    }
    if (t == aziendale)
    {

        setWindowTitle(tr("Nuovo Noleggio Veicolo Aziendale"));
        nomeIntestatario = new QLineEdit("");
        layout->addRow("Nome Intestatario:", nomeIntestatario);
        QGroupBox * tipoAziendale = new QGroupBox();
        tALP= new QRadioButton((tr("&Libero Professionista")));
        tAA= new QRadioButton((tr("&Azienda")));
        tAPA= new QRadioButton((tr("&Pubblica Amministrazione")));

        QHBoxLayout *boxtA = new QHBoxLayout;
        boxtA->addWidget(tALP);
        boxtA->addWidget(tAA);
        boxtA->addWidget(tAPA);


        tipoAziendale->setLayout(boxtA);
        layout->addRow("Tipologia Cliente Aziendale:", tipoAziendale);


        if (indiceVeicolo == -1) {

            nuovoV = new VeicoloCard(-1 , t);
            nuovoV->setText("Crea Veicolo");
            layout->addRow(nuovoV);
            connect(nuovoV, SIGNAL(clicked()), this, SLOT(creaAziendale()));
        }
        else {
            nuovoV = new VeicoloCard(indiceVeicolo, t);
            layout->addRow(nuovoV);
            nuovoV->setText("Modifica Veicolo Aziendale");

            connect(nuovoV, SIGNAL(clicked()), this, SLOT(modificaAziendale()));
        }
        setLayout(layout);
    }

}

void Dialog::creaCivile()
{
    //nome
    std::string modelName = modelloVeicolo->text().toStdString();
    //stato noleggio
    bool checkNoleggio = boolNoleggioN->isChecked() ? false : true ;
    //anno Immatricolazione
    unsigned int aI = annoImmVeicolo->value();
    //giorni noleggio
    unsigned int giorniNoleggioCopy = giorniNoleggio->text().toInt();
    //nomeIntestatario
    std::string nomeIntestatarioCopy= nomeIntestatario->text().toStdString();
    controller->nuovoCivile(modelName,checkNoleggio, aI,giorniNoleggioCopy,nomeIntestatarioCopy);
    vista->aggiornaApp();
    emit close();
}
void Dialog::creaAziendale()
{
    //nome
    std::string modelName = modelloVeicolo->text().toStdString();
    //stato noleggio
    bool checkNoleggio = boolNoleggioN->isChecked() ? false : true ;
    //anno Immatricolazione
    unsigned int aI = annoImmVeicolo->value();
    //giorni noleggio
    unsigned int giorniNoleggioCopy = giorniNoleggio->text().toInt();
    //nomeIntestatario
    std::string nomeIntestatarioCopy= nomeIntestatario->text().toStdString();
    //tipoAzienda
    tipoCliente tP;
    if(tALP->isChecked()) tP = liberoProfessionista;
    if(tAA->isChecked()) tP = azienda;
    if(tAPA->isChecked()) tP = pubblicaAmministrazione;


    controller->nuovoAziendale(modelName,checkNoleggio, aI,giorniNoleggioCopy,nomeIntestatarioCopy,tP);
    vista->aggiornaApp();
    emit close();
}


void Dialog::modificaCivile()
{
    VeicoloCard* veicolo = qobject_cast<VeicoloCard *>(sender());
    short int i = veicolo->getIndice();

    QString nome = modelloVeicolo->text();
    bool e = false; if (boolNoleggioY->isChecked()) {e=true;};
    unsigned int p = annoImmVeicolo->value();
    unsigned int o = giorniNoleggio->value();
    QString nI = nomeIntestatario->text();

    try {
        controller->modificaCivile(nome, e, p, o, nI,i);
        vista->aggiornaApp();
        emit close();
    } catch (std::exception* exc) {}
}
void Dialog::modificaAziendale()
{
    VeicoloCard* veicolo = qobject_cast<VeicoloCard *>(sender());
    short int i = veicolo->getIndice();

    QString nome = modelloVeicolo->text();
    bool e = false; if (boolNoleggioY->isChecked()) {e=true;};
    unsigned int p = annoImmVeicolo->value();
    unsigned int o = giorniNoleggio->value();
    QString nI = nomeIntestatario->text();

    unsigned int m_tP = 0 ;
    if(tAPA->isChecked())m_tP = 2;
    if (tAA->isChecked()) m_tP = 1;



    tipoCliente tP = static_cast<tipoCliente>(m_tP);


    try {
        controller->modificaAziendale(nome, e, p, o, nI,tP,i);
        vista->aggiornaApp();
        emit close();
    } catch (std::exception* exc) {}
}
