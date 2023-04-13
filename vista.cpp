#include "vista.h"
#include "controller.h"
#include<QDebug>
#include <QtCharts>
#include <QDebug>
QT_USE_NAMESPACE





Vista::Vista(Controller * c, QWidget *parent) : QMainWindow(parent), controller(c)
{

    setWindowTitle(tr("Gestore Noleggi Veicoli"));
    QWidget *widget = new QWidget();

    QWidget * central = new QWidget(this);
    mainLayout = new QGridLayout(central);
    addMenu();

    addVeicoliBox();
    addChooseChart();
    addGraphsBox();

    chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chartView = new QChartView();
    chartView->setChart(chart);

    mainLayout->addWidget(veicoli,0, 0);
    mainLayout->addWidget(choice, 0, 1);
    mainLayout->addWidget(graphs, 1, 0);

    QHBoxLayout * GraphBox = new QHBoxLayout(widget);

    GraphBox->addWidget(chartView);

    graphs->setLayout(GraphBox);

    central->setLayout(mainLayout);
    setCentralWidget(central);
    resize(1440,900);
}

void Vista::aggiornaApp()
{
    delete veicoli;
    delete choice;


    QWidget *widget = new QWidget();

    QWidget * central = new QWidget(this);
    mainLayout = new QGridLayout(central);

    addMenu();

    addVeicoliBox();
    addChooseChart();

    addGraphsBox();

    chart = new QChart();
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chartView = new QChartView();
    chartView->setChart(chart);

    mainLayout->addWidget(veicoli,0, 0);
    mainLayout->addWidget(choice, 0, 1);
    mainLayout->addWidget(graphs, 1, 0);

    QHBoxLayout * GraphBox = new QHBoxLayout(widget);

    GraphBox->addWidget(chartView);

    graphs->setLayout(GraphBox);




    central->setLayout(mainLayout);
    setCentralWidget(central);
}

void Vista::addMenu()
{
    QMenuBar * menubar = new QMenuBar();

    QMenu * fileMenu = new QMenu("File",menubar);
    QMenu * nuovo = fileMenu->addMenu("Nuovo");

    QAction * esci = fileMenu->addAction("Esci");
    connect(esci, SIGNAL(triggered()), this, SLOT(close()));
    QAction * civile = nuovo->addAction("Noleggio Auto Per Civile");
    connect(civile, SIGNAL(triggered()), this, SLOT(addCivile()));
    QAction * aziendale = nuovo->addAction("Noleggio Auto Per Aziendale");
    connect(aziendale, SIGNAL(triggered()), this, SLOT(addAziendale()));

    QMenu * helpMenu = new QMenu("Help",menubar);
    QAction * guida = new QAction("Guida",helpMenu);
    helpMenu->addAction(guida);
    connect(guida, SIGNAL(triggered()), this, SLOT(showGuida()));

    menubar->addMenu(fileMenu);
    menubar->addMenu(helpMenu);
    QAction * salva = new QAction("Salva su File",menubar);
    menubar->addAction(salva);
    connect(salva, SIGNAL(triggered()), this, SLOT(saveFile()));
    QAction * apriFile = new QAction("Apri da File",menubar);
    menubar->addAction(apriFile);
    connect(apriFile, SIGNAL(triggered()), this, SLOT(loadFile()));
    mainLayout->setMenuBar(menubar);
}

void Vista::showGuida()
{
    QMessageBox::about(this, tr("Gestore Noleggi Veicoli"),
                       tr(
                           "<p>Benvenuti in <b>Gestore Noleggi Veicoli</b>, di Giorgio Zarantonello.</p>"
                           "<ul>"
                           "<li>Questo programma si prefigge lo scopo di contabilizzare le auto di una ipotetica attivita' di noleggio veicolo</li>"
                           "<li>Consultare la relazione per ulteriori informazioni</li>"
                           "</ul>"
                           ));
}

void Vista::saveFile(){
    QString fileName = QFileDialog::getSaveFileName(this);
    QFile saveFile(fileName);
        if(!saveFile.open(QIODevice::WriteOnly)){
            qWarning("file non salvato");
        }
        else{
            controller->h_saveFile(Modello::Json,fileName);
        }}

