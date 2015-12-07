#pragma once
#include <vector>
#include <exception>

class InvalidGateException : public std::exception
{
public:
    InvalidGateException(const char *message) : exception(message) {}
};

class LogicGate
{
protected:
    std::vector<LogicGate *> m_inputs;
    unsigned int m_cached;

public:
    virtual ~LogicGate();
    unsigned short evaluate();
    void setInput(int idx, LogicGate *gate);
    void resetCache();

protected:
    LogicGate();
    virtual unsigned short doEvaluate() const = 0;
    
};

class ConstantGate : public LogicGate
{
    unsigned short m_value;
public:
    explicit ConstantGate(unsigned short value);

protected:
    unsigned short doEvaluate() const override;
};

class IdentityGate : public LogicGate
{
public:
    IdentityGate();

protected:
    unsigned short doEvaluate() const override;
};

class AndGate : public LogicGate
{
public:
    AndGate();

protected:
    unsigned short doEvaluate() const override;
};

class OrGate : public LogicGate
{
public:
    OrGate();

protected:
    unsigned short doEvaluate() const override;
};

class NotGate : public LogicGate
{
public:
    NotGate();

protected:
    unsigned short doEvaluate() const override;
};

class LShiftGate : public LogicGate
{
    unsigned short m_shift;
public:
    explicit LShiftGate(unsigned short shift);

protected:
    unsigned short doEvaluate() const override;
};

class RShiftGate : public LogicGate
{
    unsigned short m_shift;
public:
    explicit RShiftGate(unsigned short shift);

protected:
    unsigned short doEvaluate() const override;
};