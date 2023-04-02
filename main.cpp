#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QHBoxLayout>
#include <QAbstractButton>
#include <QPushButton>
#include <QValueAxis>
#include <QLineEdit>
#include <QLabel>
#include "Parser/Numerics.cpp"
#include "Parser/EquationSolver.h"


QT_CHARTS_USE_NAMESPACE

int calculeExpression(string expression, int x)
{
    try{
        string strX = std::to_string(x);
        expression = expression.replace(expression.find("x"), 1, strX);
        string strResult = EquationHelper::EquationSolver::solve(expression, 50);
        return std::stoi(strResult);
    }catch(...){
        cout << "Invalid expression! Please try again!" << endl;
    }

}

void calculerSerie(QSplineSeries * series, int minX, int maxX, string fonction, int &minY, int &maxY)
{
    for(int i = minX; i < maxX; i++)
    {
        int res = calculeExpression(fonction, i);
        series->append(i, res);
        if(res < minY)
        {
            minY = res;
        }
        if (res > maxY)
        {
            maxY = res;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    string fontion = "(x+2)/3";
    int minX = -10;
    int maxX = 50;
    int minY = 1000;
    int maxY = -1000;
    /*
    // Création des boutons pour ajouter/supprimer des points
    QPushButton *addButton = new QPushButton("Ajouter un point");
    QPushButton *removeButton = new QPushButton("Supprimer le dernier point");



    // Connexion des signaux des boutons aux slots correspondants
    QObject::connect(addButton, &QPushButton::clicked, [=]() {
        qreal x = (series->count() + 1) *2;
        qreal y = qrand() % 10;
        series->append(x, y);
        axisX->setRange(0, series->count()*2);
    });
    QObject::connect(removeButton, &QPushButton::clicked, [=]() {
        series->remove(series->count() - 1);
    });
     */

    QLabel *labelFonction = new QLabel();
    labelFonction->setText("f(x) = ");
    QLineEdit *lineEditFonction = new QLineEdit();
    lineEditFonction->setText(QString(fontion.c_str()));
    lineEditFonction->setMaximumWidth(200);



    QLabel *labelMin = new QLabel();
    labelMin->setText("Min x");
    QLineEdit *lineEditMin = new QLineEdit();
    lineEditMin->setText(QString::number(minX));
    lineEditMin->setMaximumWidth(100);

    QLabel *labelMax = new QLabel();
    labelMax->setText("Max x");
    QLineEdit *lineEditMax = new QLineEdit();
    lineEditMax->setText(QString::number(maxX));
    lineEditMax->setMaximumWidth(100);

    // Création du layout pour les boutons
    QVBoxLayout *buttonLayout = new QVBoxLayout();
    //buttonLayout->addWidget(addButton);
    //buttonLayout->addWidget(removeButton);
    buttonLayout->addWidget(labelFonction);
    buttonLayout->addWidget(lineEditFonction);
    buttonLayout->addWidget(labelMin);
    buttonLayout->addWidget(lineEditMin);
    buttonLayout->addWidget(labelMax);
    buttonLayout->addWidget(lineEditMax);
    buttonLayout->addStretch();




    // Création de la série de données pour la courbe
    QtCharts::QSplineSeries *series = new QtCharts::QSplineSeries();
    calculerSerie(series, minX, maxX, fontion, minY, maxY);
    cout << minY << " " << maxY << endl;

    QtCharts::QSplineSeries *series2 = new QtCharts::QSplineSeries();
    series2->append(0, 3);
    series2->append(2, 7);
    series2->append(3, 8);
    series2->append(7, 2);
    series2->append(10, 1);

    // Création du graphique et ajout de la série de données
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->createDefaultAxes();

    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    if (axisX)
        axisX->setRange(minX, maxX);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisY)
        axisY->setRange(minY, maxY);

    // Création de la vue pour le graphique
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QLegend *legend = chart->legend();
    legend->setVisible(false);


    // Création du layout principal pour la fenêtre
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(chartView);

    // Création de la fenêtre principale
    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    window->resize(800, 600);
    window->show();

    return app.exec();
}