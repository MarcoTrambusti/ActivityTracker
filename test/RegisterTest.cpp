#include "gtest/gtest.h"

#include "../activity.h"

#include "../register.h"
class RegisterTestFixture : public ::testing::Test {
public:
    Activity a;
    Register r;
    QString testDescription="test";
    QDate testDate= QDate::currentDate();
    QTime testStart=QTime::currentTime();
    QTime testEnd=QTime::currentTime();
protected:
    virtual void SetUp() {
        a.setDescription(testDescription);
        a.setDate(testDate);
        a.setStartTime(testStart);
        a.setEndTime(testEnd);
    }
};
TEST_F(RegisterTestFixture, testException){
    ASSERT_THROW(r.addActivity(Activity(testDescription, QDate::fromString("00.00.0000", "dd.MM.yyyy"), testStart, testEnd)),std::runtime_error);
}
TEST_F(RegisterTestFixture,testAdd){
    r.addActivity(a);
    ASSERT_EQ(1,r.getListByDate(testDate).count());
}

TEST_F(RegisterTestFixture,testRemove){
    r.addActivity(a);
    r.removeActivity(a);
    ASSERT_EQ(0,r.getListByDate(testDate).count());
}

TEST_F(RegisterTestFixture,TestGetByDate){
    r.addActivity(a);
    ASSERT_EQ(1,r.getListByDate(testDate).count());
}

TEST_F(RegisterTestFixture,TestFind){
    r.addActivity(a);
    ASSERT_EQ(r.getListByDate(testDate).value(r.getListByDate(testDate).indexOf(a)),*r.find(testDate,a));
}

TEST_F(RegisterTestFixture,TestSaveAndLoad){
    r.addActivity(a);
    r.save();
    r.removeActivity(a);
    ASSERT_EQ(0,r.getListByDate(testDate).count());
    r.load();
    ASSERT_EQ(1,r.getListByDate(testDate).count());
}
