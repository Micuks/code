pub mod disjoint_set_union;
pub mod utils;

use disjoint_set_union::DisjointSetUnion;
use std::{
    cmp::Ordering,
    collections::BinaryHeap,
    fmt::Display,
    fs::File,
    io::{self, Read, Write as IoWrite},
    path::Path,
    time::Instant,
};

#[cfg(feature = "debug")]
use std::fmt::Write as fmtWrite;

#[allow(unused)]
use utils::cli_parser;

/**
 * Macros written for debug purpose.
 *
 * If debug output is needed, add --features debug flag in rustc compilation.
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

type Weight = i32;
type Vertex = i32;

#[derive(PartialEq, Eq, Ord, Clone)]
struct Edge {
    a: Vertex,
    b: Vertex,
    weight: Weight,
}

// Implement PartialEq for MinHeap.
impl PartialOrd for Edge {
    // Reverse from greater first to lesser first.
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        // First compare a and b's weight.
        let mut result = self
            .weight
            .partial_cmp(&other.weight)
            .map(|ord| ord.reverse());
        // If they have the same weight, compare their vertex a.
        if result == Some(Ordering::Equal) {
            result = self.a.partial_cmp(&other.a).map(|ord| ord.reverse());
            // If they have the same vertex a, compare vertex b.
            if result == Some(Ordering::Equal) {
                return self.b.partial_cmp(&other.b).map(|ord| ord.reverse());
            }

            return result;
        }

        result
    }
}

impl Edge {
    // Implement constructor for Edge.
    fn new(a: Vertex, b: Vertex, weight: Weight) -> Self {
        Self { a, b, weight }
    }
}

impl Display for Edge {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {}): {}", self.a, self.b, self.weight)
    }
}

impl Default for Edge {
    fn default() -> Self {
        Self {
            a: 0,
            b: 0,
            weight: 0,
        }
    }
}

struct Kruskal {
    v: i32,
    _e: i32,
    weight_sum: Weight,
    edges: Vec<Edge>,
    edges_in_mst: Vec<Edge>,
}

impl Kruskal {
    // Kruskal constructor
    pub fn new(v: i32, e: i32, edges: Vec<Edge>) -> Self {
        Self {
            v,
            _e: e,
            weight_sum: 0,
            edges,
            edges_in_mst: Vec::new(),
        }
    }

    pub fn kruskal_mst(&mut self) -> i32 {
        let mut heap: BinaryHeap<Edge> = BinaryHeap::new();

        // Push all edges into MinHeap.
        for e in &self.edges {
            heap.push(e.clone());
        }

        let mut connected_branches = DisjointSetUnion::new(self.v as usize);

        // Merge time counter.
        let mut merge_cnt = 0;
        while !heap.is_empty() && merge_cnt < self.v - 1 {
            let e = heap.pop().expect("Failed to pop from min heap.");

            // Two endpoints of e doesn't in the same connected branches.
            if connected_branches.merge(e.a, e.b) < Vertex::MAX {
                // Increase merge count, Add weight of edge to MST's weight sum.
                merge_cnt += 1;
                self.weight_sum += e.weight;

                // Append newly inserted edge to edges_in_mst for Debug.
                self.edges_in_mst.push(e);
            }
        }

        self.weight_sum
    }

    #[cfg(feature = "debug")]
    pub fn edges_in_mst_to_string(&self) -> String {
        let mut s: String = String::new();
        for e in &self.edges_in_mst {
            write!(s, "({}, {}): {}\n", e.a, e.b, e.weight)
                .expect("Error writing edges in mst to string.");
        }

        s
    }
}

fn read_edges_from_file(filename: String) -> Option<(i32, i32, Vec<Edge>)> {
    let v: i32;
    let e: i32;
    let mut edges: Vec<Edge> = Vec::new();

    let path = Path::new(&filename);
    let display = path.display();
    println!("Load edges from file: {}", display);
    // Load lines of file to String.
    let mut file = File::open(filename).expect("Error opening file.");
    let mut contents = String::new();
    file.read_to_string(&mut contents)
        .expect("Error reading file.");
    let mut lines = contents.lines();

    let new_line = lines.next();
    // Read first line.
    let v_and_e: Vec<&str> = match new_line {
        Some(new_line) => new_line.split(" ").collect(),
        None => {
            println!("Error reading V and E.");
            Vec::new()
        }
    };
    v = v_and_e[0].parse::<i32>().expect("Error reading V.");
    e = v_and_e[1].parse::<i32>().expect("Error reading e.");

    // Read edges line by line.
    for line in lines {
        // Print line for debug.
        // println!("{}", line);
        let vec: Vec<&str> = line.split(" ").collect();

        // Stop reading lines when there's not enough values.
        if vec.len() < 3 {
            break;
        }

        let str2num =
            |x: &str| (x.parse::<i32>().expect("Error reading value."));
        let ver_a: i32 = str2num(vec[0]);
        let ver_b: i32 = str2num(vec[1]);
        let wgt: i32 = str2num(vec[2]);

        // Construct and push new edge to edges.
        let edge = Edge::new(ver_a, ver_b, wgt);
        edges.push(edge);

        // Print edges for debugging.
        // for edge in &edges {
        //     println!("{}", edge);
        // }
    }

    Some((v, e, edges))
}

fn write_weight_sum_to_file(
    filename: String,
    kruskal: &Kruskal,
) -> io::Result<()> {
    let path = Path::new(&filename);
    let display = path.display();

    println!("Write to file: {}", display);

    // Write to file, then return write result.
    let mut file = File::create(&filename)?;

    write!(file, "{}\n", kruskal.weight_sum)
}

fn main() {
    let mut in_file: String = "data/kruskal.in".to_string();
    let mut out_file: String = "data/kruskal_rs.out".to_string();
    (in_file, out_file) = cli_parser(in_file, out_file);
    let (e, v, edges) = read_edges_from_file(in_file)
        .expect("Error occurred during unpacking e, v and edges from file.");

    // It's illegal to specify source vertex in Kruskal.
    #[allow(unused)]
    let source = 1;

    let mut kruskal = Kruskal::new(v, e, edges);
    // Measure the elapsed time of kruskal algorithm.
    let begin = Instant::now();
    let distance = kruskal.kruskal_mst();
    let duration = begin.elapsed().as_secs_f64();
    println!("[Kruskal RUST] Time measured: {:?} seconds.", duration);

    // Print the edges in MST.
    debug!("{} edges in Kruskal MST:", &kruskal.edges_in_mst.len());
    debug!("{}", kruskal.edges_in_mst_to_string());

    // Print the weight sum of Kruskal MST.
    println!("Weight sum of MST:\n{}", distance);

    // Write the weight sum to out file.
    write_weight_sum_to_file(out_file, &kruskal)
        .expect("Failed to write weight sum to file.");
}
