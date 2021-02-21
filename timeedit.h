#ifndef TIMEEDIT_H
#define TIMEEDIT_H
#include<QTimeEdit>

class  Q_WIDGETS_EXPORT TimeEdit: public QTimeEdit
{
    Q_OBJECT

public:
    explicit TimeEdit(QWidget *pWidget);
    void stepBy(int steps) override;
};

#endif // TIMEEDIT_H
