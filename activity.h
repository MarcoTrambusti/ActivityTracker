#ifndef ACTIVITY_H
#define ACTIVITY_H
#include <QString>
#include <QDate>
#include <utility>
class Activity
{
public:
    Activity() = default;

    Activity(QString description, const QDate &date, const QTime &start, const QTime &anEnd) : description(std::move(description)), date(date), start(start), end(anEnd) {
        if(date==QDate::fromString("00.00.0000","dd.MM.yyyy"))
            throw std::runtime_error("invalid date");
    }

    QString getDescription() const{
        return description;
    }
    QDate getDate() const{
        return date;
    }
    void setDescription(const QString& d){
       description=d;
    }
    void setDate (const QDate d){
        date=d;
    }

    const QTime &getStartTime() const {
        return start;
    }

    void setStartTime(const QTime &StartTime) {
       start = StartTime;
    }

    const QTime &getEndTime() const {
        return end;
    }

    void setEndTime(const QTime &EndTime) {
        end = EndTime;
    }

    bool operator==(const Activity &rhs) const {
        return description == rhs.description &&
               date == rhs.date &&
               start == rhs.start &&
               end == rhs.end;
    }

    bool operator!=(const Activity &rhs) const {
        return !(rhs == *this);
    }

private:
    QString description;
    QDate date;
    QTime start;
    QTime end;
};

#endif // ACTIVITY_H