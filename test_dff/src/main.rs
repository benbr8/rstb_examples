mod vdff;

use librstb::prelude::*;

#[allow(unreachable_code)]
async fn clk_stim(clk: SimObject, ) -> RstbResult {
    loop {
        Trigger::timer_steps(5).await;
        clk.set(1);
        Trigger::timer_steps(5).await;
        clk.set(0);
    }
    Ok(Val::None)
}

async fn test_dff(dut: SimObject) -> RstbResult {
    let clk = dut.c("clk");
    let d = dut.c("d");
    let q = dut.c("q");

    // Fork clock input to run concurrently
    Task::spawn(clk_stim(clk));

    dut.c("rstn").set(1);

    for _ in 0..1_000_000 {
        let din = utils::rand_int(2);
        d.set(din);
        clk.rising_edge().await;
        if q.get() != din {
            fail_test("Q output did not match D input")
        }
    }

    pass_test("All transactions matched");
    Ok(Val::None)
}

librstb::run_with_verilator!(test_dff);