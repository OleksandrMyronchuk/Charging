#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTime>
#include <cmath>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList stringListBattery;
    stringListBattery<<"mAh"<<"Ah";
    QStringList stringListCharge;
    stringListCharge<<"mA"<<"A";
    ui->comboBoxBattery->addItems(stringListBattery);
    ui->comboBoxCharge->addItems(stringListCharge);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonExit_clicked()
{
    this->close();
}
#define CBchrg ui->comboBoxCharge->currentIndex()
#define CBbttr ui->comboBoxBattery->currentIndex()
#define DSBchrg ui->doubleSpinBoxCharge->value()
#define DSBbttr ui->doubleSpinBoxBattery->value()
#define SBt ui->spinBoxTo->value()
#define SBf ui->spinBoxFrom->value()
void MainWindow::on_pushButtonCalculate_clicked()
{
    //check
    if(DSBchrg==0 || DSBbttr==0)
    {
        QMessageBox::critical(this,"Помилка введення", "Поля \"Потужність зарядки\" і \"Потужність акумулятора\" не можуть дорівнювати нулю");
        return;
    }
    if(SBt < SBf)
    {
        QMessageBox::critical(this,"Помилка введення", "Поле \"Заряджатиметься до\" не може бути менше чим поле \"Заряджений на\"");
        return;
    }

    double p1(0), p2(0), result(0);
    //International System of Units
    //mA to A
    if(CBchrg==0)
        p1=DSBchrg*pow(10,-3);
    else if(CBchrg==1)
        p1=DSBchrg;
    //mA to A
    if(CBbttr==0)
        p2=DSBbttr*pow(10,-3);
    else if(CBbttr==1)
        p2=DSBbttr;
    if(p1 > p2)
    {
        QMessageBox::critical(this,"Помилка введення", "\"Потужність зарядки\" не може бути більша чим \"Потужність акумулятора\"");
        return;
    }
    //Ah to A
    p2*=3600;

    //Percentage
    p2=(p2*(SBt-SBf))/100;

    //calculate result
    result=p2/p1;
    QTime resultInTime(0, 0);
    resultInTime=resultInTime.addSecs(result);
    QString resultInString("");
    resultInString = "Заряджання триватиме приблизно ~";
    if(result>=86400)
        resultInString+=QString::number((result-86400)/60/60/24) + ", ";
    else
        resultInString+="0, ";
    resultInString += resultInTime.toString("hh:mm") +
    " [днів, год:хв] часу";
    ui->labelResult->setText(resultInString);
}
#undef CBchrg
#undef CBbttr
#undef SBchrg
#undef SBbttr

void MainWindow::on_pushButtonAbout_clicked()
{
    QMessageBox::about(this, "Про програму", "Програма несе розважальний характер.\nРезультати можуть бути невірними.\nАвтор: Мирончук Олександр.\nGithub: https://github.com/OleksandrMyronchuk");
}
