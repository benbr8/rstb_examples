use std::env::var;
use bindgen;

fn main() {

    let manifest_dir = var("CARGO_MANIFEST_DIR").unwrap();
    dbg!(&manifest_dir);

    let vl_path;
    if let Ok(p) = var("VL_PATH") {
        vl_path = p; 
    } else {
        vl_path = "/usr/local/share/verilator".to_string();
    }
    println!("cargo:rustc-link-search={}/verilator", manifest_dir);
    println!("cargo:rustc-link-search={}/include", vl_path);
    println!("cargo:rustc-link-lib=static=wrapper");
    println!("cargo:rustc-link-lib=static=dut");

    
    let bindings = bindgen::Builder::default()
        .header("verilator/wrapper.cpp")
        .clang_arg(&format!("-I{}/include", vl_path))
        .clang_arg(&format!("-I{}/include/vltstd", vl_path))
        .clang_arg("-Iverilator/vl_obj")
        .clang_arg("-x").clang_arg("c++")
        .allowlist_function("vl_init")
        .allowlist_function("vl_finalize")
        .allowlist_function("get_signal_by_name")
        .allowlist_function("vl_get_root_handle")
        .allowlist_function("vl_got_finish")
        .allowlist_function("vl_get_time")
        .allowlist_function("vl_set_time")
        .allowlist_function("vl_print_scope")
        .generate()
        .unwrap();
    bindings.write_to_file(&format!("{}/src/vdff.rs", manifest_dir)).unwrap();
}