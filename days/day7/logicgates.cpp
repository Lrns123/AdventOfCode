#include "logicgates.hpp"

LogicGate::LogicGate()
    : m_inputs(), m_cached(-1)
{
}

LogicGate::~LogicGate()
{
}

unsigned short LogicGate::evaluate()
{
    if (m_cached != -1)
        return m_cached;
    return m_cached = doEvaluate();
}

void LogicGate::setInput(int idx, LogicGate* gate)
{
    m_inputs[idx] = gate;
}

void LogicGate::resetCache()
{
    m_cached = -1;
}

ConstantGate::ConstantGate(unsigned short value)
    : m_value(value)
{
}

unsigned short ConstantGate::doEvaluate() const
{
    return m_value;
}

IdentityGate::IdentityGate()
{
}

unsigned short IdentityGate::doEvaluate() const
{
    if (!m_inputs[0])
        throw InvalidGateException("Identity gates need one input");

    return m_inputs[0]->evaluate();
}

AndGate::AndGate()
{
}

unsigned short AndGate::doEvaluate() const
{
    if (!m_inputs[0] || !m_inputs[1])
        throw InvalidGateException("And gates need two inputs");

    return m_inputs[0]->evaluate() & m_inputs[1]->evaluate();
}

OrGate::OrGate()
{
}

unsigned short OrGate::doEvaluate() const
{
    if (!m_inputs[0] || !m_inputs[1])
        throw InvalidGateException("Or gates need two inputs");

    return m_inputs[0]->evaluate() | m_inputs[1]->evaluate();
}

NotGate::NotGate()
{
}

unsigned short NotGate::doEvaluate() const
{
    if (!m_inputs[0])
        throw InvalidGateException("Not gates need one input");

    return (~m_inputs[0]->evaluate()) & 0xFFFF;
}

LShiftGate::LShiftGate(unsigned short shift)
    : m_shift(shift)
{
}

unsigned short LShiftGate::doEvaluate() const
{
    if (!m_inputs[0])
        throw InvalidGateException("Left shift gates need one input");

    return (m_inputs[0]->evaluate() << m_shift) & 0xFFFF;
}

RShiftGate::RShiftGate(unsigned short shift)
    : m_shift(shift)
{
}

unsigned short RShiftGate::doEvaluate() const
{
    if (!m_inputs[0])
        throw InvalidGateException("Right shift gates need one input");

    return (m_inputs[0]->evaluate() >> m_shift) & 0xFFFF;
}
