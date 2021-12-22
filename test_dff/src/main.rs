mod vdff;

use librstb::prelude::*;


async fn test() -> RstbResult {
    for j in 0..10 {
        dbg!(SIM_IF.get_sim_time_steps());
        Trigger::timer_steps(1).await;
    }
    
    Ok(Val::None)
}

librstb::run_with_verilator!(test);