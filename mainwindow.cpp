#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidgetItem>
#include "register.h"

MainWindow::MainWindow() :ui(new Ui::MainWindow),activityRegister(Register())
{
    ui->setupUi(this);
    activityRegister.load();
    ui->dateEdit->setDate( QDate::currentDate());
    ui->timeEdit_start->setTime(QTime::currentTime());
    ui->timeEdit_end->setTime(QTime::currentTime().addSecs(1800));
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
    activityRegister.addActivity(Activity(ui->lineEdit->text(),ui->dateEdit->date(),ui->timeEdit_start->time(),ui->timeEdit_end->time()));
    saveAndRefresh();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)//load activities by date
{
    QList<Activity> list=activityRegister.getListByDate(date);
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    clearInputs();
    for(auto & itr : list){
        QString stringTime=itr.getStartTime().toString("HH:mm")+itr.getEndTime().toString("-HH:mm");
        QString stringDescription=itr.getDescription();
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
    descr=ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text();
    datetime=ui->dateEdit->date();
    start=QTime::fromString(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(0),"HH:mm");
    end=QTime::fromString(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(1),"HH:mm");
    activityRegister.removeActivity( Activity(descr,datetime,start,end));
    ui->tableWidget->setSortingEnabled(false);
    ui->tableWidget->removeRow(ui->tableWidget->currentRow()+1);
    ui->tableWidget->setSortingEnabled(true);
    saveAndRefresh();
}

void MainWindow::on_modButton_clicked()
{
    descr=ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text();
    datetime=ui->dateEdit->date();
    start=QTime::fromString(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(0),"HH:mm");
    end=QTime::fromString(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text().split("-").at(1),"HH:mm");
    auto activity=activityRegister.find(ui->dateEdit->date(),Activity(descr,datetime,start,end));
    activity->setDescription(ui->lineEdit->text());
    activity->setStartTime(ui->timeEdit_start->time());
    activity->setEndTime(ui->timeEdit_end->time());
    saveAndRefresh();
}

void MainWindow:: saveAndRefresh(){
    activityRegister.save();
    activityRegister.clearMap();
    activityRegister.load();
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
    ui->timeEdit_start->setTime(QTime::currentTime());
    ui->timeEdit_end->setTime(QTime::currentTime().addSecs(1800));
    ui->tableWidget->clearSelection();
}

void MainWindow::on_timeEdit_start_timeChanged(const QTime &time)
{
    if(ui->timeEdit_end->time()<ui->timeEdit_start->time().addSecs(1800))//set minimum end time to start time+30 minutes
        ui->timeEdit_end->setTime(ui->timeEdit_start->time().addSecs(1800));
}

void MainWindow::on_timeEdit_end_timeChanged(const QTime &time)
{
    if(ui->timeEdit_end->time()<ui->timeEdit_start->time().addSecs(1800))
        ui->timeEdit_start->setTime(ui->timeEdit_end->time().addSecs(-1800));//set minimum end time to start time+30 minutes
}
