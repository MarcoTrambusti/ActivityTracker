#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAbstractButton>
#include<QListWidgetItem>
#include<QTableWidgetItem>
#include <QFile>
#include "register.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow();
    ~MainWindow() override;

private slots:
    void on_pushButton_clicked();

    void on_dateEdit_dateChanged(const QDate &date);

    void on_delButton_clicked();

    void on_tableWidget_itemSelectionChanged();

    void on_modButton_clicked();

    void on_timeEdit_start_timeChanged(const QTime &time);

    void on_timeEdit_end_timeChanged(const QTime &time);

private:
    Register activityRegister;
    Ui::MainWindow *ui;
    QString descr;
    QDate datetime;
    QTime start;
    QTime end;

    void insertActivity(const QString& time, const QString& description);

    void clearInputs();

    void saveAndRefresh();
};

#endif // MAINWINDOW_H
