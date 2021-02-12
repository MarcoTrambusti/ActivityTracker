#include "gtest/gtest.h"

#include "../activity.h"


TEST(activity, TestConstructor) {
    QString testDescription="test";
    QDate testDate= QDate::currentDate();
    QTime testStart=QTime::currentTime();
    QTime testEnd=QTime::currentTime();
    Activity a(testDescription,testDate,testStart,testEnd);
    ASSERT_EQ(a.getDescription(),testDescription);
    ASSERT_EQ(a.getDate(),testDate);
    ASSERT_EQ(a.getStartTime(),testStart);
    ASSERT_EQ(a.getEndTime(),testEnd);
}
