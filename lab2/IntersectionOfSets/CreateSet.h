#pragma once
#include "pch.h"

typedef bool (*Condition)(int a);

bool IsDividedBySumOfItsDigits(int val);
bool IsSumOfDigitsIsEven(int val);
std::set<int> CreateSetOfNumbersFrom1To(const int n, Condition isCondition);
