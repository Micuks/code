pub mod utils;
use std::{
    collections::HashMap,
    fs::File,
    io::{self, Read, Write},
    path::Path,
    time::Instant,
};
use utils::cli_parser;

/**
 * Marcros written for debug log.
 */
#[cfg(feature = "debug")]
macro_rules! debug {
    ($($args: expr), *) => {
        println!($($args), *);
    };
}

#[cfg(not(feature = "debug"))]
macro_rules! debug {
    ($($args: expr), *) => {};
}

struct Node {
    identifier: Option<i32>,
    freq: f64,
    // Use option to represent null node equal to NULL in C++.
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
}

impl Node {
    #[allow(unused)]
    pub fn to_string(&self) -> String {
        let mut sstream = "".to_string();
        match self.identifier {
            Some(_) => {
                sstream += &("(".to_string()
                    + &self.identifier.unwrap().to_string()
                    + ", "
                    + &self.freq.to_string()
                    + ")");
            }
            None => {
                sstream += "<NULL>";
            }
        }

        sstream
    }
}

fn new_node(f: f64, iden: Option<i32>) -> Node {
    Node {
        identifier: iden,
        freq: f,
        left: None,
        right: None,
    }
}

fn new_box(n: Node) -> Box<Node> {
    Box::new(n)
}

// Assign huffman code to leaves in huffman tree.
#[cfg(feature = "debug")]
fn assign_codes(p: &Box<Node>, s: String) -> String {
    let mut sstream = "".to_string();
    // If the char field of a node is not None, then it is a leaf node.
    // Insert it and its huffman code to the HashMap.
    if let Some(ref l) = p.left {
        sstream += &(assign_codes(l, s.clone() + "0"));
    }
    if let Some(ref r) = p.right {
        sstream += &(assign_codes(r, s.clone() + "1"));
    }
    if let Some(_identifier) = p.identifier {
        sstream.push_str(&p.to_string());
        sstream += ": ";
        sstream.push_str(&s);
        sstream += "\n";
    }

    sstream
}

#[cfg(not(feature = "debug"))]
fn assign_codes(_p: &Box<Node>, _s: String) -> String {
    _s
}

// Convert huffman codes to string.
#[cfg(feature = "debug")]
#[allow(unused)]
fn codes_to_string(
    freq_map: &HashMap<i32, f64>,
    code_map: &mut HashMap<i32, String>,
) -> String {
    let mut s = String::new();
    for (key, value) in code_map.into_iter() {
        s.push_str("(");
        s.push_str(&(key.to_string()));
        s.push_str(", ");
        s.push_str(&((freq_map.get(key)).unwrap().to_string()));
        s.push_str("): ");
        s.push_str(&(value.to_string()));
        s.push_str("\n");
    }

    s
}

// Calculate huffman code length expectation
#[allow(unused)]
#[cfg(feature = "debug")]
fn get_expectation_from_maps(
    freq_map: &mut HashMap<i32, f64>,
    code_map: &mut HashMap<i32, String>,
) -> f64 {
    let mut exp: f64 = 0.0;
    for (key, value) in code_map.into_iter() {
        let freq = freq_map.get(key).unwrap();
        exp += freq * (String::len(value) as f64);
    }

    exp
}

fn get_expectation(
    freq_map: &HashMap<i32, f64>,
    root: &Box<Node>,
    depth: i32,
    exp: &mut f64,
) -> f64 {
    // If the char field of a node is node None, then it is a leaf node.
    // Accumulate the value calculated by multiplying its frequency and code length.
    if let Some(_) = root.identifier {
        *exp += depth as f64 * root.freq;
    } else {
        if let Some(ref l) = root.left {
            get_expectation(freq_map, l, depth + 1, exp);
        }
        if let Some(ref r) = root.right {
            get_expectation(freq_map, r, depth + 1, exp);
        }
    }

    *exp
}

fn load_freq_map_from_file(filename: String) -> HashMap<i32, f64> {
    // The HashMap used to store identifiers and corresponding frequencies.
    let mut freq_map: HashMap<i32, f64> = HashMap::new();

    // Create a path to the desired file.
    let path = Path::new(&filename);
    let display = path.display();

    println!("Load from file: {}", display);

    // Load lines of file to String.
    let mut file = File::open(filename).unwrap();
    let mut contents = String::new();
    file.read_to_string(&mut contents).unwrap();
    let mut lines = contents.lines();

    let size: usize = lines.next().unwrap().parse::<usize>().unwrap();

    // Read the file contents into freq_map.
    let freqs: Vec<&str> = lines.next().unwrap().split(" ").collect();
    for i in 0..size {
        let freq: String = String::from(freqs[i]);
        freq_map.insert(i.try_into().unwrap(), freq.parse::<f64>().unwrap());
    }

    assert!(freq_map.len() == size.try_into().unwrap());

    // println!("Freq_map loaded: {:?}", freq_map);

    freq_map
}

fn write_expectation_to_file(
    filename: String,
    expectation: f64,
) -> io::Result<()> {
    let path = Path::new(&filename);
    let display = path.display();

    println!("Write to file: {}", display);

    let mut file = File::create(filename)?;
    write!(file, "{:.3}\n", expectation)
}

fn main() -> io::Result<()> {
    let mut in_file: String = "data/huffman/huffman.in".to_owned();
    let mut out_file: String = "data/huffman/huffman_rs.out".to_owned();
    (in_file, out_file) = cli_parser(in_file, out_file);

    let freq_map = load_freq_map_from_file(in_file);

    // Put <k, v> from hashmap to vector.
    let mut p: Vec<Box<Node>> = freq_map
        .iter()
        .map(|x| new_box(new_node(*(x.1), Some(*(x.0)))))
        .collect();

    // Measure the elapsed time of Huffman algorithm.
    let begin = Instant::now();

    // Build the huffman tree.
    while p.len() > 1 {
        p.sort_unstable_by(|a, b| (b.freq).partial_cmp(&(a.freq)).unwrap());
        let a = p.pop().unwrap();
        let b = p.pop().unwrap();
        let mut c = new_box(new_node(a.freq + b.freq, None));
        c.left = Some(a);
        c.right = Some(b);
        p.push(c);
    }

    // Get root of huffman tree.
    let root = p
        .pop()
        .unwrap_or_else(|| panic!("Failed to get huffman root."));

    // Create the huffman code.
    let _code_string = assign_codes(&root, "".to_string());
    debug!("{}", _code_string);

    let mut exp: f64 = 0.0;
    exp = get_expectation(&freq_map, &root, 0, &mut exp);
    let elapsed = begin.elapsed().as_secs_f64();

    // Print the elapsed time of Huffman algorithm.
    println!("[Huffman RUST] Time measured: {} seconds.", elapsed);

    // println!("{}", codes_to_string(&mut freq_map, &mut code_map));
    println!("Expectation:\n{:.3}", exp);

    // Write expectation to file.
    write_expectation_to_file(out_file, exp)
}
