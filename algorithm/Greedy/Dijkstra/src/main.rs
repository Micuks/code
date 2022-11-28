pub mod utils;
use std::{
    cmp::Ordering,
    collections::BinaryHeap,
    fs::File,
    io::{self, Read, Write},
    path::Path,
};

use crate::utils::cli_parser;

#[derive(Clone, Copy)]
struct Edge {
    node: i32,
    dis: i32,
}

// Derive Copy, Clone, PartialEq and Eq for Ord and PartialOrd of State.
#[derive(Clone, Copy, PartialEq, Eq)]
struct State {
    dis: i32,
    position: i32,
}

// Implement Ord for priority queue.
// To let it be a min-heap.
impl Ord for State {
    fn cmp(&self, other: &Self) -> Ordering {
        other
            .dis
            .cmp(&self.dis)
            .then_with(|| self.position.cmp(&other.position))
    }
}

// Implement PartialOrd for Orf of State
impl PartialOrd for State {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}

fn dijkstra(adj_list: &Vec<Vec<Edge>>, begin: i32, end: i32) -> Option<i32> {
    // dist[node] = current shortest distance from begin to node.
    let mut dist: Vec<_> = (0..adj_list.len()).map(|_| i32::MAX).collect();

    let mut heap = BinaryHeap::new();

    dist[begin as usize] = 0;
    heap.push(State {
        dis: 0,
        position: begin,
    });

    while let Some(State { dis, position }) = heap.pop() {
        // If reaches end node, return. Else can stay here and find shortest way to all
        // nodes.
        if position == end {
            return Some(dis);
        }

        // If an shorter way already exists, skip this state.
        if dis > dist[position as usize] {
            continue;
        }

        for edge in &adj_list[position as usize] {
            let next_node = State {
                dis: dis + edge.dis,
                position: edge.node,
            };

            if next_node.dis < dist[next_node.position as usize] {
                heap.push(next_node);
                dist[next_node.position as usize] = next_node.dis;
            }
        }
    }

    // Return none if end node not reached.
    None
}

fn read_graph_from_file(filename: String) -> (i32, i32, Vec<Vec<Edge>>) {
    let path = Path::new(&filename);
    let display = path.display();

    println!("Load from file: {}", display);

    let mut file = File::open(filename).unwrap();
    let mut contents = String::new();
    file.read_to_string(&mut contents).unwrap();
    let mut lines = contents.lines();

    let v: i32;
    let e: i32;
    let first_line: Vec<&str> = lines.next().unwrap().split(" ").collect();
    v = first_line[0].parse::<i32>().unwrap();
    e = first_line[1].parse::<i32>().unwrap();

    // adj_list[i] collects edges starting from node i.
    let mut adj_list: Vec<Vec<Edge>> = vec![vec![]; (v + 1) as usize];
    println!("adj_list[{}]", adj_list.capacity());

    for line in lines {
        println!("{}", line);

        let vec: Vec<_> = line.split(" ").collect();

        let node_a: i32 = vec[0].parse::<i32>().unwrap();
        let node_b: i32 = vec[1].parse::<i32>().unwrap();
        let dist: i32 = vec[2].parse::<i32>().unwrap();

        let edges_a: &mut Vec<Edge> = &mut adj_list[node_a as usize];
        edges_a.push(Edge {
            node: node_b,
            dis: dist,
        });

        adj_list[node_b as usize].push(Edge {
            node: node_a,
            dis: dist,
        })
    }

    for i in 1..e {
        println!("{}: edges:", i);
        for &mut edge in &mut adj_list[i as usize] {
            println!("To[{}], Len[{}]", edge.node, edge.dis);
        }
        println!("");
    }

    (v, e, adj_list)
}

fn write_shortest_distance_to_file(
    filename: String,
    distance: i32,
) -> io::Result<()> {
    let path = Path::new(&filename);
    let display = path.display();

    println!("Write to file: {}", display);

    let mut file = File::create(filename)?;
    write!(file, "{}\n", distance)
}

fn main() {
    let mut in_file: String = "data/dijkstra.in".to_owned();
    let mut out_file: String = "data/dijkstra.out".to_owned();
    (in_file, out_file) = cli_parser(in_file, out_file);
    let (v, _e, adj_list) = read_graph_from_file(in_file);
    let result = dijkstra(&adj_list, 1, v);
    println!("{:?}", result);
    let distance: i32;
    match result {
        // If node[e] cannot be reached from node[1], assign 1 to distance.
        None => distance = -1,
        Some(result) => {
            distance = result;
        }
    }

    let ok = write_shortest_distance_to_file(out_file.clone(), distance);
    if ok.is_err() {
        panic!(
            "Panicked to write result[{}] to file[{}]",
            distance,
            out_file.clone()
        );
    }
}