void Vista::loadFile()
{


    QString fileName = QFileDialog::getOpenFileName(this);

        QFile loadFile(fileName);
        if(!loadFile.open(QIODevice::ReadOnly)){
            qWarning("nessun file non caricato.");
        }
        else{
            controller->h_loadFile(Modello::Json,fileName);
        }

    aggiornaApp();




}

void Vista::addCivile()
{
    Dialog * finestra = new Dialog(controller, this, civile, -1);

    finestra->exec();
}
void Vista::addAziendale()
{
    Dialog * finestra = new Dialog(controller, this, aziendale, -1);

    finestra->exec();
}

void Vista::addVeicoliBox()
{
    veicoli = new QGroupBox(tr("Veicoli:"));

    QScrollArea * scrollArea = new QScrollArea();
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);
    scrollArea->setGeometry(10, 10, 100, 100);
    QWidget *widget = new QWidget();
    scrollArea->setWidget(widget);

    QVBoxLayout * lista = new QVBoxLayout();
    widget->setLayout(lista);

    for (unsigned short i = 0; i < controller->getSize(); i++) {
        QWidget * temp = new QWidget();
        QHBoxLayout * riga = new QHBoxLayout(temp);
        riga->setContentsMargins(0, 0, 0, 0);
        riga->setSpacing(0);


        QString nome = controller->getNomeVeicolo(i);
        type t = controller->getTipoCliente(i);

        VeicoloCard* info = new VeicoloCard(i,t);
        VeicoloCard* modifica = new VeicoloCard(i,t);
        modifica->setIcon(QIcon(":./icons/pen.svg"));
        VeicoloCard* elimina = new VeicoloCard(i,t);
        elimina->setIcon(QIcon(":./icons/x.svg"));

        riga->addWidget(info, 70);
        riga->addWidget(modifica, 15);
        riga->addWidget(elimina, 15);
        temp->setLayout(riga);


        if (t == civile){

            connect(modifica, SIGNAL(clicked()), this, SLOT(modificaCivile()));

        }
        if (t == aziendale){

            connect(modifica, SIGNAL(clicked()), this, SLOT(modificaAziendale()));

        }

        connect(elimina, SIGNAL(clicked()), this, SLOT(eliminaVeicolo()));

        info->setText(nome);

        lista->addWidget(temp);

    }

    QGridLayout * layout = new QGridLayout;
    layout->addWidget(scrollArea, 0, 0);
    veicoli->setLayout(layout);
}
void Vista::eliminaVeicolo()
{

    VeicoloCard* veicolo = qobject_cast<VeicoloCard *>(sender());
    unsigned short i = veicolo->getIndice();

    controller->cancellaVeicolo(i);

    aggiornaApp();
}

void Vista::modificaCivile()
{

    VeicoloCard* veicolo = qobject_cast<VeicoloCard *>(sender());
    short int i = veicolo->getIndice();
    Dialog * finestra = new Dialog(controller, this, civile, i);

    finestra->setWindowTitle(tr("Modifica Civile"));

    QString name = controller->getNomeVeicolo(i);
    bool stateNol = controller->getStatoNoleggio(i);
    unsigned int annoImmVeicolo = controller->getAnnoImmatricolazione(i);
    double gN = controller->getGiorniNoleggio(i);
    QString nomeInt = controller->getNomeIntestatario(i);


    finestra->modelloVeicolo->setText(name);
    finestra->annoImmVeicolo->setValue(annoImmVeicolo);
    finestra->giorniNoleggio->setValue(gN);
    finestra->nomeIntestatario->setText(nomeInt);

    if (!stateNol) {
        finestra->boolNoleggioY->setChecked(false);
        finestra->boolNoleggioN->setChecked(true);
    }
    else {
        finestra->boolNoleggioY->setChecked(true);
        finestra->boolNoleggioN->setChecked(false);
    }

    finestra->exec();
}

