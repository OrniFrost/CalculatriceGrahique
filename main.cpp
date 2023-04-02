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

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    string fontion = "(x+2)/3";
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
    lineEditFonction->setText("x^2");
    lineEditFonction->setMaximumWidth(200);

    QLabel *labelMin = new QLabel();
    labelMin->setText("Min x");
    QLineEdit *lineEditMin = new QLineEdit();
    lineEditMin->setText("0");
    lineEditMin->setMaximumWidth(100);

    QLabel *labelMax = new QLabel();
    labelMax->setText("Max x");
    QLineEdit *lineEditMax = new QLineEdit();
    lineEditMax->setText("20");
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


    cout << calculeExpression("(x+2)/3",1) << endl;

    // Création de la série de données pour la courbe
    QtCharts::QSplineSeries *series = new QtCharts::QSplineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    // Création du graphique et ajout de la série de données
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    if (axisX)
        axisX->setRange(0, series->count()*2);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisY)
        axisY->setRange(0, 10);

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