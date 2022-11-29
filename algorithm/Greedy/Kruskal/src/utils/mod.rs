use std::collections::HashMap;
use std::env;
fn help_str() -> String {
    "Kruskal in Rust
    If no args are passed, will use default infile and outfile.
    usage:
    --help           show help info.
    --in <filename>  load from given file.
    --out <filename> save output to given file."
        .to_string()
}

/**
 * A simple Command Line Interface arguments parser to extract in file
 * and out file path from command line arguments.
 */
pub fn cli_parser(
    default_in_file: String,
    default_out_file: String,
) -> (String, String) {
    let args: Vec<String> = env::args().collect();
    let mut in_file = default_in_file.clone();
    let mut out_file = default_out_file.clone();

    match args.len() {
        // No args passed
        1 => {
            println!("{}", help_str());
        }
        // Illegal.
        2 => {
            println!("{}", help_str());
        }
        // Only in file or out file is given.
        3 => {
            let flag = &args[1];
            let attr = &args[2];
            if flag == "--in" {
                in_file = attr.clone();
            } else if flag == "--out" {
                out_file = attr.clone();
            } else {
                println!("{}", help_str());
            }
        }
        // Illegal.
        4 => {
            println!("{}", help_str());
        }
        // In file and out file are both specified.
        5 => {
            let mut args_map: HashMap<String, String> = HashMap::new();
            args_map.insert(args[1].clone(), args[2].clone());
            args_map.insert(args[3].clone(), args[4].clone());
            if !args_map.contains_key("--in") || !args_map.contains_key("--out")
            {
                println!("{}", help_str());
            }
            in_file = args_map.get("--in").unwrap().to_string();
            out_file = args_map.get("--out").unwrap().to_string();
        }
        _ => {
            println!("{}", help_str());
        }
    }
    (in_file, out_file)
}
