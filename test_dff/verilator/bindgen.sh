# bindgen dff_obj/Vdff.h -o vdff.rs --no-layout-tests \
#     --allowlist-type Vdff \
#     -- -I/usr/local/share/verilator/include/ -Iobj_dir -x c++

bindgen dff.cpp -o ../src/vdff.rs --no-layout-tests \
    --allowlist-function get_dut \
    -- -I/usr/local/share/verilator/include/ -Iobj_dir -x c++