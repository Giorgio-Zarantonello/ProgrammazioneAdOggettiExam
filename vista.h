#ifndef VISTA_H
#define VISTA_H

#include "type.h"
#include "veicolocard.h"
#include "dialog.h"

#include <QMainWindow>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QMenuBar>
#include <QDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QtCharts>

class Controller;

class Vista : public QMainWindow
{
    Q_OBJECT

public:
    Vista(Controller *, QWidget *parent = nullptr);
    void aggiornaApp();


private slots:
    void showGuida();
    void addCivile();
    void addAziendale();
    void saveFile();
    void loadFile();

    void modificaCivile();
    void modificaAziendale();
    void eliminaVeicolo();
    void addPieGraphs();

    void addRigheGraphs();

    void addLineGraphs();


private:
    Controller * controller;
    QGridLayout * mainLayout;
    QGroupBox * veicoli;
    QGroupBox * choice;

    QGroupBox * graphs;
    //QCHART
    QChart *chart;

    QAbstractSeries* series;
    QValueAxis* axisY;
    QValueAxis* axisX;

    QBarCategoryAxis* axisL;
    QChartView *chartView;
    QPushButton *button;




    void addMenu();

    void addVeicoliBox();
    void addChooseChart();
    void addGraphsBox();




};



#endif // VISTA_H
