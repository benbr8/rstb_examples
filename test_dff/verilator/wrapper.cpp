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

extern "C" uintptr_t vl_get_scope_handle_by_name(const char* name) {
    const VerilatedScope* scopep = Verilated::threadContextp()->scopeFind(name);
    return reinterpret_cast<uintptr_t>(scopep);
}

extern "C" const char* vl_get_root_scope_name() {
    return get_root_scope()->name();
}

extern "C" uintptr_t vl_get_root_scope_handle() {
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
    
    std::cout << var->name() << ':'
        << var->datap() << ':'
        << var->isPublicRW() << ':'
        << var->low(0) << ':'
        << var->high(0) << ':'
        << (int)var->vltype() << ':'
        << "end"
        << std::endl;
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