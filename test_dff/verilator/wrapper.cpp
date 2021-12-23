#include <verilated.h> // Defines common routines
#include <verilated_vpi.h> // Defines common routines
#include <iostream> // Need std::cout
#include "Dut.h" // From Verilating "top.v"
#include <stdint.h>


Dut *dut = nullptr;

/*
 * SCOPES
 */

const VerilatedScope* get_root_scope() {
    const VerilatedScopeNameMap* mapp = Verilated::threadContextp()->scopeNameMap();
    const VerilatedScope* ret = nullptr;
    // 2nd scope is top-level module scope (first is 'TOP.TOP')
    int i = 0;
    for (const auto& it : *mapp) {
        if (i++ == 1) {
            ret = it.second;
            break;
        }
    }
    return ret;
}

extern "C" uintptr_t vl_get_scope_by_name(const char* name) {
    const VerilatedScope* scopep = Verilated::threadContextp()->scopeFind(name);
    return reinterpret_cast<uintptr_t>(scopep);
}

extern "C" const char* vl_get_root_scope_name() {
    return get_root_scope()->name();
}

extern "C" uintptr_t vl_get_root_scope() {
    return reinterpret_cast<uintptr_t>(get_root_scope());
}

extern "C" const char* vl_get_scope_name(uintptr_t handle) {
    const VerilatedScope* scopep = reinterpret_cast<const VerilatedScope*>(handle);
    return scopep->name();
}

extern "C" void vl_print_scope(const char* name) {
    const VerilatedScope* scopep = Verilated::threadContextp()->scopeFind(name);
    const VerilatedVarNameMap* varsp = scopep->varsp();
    std::cout << "Vars in " << name << std::endl;
    for (const auto& it : *varsp) {
        std::cout << it.first << std::endl;
    }
}

extern "C" void vl_print_scopes() {
    const VerilatedScopeNameMap* mapp = Verilated::threadContextp()->scopeNameMap();

    std::cout << "Scopes:" << std::endl;
    for (const auto& it : *mapp) {
        std::cout << "Scope: " << it.first << std::endl;
        for (const auto& it : *it.second->varsp()) {
            std::cout << "Var: " << it.first << std::endl;
        }
    }
}

/*
 * VARS
 */

void print_var(VerilatedVar* var) {
    std::cout << "Name: " << var->name() << std::endl;
    std::cout << "  Type: " << (int)var->vltype() << std::endl;
    std::cout << "  Dims: " << var->dims() << std::endl;
    std::cout << "  Elems0: " << var->elements(0) << std::endl;
    std::cout << "  entSize: " << var->entSize() << std::endl;
    std::cout << "  pubRW: " << var->isPublicRW() << std::endl;
}

extern "C" uintptr_t vl_get_var_by_name(uintptr_t scope, const char* name) {
    const VerilatedScope* scopep = reinterpret_cast<const VerilatedScope*>(scope);
    auto varp = scopep->varFind(name);
    // if (varp != nullptr) {
    //     print_var(varp);
    // }
    return reinterpret_cast<uintptr_t>(varp);
}

extern "C" const char* vl_get_var_name(uintptr_t handle) {
    auto varp = reinterpret_cast<const VerilatedVar*>(handle);
    return varp->name();
}

extern "C" uint8_t vl_get_var_type(uintptr_t var) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    return (uint8_t)varp->vltype();
}

// set values
extern "C" void vl_set_var_u8(uintptr_t var, uint8_t val) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint8_t*>(varp->datap());
    *datap = val;
}
extern "C" void vl_set_var_u16(uintptr_t var, uint16_t val) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint16_t*>(varp->datap());
    *datap = val;
}
extern "C" void vl_set_var_u32(uintptr_t var, uint32_t val) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint32_t*>(varp->datap());
    *datap = val;
}
extern "C" void vl_set_var_u64(uintptr_t var, uint64_t val) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint64_t*>(varp->datap());
    *datap = val;
}

// get values
extern "C" uint8_t vl_get_var_u8(uintptr_t var) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint8_t*>(varp->datap());
    return *datap;
}
extern "C" uint16_t vl_get_var_u16(uintptr_t var) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint16_t*>(varp->datap());
    return *datap;
}
extern "C" uint32_t vl_get_var_u32(uintptr_t var) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint32_t*>(varp->datap());
    return *datap;
}
extern "C" uint64_t vl_get_var_u64(uintptr_t var) {
    auto varp = reinterpret_cast<const VerilatedVar*>(var);
    auto datap = static_cast<uint64_t*>(varp->datap());
    return *datap;
}


/*
 * GEARS
 */

extern "C" void vl_init() {
    // Verilated::debug(99);
    dut = new Dut; // Create model
}

extern "C" void vl_eval() {
    dut->eval();
}

extern "C" void vl_finalize() {
    dut->final();
    delete dut;
}

extern "C" bool vl_got_finish() {
    return Verilated::gotFinish();
}


/*
 * TIME
 */

vluint64_t main_time = 0; // Current simulation time

double sc_time_stamp() { // Called by $time in Verilog
    return main_time; // converts to double, to match
}

extern "C" unsigned long vl_get_time() {
    return main_time;
}

extern "C" void vl_set_time(unsigned long t) {
    main_time = t;
}