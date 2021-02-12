#include "gtest/gtest.h"

#include "../activity.h"

#include "../register.h"
class RegisterTestFixture : public ::testing::Test {
public:
    Activity* a;
    Register r;
    QString testDescription="test";
    QDate testDate= QDate::currentDate();
    QTime testStart=QTime::currentTime();
    QTime testEnd=QTime::currentTime();
protected:
    virtual void SetUp() {
        a=new Activity(testDescription,testDate,testStart,testEnd);
    }
};

TEST_F(RegisterTestFixture,testAdd){
    r.addActivity(a);
    ASSERT_EQ(1,r.getActivitylist().count());
}
TEST_F(RegisterTestFixture,testRemove){
    r.addActivity(a);
    r.removeActivity(a);
    ASSERT_EQ(0,r.getActivitylist().count());
}
TEST_F(RegisterTestFixture,TestGetByDate){
    r.addActivity(a);
    ASSERT_EQ(1,r.getListByDate(QDate::currentDate()).count());
}
TEST_F(RegisterTestFixture,TestFind){
    r.addActivity(a);
    ASSERT_EQ(r.getActivitylist().back(),r.find(testDescription,testDate,testStart.toString("HH:mm"),testEnd.toString("HH:mm")));
}
TEST_F(RegisterTestFixture,TestSaveAndLoad){
    r.addActivity(a);
    r.save();
    r.removeActivity(a);
    ASSERT_EQ(0,r.getActivitylist().count());
    r.load();
    ASSERT_EQ(1,r.getActivitylist().count());
}
