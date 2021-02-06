#include <iostream>
#include "register.h"

Register::Register()= default;

void Register::save() {//save activities on list.txt
    QString filename="../list.txt";
    QFile file(filename);
    QTextStream memo(&file);
    if(file.open(QIODevice::WriteOnly)) {
        for (auto & itr : Activitylist) {
            memo << itr->getDate().toString("dd.MM.yyyy") << "| " <<itr->getDescription()<<"| "<<itr->getStartTime().toString("HH:mm")<<"| "<<itr->getEndTime().toString("HH:mm")<<"\n";
        }
    }
}

void Register::load() { //load activities from lists.txt
    QString filename="../list.txt";
    QFile file(filename);
    QTextStream memo(&file);
    if(file.open(QIODevice::ReadOnly)) {
        while (!memo.atEnd()) {
            QString line = memo.readLine();
            if(line!="") {
                QString d = line.split("| ").at(0);
                QString a = line.split("| ").at(1);
                QString s=line.split("| ").at(2);
                QString e=line.split("| ").at(3);
                QDate date = QDate::fromString(d, "dd.MM.yyyy");
                QTime start=QTime::fromString(s,"HH:mm");
                QTime end=QTime::fromString(e,"HH:mm");
                Activitylist.push_back(new Activity(a, date,start,end));
            }
        }
    }
}

QList<Activity *> Register::getListByDate(QDate d) {
    QList<Activity*> l;
    for(auto & itr : Activitylist){
        if(itr->getDate()==d)
        l.push_back(itr);
    }
    return l;
}

Activity *Register::find(const QString& a, const QDate& d,const QString& s, const QString& e) {
    for(auto & itr : Activitylist){
        if(itr->getDate()==d && itr->getDescription()==a && itr->getStartTime().toString("HH:mm")==s && itr->getEndTime().toString("HH:mm")==e)
            return itr;
    }
    return nullptr;
}




