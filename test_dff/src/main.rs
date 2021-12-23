mod vdff;

use librstb::prelude::*;


async fn test(_dut: SimObject) -> RstbResult {
    for j in 0..10 {
        Trigger::timer_steps(1).await;
        dbg!(SIM_IF.get_sim_time_steps());
    }
    
    Ok(Val::None)
}

librstb::run_with_verilator!(test);