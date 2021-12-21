use std::env::var;
use bindgen;

fn main() {
    let manifest_dir = var("CARGO_MANIFEST_DIR").unwrap();
    dbg!(&manifest_dir);
    println!("cargo:rustc-link-search={}/verilator", manifest_dir);
    println!("cargo:rustc-link-search=/usr/local/share/verilator/include");
    println!("cargo:rustc-link-lib=static=dff");
    println!("cargo:rustc-link-lib=static=vl");

    
    let bindings = bindgen::Builder::default()
        .header("verilator/dff.cpp")
        .clang_arg("-I/usr/local/share/verilator/include")
        .clang_arg("-I/usr/local/share/verilator/include/vltstd")
        .clang_arg("-Iverilator/dff_obj")
        .clang_arg("-x").clang_arg("c++")
        .allowlist_function("vl_init")
        .allowlist_function("vl_finalize")
        .allowlist_function("get_signal_by_name")
        .generate()
        .unwrap();
    bindings.write_to_file(&format!("{}/src/vdff.rs", manifest_dir)).unwrap();
}