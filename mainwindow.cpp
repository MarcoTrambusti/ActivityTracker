#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include "register.h"

MainWindow::MainWindow(Register* r,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    activityRegister=r;
    ui->setupUi(this);
    activityRegister->load();
    QDate data= QDate::currentDate();
    ui->dateEdit->setDate(data);
    ui->tableWidget->sortByColumn(0,Qt::AscendingOrder);//sort rows by time column
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString stringDescription=ui->lineEdit->text();
    QString stringTime=ui->timeEdit_start->text()+"-"+ui->timeEdit_end->text();
    insertActivity(stringTime,stringDescription);
    activityRegister->addActivity(new Activity(ui->lineEdit->text(),ui->dateEdit->date(),ui->timeEdit_start->time(),ui->timeEdit_end->time()));
    activityRegister->save();
    clearInputs();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)//load activities by date
{
    QList<Activity*> list=activityRegister->getListByDate(date);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    clearInputs();
    for(auto & itr : list){
        QString stringTime=itr->getStartTime().toString("HH:mm")+itr->getEndTime().toString("-HH:mm");
        QString stringDescription=itr->getDescription();
        insertActivity(stringTime,stringDescription);
    }
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
  ui->delButton->setEnabled(true);
  ui->modButton->setEnabled(true);
  ui->lineEdit->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text());
  ui->timeEdit_start->setTime(QTime::fromString(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(0),"HH:mm"));
  ui->timeEdit_end->setTime(QTime::fromString(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(1),"HH:mm"));
}

void MainWindow::on_delButton_clicked()
{
    activityRegister->removeActivity(activityRegister->find(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text(),ui->dateEdit->date(),ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(0),ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(1)));
    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow()+1);
    ui->tableWidget->setSortingEnabled(true);
    saveAndRefresh();
}

void MainWindow::on_modButton_clicked()
{
    auto activity=activityRegister->find(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text(),ui->dateEdit->date(),ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(0),ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(1));
    activity->setDescription(ui->lineEdit->text());
    activity->setStartTime(ui->timeEdit_start->time());
    activity->setEndTime(ui->timeEdit_end->time());
    saveAndRefresh();
}

void MainWindow:: saveAndRefresh(){
    activityRegister->save();
    on_dateEdit_dateChanged(ui->dateEdit->date());//refresh table rows
    ui->delButton->setEnabled(false);
    ui->modButton->setEnabled(false);
    clearInputs();
}

void MainWindow::insertActivity(const QString& time, const QString& description){
    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setItem((ui->tableWidget->rowCount()-1),0,new QTableWidgetItem(time));
    ui->tableWidget->setItem((ui->tableWidget->rowCount()-1),1,new QTableWidgetItem(description));
    ui->tableWidget->setSortingEnabled(true);
}

void MainWindow::clearInputs(){
    ui->lineEdit->clear();
    ui->timeEdit_start->setTime(QTime::fromString("00:00","HH:mm"));
    ui->timeEdit_end->setTime(QTime::fromString("00:00","HH:mm"));
    ui->tableWidget->clearSelection();
}

void MainWindow::on_timeEdit_start_timeChanged(const QTime &time)
{
    if(ui->timeEdit_end->time()<ui->timeEdit_start->time())//set minimum end time to start time
        ui->timeEdit_end->setTime(ui->timeEdit_start->time());
}

void MainWindow::on_timeEdit_end_timeChanged(const QTime &time)
{
    if(ui->timeEdit_end->time()<ui->timeEdit_start->time())
        ui->timeEdit_start->setTime(ui->timeEdit_end->time());//set minimum end time to start time
}

