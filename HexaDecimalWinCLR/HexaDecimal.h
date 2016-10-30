#ifdef HEXADECIMAL_EXPORTS
#define HEXADECIMAL_API __declspec(dllexport)
#else
#define HEXADECIMAL_API __declspec(dllimport)
#endif // HEXADECIMAL_EXPORTS

#pragma once

#include "stdafx.h" // ✝

class IHexaDecimal
{
public:

    enum ValueType
    {
        HEX, NUM_INT, NUM_LONG, NUM_DECIMAL, BCD, BCD_LONG, BCD_DATE, BCD_DATE_LONG, RAW_STR, STR
    };

    virtual ValueType GetType() = 0;

    virtual void SetSize(int arg) = 0;

    virtual void SetHexa(char * arg) = 0;

    virtual char * GetHexa() = 0;

    virtual long GetNumericValue() = 0;

    virtual string GetRawValue() = 0;

    virtual void HexaToValue() = 0;

    virtual void ValueToHexa() = 0;
};

class BCDHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    int myValue;

    char * hexaValue;

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(int arg);

    int GetValue();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    BCDHexaDecimal();

    void DisposeHexaValue();

    ~BCDHexaDecimal();
};

class DateBCDHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    int yyyy;

    int mm;

    int dd;

    char * hexaValue;

    string YYYYtoString();

    string MMtoString();

    string DDtoString();

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(int arg1yyyy, int arg2mm, int arg3dd);

    string GetBCDStr();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    DateBCDHexaDecimal();

    void DisposeHexaValue();

    ~DateBCDHexaDecimal();
};

class IntHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    int myValue;

    char * hexaValue;

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(int arg);

    int GetValue();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    IntHexaDecimal();

    void DisposeHexaValue();

    ~IntHexaDecimal();
};

class LongDateBCDHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    int yyyy;

    int mm;

    int dd;

    int hh24;

    int mi;

    int ss;

    char * hexaValue;

    string YYYYtoString();

    string MMtoString();

    string DDtoString();

    string HH24toString();

    string MItoString();

    string SStoString();

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(int arg1yyyy, int arg2mm, int arg3dd, int arg4hh24, int arg5mi, int arg6ss);

    string GetBCDStr();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    LongDateBCDHexaDecimal();

    void DisposeHexaValue();

    ~LongDateBCDHexaDecimal();
};

class LongHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    long myValue;

    char * hexaValue;

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(long arg);

    long GetValue();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    LongHexaDecimal();

    void DisposeHexaValue();

    ~LongHexaDecimal();
};

class RawStrHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    string myValue;

    char * hexaValue;

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(string arg);

    string GetValue();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    RawStrHexaDecimal();

    void DisposeHexaValue();

    ~RawStrHexaDecimal();
};

class StrHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    string myValue;

    char * hexaValue;

    bool disposed;

public:

    ValueType GetType();

    void SetSize(int arg);

    void SetHexa(char * arg);

    char * GetHexa();

    void SetValue(string arg);

    string GetValue();

    long GetNumericValue();

    string GetRawValue();

    void HexaToValue();

    void ValueToHexa();

    StrHexaDecimal();

    void DisposeHexaValue();

    ~StrHexaDecimal();
};

class ColumnDefinition
{
public:

    enum Order
    {
        ASC, DESC, NONE,
    };

private:

    int index;

    Order order;

    IHexaDecimal::ValueType type;

public:

    void SetIndex(int arg);

    int GetIndex();

    void SetOrder(Order arg);

    ColumnDefinition::Order GetOrder();

    void SetType(IHexaDecimal::ValueType arg);

    IHexaDecimal::ValueType GetType();

    ColumnDefinition * Value(int arg1index, Order arg2order, IHexaDecimal::ValueType arg3type);

    ColumnDefinition();

    ~ColumnDefinition();
};

class HexaTable
{
private:

    vector<ColumnDefinition *> columns;

    char * rawTableData;

    vector<vector<IHexaDecimal *>> table;

public:

    void AddColumn(ColumnDefinition * arg);

    void SetRawTableData(char * arg);

    HexaTable();

    void SetTable(int r, int c, IHexaDecimal * item);

    vector<IHexaDecimal *> GetRow(int r);

    HexaTable(int r, int c);

    ~HexaTable();
};