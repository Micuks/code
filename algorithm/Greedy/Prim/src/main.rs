pub mod utils;
use std::{
    collections::{BinaryHeap, HashSet},
    fs::File,
    io::{self, Read, Write},
    path::Path,
    time::Instant,
};

use crate::utils::cli_parser;

#[derive(Clone, Copy)]
struct Edge {
    to: i32,
    weight: i32,
}

fn read_graph_from_file(filename: String) -> (i32, i32, Vec<Vec<Edge>>) {
    let path = Path::new(&filename);
    let display = path.display();
    println!("Load from file: {}", display);
    let mut file = File::open(filename).expect("Error opening file.");

    // Get lines from file.
    let mut contents = String::new();
    file.read_to_string(&mut contents)
        .expect("Error reading file.");
    let mut lines = contents.lines();

    let v: i32;
    let e: i32;
    let new_line = lines.next();
    // Get first line and handle error.
    let first_line: Vec<&str> = match new_line {
        Some(new_line) => new_line.split(" ").collect(),
        None => {
            println!("Error reading V and E.");
            Vec::new()
        }
    };
    // Read V and E from file.
    v = first_line[0].parse::<i32>().expect("Error reading V.");
    e = first_line[1].parse::<i32>().expect("Error reading E.");

    // adj_list[i] collects edges starting from vertex i.
    let mut adj_list: Vec<Vec<Edge>> = vec![vec![]; (v + 1) as usize];
    // println!("adj_list[{}]", adj_list.capacity());

    for line in lines {
        // println!("{}", line);

        let vec: Vec<&str> = line.split(" ").collect();
        // Stop reading when line doesn't match the input requirement.
        if vec.len() < 3 {
            break;
        }

        let ver_a: i32 = vec[0]
            .parse::<i32>()
            .expect("Error reading vertex {vec[0]}");
        let ver_b: i32 = vec[1]
            .parse::<i32>()
            .expect("Error reading vertex {vec[1]}");
        let wei: i32 = vec[2]
            .parse::<i32>()
            .expect("Error reading weight {vec[2]}");

        // Create edge and append to vertex a's adjacent list.
        let edges_a = &mut adj_list[ver_a as usize];
        edges_a.push(Edge {
            to: ver_b,
            weight: wei,
        });

        // Create edge and append to vertex b's adjacent list.
        adj_list[ver_b as usize].push(Edge {
            to: ver_a,
            weight: wei,
        });
    }

    // Print adjacent lists to debug.
    // for i in 1..e {
    //     println!("{}: edges:", i);
    //     // Borrow edge from adj_list.
    //     for &edge in &adj_list[i as usize] {
    //         println!("to[{}], weight[{}]", edge.to, edge.weight);
    //     }
    // }

    (v, e, adj_list)
}

#[derive(PartialEq, Eq, Ord)]
struct State {
    distance: i32,
    vertex: i32,
}

// Implement ParitialOrd for State for MinHeap.
impl PartialOrd for State {
    // Reverse from greater fist to lesser first.
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.distance
            .partial_cmp(&other.distance)
            .map(|ord| ord.reverse())
    }
}

// Return end vertex ,weight sum and edges in Prim MST.
fn prim(adj: &Vec<Vec<Edge>>, source: i32, v: i32) -> (i32, i32, Vec<Edge>) {
    type Vertex = i32;
    type Distance = i32;
    // Memorize end vertex in MST.
    let mut end: Vertex = source;
    // Accumulate MST weight sum.
    let mut weight_sum: i32 = 0;

    // Edges in Prim MST for debug.
    let mut edges_in_mst: Vec<Edge> = Vec::new();

    // Initialize states of all vertices.
    let mut dists: Vec<Distance> = Vec::new();
    dists.extend((0..v + 1).into_iter().map(|_| i32::MAX));

    // Initialize state of source's distance to 0 and push source into Minheap.
    let mut heap: BinaryHeap<State> = BinaryHeap::new();
    // Get ownership of distance of vertex source.
    let dis = &mut dists[source as usize];
    *dis = 0;
    heap.push(State {
        distance: *dis,
        vertex: source,
    });

    // Collect vertices that are already in MST to avoid adding a point twice.
    let mut mst: HashSet<Vertex> = HashSet::new();

    // Build MST.
    while !heap.is_empty() {
        // stat gets top vertex's ownership.
        let stat = heap.pop().expect("Error picking top vertex from heap.");

        // Skip vertices already in MST.
        if mst.contains(&(stat.vertex)) {
            continue;
        }

        mst.insert(stat.vertex);
        // Memorize the end vertex.
        end = stat.vertex;
        weight_sum += stat.distance as i32;

        // Iterate through current state vertex's edges.
        let edges = &adj[stat.vertex as usize];
        for edge in edges {
            let neighbor_ver = edge.to;
            let neighbor_dist = &mut dists[edge.to as usize];
            if *neighbor_dist > edge.weight {
                *neighbor_dist = edge.weight;
            }
            heap.push(State {
                distance: *neighbor_dist,
                vertex: neighbor_ver,
            });
        }
    }

    (end, weight_sum)
}

fn write_distance_to_file(filename: &String, distence: &i32) -> io::Result<()> {
    let path = Path::new(&filename);
    let display = path.display();

    println!("Write to file: {}", &display);

    // Try to create new file {filename}.
    let mut file = File::create(&filename)?;
    write!(file, "{}\n", distence)
}

fn main() {
    let mut in_file: String = "data/prim.in".to_string();
    let mut out_file: String = "data/prim_rs.out".to_string();
    (in_file, out_file) = cli_parser(in_file, out_file);
    let (v, _e, adj_list) = read_graph_from_file(in_file);
    // Compute Prim MST cost whose source is vertex 1.
    let source: i32 = 1;

    // Measure the time elapsed of prim algorithm.
    let begin = Instant::now();
    let (_end, distance) = prim(&adj_list, source, v);
    // Record the elapsed time in seconds.
    let elapsed = begin.elapsed().as_secs_f64();
    println!("[Prim RUST] Time measured: {:?} seconds.", elapsed);
    // Error handler
    println!("{}", distance);

    // Write result to out file.
    let ok = write_distance_to_file(&out_file, &distance);
    if ok.is_err() {
        panic!(
            "Panicked to write result[{}] to file [{}]",
            distance, &out_file
        );
    }
}
