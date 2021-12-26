mod vdff;

use librstb::prelude::*;


async fn clk_stim(clk: SimObject, ) -> RstbResult {
    loop {
        Trigger::timer_steps(5).await;
        SIM_IF.log("Setting clk to 1");
        clk.set(1);
        SIM_IF.log(&format!("checking clk: {}", clk.get()));
        Trigger::timer_steps(5).await;
        SIM_IF.log("Setting clk to 0");
        clk.set(0);
        SIM_IF.log(&format!("checking clk: {}", clk.get()));
    }
    Ok(Val::None)
}

async fn test_dff(dut: SimObject) -> RstbResult {
    // Fork clock input to run concurrently
    let clk = dut.c("clk");
    let d = dut.c("d");
    let q = dut.c("q");

    clk.set(1);
    dbg!(clk.get());
    Trigger::timer_steps(10).await;
    dbg!(clk.get());

    // Task::spawn(clk_stim(clk));

    for j in 0..10 {
        let din = utils::rand_int(2);
        d.set(din);
        dbg!(j);
        clk.rising_edge().await;
        if q.get() != din {
            fail_test("Q output did not match D input");
        }
    }

    pass_test("All transactions matched");
    Ok(Val::None)
}

librstb::run_with_verilator!(test_dff);