#include <verilated.h> // Defines common routines
#include <verilated_vpi.h> // Defines common routines
#include <iostream> // Need std::cout
#include "Vdff.h" // From Verilating "top.v"



extern "C" void vpi_entry_point(void);


Vdff *dut = nullptr;

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

extern "C" void get_signal_by_name(void) {
    const VerilatedScope* scopep;
    const VerilatedVar* varp = nullptr;
    const char* baseNamep = "d";
    
    scopep = Verilated::threadContextp()->scopeFind("TOP");
    // std::cout << scopep << std::endl;
    // if (scopep) varp = scopep->varFind(baseNamep);
    // std::cout << varp << std::endl;

    const VerilatedScopeNameMap* scopeMapP = Verilated::threadContextp()->scopeNameMap();
    
    std::cout << scopeMapP->empty() << std::endl;
    for (auto it = scopeMapP->begin(); it != scopeMapP->end(); it++)
    {
        std::cout << it->first    // string (key)
                << ':'
                << it->second   // string's value 
                << ':'
                << (int)it->second->type()
                << std::endl;

        const VerilatedScope* ScopeP = it->second;
        auto VarsP = ScopeP->varsp();
        for (auto it = VarsP->begin(); it != VarsP->end(); it++) {
            std::cout << it->first << ':';
            print_var(&it->second);
        }
    }

}

vluint64_t main_time = 0; // Current simulation time
// This is a 64-bit integer to reduce wrap over issues and
// allow modulus. This is in units of the timeprecision
// used in Verilog (or from --timescale-override)

double sc_time_stamp() { // Called by $time in Verilog
    return main_time; // converts to double, to match
}


extern "C" void vl_init() {
    // Verilated::debug(99);
    dut = new Vdff; // Create model
}

extern "C" void vl_finalize() {
    dut->final();
    delete dut;
}

// int main(int argc, char** argv) {
//     Verilated::commandArgs(argc, argv); // Remember args
//     Verilated::debug(99);
//     dut = new Vdff; // Create model
//     get_signal_by_name();
//     vpi_entry_point();
//     dut->rstn = 0;

//     while (!Verilated::gotFinish()) {
//         dut->eval(); // Evaluate model
//         // if (main_time > 10) {
//         //     dut->rstn = 1; // Deassert reset
//         // }
//         // if ((main_time % 10) == 1) {
//         //     dut->clk = 1; // Toggle clock
//         // }
//         // if ((main_time % 10) == 6) {
//         //     dut->clk = 0;
//         //     dut->d = !dut->d;
//         // }
//         // if (main_time % 1 == 0) {
//         //     int a = dut->q;
//         //     std::cout << "main_time:" << main_time << ": " << a << std::endl; // Read a output
//         // }

//         vluint64_t next_time = main_time+1;
//         if (next_time == static_cast<vluint64_t>(~0ULL)) {
//             vl_finish(__FILE__, __LINE__, "");
//             break;
//         } else {
//             main_time = next_time;
//         }
//     }
//     dut->final(); // Done simulating
//     // // (Though this example doesn't get here)
//     delete dut;
// }
