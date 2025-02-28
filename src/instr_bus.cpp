#include <memory>
#include <instruction.h>
#include <instruction_map.h>

Bus::Bus(std::vector<uint8_t> instr, uint16_t pc_starting)
{
    this->instr = instr;
    this->reset_vector = pc_starting;
}

void Bus::fill_instr(uint16_t new_pc)
{

    this->pc = new_pc;
    stored_instructions[0] = instr[(pc + 1) - reset_vector];
    stored_instructions[1] = instr[(pc - reset_vector)];
    pc_visited.insert(pc);
    // instr[this->pc - reset_vector] = 0x82;
    pc++;
}
uint16_t Bus::read_rom_mem(uint16_t mem_address)
{
    uint8_t byte1 = instr[(mem_address + 1) - reset_vector];
    uint8_t byte2 = instr[(mem_address)-reset_vector];
    return byte1 << 8 | byte2;
}
uint8_t Bus::get_instr()
{
    uint8_t current_instruction = stored_instructions[1];
    stored_instructions[1] = stored_instructions[0];
    stored_instructions[0] = instr[(this->pc + 1) - reset_vector];
    // instr[this->pc - reset_vector] = 0x82;
    pc_visited.insert(pc);
    std::cout << (pc_visited.find(pc) != pc_visited.end()) << std::endl;
    pc++;
    return current_instruction;
}
uint16_t Bus::get_pc()
{
    return this->pc;
}
void Bus::add_to_queue(uint16_t addr)
{
    // at a jump  or branch instr
    // what we will do is push the new PC into this queue
    // once we run out instructions or apporach RTS, or RTI we wil set the PC to a value in this queue
    // effectivelya allowing us to disassemble the branch
    uint16_t new_pc = addr;
    // printf("pc adding to quue: 0x%x instr at the addr: 0x%x \n", new_pc, instr[new_pc - reset_vector]);
    // printf("%d \n", InstructionValid(instr[new_pc - reset_vector]));
    if (pc_visited.find(new_pc) == pc_visited.end())
    {
        pc_queue.push_back(addr);
    }
}
uint16_t Bus::get_next_queue()
{
    if (pc_queue.size() == 0)
    {
        return 0;
    }
    uint16_t new_pc = pc_queue[0];
    pc_queue.erase(pc_queue.begin());
    if (pc_visited.find(new_pc) != pc_visited.end())
    {
        printf("rejected: %x \n", new_pc);
        return get_next_queue();
    }
    printf("accepted: %x \n", new_pc);

    return new_pc;
}