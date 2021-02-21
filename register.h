#ifndef REGISTER_H
#define REGISTER_H
#include"QList"
#include"activity.h"
#include <QFile>
#include <QTextStream>
#include <memory>
class Register
{
public:
    Register();

    void addActivity(const Activity& a){
        ActivityMap.insert(a.getDate(),a);
    }
    void removeActivity(const Activity& a){
       ActivityMap.erase(ActivityMap.find(a.getDate(),a));
    }
    void clearMap(){
        ActivityMap.clear();
    }
    Activity* find(const QDate& d, const Activity& a);
    void save();
    void load();
    QList<Activity> getListByDate(QDate d);

private:
    QMultiMap<QDate, Activity> ActivityMap;
};

#endif // REGISTER_H
