#include <iostream>
#include "../Fuzzy.h"
#include "../FuzzyComposition.h"
#include "../FuzzyIO.h"
#include "../FuzzyInput.h"
#include "../FuzzyOutput.h"
#include "../FuzzyRule.h"
#include "../FuzzyRuleAntecedent.h"
#include "../FuzzyRuleConsequent.h"
#include "../FuzzySet.h"
#include "gtest/gtest.h"

// ############### FUZZYSET

TEST(FuzzySet, setPertinenceAndgetPertinence){
  FuzzySet* fuzzySet = new FuzzySet(0, 10, 10, 20);

  fuzzySet->setPertinence(0.5);

  float result = fuzzySet->getPertinence();

  EXPECT_EQ(result, 0.5);
}

TEST(FuzzySet, calculatePertinenceAndgetPertinence){
  FuzzySet* fuzzySet = new FuzzySet(0, 10, 10, 20);

  // Valor 1
  fuzzySet->calculatePertinence(-5);
  float result1 = fuzzySet->getPertinence();

  // Valor 2
  fuzzySet->calculatePertinence(5);
  float result2 = fuzzySet->getPertinence();

  // Valor 3
  fuzzySet->calculatePertinence(10);
  float result3 = fuzzySet->getPertinence();

  // Valor 4
  fuzzySet->calculatePertinence(15);
  float result4 = fuzzySet->getPertinence();

  // Valor 5
  fuzzySet->calculatePertinence(25);
  float result5 = fuzzySet->getPertinence();

  EXPECT_EQ(result1, 0.0);
  EXPECT_EQ(result2, 0.5);
  EXPECT_EQ(result3, 1.0);
  EXPECT_EQ(result4, 0.5);
  EXPECT_EQ(result5, 0.0);
}

// ############### FUZZYINPUT

TEST(FuzzyInput, addFuzzySet){
  FuzzyInput* fuzzyInput = new FuzzyInput(1);

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyInput->addFuzzySet(fuzzySetTest);

  EXPECT_TRUE(result);
}

TEST(FuzzyInput, setCrispInputAndGetCrispInput){
  FuzzyInput* fuzzyInput = new FuzzyInput(1);

  fuzzyInput->setCrispInput(10.190);

  EXPECT_FLOAT_EQ(10.190, fuzzyInput->getCrispInput());  
}

TEST(FuzzyInput, calculateFuzzySetPertinences){
  FuzzyInput* fuzzyInput = new FuzzyInput(1);

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  fuzzyInput->addFuzzySet(fuzzySetTest);

  bool result = fuzzyInput->calculateFuzzySetPertinences();

  EXPECT_TRUE(result);
}

// ############### FUZZYOUTPUT

TEST(FuzzyOutput, addFuzzySet){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyOutput->addFuzzySet(fuzzySetTest);

  EXPECT_TRUE(result);
}

TEST(FuzzyOutput, setCrispInputAndGetCrispInput){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  fuzzyOutput->setCrispInput(10.190);

  EXPECT_FLOAT_EQ(10.190, fuzzyOutput->getCrispInput());  
}

TEST(FuzzyOutput, truncate){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  FuzzySet* fuzzySetTest1 = new FuzzySet(0, 10, 10, 20);
  fuzzyOutput->addFuzzySet(fuzzySetTest1);

  FuzzySet* fuzzySetTest2 = new FuzzySet(10, 20, 20, 30);
  fuzzyOutput->addFuzzySet(fuzzySetTest2);

  FuzzySet* fuzzySetTest3 = new FuzzySet(20, 30, 30, 40);
  fuzzyOutput->addFuzzySet(fuzzySetTest3);

  bool result = fuzzyOutput->truncate();

  EXPECT_TRUE(result);
}

