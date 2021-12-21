mod vdff;

use librstb::prelude::*;






fn main() {
    unsafe {
        vdff::vl_init();
        vdff::get_signal_by_name();
        vdff::vl_finalize();
    }
}