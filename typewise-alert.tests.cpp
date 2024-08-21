#include <gtest/gtest.h>
#include "typewise-alert.h"

TEST(TypeWiseAlertTestSuite, InfersBreachAccordingToLimits) {
    EXPECT_EQ(inferBreach(12, 10, 20), NORMAL);
    EXPECT_EQ(inferBreach(5, 10, 20), TOO_LOW);
    EXPECT_EQ(inferBreach(25, 10, 20), TOO_HIGH);
}

TEST(TypeWiseAlertTestSuite, ClassifiesTemperatureBreach) {
    EXPECT_EQ(classifyTemperatureBreach(PASSIVE_COOLING, 36), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(HI_ACTIVE_COOLING, 46), TOO_HIGH);
    EXPECT_EQ(classifyTemperatureBreach(MED_ACTIVE_COOLING, 39), NORMAL);
}

TEST(TypeWiseAlertTestSuite, SendsAlertToController) {
    testing::internal::CaptureStdout();
    sendToController(TOO_HIGH);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "feed : 2\n");
}

TEST(TypeWiseAlertTestSuite, SendsAlertToEmail) {
    testing::internal::CaptureStdout();
    sendToEmail(TOO_HIGH);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "To: a.b@c.com\nHi, the temperature is too high\n");
}

TEST(TypeWiseAlertTestSuite, CheckAndAlert) {
    BatteryCharacter batteryChar = {PASSIVE_COOLING, "BrandX"};
    
    testing::internal::CaptureStdout();
    checkAndAlert(TO_CONTROLLER, batteryChar, 36);
    std::string outputController = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputController, "feed : 2\n");

    testing::internal::CaptureStdout();
    checkAndAlert(TO_EMAIL, batteryChar, -1);
    std::string outputEmail = testing::internal::GetCapturedStdout();
    EXPECT_EQ(outputEmail, "To: a.b@c.com\nHi, the temperature is too low\n");
}