TEST(FuzzyOutput, getCrispOutput){
  FuzzyOutput* fuzzyOutput = new FuzzyOutput(1);

  FuzzySet* fuzzySetTest1 = new FuzzySet(0, 10, 10, 20);
  fuzzySetTest1->setPertinence(0.5);
  fuzzyOutput->addFuzzySet(fuzzySetTest1);

  FuzzySet* fuzzySetTest2 = new FuzzySet(10, 20, 20, 30);
  fuzzySetTest2->setPertinence(0.5);
  fuzzyOutput->addFuzzySet(fuzzySetTest2);

  FuzzySet* fuzzySetTest3 = new FuzzySet(20, 30, 30, 40);
  fuzzySetTest3->setPertinence(0.5);
  fuzzyOutput->addFuzzySet(fuzzySetTest3);

  fuzzyOutput->truncate();

  float result = fuzzyOutput->getCrispOutput();

  EXPECT_GT(result, 0.0);
  EXPECT_GT(result, 15);
}

// ############### FUZZYRULEANTECEDENT

TEST(FuzzyRuleAntecedent, joinSingle){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent = new FuzzyRuleAntecedent();

  FuzzySet* fuzzySet = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyRuleAntecedent->joinSingle(fuzzySet);

  EXPECT_TRUE(result);
}

TEST(FuzzyRuleAntecedent, joinWithAND){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  bool result1 = fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  bool result2 = fuzzyRuleAntecedent2->joinWithAND(temperatureLow, pressureSmall);
  
  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  bool result3 = fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);
  
  FuzzyRuleAntecedent* fuzzyRuleAntecedent4 = new FuzzyRuleAntecedent();
  bool result4 = fuzzyRuleAntecedent4->joinWithAND(fuzzyRuleAntecedent1, pressureSmall);
  
  FuzzyRuleAntecedent* fuzzyRuleAntecedent5 = new FuzzyRuleAntecedent();
  bool result5 = fuzzyRuleAntecedent5->joinWithAND(temperatureLow, fuzzyRuleAntecedent2);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result3);
  EXPECT_TRUE(result4);
  EXPECT_TRUE(result5);
}

TEST(FuzzyRuleAntecedent, joinWithOR){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  bool result1 = fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  bool result2 = fuzzyRuleAntecedent2->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  bool result3 = fuzzyRuleAntecedent3->joinWithOR(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);
  FuzzyRuleAntecedent* fuzzyRuleAntecedent4 = new FuzzyRuleAntecedent();

  bool result4 = fuzzyRuleAntecedent4->joinWithOR(fuzzyRuleAntecedent1, pressureSmall);
  FuzzyRuleAntecedent* fuzzyRuleAntecedent5 = new FuzzyRuleAntecedent();

  bool result5 = fuzzyRuleAntecedent5->joinWithOR(temperatureLow, fuzzyRuleAntecedent2);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result3);
  EXPECT_TRUE(result4);
  EXPECT_TRUE(result5);
}

TEST(FuzzyRuleAntecedent, evaluate){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();

  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  riskMinimum->setPertinence(0.5);
  fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  temperatureLow->setPertinence(0.0);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  pressureSmall->setPertinence(0.5);
  fuzzyRuleAntecedent2->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent1, fuzzyRuleAntecedent2);

  float result = fuzzyRuleAntecedent3->evaluate();

  EXPECT_GT(result, 0.0);
}

// ############### FUZZYRULECONSEQUENTE

TEST(FuzzyRuleConsequent, addOutput){
  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  bool result = fuzzyRuleConsequent->addOutput(fuzzySetTest);

  EXPECT_TRUE(result);
}

TEST(FuzzyRuleConsequent, evaluate){
  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzySet* fuzzySetTest = new FuzzySet(0, 10, 10, 20);

  fuzzyRuleConsequent->addOutput(fuzzySetTest);

  bool result = fuzzyRuleConsequent->evaluate(0.5);

  EXPECT_TRUE(result);
}

// ############### FUZZYRULE

TEST(FuzzyRule, getIndex){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent = new FuzzyRuleAntecedent();
  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzyRule* fuzzyRule = new FuzzyRule(1, fuzzyRuleAntecedent, fuzzyRuleConsequent);
  
  int result = fuzzyRule->getIndex();

  EXPECT_EQ(1, result);
}

