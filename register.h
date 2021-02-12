#ifndef REGISTER_H
#define REGISTER_H
#include"QList"
#include"activity.h"
#include <QFile>
#include <QTextStream>
class Register
{
public:
    Register();
    void addActivity(Activity* a){
        Activitylist.push_back(a);
    }
    void removeActivity(Activity* a){
        Activitylist.removeOne(a);
    }
    void clearList(){
        Activitylist.clear();
    }
    Activity* find(const QString& a,const QDate& d,const QString& s, const QString& e);
   void save();
    void load();
    QList<Activity*> getListByDate(QDate d);

    const QList<Activity *> &getActivitylist() const;

private:
 QList<Activity*> Activitylist;
};

#endif // REGISTER_H
