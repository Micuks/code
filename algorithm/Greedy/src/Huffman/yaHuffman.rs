use std::{collections::HashMap, fs::File, io::Read, path::Path};

struct Node {
    identifier: Option<i32>,
    freq: f64,
    // Use option to represent null node equal to NULL in C++.
    left: Option<Box<Node>>,
    right: Option<Box<Node>>,
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
fn assign_codes(p: &Box<Node>, h: &mut HashMap<i32, String>, s: String) {
    // If the char field of a node is not None, then it is a leaf node.
    // Insert it and its huffman code to the HashMap.
    if let Some(identifier) = p.identifier {
        h.insert(identifier, s);
    } else {
        if let Some(ref l) = p.left {
            assign_codes(l, h, s.clone() + "0");
        }
        if let Some(ref r) = p.right {
            assign_codes(r, h, s.clone() + "1");
        }
    }
}

// Convert huffman codes to string.
fn codes_to_string(
    freq_map: &mut HashMap<i32, f64>,
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
fn get_expectation(
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

    let size: i32 = lines.next().unwrap().parse::<i32>().unwrap();

    // Read the file contents into freq_map.
    let mut idx: i32 = 0;
    for freq in lines.next().unwrap().split(" ") {
        freq_map.insert(idx, freq.parse::<f64>().unwrap());
        idx += 1;
    }

    assert!(freq_map.len() == size.try_into().unwrap());

    println!("Freq_map loaded: {:?}", freq_map);

    freq_map
}

fn main() {
    let in_file: String = "data/huffman/huffman.in".to_owned();
    let mut freq_map = load_freq_map_from_file(in_file);

    // Put <k, v> from hashmap to vector.
    let mut p: Vec<Box<Node>> = freq_map
        .iter()
        .map(|x| new_box(new_node(*(x.1), Some(*(x.0)))))
        .collect();

    // Build the huffman tree.
    while p.len() > 1 {
        p.sort_by(|a, b| (b.freq).partial_cmp(&(a.freq)).unwrap());
        let a = p.pop().unwrap();
        let b = p.pop().unwrap();
        let mut c = new_box(new_node(a.freq + b.freq, None));
        c.left = Some(a);
        c.right = Some(b);
        p.push(c);
    }

    // Get root of huffman tree.
    let root = p.pop().unwrap();

    // Create the huffman code.
    let mut code_map: HashMap<i32, String> = HashMap::new();
    assign_codes(&root, &mut code_map, "".to_string());

    println!("{}", codes_to_string(&mut freq_map, &mut code_map));
    println!(
        "Expectation: {}",
        get_expectation(&mut freq_map, &mut code_map)
    );
}
