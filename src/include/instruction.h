#include <iostream>
#include <vector>
#include <RomUtil.h>
#include <stdint.h>
#include <map>
#include <unordered_set>

#ifndef ADDRESS_MODE_H
#define ADDRESS_MODE_H
enum AddressMode
{
    ACCUMULATOR,
    ABSOLUTE,
    ABSOLUTE_Y,
    ABSOLUTE_X,
    ZERO_PAGE,
    ZERO_PAGE_X,
    ZERO_PAGE_Y,
    IMMEDIATE,
    INDIRECT,
    INDIRECT_X,
    INDIRECT_Y,
    RELATIVE,
    IMPLIED
};
#endif

#ifndef BUS_H
#define BUS_H
class Bus
{
public:
    uint8_t stored_instructions[2];
    std::vector<uint8_t> instr;
    std::unordered_set<uint16_t> pc_visited;
    std::vector<uint16_t> pc_queue;
    uint16_t reset_vector;
    uint16_t pc;

    Bus(std::vector<uint8_t> instr, uint16_t pc_starting);
    uint8_t get_instr();
    uint16_t get_pc();
    uint16_t get_next_queue();
    void add_to_queue(uint16_t addr);
    void fill_instr(uint16_t new_pc);

    uint16_t read_rom_mem(uint16_t mem_address);
};
#endif

#ifndef DIS_ASM_STATE_H
#define DIS_ASM_STATE_H
struct DisAsmState
{
    Bus bus;
    std::map<uint16_t, std::string> known_lables;
    std::map<uint16_t, std::string> assembled;
    int label;
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
    uint16_t pc;
    instr();
    instr(uint16_t pc);
    virtual std::string disassm() = 0;
};

#endif
#ifndef LABEL_H
#define LABEL_H

class Label : public instr
{
public:
    std::string name;
    uint16_t pc;
    Label(std::string name, uint16_t pc);
    std::string disassm() override;
};
#endif

#ifndef LDA_H
#define LDA_H

class Lda : public instr
{
public:
    std::vector<uint8_t> opcodes;
    uint16_t pc;
    AddressMode addressMode;
    Lda();
    Lda(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc);
    std::string disassm() override;
};

#endif

#ifndef JMP_h
#define JMP_h

class Jmp : public instr
{
public:
    std::vector<uint8_t> opcodes;
    uint16_t pc;
    AddressMode addressMode;
    std::string lable_name;
    Jmp();
    Jmp(AddressMode addressMode, std::string lable, uint16_t pc);
    Jmp(AddressMode addressMode, std::vector<uint8_t> opcodes, uint16_t pc);
    std::string disassm() override;
};
#endif

#ifndef RTI_h
#define RTI_h

class Rti : public instr
{
public:
    std::vector<uint8_t> opcodes;
    uint16_t pc;
    AddressMode addressMode;
    std::string lable_name;
    Rti(AddressMode addressMode, uint16_t pc);
    std::string disassm() override;
};
#endif

#ifndef DEFINED_BYTE_H
#define DEFINED_BYTE_H

class DefinedByte : public instr
{
public:
    // std::vector<uint8_t> opcodes;
    uint16_t pc;
    uint8_t byte;
    // AddressMode addressMode;
    // std::string lable_name;
    DefinedByte(uint8_t byte, uint16_t pc);
    std::string disassm() override;
};
#endif

// #ifndef PRGRAM_H
// #define PROGRAM_H
// class Program
// {
// public:
//     Header header;
//     std::vector<instr> instrunctions;

//     Program(Header header, std::vector<instr> instrunctions);
//     std::string disassm();
// };
// #endif