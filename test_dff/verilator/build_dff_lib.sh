if [[ -z "${VL_PATH}" ]]; then
  VL_PATH_INT="/usr/local/share/verilator"
else
  MY_SCRIPT_VARIABLE="${VL_PATH}"
fi

verilator -Mdir vl_obj --prefix Dut -cc ../hdl/dff.v ../hdl/not.v
clang++ -DVL_DEBUG -c -o verilated.o -I vl_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ ${VL_PATH}/include/verilated.cpp
clang++ -DVL_DEBUG -c -o verilated_vpi.o -I vl_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ ${VL_PATH}/include/verilated_vpi.cpp
# clang++ -flto -DVL_DEBUG -c -o Vdff.o -I dff_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ dff_obj/Vdff.cpp
# clang++ -flto -DVL_DEBUG -c -o Vdff___024root__Slow.o -I dff_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ dff_obj/Vdff___024root__Slow.cpp
# clang++ -flto -DVL_DEBUG -c -o Vdff__Syms.o -I dff_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ dff_obj/Vdff__Syms.cpp
# clang++ -flto -DVL_DEBUG -c -o Vdff___024root__DepSet_h998c48f4__0.o -I${VL_PATH}/include/vltstd -I dff_obj -I${VL_PATH}/include/ dff_obj/Vdff___024root__DepSet_h998c48f4__0.cpp
# clang++ -flto -DVL_DEBUG -c -o Vdff___024root__DepSet_h998c48f4__0__Slow.o -I${VL_PATH}/include/vltstd -I dff_obj -I${VL_PATH}/include/ dff_obj/Vdff___024root__DepSet_h998c48f4__0__Slow.cpp
# clang++ -flto -DVL_DEBUG -c -o dff.o -I dff_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ dff.cpp 

cd vl_obj
make -f Dut.mk
cd ..

clang++ -DVL_DEBUG -c -o wrapper.o -Ivl_obj -I${VL_PATH}/include/vltstd -I${VL_PATH}/include/ wrapper.cpp 
ar rcs libwrapper.a wrapper.o verilated.o verilated_vpi.o
cp vl_obj/Dut__ALL.a libdut.a


# ar rcs libdff.a \
#     # verilated.o \
#     verilated_vpi.o \
#     Vdff.o \
#     Vdff___024root__Slow.o \
#     Vdff__Syms.o \
#     Vdff___024root__DepSet_h998c48f4__0.o \
#     Vdff___024root__DepSet_h998c48f4__0__Slow.o \
#     dff.o


# clang++ -flto -fuse-ld=lld -L../../target/release/ -ltest_dff -lpthread -ldl -o dff_incr -O2 \
#     verilated.o \
#     verilated_vpi.o \
#     Vdff.o \
#     Vdff___024root__Slow.o \
#     Vdff__Syms.o \
#     Vdff___024root__DepSet_h998c48f4__0.o \
#     Vdff___024root__DepSet_h998c48f4__0__Slow.o \
#     dff.o
    