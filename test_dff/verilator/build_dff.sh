rm -r dff_obj
verilator -Mdir dff_obj -cc ../hdl/dff.v
cd dff_obj
make -f Vdff.mk
cd ..

clang++ -DVL_DEBUG -c -o verilated.o -I dff_obj -I/usr/local/share/verilator/include/vltstd -I/usr/local/share/verilator/include/ /usr/local/share/verilator/include/verilated.cpp
clang++ -DVL_DEBUG -c -o verilated_vpi.o -I dff_obj -I/usr/local/share/verilator/include/vltstd -I/usr/local/share/verilator/include/ /usr/local/share/verilator/include/verilated_vpi.cpp
clang++ -DVL_DEBUG -c -o dff.o -Idff_obj -I/usr/local/share/verilator/include/vltstd -I/usr/local/share/verilator/include/ dff.cpp 


clang++ -fuse-ld=lld -L../../target/release/ -ltest_dff -lpthread -ldl -o dff_incr -O2 \
    dff_obj/Vdff__ALL.a \
    verilated.o \
    verilated_vpi.o \
    dff.o
    