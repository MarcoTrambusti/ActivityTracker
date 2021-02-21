#include "timeedit.h"

TimeEdit::TimeEdit(QWidget *pWidget) : QTimeEdit(pWidget) {
setWrapping(true);
}

void TimeEdit::stepBy(int steps) {
    if(currentSection() == MinuteSection){
        setTime(time().addSecs(steps*1800));
        return;
    }
    QTimeEdit::stepBy(steps);
}


