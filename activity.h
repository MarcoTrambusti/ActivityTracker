#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <QString>
#include <QDate>
#include <utility>
class Activity
{
public:
    Activity(QString description, const QDate &date, const QTime &start, const QTime &anEnd) : description(std::move(description)), date(date), start(start), end(anEnd) {}
    QString getDescription() {
        return description;
    }
    QDate getDate(){
        return date;
    }
    void setDescription(const QString& d){
       description=d;
    }
    void setDate (const QDate d){
        date=d;
    }

    const QTime &getStart() const {
        return start;
    }

    void setStart(const QTime &start) {
        Activity::start = start;
    }

    const QTime &getEndTime() const {
        return end;
    }

    void setEndTime(const QTime &EndTime) {
        end = EndTime;
    }

private:
    QString description;
    QDate date;
    QTime start;
    QTime end;
};

#endif // ACTIVITY_H