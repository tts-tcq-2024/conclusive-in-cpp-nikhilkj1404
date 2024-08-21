#pragma once

typedef enum {
    PASSIVE_COOLING,
    HI_ACTIVE_COOLING,
    MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
    NORMAL,
    TOO_LOW,
    TOO_HIGH
} BreachType;

typedef struct {
    int lowerLimit;
    int upperLimit;
} Limits;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
Limits getLimits(CoolingType coolingType);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
    TO_CONTROLLER,
    TO_EMAIL
} AlertTarget;

typedef struct {
    CoolingType coolingType;
    char brand[48];
} BatteryCharacter;

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);
void sendAlert(AlertTarget alertTarget, BreachType breachType);
void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