TEST(FuzzyRule, evaluateExpressionAndIsFired){
  FuzzyRuleAntecedent* fuzzyRuleAntecedent2 = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  temperatureLow->setPertinence(0.5);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  pressureSmall->setPertinence(0.5);
  fuzzyRuleAntecedent2->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent1 = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  riskMinimum->setPertinence(0.7);
  fuzzyRuleAntecedent1->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* fuzzyRuleAntecedent3 = new FuzzyRuleAntecedent();
  fuzzyRuleAntecedent3->joinWithAND(fuzzyRuleAntecedent2, fuzzyRuleAntecedent1);

  FuzzyRuleConsequent* fuzzyRuleConsequent = new FuzzyRuleConsequent();

  FuzzySet* dangerLow = new FuzzySet(0, 10, 10, 20);

  fuzzyRuleConsequent->addOutput(dangerLow);

  FuzzyRule* fuzzyRule = new FuzzyRule(1, fuzzyRuleAntecedent3, fuzzyRuleConsequent);
  
  bool result1 = fuzzyRule->evaluateExpression();

  bool result2 = fuzzyRule->isFired();

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
}

// ############### FUZZYCOMPOSITION

TEST(FuzzyComposition, addPoint){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  bool result1 = fuzzyComposition->addPoint(1, 0.1);

  bool result2 = fuzzyComposition->addPoint(5, 0.5);
  
  bool result3 = fuzzyComposition->addPoint(9, 0.9);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_TRUE(result3);
}

TEST(FuzzyComposition, checkPoint){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  fuzzyComposition->addPoint(5, 0.5);

  bool result1 = fuzzyComposition->checkPoint(5, 0.5);

  bool result2 = fuzzyComposition->checkPoint(5, 0.1);

  EXPECT_TRUE(result1);
  EXPECT_FALSE(result2);
}


TEST(FuzzyComposition, build){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  fuzzyComposition->addPoint(0, 0);
  fuzzyComposition->addPoint(20, 0.7);
  fuzzyComposition->addPoint(40, 0);

  fuzzyComposition->addPoint(20, 0);
  fuzzyComposition->addPoint(40, 0.3);
  fuzzyComposition->addPoint(70, 0.3);
  fuzzyComposition->addPoint(80, 0);

  fuzzyComposition->addPoint(50, 0);
  fuzzyComposition->addPoint(80, 0.7);
  fuzzyComposition->addPoint(90, 0);

  bool result = fuzzyComposition->build();

  EXPECT_TRUE(result);
}

TEST(FuzzyComposition, avaliate){
  FuzzyComposition* fuzzyComposition = new FuzzyComposition();

  fuzzyComposition->addPoint(0, 0);
  fuzzyComposition->addPoint(20, 0.7);
  fuzzyComposition->addPoint(40, 0);

  fuzzyComposition->addPoint(20, 0);
  fuzzyComposition->addPoint(40, 0.3);
  fuzzyComposition->addPoint(70, 0.3);
  fuzzyComposition->addPoint(80, 0);

  fuzzyComposition->addPoint(50, 0);
  fuzzyComposition->addPoint(80, 0.7);
  fuzzyComposition->addPoint(90, 0);

  fuzzyComposition->build();

  float result = fuzzyComposition->avaliate();

  EXPECT_GT(result, 0.0);
}

// ############### FUZZY

