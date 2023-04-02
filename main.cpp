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
using namespace std;

int calculeExpression(string expression, int x)
{
    try{
        string strX = std::to_string(x);
        int nbX = std::count(expression.begin(), expression.end(), 'x');
        for (int i = 0; i < nbX; ++i) {
            expression = expression.replace(expression.find("x"), 1, strX);
        }
        string strResult = EquationHelper::EquationSolver::solve(expression, 50);
        return std::stoi(strResult);
    }catch(...){
        cout << "Invalid expression! Please try again!" << endl;
    }

}

int minX = 0;
int maxX = 20;

int minY = 1000;
int maxY = -1000;
std::array<int,2> calculerSerie(QSplineSeries * series, int minX, int maxX, string fonction)
{
    for(int i = minX; i <= maxX; i++)
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
        if(i == maxX && maxY != res)
        {
            maxY = res;
        }

    }

    return {minY, maxY};
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    string fontion = "(x+2)/3";

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

    QVBoxLayout *optionLayout = new QVBoxLayout();
    optionLayout->addWidget(labelFonction);
    optionLayout->addWidget(lineEditFonction);
    optionLayout->addWidget(labelMin);
    optionLayout->addWidget(lineEditMin);
    optionLayout->addWidget(labelMax);
    optionLayout->addWidget(lineEditMax);
    optionLayout->addStretch();

    QtCharts::QSplineSeries *series = new QtCharts::QSplineSeries();
    calculerSerie(series, minX, maxX, fontion);

    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
    if (axisX)
        axisX->setRange(minX, maxX);

    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
    if (axisY)
        axisY->setRange(minY, maxY);

    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QLegend *legend = chart->legend();
    legend->setVisible(false);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(optionLayout);
    mainLayout->addWidget(chartView);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);
    window->resize(800, 600);
    window->show();

    QObject::connect(lineEditFonction, &QLineEdit::editingFinished, [=]() {
        series->clear();
        calculerSerie(series, minX, maxX, lineEditFonction->text().toStdString());
        QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
        if (axisX)
            axisX->setRange(minX, maxX);

        QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
        if (axisY)
            axisY->setRange(minY, maxY);
    });

    QObject::connect(lineEditMin, &QLineEdit::editingFinished, [=]() {
        series->clear();
        minX = lineEditMin->text().toInt();
        calculerSerie(series, minX, maxX, lineEditFonction->text().toStdString());
        QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
        if (axisX)
            axisX->setRange(minX, maxX);

        QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
        if (axisY)
            axisY->setRange(minY, maxY);
    });

    QObject::connect(lineEditMax, &QLineEdit::editingFinished, [=]() {
        series->clear();
        maxX = lineEditMax->text().toInt();
        calculerSerie(series, minX, maxX, lineEditFonction->text().toStdString());
        QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axisX());
        if (axisX)
            axisX->setRange(minX, maxX);

        QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axisY());
        if (axisY)
            axisY->setRange(minY, maxY);
    });


    return app.exec();
}