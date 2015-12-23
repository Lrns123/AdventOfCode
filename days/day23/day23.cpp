#include <iostream>
#include <vector>
#include <regex>

class VM
{
public:
    enum OpCode { HLF, TPL, INC, JMP, JIE, JIO, INVALID };

private:
    struct Instruction
    {
        OpCode op;
        int operands[2];
    };

    unsigned m_registers[2];
    unsigned m_pc;
    std::vector<Instruction> m_instructions;

public:
    explicit VM()
        : m_registers{0}, m_pc(0)
    {}

    void addInstruction(OpCode op, int operand1 = 0, int operand2 = 0)
    {
        m_instructions.push_back({ op, operand1, operand2 });
    }

    void run(unsigned regA = 0, unsigned regB = 0)
    {
        m_pc = 0;
        m_registers[0] = regA;
        m_registers[1] = regB;
        
        while (step()) {}
    }

    unsigned getRegister(unsigned idx) const
    {
        return idx > 1 ? 0 : m_registers[idx];
    }

    void setRegister(unsigned idx, unsigned value)
    {
        if (idx < 2) m_registers[idx] = value;
    }

    bool step()
    {
        if (m_pc >= m_instructions.size())
            return false;

        auto &ins = m_instructions[m_pc];
        switch (ins.op)
        {
            case HLF: m_registers[ins.operands[0]] >>= 1, ++m_pc; break;
            case TPL: m_registers[ins.operands[0]] *= 3;  ++m_pc; break;
            case INC: ++m_registers[ins.operands[0]];     ++m_pc; break;
            case JMP: m_pc += ins.operands[0];                    break;
            case JIE: m_pc += m_registers[ins.operands[0]] % 2 == 0 ? ins.operands[1] : 1; break;
            case JIO: m_pc += m_registers[ins.operands[0]] == 1 ? ins.operands[1] : 1;     break;
            default: return false;
        }
        return true;
    }
};

VM::OpCode opcodeForString(const char *str)
{
    static const char *opcodeNames[]{ "hlf", "tpl", "inc", "jmp", "jie", "jio" };

    for (auto it = std::begin(opcodeNames), eit = std::end(opcodeNames); it != eit; ++it)
        if (strcmp(*it, str) == 0)
            return VM::OpCode(it - std::begin(opcodeNames));
    
    return VM::INVALID;
}

int main(int, char **)
{
    static const std::regex inputRegex("(\\w+) (a|b|[-+]\\d+)?(?:, ([-+]\\d+))?");
    VM vm;

    std::string line;
    while (getline(std::cin, line))
    {
        std::smatch match;
        if (regex_match(line, match, inputRegex))
        {
            auto op = opcodeForString(match[1].str().c_str());
            if (op == VM::INVALID)
                std::cout << "Invalid opcode: " << match[1] << std::endl;
            else
            {
                int operand1 = !match[2].matched ? 0 : match[2].length() == 1 ? match[2].str().front() - 'a' : stoi(match[2]);
                int operand2 = !match[3].matched ? 0 : match[3].length() == 1 ? match[3].str().front() - 'a' : stoi(match[3]);

                vm.addInstruction(op, operand1, operand2);
            }
        }
        else
            std::cout << "Could not parse line '" << line << '\'' << std::endl;
    }

    vm.run();
    std::cout << "Value of register b (a = 0): " << vm.getRegister(1) << std::endl;
    
    vm.run(1);
    std::cout << "Value of register b (a = 1): " << vm.getRegister(1) << std::endl;
}