TEST(Fuzzy, addFuzzyInput){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(0, 10, 10, 20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(10, 20, 30, 40);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(30, 40, 40, 50);
  temperature->addFuzzySet(high);

  bool result = fuzzy->addFuzzyInput(temperature);

  EXPECT_TRUE(result);
}

TEST(Fuzzy, addFuzzyOutput){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyOutput* climate = new FuzzyOutput(1);

  FuzzySet* cold = new FuzzySet(0, 10, 10, 20);
  climate->addFuzzySet(cold);
  FuzzySet* good = new FuzzySet(10, 20, 30, 40);
  climate->addFuzzySet(good);
  FuzzySet* hot = new FuzzySet(30, 40, 40, 50);
  climate->addFuzzySet(hot);

  bool result = fuzzy->addFuzzyOutput(climate);

  EXPECT_TRUE(result);
}

TEST(Fuzzy, addFuzzyRule){
  Fuzzy* fuzzy = new Fuzzy();

  FuzzyRuleAntecedent* seTemperatureLowOrpressureSmall = new FuzzyRuleAntecedent();
  FuzzySet* temperatureLow = new FuzzySet(0, 10, 10, 20);
  temperatureLow->setPertinence(0.5);
  FuzzySet* pressureSmall = new FuzzySet(0, 10, 10, 20);
  pressureSmall->setPertinence(0.5);
  seTemperatureLowOrpressureSmall->joinWithOR(temperatureLow, pressureSmall);

  FuzzyRuleAntecedent* andRiskMinimum = new FuzzyRuleAntecedent();
  FuzzySet* riskMinimum = new FuzzySet(0, 10, 10, 20);
  riskMinimum->setPertinence(0.7);
  andRiskMinimum->joinSingle(riskMinimum);

  FuzzyRuleAntecedent* seTemperatureLowOrpressureSmallandRiskMinimum = new FuzzyRuleAntecedent();
  seTemperatureLowOrpressureSmallandRiskMinimum->joinWithAND(seTemperatureLowOrpressureSmall, andRiskMinimum);

  FuzzyRuleConsequent* thenDangerLow = new FuzzyRuleConsequent();

  FuzzySet* dangerLow = new FuzzySet(0, 10, 10, 20);

  thenDangerLow->addOutput(dangerLow);

  FuzzyRule* fuzzyRule = new FuzzyRule(1, seTemperatureLowOrpressureSmallandRiskMinimum, thenDangerLow);
  
  bool result = fuzzy->addFuzzyRule(fuzzyRule);

  EXPECT_TRUE(result);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify01){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(0, 10, 10, 20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(10, 20, 30, 40);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(30, 40, 40, 50);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyOutput
  FuzzyOutput* climate = new FuzzyOutput(1);

  FuzzySet* cold = new FuzzySet(0, 10, 10, 20);
  climate->addFuzzySet(cold);
  FuzzySet* good = new FuzzySet(10, 20, 30, 40);
  climate->addFuzzySet(good);
  FuzzySet* hot = new FuzzySet(30, 40, 40, 50);
  climate->addFuzzySet(hot);

  fuzzy->addFuzzyOutput(climate);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLow = new FuzzyRuleAntecedent();
  ifTemperatureLow->joinSingle(low);
  FuzzyRuleConsequent* thenClimateCold = new FuzzyRuleConsequent();
  thenClimateCold->addOutput(cold);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLow, thenClimateCold);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMean = new FuzzyRuleAntecedent();
  ifTemperatureMean->joinSingle(mean);
  FuzzyRuleConsequent* thenClimateGood = new FuzzyRuleConsequent();
  thenClimateGood->addOutput(good);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMean, thenClimateGood);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHigh = new FuzzyRuleAntecedent();
  ifTemperatureHigh->joinSingle(low);
  FuzzyRuleConsequent* thenClimateHot = new FuzzyRuleConsequent();
  thenClimateHot->addOutput(cold);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHigh, thenClimateHot);
  fuzzy->addFuzzyRule(fuzzyRule3);

  bool result1 = fuzzy->setInput(1, 15);

  bool result2 = fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_TRUE(result1);
  EXPECT_TRUE(result2);
  EXPECT_GT(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify02){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(0, 10, 10, 20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(10, 20, 30, 40);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(30, 40, 40, 50);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(0, 10, 10, 20);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(10, 20, 30, 40);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(30, 40, 40, 50);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(0, 10, 10, 20);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(10, 20, 30, 40);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(30, 40, 40, 50);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, 15);
  fuzzy->setInput(2, 35);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_GT(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify03){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(-30, -20, -20, -10);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(-20, -10, 10, 20);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(10, 20, 20, 30);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(-30, -20, -20, -10);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(-20, -10, 10, 20);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(10, 20, 20, 30);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(-30, -20, -20, -10);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(-20, -10, 10, 20);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(10, 20, 20, 30);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, -25);
  fuzzy->setInput(2, -15);

  fuzzy->fuzzify();

  bool fuzzyRule1IsFired = fuzzy->isFiredRule(1);

  float output = fuzzy->defuzzify(1);

  EXPECT_GT(0.0, output);
  EXPECT_TRUE(fuzzyRule1IsFired);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify04){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(-20, -20, -20, -10);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(-20, -10, 10, 20);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(10, 20, 20, 20);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(-20, -20, -20, -10);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(-20, -10, 10, 20);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(10, 20, 20, 20);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(-20, -20, -20, -10);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(-20, -10, 10, 20);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(10, 20, 20, 20);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, -25);
  fuzzy->setInput(2, -15);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_EQ(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify05){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(1);

  FuzzySet* low = new FuzzySet(-20, -20, -20, -20);
  temperature->addFuzzySet(low);
  FuzzySet* mean = new FuzzySet(-10, -10, -10, -10);
  temperature->addFuzzySet(mean);
  FuzzySet* high = new FuzzySet(10, 10, 10, 10);
  temperature->addFuzzySet(high);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput
  FuzzyInput* pressure = new FuzzyInput(2);

  FuzzySet* small = new FuzzySet(-20, -20, -20, -20);
  pressure->addFuzzySet(small);
  FuzzySet* normal = new FuzzySet(-10, -10, -10, -10);
  pressure->addFuzzySet(normal);
  FuzzySet* big = new FuzzySet(10, 10, 10, 10);
  pressure->addFuzzySet(big);

  fuzzy->addFuzzyInput(pressure);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(-20, -20, -20, -20);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(-10, -10, -10, -10);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(10, 10, 10, 10);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureLowAndPressureSmall = new FuzzyRuleAntecedent();
  ifTemperatureLowAndPressureSmall->joinWithAND(low, small);
  FuzzyRuleConsequent* thenRiskMinimum = new FuzzyRuleConsequent();
  thenRiskMinimum->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifTemperatureLowAndPressureSmall, thenRiskMinimum);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureMeanAndPressureNormal = new FuzzyRuleAntecedent();
  ifTemperatureMeanAndPressureNormal->joinWithAND(mean, normal);
  FuzzyRuleConsequent* theRiskAverage = new FuzzyRuleConsequent();
  theRiskAverage->addOutput(average);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifTemperatureMeanAndPressureNormal, theRiskAverage);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifTemperatureHighAndPressureBig = new FuzzyRuleAntecedent();
  ifTemperatureHighAndPressureBig->joinWithAND(high, big);
  FuzzyRuleConsequent* thenRiskMaximum = new FuzzyRuleConsequent();
  thenRiskMaximum->addOutput(maximum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifTemperatureHighAndPressureBig, thenRiskMaximum);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, -20);
  fuzzy->setInput(2, -15);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_EQ(output, 0.0);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify06){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* distance = new FuzzyInput(1);

  FuzzySet* close = new FuzzySet(0, 20, 20, 40);
  distance->addFuzzySet(close);
  FuzzySet* safe = new FuzzySet(30, 50, 50, 70);
  distance->addFuzzySet(safe);
  FuzzySet* distante = new FuzzySet(60, 80, 100, 100);
  distance->addFuzzySet(distante);

  fuzzy->addFuzzyInput(distance);

  // FuzzyInput
  FuzzyInput* inputSpeed = new FuzzyInput(2);

  FuzzySet* stoped = new FuzzySet(0, 0, 0, 0);
  inputSpeed->addFuzzySet(stoped);
  FuzzySet* slow = new FuzzySet(1, 10, 10, 20);
  inputSpeed->addFuzzySet(slow);
  FuzzySet* normal = new FuzzySet(15, 30, 30, 50);
  inputSpeed->addFuzzySet(normal);
  FuzzySet* quick = new FuzzySet(45, 60, 70, 70);
  inputSpeed->addFuzzySet(quick);

  fuzzy->addFuzzyInput(inputSpeed);

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(3);

  FuzzySet* cold = new FuzzySet(-30, -30, -20, -10);
  temperature->addFuzzySet(cold);
  FuzzySet* good = new FuzzySet(-15, 0, 0, 15);
  temperature->addFuzzySet(good);
  FuzzySet* hot = new FuzzySet(10, 20, 30, 30);
  temperature->addFuzzySet(hot);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(0, 20, 20, 40);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(30, 50, 50, 70);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(60, 80, 80, 100);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // FuzzyOutput
  // adicionando speed como output também
  FuzzyOutput* outputSpeed = new FuzzyOutput(2);

  FuzzySet* stopedOut = new FuzzySet(0, 0, 0, 0);
  outputSpeed->addFuzzySet(stopedOut);
  FuzzySet* slowOut = new FuzzySet(1, 10, 10, 20);
  outputSpeed->addFuzzySet(slowOut);
  FuzzySet* normalOut = new FuzzySet(15, 30, 30, 50);
  outputSpeed->addFuzzySet(normalOut);
  FuzzySet* quickOut = new FuzzySet(45, 60, 70, 70);
  outputSpeed->addFuzzySet(quickOut);

  fuzzy->addFuzzyOutput(outputSpeed);

  // Building FuzzyRule
  FuzzyRuleAntecedent* distanceCloseAndSpeedQuick = new FuzzyRuleAntecedent();
  distanceCloseAndSpeedQuick->joinWithAND(close, quick);
  FuzzyRuleAntecedent* temperatureCold = new FuzzyRuleAntecedent();
  temperatureCold->joinSingle(cold);
  FuzzyRuleAntecedent* ifDistanceCloseAndSpeedQuickOrTemperatureCold = new FuzzyRuleAntecedent();
  ifDistanceCloseAndSpeedQuickOrTemperatureCold->joinWithOR(distanceCloseAndSpeedQuick, temperatureCold);

  FuzzyRuleConsequent* thenRisMaximumAndSpeedSlow = new FuzzyRuleConsequent();
  thenRisMaximumAndSpeedSlow->addOutput(maximum);
  thenRisMaximumAndSpeedSlow->addOutput(slowOut);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndSpeedQuickOrTemperatureCold, thenRisMaximumAndSpeedSlow);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* distanceSafeAndSpeedNormal = new FuzzyRuleAntecedent();
  distanceSafeAndSpeedNormal->joinWithAND(safe, normal);
  FuzzyRuleAntecedent* ifDistanceSafeAndSpeedNormalOrTemperatureGood = new FuzzyRuleAntecedent();
  ifDistanceSafeAndSpeedNormalOrTemperatureGood->joinWithOR(distanceSafeAndSpeedNormal, good);

  FuzzyRuleConsequent* thenRiskAverageAndSpeedNormal = new FuzzyRuleConsequent();
  thenRiskAverageAndSpeedNormal->addOutput(average);
  thenRiskAverageAndSpeedNormal->addOutput(normalOut);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifDistanceSafeAndSpeedNormalOrTemperatureGood, thenRiskAverageAndSpeedNormal);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* distanceDistanteAndSpeedSlow = new FuzzyRuleAntecedent();
  distanceDistanteAndSpeedSlow->joinWithAND(distante, slow);
  FuzzyRuleAntecedent* ifDistanceDistanteAndSpeedSlowOrTemperatureHot = new FuzzyRuleAntecedent();
  ifDistanceDistanteAndSpeedSlowOrTemperatureHot->joinWithOR(distanceDistanteAndSpeedSlow, hot);

  FuzzyRuleConsequent* thenRiskMinimumSpeedQuick = new FuzzyRuleConsequent();
  thenRiskMinimumSpeedQuick->addOutput(minimum);
  thenRiskMinimumSpeedQuick->addOutput(quickOut);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifDistanceDistanteAndSpeedSlowOrTemperatureHot, thenRiskMinimumSpeedQuick);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, 10);
  fuzzy->setInput(2, 30);
  fuzzy->setInput(3, -15);

  fuzzy->fuzzify();

  float output1 = fuzzy->defuzzify(1);
  float output2 = fuzzy->defuzzify(2);

  EXPECT_EQ(80.0, output1);
  EXPECT_EQ(10.5, output2);
}

