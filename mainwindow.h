#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAbstractButton>
#include<QListWidgetItem>
#include <QFile>
#include "register.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Register* r, QWidget *parent = 0);
    ~MainWindow() override;

private slots:
    void on_pushButton_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_delButton_clicked();

private:
    Register* activityRegister;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
