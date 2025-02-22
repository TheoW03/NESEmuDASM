#include <iostream>
#include <vector>
#include <RomUtil.h>
#include <stdint.h>
#ifndef BUS_H
#define BUS_H
class Bus
{
public:
    uint8_t stored_instructions[2];
    std::vector<uint8_t> instr;
    uint16_t reset_vector;
    uint16_t pc;
    Bus(std::vector<uint8_t> instr, uint16_t pc_starting);
    uint8_t get_instr();
    void fill_instr(uint16_t new_pc);
};
#endif
#ifndef HEADER_DISASM_H
#define HEADER_DISASM_H
class Header
{
public:
    NESHeader header;
    Header(NESHeader header);
    std::string disassm();
};
#endif
#ifndef INSTR_H
#define INSTR_H

class instr
{
public:
    instr();
    virtual std::string disassm() = 0;
};
#ifndef LDA_H
#define LDA_H
class Lda : public instr
{
public:
    std::vector<uint8_t> opcodes;
    Lda();
    Lda(std::vector<uint8_t> opcodes);
    std::string disassm() override;
};

#endif

#endif
#ifndef PRGRAM_H
#define PROGRAM_H
class Program
{
public:
    Header header;
    std::vector<instr> instrunctions;

    Program(Header header, std::vector<instr> instrunctions);
    std::string disassm();
};
#endif