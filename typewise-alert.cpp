#include "typewise-alert.h"
#include <stdio.h>

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
    return (value < lowerLimit) ? TOO_LOW : (value > upperLimit) ? TOO_HIGH : NORMAL;
}

Limits getLimits(CoolingType coolingType) {
    static const Limits limits[] = {
        {0, 35},  // PASSIVE_COOLING
        {0, 45},  // HI_ACTIVE_COOLING
        {0, 40}   // MED_ACTIVE_COOLING
    };
    return limits[coolingType];
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) {
    Limits limits = getLimits(coolingType);
    return inferBreach(temperatureInC, limits.lowerLimit, limits.upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {
    BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
    sendAlert(alertTarget, breachType);
}

void sendAlert(AlertTarget alertTarget, BreachType breachType) {
    if(alertTarget == TO_CONTROLLER) {
        sendToController(breachType);
    } else if(alertTarget == TO_EMAIL) {
        sendToEmail(breachType);
    }
}

void sendToController(BreachType breachType) {
    const unsigned short header = 0xfeed;
    printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
    const char* recepient = "a.b@c.com";
    if (breachType == TOO_LOW) {
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too low\n");
    } else if (breachType == TOO_HIGH) {
        printf("To: %s\n", recepient);
        printf("Hi, the temperature is too high\n");
    }
}
