#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString string=ui->lineEdit->text()+" "+"("+ui->timeEdit_start->text()+" "+"-"+ui->timeEdit_end->text()+")";
    ui->listWidget->addItem(string);
    activityRegister->addActivity(new Activity(ui->lineEdit->text(),ui->dateEdit->date(),ui->timeEdit_start->time(),ui->timeEdit_end->time()));
    ui->lineEdit->clear();
    activityRegister->save();
    ui->timeEdit_end->time();
}

void MainWindow::on_dateEdit_dateChanged(const QDate &date)
{
    QList<Activity*> list=activityRegister->getListByDate(date);
    ui->listWidget->clear();
    for(auto & itr : list){
        QString string=itr->getDescription()+" "+itr->getStart().toString("(HH:mm")+" "+itr->getEndTime().toString("-HH:mm)");
        ui->listWidget->addItem(string);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->delButton->setEnabled(true);
}

void MainWindow::on_delButton_clicked()
{
 activityRegister->removeActivity(activityRegister->find(ui->listWidget->currentItem()->text().split(" ").at(0),ui->dateEdit->date(),ui->listWidget->currentItem()->text().split(" ").at(1),ui->listWidget->currentItem()->text().split(" ").at(2)));
 ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
 activityRegister->save();
 on_dateEdit_dateChanged(ui->dateEdit->date());
 ui->delButton->setEnabled(false);
}
