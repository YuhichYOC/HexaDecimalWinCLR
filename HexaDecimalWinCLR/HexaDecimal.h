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

    HEXADECIMAL_API virtual ValueType __stdcall GetType() = 0;

    HEXADECIMAL_API virtual void __stdcall SetSize(int arg) = 0;

    HEXADECIMAL_API virtual void __stdcall SetHexa(char * arg) = 0;

    HEXADECIMAL_API virtual char * __stdcall GetHexa() = 0;

    HEXADECIMAL_API virtual long __stdcall GetNumericValue() = 0;

    HEXADECIMAL_API virtual string __stdcall GetRawValue() = 0;

    HEXADECIMAL_API virtual void __stdcall HexaToValue() = 0;

    HEXADECIMAL_API virtual void __stdcall ValueToHexa() = 0;
};

class BCDHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    int myValue;

    char * hexaValue;

    bool disposed;

public:

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(int arg);

    HEXADECIMAL_API int __stdcall GetValue();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall BCDHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~BCDHexaDecimal();
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

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(int arg1yyyy, int arg2mm, int arg3dd);

    HEXADECIMAL_API string __stdcall GetBCDStr();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall DateBCDHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~DateBCDHexaDecimal();
};

class IntHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    int myValue;

    char * hexaValue;

    bool disposed;

public:

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(int arg);

    HEXADECIMAL_API int __stdcall GetValue();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall IntHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~IntHexaDecimal();
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

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(int arg1yyyy, int arg2mm, int arg3dd, int arg4hh24, int arg5mi, int arg6ss);

    HEXADECIMAL_API string __stdcall GetBCDStr();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall LongDateBCDHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~LongDateBCDHexaDecimal();
};

class LongHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    long myValue;

    char * hexaValue;

    bool disposed;

public:

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(long arg);

    HEXADECIMAL_API long __stdcall GetValue();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall LongHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~LongHexaDecimal();
};

class RawStrHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    string myValue;

    char * hexaValue;

    bool disposed;

public:

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(string arg);

    HEXADECIMAL_API string __stdcall GetValue();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall RawStrHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~RawStrHexaDecimal();
};

class StrHexaDecimal : public IHexaDecimal
{
private:

    int mySize;

    string myValue;

    char * hexaValue;

    bool disposed;

public:

    HEXADECIMAL_API ValueType __stdcall GetType();

    HEXADECIMAL_API void __stdcall SetSize(int arg);

    HEXADECIMAL_API void __stdcall SetHexa(char * arg);

    HEXADECIMAL_API char * __stdcall GetHexa();

    HEXADECIMAL_API void __stdcall SetValue(string arg);

    HEXADECIMAL_API string __stdcall GetValue();

    HEXADECIMAL_API long __stdcall GetNumericValue();

    HEXADECIMAL_API string __stdcall GetRawValue();

    HEXADECIMAL_API void __stdcall HexaToValue();

    HEXADECIMAL_API void __stdcall ValueToHexa();

    HEXADECIMAL_API __stdcall StrHexaDecimal();

    HEXADECIMAL_API void __stdcall DisposeHexaValue();

    HEXADECIMAL_API __stdcall ~StrHexaDecimal();
};

class ColumnDefinition
{
public:

    enum Order
    {
        ASC, DESC
    };

private:

    int startAt;

    int endAt;

    Order order;

    IHexaDecimal::ValueType type;

public:

    HEXADECIMAL_API void __stdcall SetRange(int start, int end);

    HEXADECIMAL_API int __stdcall GetRangeStart();

    HEXADECIMAL_API int __stdcall GetRangeEnd();

    HEXADECIMAL_API void __stdcall SetOrder(Order arg);

    HEXADECIMAL_API ColumnDefinition::Order __stdcall GetOrder();

    HEXADECIMAL_API void __stdcall SetType(IHexaDecimal::ValueType arg);

    HEXADECIMAL_API IHexaDecimal::ValueType __stdcall GetType();

    HEXADECIMAL_API ColumnDefinition * __stdcall Value(int arg1start, int arg2end, Order arg3order, IHexaDecimal::ValueType arg4type);

    HEXADECIMAL_API __stdcall ColumnDefinition();

    HEXADECIMAL_API __stdcall ~ColumnDefinition();
};

class Compare
{
private:

    vector<ColumnDefinition *> columns;

    IHexaDecimal * CastLeft(int arg, char * left);

    IHexaDecimal * CastRight(int arg, char * right);

public:

    HEXADECIMAL_API void __stdcall SetColumns(vector<ColumnDefinition *> arg);

    HEXADECIMAL_API bool __stdcall operator()(char * leftSide, char * rightSide);
};

class HexaTable
{
private:

    vector<ColumnDefinition *> columns;

    char * rawTableData;

    vector<vector<IHexaDecimal *>> table;

public:

    HEXADECIMAL_API void __stdcall AddColumn(ColumnDefinition * arg);

    HEXADECIMAL_API void __stdcall SetRawTableData(char * arg);

    HEXADECIMAL_API __stdcall HexaTable();

    HEXADECIMAL_API void __stdcall SetTable(int r, int c, IHexaDecimal * item);

    HEXADECIMAL_API vector<IHexaDecimal *> __stdcall GetRow(int r);

    HEXADECIMAL_API __stdcall HexaTable(int r, int c);

    HEXADECIMAL_API __stdcall ~HexaTable();
};