﻿/*
*
* HexaDecimal.cpp
*
* Copyright 2016 Yuichi Yoshii
*     吉井雄一 @ 吉井産業  you.65535.kir@gmail.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/

#include "stdafx.h"

#include "HexaDecimal.h"

string GetRawStr(char arg)
{
    char upperValue = arg / 16;
    char lowerValue = arg % 16;
    char replaceArray[17] = "0123456789ABCDEF";
    char ret[3] = { replaceArray[upperValue], replaceArray[lowerValue], char('\0') };
    return string(ret);
}

string GetBCDStr(char arg)
{
    string ret = to_string(arg);
    if (ret.length() == 1) {
        ret.insert(0, "0");
    }
    return ret;
}

char GetChar(string arg)
{
    if (arg.length() != 2) {
        throw "Argument length is bad.";
    }
    char replaceArray[17] = "0123456789ABCDEF";
    char upperValue;
    for (int i = 0; i < 16; i++) {
        if (arg[0] == replaceArray[i]) {
            upperValue = i;
        }
    }
    char lowerValue;
    for (int j = 0; j < 16; j++) {
        if (arg[1] == replaceArray[j]) {
            lowerValue = j;
        }
    }
    return (char)(upperValue * 16 + lowerValue);
}

IHexaDecimal::ValueType BCDHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::BCD;
}

void BCDHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void BCDHexaDecimal::SetHexa(char * arg)
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    hexaValue = new char[mySize];
    disposed = false;
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = arg[i];
    }
}

char * BCDHexaDecimal::GetHexa()
{
    return hexaValue;
}

void BCDHexaDecimal::SetValue(int arg)
{
    myValue = arg;
}

int BCDHexaDecimal::GetValue()
{
    return myValue;
}

long BCDHexaDecimal::GetNumericValue()
{
    return (long)myValue;
}

string BCDHexaDecimal::GetRawValue()
{
    string ret;
    for (int i = 0; i < mySize; i++) {
        ret.append(::GetRawStr(hexaValue[i]));
    }
    return ret;
}

void BCDHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    string value;
    for (int i = 0; i < mySize; i++) {
        value.append(::GetBCDStr(hexaValue[i]));
    }
    myValue = stoi(value);
}

void BCDHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    BCDHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    string value = to_string(myValue);
    if (value.length() % 2 != 0) {
        value.insert(0, "0");
    }
    while ((int)value.length() < mySize * 2) {
        value.insert(0, "00");
    }
    for (int i = 0; i < mySize; i++) {
        char item = stoi(value.substr(i * 2)) * 16 + stoi(value.substr(i * 2 + 1));
        hexaValue[i] = item;
    }
}

BCDHexaDecimal::BCDHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void BCDHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

BCDHexaDecimal::~BCDHexaDecimal()
{
    BCDHexaDecimal::DisposeHexaValue();
    disposed = true;
}

string DateBCDHexaDecimal::YYYYtoString()
{
    string ret;
    if (yyyy / 1000 >= 1) {
        ret.append(to_string(yyyy));
    }
    else if (yyyy / 100 >= 1) {
        ret.append("0").append(to_string(yyyy));
    }
    else if (yyyy / 10 >= 1) {
        ret.append("00").append(to_string(yyyy));
    }
    else {
        ret.append("000").append(to_string(yyyy));
    }
    return ret;
}

string DateBCDHexaDecimal::MMtoString()
{
    string ret;
    if (mm / 10 >= 1) {
        ret.append(to_string(mm));
    }
    else {
        ret.append("0").append(to_string(mm));
    }
    return ret;
}

string DateBCDHexaDecimal::DDtoString()
{
    string ret;
    if (dd / 10 >= 1) {
        ret.append(to_string(dd));
    }
    else {
        ret.append("0").append(to_string(dd));
    }
    return ret;
}

IHexaDecimal::ValueType DateBCDHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::BCD_DATE;
}

void DateBCDHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void DateBCDHexaDecimal::SetHexa(char * arg)
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    hexaValue = new char[mySize];
    disposed = false;
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = arg[i];
    }
}

char * DateBCDHexaDecimal::GetHexa()
{
    return hexaValue;
}

void DateBCDHexaDecimal::SetValue(int arg1yyyy, int arg2mm, int arg3dd)
{
    yyyy = arg1yyyy;
    mm = arg2mm;
    dd = arg3dd;
}

string DateBCDHexaDecimal::GetBCDStr()
{
    string ret;
    for (int i = 0; i < mySize; i++) {
        ret.append(::GetRawStr(hexaValue[i]));
    }
    return ret;
}

long DateBCDHexaDecimal::GetNumericValue()
{
    long ret = yyyy * 10000 + mm * 100 + dd * 1;
    return ret;
}

string DateBCDHexaDecimal::GetRawValue()
{
    string ret;
    for (int i = 0; i < mySize; i++) {
        ret.append(::GetRawStr(hexaValue[i]));
    }
    return ret;
}

void DateBCDHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    string value;
    for (int i = 0; i < mySize; i++) {
        value.append(::GetBCDStr(hexaValue[i]));
    }
    yyyy = stoi(value.substr(0, 4));
    mm = stoi(value.substr(4, 2));
    dd = stoi(value.substr(6, 2));
}

void DateBCDHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    DateBCDHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    string value = DateBCDHexaDecimal::YYYYtoString();
    value.append(DateBCDHexaDecimal::MMtoString());
    value.append(DateBCDHexaDecimal::DDtoString());
    if (value.length() % 2 != 0) {
        value.insert(0, "0");
    }
    while ((int)value.length() < mySize * 2) {
        value.insert(0, "00");
    }
    for (int i = 0; i < mySize; i++) {
        char item = stoi(value.substr(i * 2)) * 16 + stoi(value.substr(i * 2 + 1));
        hexaValue[i] = item;
    }
}

DateBCDHexaDecimal::DateBCDHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void DateBCDHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

DateBCDHexaDecimal::~DateBCDHexaDecimal()
{
    DateBCDHexaDecimal::DisposeHexaValue();
    disposed = true;
}

IHexaDecimal::ValueType IntHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::NUM_INT;
}

void IntHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void IntHexaDecimal::SetHexa(char * arg)
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    hexaValue = new char[mySize];
    disposed = false;
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = arg[i];
    }
}

char * IntHexaDecimal::GetHexa()
{
    return hexaValue;
}

void IntHexaDecimal::SetValue(int arg)
{
    myValue = arg;
}

int IntHexaDecimal::GetValue()
{
    return myValue;
}

long IntHexaDecimal::GetNumericValue()
{
    return (long)myValue;
}

string IntHexaDecimal::GetRawValue()
{
    return string("");
}

void IntHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    myValue = 0;
    for (int i = mySize; i > 0; i--) {
        int radix = 1;
        for (int j = 0; j < mySize - i; j++) {
            radix *= 256;
        }
        myValue += (uint8_t)hexaValue[i] * radix;
    }
}

void IntHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    IntHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    int i = 0;
    unique_ptr<char> reverse(new char[mySize]);

    int value = myValue;
    do {
        uint8_t mod = value % 256;
        reverse.get()[i] = mod;
        value /= 256;
        i++;
    } while (value != 0);

    if (i < mySize) {
        for (int j = i; j < mySize; j++) {
            reverse.get()[j] = char('\0');
        }
    }
    for (int k = 0; k < mySize; k++) {
        hexaValue[k] = reverse.get()[mySize - k];
    }
}

IntHexaDecimal::IntHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void IntHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

IntHexaDecimal::~IntHexaDecimal()
{
    IntHexaDecimal::DisposeHexaValue();
    disposed = true;
}

string LongDateBCDHexaDecimal::YYYYtoString()
{
    string ret;
    if (yyyy / 1000 >= 1) {
        ret.append(to_string(yyyy));
    }
    else if (yyyy / 100 >= 1) {
        ret.append("0").append(to_string(yyyy));
    }
    else if (yyyy / 10 >= 1) {
        ret.append("00").append(to_string(yyyy));
    }
    else {
        ret.append("000").append(to_string(yyyy));
    }
    return ret;
}

string LongDateBCDHexaDecimal::MMtoString()
{
    string ret;
    if (mm / 10 >= 1) {
        ret.append(to_string(mm));
    }
    else {
        ret.append("0").append(to_string(mm));
    }
    return ret;
}

string LongDateBCDHexaDecimal::DDtoString()
{
    string ret;
    if (dd / 10 >= 1) {
        ret.append(to_string(dd));
    }
    else {
        ret.append("0").append(to_string(dd));
    }
    return ret;
}

string LongDateBCDHexaDecimal::HH24toString()
{
    string ret;
    if (hh24 / 10 >= 1) {
        ret.append(to_string(hh24));
    }
    else {
        ret.append("0").append(to_string(hh24));
    }
    return ret;
}

string LongDateBCDHexaDecimal::MItoString()
{
    string ret;
    if (mi / 10 >= 1) {
        ret.append(to_string(mi));
    }
    else {
        ret.append("0").append(to_string(mi));
    }
    return ret;
}

string LongDateBCDHexaDecimal::SStoString()
{
    string ret;
    if (ss / 10 >= 1) {
        ret.append(to_string(ss));
    }
    else {
        ret.append("0").append(to_string(ss));
    }
    return ret;
}

IHexaDecimal::ValueType LongDateBCDHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::BCD_DATE_LONG;
}

void LongDateBCDHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void LongDateBCDHexaDecimal::SetHexa(char * arg)
{
    hexaValue = arg;
}

char * LongDateBCDHexaDecimal::GetHexa()
{
    return hexaValue;
}

void LongDateBCDHexaDecimal::SetValue(int arg1yyyy, int arg2mm, int arg3dd, int arg4hh24, int arg5mi, int arg6ss)
{
    yyyy = arg1yyyy;
    mm = arg2mm;
    dd = arg3dd;
    hh24 = arg4hh24;
    mi = arg5mi;
    ss = arg6ss;
}

string LongDateBCDHexaDecimal::GetBCDStr()
{
    string ret;
    for (int i = 0; i < mySize; i++) {
        ret.append(::GetRawStr(hexaValue[i]));
    }
    return ret;
}

long LongDateBCDHexaDecimal::GetNumericValue()
{
    long ret = yyyy * 10000 * 1000000 + mm * 100 * 1000000 + dd * 1 * 1000000;
    ret += hh24 * 10000 + mi * 100 + ss * 1;
    return ret;
}

string LongDateBCDHexaDecimal::GetRawValue()
{
    string ret;
    for (int i = 0; i < mySize; i++) {
        ret.append(::GetRawStr(hexaValue[i]));
    }
    return ret;
}

void LongDateBCDHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    string value;
    for (int i = 0; i < mySize; i++) {
        value.append(::GetBCDStr(hexaValue[i]));
    }
    yyyy = stoi(value.substr(0, 4));
    mm = stoi(value.substr(4, 2));
    dd = stoi(value.substr(6, 2));
    hh24 = stoi(value.substr(8, 2));
    mi = stoi(value.substr(10, 2));
    ss = stoi(value.substr(12, 2));
}

void LongDateBCDHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    LongDateBCDHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    string value = LongDateBCDHexaDecimal::YYYYtoString();
    value.append(LongDateBCDHexaDecimal::MMtoString());
    value.append(LongDateBCDHexaDecimal::DDtoString());
    value.append(LongDateBCDHexaDecimal::HH24toString());
    value.append(LongDateBCDHexaDecimal::MItoString());
    value.append(LongDateBCDHexaDecimal::SStoString());
    if (value.length() % 2 != 0) {
        value.insert(0, "0");
    }
    while ((int)value.length() < mySize * 2) {
        value.insert(0, "00");
    }
    for (int i = 0; i < mySize; i++) {
        char item = stoi(value.substr(i * 2)) * 16 + stoi(value.substr(i * 2 + 1));
        hexaValue[i] = item;
    }
}

LongDateBCDHexaDecimal::LongDateBCDHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void LongDateBCDHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

LongDateBCDHexaDecimal::~LongDateBCDHexaDecimal()
{
    LongDateBCDHexaDecimal::DisposeHexaValue();
    disposed = true;
}

IHexaDecimal::ValueType LongHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::NUM_LONG;
}

void LongHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void LongHexaDecimal::SetHexa(char * arg)
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    hexaValue = new char[mySize];
    disposed = false;
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = arg[i];
    }
}

char * LongHexaDecimal::GetHexa()
{
    return hexaValue;
}

void LongHexaDecimal::SetValue(long arg)
{
    myValue = arg;
}

long LongHexaDecimal::GetValue()
{
    return myValue;
}

long LongHexaDecimal::GetNumericValue()
{
    return myValue;
}

string LongHexaDecimal::GetRawValue()
{
    return string("");
}

void LongHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    myValue = 0;
    for (int i = mySize; i > 0; i--) {
        int radix = 1;
        for (int j = 0; j < mySize - i; j++) {
            radix *= 256;
        }
        myValue += (uint8_t)hexaValue[i] * radix;
    }
}

void LongHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    LongHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    int i = 0;
    unique_ptr<char> reverse(new char[mySize]);

    int value = myValue;
    do {
        uint8_t mod = value % 256;
        reverse.get()[i] = mod;
        value /= 256;
        i++;
    } while (value != 0);

    if (i < mySize) {
        for (int j = i; j < mySize; j++) {
            reverse.get()[j] = char('\0');
        }
    }
    for (int k = 0; k < mySize; k++) {
        hexaValue[k] = reverse.get()[mySize - k];
    }
}

LongHexaDecimal::LongHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void LongHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

LongHexaDecimal::~LongHexaDecimal()
{
    LongHexaDecimal::DisposeHexaValue();
    disposed = true;
}

IHexaDecimal::ValueType RawStrHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::RAW_STR;
}

void RawStrHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void RawStrHexaDecimal::SetHexa(char * arg)
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    hexaValue = new char[mySize];
    disposed = false;
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = arg[i];
    }
}

char * RawStrHexaDecimal::GetHexa()
{
    return hexaValue;
}

void RawStrHexaDecimal::SetValue(string arg)
{
    if (arg.substr(0, 2) == "0x") {
        myValue.assign(arg);
    }
    else {
        myValue.assign("0x");
        myValue.append(arg);
    }
}

string RawStrHexaDecimal::GetValue()
{
    return myValue;
}

long RawStrHexaDecimal::GetNumericValue()
{
    return 0;
}

string RawStrHexaDecimal::GetRawValue()
{
    return myValue;
}

void RawStrHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    myValue.assign("0x");
    for (int i = 0; i < mySize; i++) {
        myValue.append(::GetRawStr(hexaValue[i]));
    }
}

void RawStrHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    RawStrHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    string value = myValue;
    if (value.substr(0, 2) == "0x") {
        value.assign(value.substr(2, value.length() - 2));
    }
    if (value.length() % 2 != 0) {
        value.insert(0, "0");
    }
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = ::GetChar(value.substr(i * 2, 2));
    }
}

RawStrHexaDecimal::RawStrHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void RawStrHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

RawStrHexaDecimal::~RawStrHexaDecimal()
{
    RawStrHexaDecimal::DisposeHexaValue();
    disposed = true;
}

IHexaDecimal::ValueType StrHexaDecimal::GetType()
{
    return IHexaDecimal::ValueType::STR;
}

void StrHexaDecimal::SetSize(int arg)
{
    mySize = arg;
}

void StrHexaDecimal::SetHexa(char * arg)
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    hexaValue = new char[mySize];
    disposed = false;
    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = arg[i];
    }
}

char * StrHexaDecimal::GetHexa()
{
    return hexaValue;
}

void StrHexaDecimal::SetValue(string arg)
{
    myValue = arg;
}

string StrHexaDecimal::GetValue()
{
    return myValue;
}

long StrHexaDecimal::GetNumericValue()
{
    return 0;
}

string StrHexaDecimal::GetRawValue()
{
    string ret;
    for (int i = 0; i < mySize; i++) {
        ret.append(::GetRawStr(hexaValue[i]));
    }
    return ret;
}

void StrHexaDecimal::HexaToValue()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    myValue.assign("");

    for (int i = 0; i < mySize; i++) {
        myValue.append(&hexaValue[i]);
    }
}

void StrHexaDecimal::ValueToHexa()
{
    if (mySize < 0) {
        throw "Size of this instance is not set yet.";
    }
    StrHexaDecimal::DisposeHexaValue();
    hexaValue = new char[mySize];
    disposed = false;

    for (int i = 0; i < mySize; i++) {
        hexaValue[i] = myValue[i];
    }
}

StrHexaDecimal::StrHexaDecimal()
{
    mySize = -1;
    disposed = true;
}

void StrHexaDecimal::DisposeHexaValue()
{
    if (!disposed)
    delete hexaValue;
}

StrHexaDecimal::~StrHexaDecimal()
{
    StrHexaDecimal::DisposeHexaValue();
    disposed = true;
}

void ColumnDefinition::SetRange(int start, int end)
{
    startAt = start;
    endAt = end;
}

int ColumnDefinition::GetRangeStart()
{
    return startAt;
}

int ColumnDefinition::GetRangeEnd()
{
    return endAt;
}

void ColumnDefinition::SetOrder(Order arg)
{
    order = arg;
}

ColumnDefinition::Order ColumnDefinition::GetOrder()
{
    return order;
}

void ColumnDefinition::SetType(IHexaDecimal::ValueType arg)
{
    type = arg;
}

IHexaDecimal::ValueType ColumnDefinition::GetType()
{
    return type;
}

ColumnDefinition * ColumnDefinition::Value(int arg1start, int arg2end, Order arg3order, IHexaDecimal::ValueType arg4type)
{
    ColumnDefinition * ret = new ColumnDefinition();
    ret->SetRange(arg1start, arg2end);
    ret->SetOrder(arg3order);
    ret->SetType(arg4type);
    return ret;
}

ColumnDefinition::ColumnDefinition()
{
}

ColumnDefinition::~ColumnDefinition()
{
}

IHexaDecimal * Compare::CastLeft(int arg, char * left)
{
    IHexaDecimal * ret = nullptr;
    switch (columns[arg]->GetType()) {
    case IHexaDecimal::ValueType::BCD:
        ret = new BCDHexaDecimal();
    case IHexaDecimal::ValueType::BCD_DATE:
        ret = new DateBCDHexaDecimal();
    case IHexaDecimal::ValueType::BCD_DATE_LONG:
        ret = new LongDateBCDHexaDecimal();
    case IHexaDecimal::ValueType::HEX:
        ret = new RawStrHexaDecimal();
    case IHexaDecimal::ValueType::NUM_INT:
        ret = new IntHexaDecimal();
    case IHexaDecimal::ValueType::NUM_LONG:
        ret = new LongHexaDecimal();
    case IHexaDecimal::ValueType::RAW_STR:
        ret = new RawStrHexaDecimal();
    default:
        ret = new StrHexaDecimal();
    }
    int range = columns[arg]->GetRangeEnd() - columns[arg]->GetRangeStart();
    ret->SetSize(range);
    char * value = new char[range];
    for (int i = 0; i < range; i++) {
        value[i] = left[columns[arg]->GetRangeStart() + i];
    }
    ret->SetHexa(value);
    return ret;
}

IHexaDecimal * Compare::CastRight(int arg, char * right)
{
    IHexaDecimal * ret = nullptr;
    switch (columns[arg]->GetType()) {
    case IHexaDecimal::ValueType::BCD:
        ret = new BCDHexaDecimal();
    case IHexaDecimal::ValueType::BCD_DATE:
        ret = new DateBCDHexaDecimal();
    case IHexaDecimal::ValueType::BCD_DATE_LONG:
        ret = new LongDateBCDHexaDecimal();
    case IHexaDecimal::ValueType::HEX:
        ret = new RawStrHexaDecimal();
    case IHexaDecimal::ValueType::NUM_INT:
        ret = new IntHexaDecimal();
    case IHexaDecimal::ValueType::NUM_LONG:
        ret = new LongHexaDecimal();
    case IHexaDecimal::ValueType::RAW_STR:
        ret = new RawStrHexaDecimal();
    default:
        ret = new StrHexaDecimal();
    }
    int range = columns[arg]->GetRangeEnd() - columns[arg]->GetRangeStart();
    ret->SetSize(range);
    char * value = new char[range];
    for (int i = 0; i < range; i++) {
        value[i] = right[columns[arg]->GetRangeStart() + i];
    }
    ret->SetHexa(value);
    return ret;
}

void Compare::SetColumns(vector<ColumnDefinition *> arg)
{
    columns = arg;
}

bool Compare::operator()(char * leftSide, char * rightSide)
{
    for (size_t i = 0; i < columns.size(); i++) {
        IHexaDecimal * leftItem = CastLeft((int)i, leftSide);
        IHexaDecimal * rightItem = CastRight((int)i, rightSide);
        if (columns[i]->GetOrder() == ColumnDefinition::Order::ASC) {
            switch (columns[i]->GetType()) {
            case IHexaDecimal::ValueType::BCD:
            case IHexaDecimal::ValueType::BCD_DATE:
            case IHexaDecimal::ValueType::BCD_DATE_LONG:
            case IHexaDecimal::ValueType::NUM_INT:
            case IHexaDecimal::ValueType::NUM_LONG:
                if (leftItem->GetNumericValue() < rightItem->GetNumericValue()) {
                    return true;
                }
                else if (leftItem->GetNumericValue() > rightItem->GetNumericValue()) {
                    return false;
                }
                break;
            default:
                if (leftItem->GetRawValue() < rightItem->GetRawValue()) {
                    return true;
                }
                else if (leftItem->GetRawValue() > rightItem->GetRawValue()) {
                    return false;
                }
                break;
            }
        }
        else {
            switch (columns[i]->GetType()) {
            case IHexaDecimal::ValueType::BCD:
            case IHexaDecimal::ValueType::BCD_DATE:
            case IHexaDecimal::ValueType::BCD_DATE_LONG:
            case IHexaDecimal::ValueType::NUM_INT:
            case IHexaDecimal::ValueType::NUM_LONG:
                if (leftItem->GetNumericValue() > rightItem->GetNumericValue()) {
                    return true;
                }
                else if (leftItem->GetNumericValue() < rightItem->GetNumericValue()) {
                    return false;
                }
                break;
            default:
                if (leftItem->GetRawValue() > rightItem->GetRawValue()) {
                    return true;
                }
                else if (leftItem->GetRawValue() < rightItem->GetRawValue()) {
                    return false;
                }
                break;
            }
        }
    }
    return false;
}

void HexaTable::Row::Allocate(vector<ColumnDefinition *> arg)
{
    self = vector<IHexaDecimal *>();
    IHexaDecimal * item = nullptr;
    for (size_t i = 0; i < arg.size(); i++) {
        if (arg[i]->GetType() == IHexaDecimal::ValueType::HEX) {
            item = new RawStrHexaDecimal();
        }
        else if (arg[i]->GetType() == IHexaDecimal::ValueType::STR) {
            item = new StrHexaDecimal();
        }
        else if (arg[i]->GetType() == IHexaDecimal::ValueType::NUM_INT) {
            item = new IntHexaDecimal();
        }
        else if (arg[i]->GetType() == IHexaDecimal::ValueType::BCD_DATE_LONG) {
            item = new LongDateBCDHexaDecimal();
        }
        else if (arg[i]->GetType() == IHexaDecimal::ValueType::NUM_LONG) {
            item = new LongHexaDecimal();
        }
        item->SetSize(arg[i]->GetRangeEnd() - arg[i]->GetRangeStart());
        self.push_back(item);
    }
}

vector<IHexaDecimal *> HexaTable::Row::Get()
{
    return self;
}

HexaTable::Row::Row()
{
}

HexaTable::Row::~Row()
{
}

void HexaTable::AddColumn(ColumnDefinition * arg)
{
    columns.push_back(arg);
}

void HexaTable::SetRowCount(int arg)
{
    rowcount = arg;
}

void HexaTable::Allocate()
{
    HexaTable::Row * row = new HexaTable::Row();
    row->Allocate(columns);
    rows = vector<Row *>();
    rows.resize(rowcount, row);
}

void HexaTable::SetTableData(char * arg)
{
    tabledata = arg;
}

int GetRowSize(vector<ColumnDefinition *> columns)
{
    int ret = 0;
    for (size_t i = 0; i < columns.size(); i++) {
        ret += columns[i]->GetRangeEnd() - columns[i]->GetRangeStart();
    }
    return ret;
}

char * CutRowData(int r, int c, vector<ColumnDefinition *> columns, int rowSize, char * tabledata)
{
    int retSize = columns[c]->GetRangeEnd() - columns[c]->GetRangeStart();
    char * ret = new char[retSize];
    int start = rowSize * r + columns[c]->GetRangeStart();
    for (int i = 0; i < retSize; i++) {
        ret[i] = tabledata[start + i];
    }
    ret[retSize] = char('\0');
    return ret;
}

void HexaTable::Cast()
{
    int rowSize = GetRowSize(columns);
    for (int i = 0; i < rowcount; i++) {
        for (size_t j = 0; j < columns.size(); j++) {
            char * item = CutRowData(i, (int)j, columns, rowSize, tabledata);
            rows[i]->Get()[j]->SetHexa(item);
        }
    }
}

HexaTable::HexaTable()
{
}

HexaTable::~HexaTable()
{
}