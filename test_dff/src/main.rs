mod vdff;

use librstb::prelude::*;


async fn test(dut: SimObject) -> RstbResult {
    dbg!(dut);
    dbg!(dut.name());
    let a = dut.c("q");
    dbg!(a);
    // dbg!(a.name());
    let b = dut.c("not_inst");
    dbg!(b);
    dbg!(b.name());

    a.set(1);
    dbg!(a.get());
    a.set(0);
    dbg!(a.get());
    for j in 0..10 {
        Trigger::timer_steps(1).await;
        dbg!(SIM_IF.get_sim_time_steps());
    }
    
    Ok(Val::None)
}

librstb::run_with_verilator!(test);