TEST(Fuzzy, setInputAndFuzzifyAndDefuzzify07){
  Fuzzy* fuzzy = new Fuzzy();

  // FuzzyInput
  FuzzyInput* distance = new FuzzyInput(1);

  FuzzySet* close = new FuzzySet(0, 20, 20, 40);
  distance->addFuzzySet(close);
  FuzzySet* safe = new FuzzySet(30, 50, 50, 70);
  distance->addFuzzySet(safe);
  FuzzySet* distante = new FuzzySet(60, 80, 100, 100);
  distance->addFuzzySet(distante);

  fuzzy->addFuzzyInput(distance);

  // FuzzyInput
  FuzzyInput* temperature = new FuzzyInput(2);

  FuzzySet* cold = new FuzzySet(-30, -30, -20, -10);
  temperature->addFuzzySet(cold);
  FuzzySet* good = new FuzzySet(-15, 0, 0, 15);
  temperature->addFuzzySet(good);
  FuzzySet* hot = new FuzzySet(10, 20, 30, 30);
  temperature->addFuzzySet(hot);

  fuzzy->addFuzzyInput(temperature);

  // FuzzyOutput
  FuzzyOutput* risk = new FuzzyOutput(1);

  FuzzySet* minimum = new FuzzySet(0, 20, 20, 40);
  risk->addFuzzySet(minimum);
  FuzzySet* average = new FuzzySet(30, 50, 50, 70);
  risk->addFuzzySet(average);
  FuzzySet* maximum = new FuzzySet(60, 80, 80, 100);
  risk->addFuzzySet(maximum);

  fuzzy->addFuzzyOutput(risk);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifDistanceCloseAndTemperatureCold = new FuzzyRuleAntecedent();
  ifDistanceCloseAndTemperatureCold->joinWithAND(close, cold);

  FuzzyRuleConsequent* thenRiskMinimum1 = new FuzzyRuleConsequent();
  thenRiskMinimum1->addOutput(minimum);

  FuzzyRule* fuzzyRule1 = new FuzzyRule(1, ifDistanceCloseAndTemperatureCold, thenRiskMinimum1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifDistanceCloseAndTemperatureGood = new FuzzyRuleAntecedent();
  ifDistanceCloseAndTemperatureGood->joinWithAND(close, good);

  FuzzyRuleConsequent* thenRiskMinimum2 = new FuzzyRuleConsequent();
  thenRiskMinimum2->addOutput(minimum);

  FuzzyRule* fuzzyRule2 = new FuzzyRule(2, ifDistanceCloseAndTemperatureGood, thenRiskMinimum2);
  fuzzy->addFuzzyRule(fuzzyRule2);

  // Building FuzzyRule
  FuzzyRuleAntecedent* ifDistanceSafeAndTemperatureCold = new FuzzyRuleAntecedent();
  ifDistanceSafeAndTemperatureCold->joinWithAND(safe, cold);

  FuzzyRuleConsequent* thenRiskMinimum3 = new FuzzyRuleConsequent();
  thenRiskMinimum3->addOutput(minimum);

  FuzzyRule* fuzzyRule3 = new FuzzyRule(3, ifDistanceSafeAndTemperatureCold, thenRiskMinimum3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  fuzzy->setInput(1, 10);
  fuzzy->setInput(2, -5);

  fuzzy->fuzzify();

  float output = fuzzy->defuzzify(1);

  EXPECT_EQ(20.0, output);
}
// ############### MAIN

int main(int argc, char* *argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}