void Vista::modificaAziendale()
{


    VeicoloCard* veicolo = qobject_cast<VeicoloCard *>(sender());
    short int i = veicolo->getIndice();
    Dialog * finestra = new Dialog(controller, this, aziendale, i);

    finestra->setWindowTitle(tr("Modifica Aziendale"));

    QString name = controller->getNomeVeicolo(i);
    bool stateNol = controller->getStatoNoleggio(i);
    unsigned int annoImmVeicolo = controller->getAnnoImmatricolazione(i);
    double gN = controller->getGiorniNoleggio(i);
    QString nomeInt = controller->getNomeClienteNoleggio(i);
    tipoCliente m_tA = controller->getTipoAziendale(i);

    switch(m_tA){
    case liberoProfessionista :
        finestra->tALP->setChecked(true);
        finestra->tAA->setChecked(false);
        finestra->tAPA->setChecked(false);
        break;
    case azienda:
        finestra->tAA->setChecked(true);
        finestra->tALP->setChecked(false);
        finestra->tAPA->setChecked(false);
        break;
    case pubblicaAmministrazione:
        finestra->tAPA->setChecked(true);
        finestra->tAA->setChecked(false);
        finestra->tALP->setChecked(false);
        break;
    }


    finestra->modelloVeicolo->setText(name);
    finestra->giorniNoleggio->setValue(gN);
    finestra->annoImmVeicolo->setValue(annoImmVeicolo);
    finestra->nomeIntestatario->setText(nomeInt);





    if (!stateNol) {
        finestra->boolNoleggioY->setChecked(false);
        finestra->boolNoleggioN->setChecked(true);
    }
    else {
        finestra->boolNoleggioY->setChecked(true);
        finestra->boolNoleggioN->setChecked(false);
    }

    finestra->exec();
}



void Vista::addChooseChart() {
    choice = new QGroupBox(tr("Scegli Tipologia Grafico:"));

    QWidget *widget = new QWidget();

    QVBoxLayout * riga = new QVBoxLayout(widget);

    QPushButton *c1 = new QPushButton();
    QPushButton* c2 = new  QPushButton();

    QPushButton* c3 = new  QPushButton();


    c1->setText("torta");
    c2->setText("righe");
    c3->setText("Line");

    riga->addWidget(c1);
    riga->addWidget(c2);
    riga->addWidget(c3);




    choice->setLayout(riga);

    connect(c1,SIGNAL(clicked(bool)),this,SLOT(addPieGraphs()));
    connect(c2,SIGNAL(clicked()),this,SLOT(addRigheGraphs()));
    connect(c3,SIGNAL(clicked()),this,SLOT(addLineGraphs()));

}

void Vista::addGraphsBox()
{

    graphs = new QGroupBox(tr("Grafico:"));




}
void Vista::addPieGraphs() {
    chart->removeAllSeries();

    if (chart->axes().size() > 0 ){
        chart->removeAxis(axisL);
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);

    }





    series = new QPieSeries(this);

    QPieSeries *pieSeries = static_cast<QPieSeries*>(series);
    pieSeries->append("Civili",controller->c_countVeicolo(1));
    pieSeries->append("Libero Professionista",controller->c_countVeicolo(2));
    pieSeries->append("Aziendale",controller->c_countVeicolo(3));
    pieSeries->append("Pubblica Amministrazione",controller->c_countVeicolo(4));

    chart->addSeries(pieSeries);
    chart->setTitle("Grafico Torta di quante auto per ogni entita'");

}


