use crate::Vertex;

pub struct DSUVertex {
    parent: Vertex,
    size: usize,
}

pub struct DisjointSetUnion {
    vertices: Vec<DSUVertex>,
}

impl DisjointSetUnion {
    // Create n+1 sets [0, n]
    pub fn new(n: usize) -> Self {
        // Reserve memory space for n+1 vertices.
        let vertices: Vec<DSUVertex> = Vec::new();
        vertices.reserve_exact(n + 1);

        // Initialize n+1 disjoint set unions.
        for i in 0..=n {
            vertices.push(DSUVertex {
                parent: i as i32,
                size: 1 as usize,
            });
        }

        Self { vertices }
    }

    // Find the disjoint set the vertex belongs to. If none disjoint set the vertex belonging to,
    // return None.
    pub fn find_set(&self, ver: Vertex) -> Option<i32> {
        // Find the origin ancestor of ver recursively.
        let mut v = ver;
        // Keep counting how deep the recursion goes. Interrupt it when falls into an endless loop.
        let mut depth = 0;
        while (v != self.vertices[v as usize].parent)
            && (depth <= self.vertices.len())
        {
            v = self.vertices[v as usize].parent;
            depth += 1;
        }

        // If falls into endless recursion, return None.
        if depth > self.vertices.len() {
            None
        } else {
            Some(v)
        }
    }
}