void Vista::addRigheGraphs() {
    /* PARCO AUTO NOLEGGIATE per categoria */
    chart->removeAllSeries();

    if (chart->axes().size() > 0 ){
        chart->removeAxis(axisL);
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);

    }

    QBarSet *set0 = new QBarSet("Civili");
    QBarSet *set1 = new QBarSet("Libero Professionista");
    QBarSet *set2 = new QBarSet("Azienda");
    QBarSet *set3 = new QBarSet("Pubblica Amministrazione");
    QBarSet *set4 = new QBarSet("Aziendale");

    //set auto noleggiate / non noleggiate
    *set0 << controller->c_countNoleggioVeicolo(1,true) ;
    *set1 << controller->c_countNoleggioVeicolo(2,true) ;
    *set2 << controller->c_countNoleggioVeicolo(3,true) ;
    *set3 << controller->c_countNoleggioVeicolo(4,true) ;
    *set4 << controller->c_countNoleggioVeicolo(0,true) ;

    *set0 << controller->c_countNoleggioVeicolo(1,false) ;
    *set4 << controller->c_countNoleggioVeicolo(2,false) << controller->c_countNoleggioVeicolo(3,false)   << controller->c_countNoleggioVeicolo(4,false)  ;



    series = new QBarSeries();
    QBarSeries *barSeries = static_cast<QBarSeries*>(series);

    barSeries->append(set0);
    barSeries->append(set1);
    barSeries->append(set2);
    barSeries->append(set3);
    barSeries->append(set4);
    chart->addSeries(barSeries);

    QStringList categories;
    categories << "Noleggiato" << "Noleggiabile";

    axisL = new QBarCategoryAxis();
    axisY = new QValueAxis();

    axisL->append(categories);


    chart->setAxisX(axisL);
    chart->setAxisY(axisY);
    series->attachAxis(axisL);
    series->attachAxis(axisY);
    chart->setTitle("Parco auto noleggiate per categoria");


}

void Vista::addLineGraphs()
{
    chart->removeAllSeries();
    if (chart->axes().size() > 0 ){
        chart->removeAxis(axisL);
        chart->removeAxis(axisX);
        chart->removeAxis(axisY);

    }


    axisX = new QValueAxis();
    axisY = new QValueAxis();
    series = new QLineSeries();
    QLineSeries *lineSeries = static_cast<QLineSeries*>(series);

    lineSeries->append(2000, controller->c_calcolaRicavoAnnoImm(2000));
    lineSeries->append(2001, controller->c_calcolaRicavoAnnoImm(2001));
    lineSeries->append(2002, controller->c_calcolaRicavoAnnoImm(2002));
    lineSeries->append(2003, controller->c_calcolaRicavoAnnoImm(2003));
    lineSeries->append(2004, controller->c_calcolaRicavoAnnoImm(2004));
    lineSeries->append(2005, controller->c_calcolaRicavoAnnoImm(2005));
    lineSeries->append(2006, controller->c_calcolaRicavoAnnoImm(2006));
    lineSeries->append(2007, controller->c_calcolaRicavoAnnoImm(2007));
    lineSeries->append(2008, controller->c_calcolaRicavoAnnoImm(2008));
    lineSeries->append(2009, controller->c_calcolaRicavoAnnoImm(2009));
    lineSeries->append(2010, controller->c_calcolaRicavoAnnoImm(2010));
    lineSeries->append(2011, controller->c_calcolaRicavoAnnoImm(2011));
    lineSeries->append(2012, controller->c_calcolaRicavoAnnoImm(2012));
    lineSeries->append(2013, controller->c_calcolaRicavoAnnoImm(2013));
    lineSeries->append(2014, controller->c_calcolaRicavoAnnoImm(2014));
    lineSeries->append(2015, controller->c_calcolaRicavoAnnoImm(2015));
    lineSeries->append(2016, controller->c_calcolaRicavoAnnoImm(2016));
    lineSeries->append(2017, controller->c_calcolaRicavoAnnoImm(2017));
    lineSeries->append(2018, controller->c_calcolaRicavoAnnoImm(2018));
    lineSeries->append(2019, controller->c_calcolaRicavoAnnoImm(2019));
    lineSeries->append(2020, controller->c_calcolaRicavoAnnoImm(2020));
    lineSeries->append(2021, controller->c_calcolaRicavoAnnoImm(2021));
    lineSeries->append(2022, controller->c_calcolaRicavoAnnoImm(2022));


    chart->addSeries(lineSeries);
    chart->setAxisX(axisX);
    chart->setAxisY(axisY);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    chart->setTitle("Ricavi totali dei veicoli in noleggio , per anno di immatricolazione.");

}
