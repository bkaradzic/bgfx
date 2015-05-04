# Vertex Cache Optimised Index Buffer Compression

This is a small proof of concept for compressing and decompressing index buffer triangle lists. It's designed to maintain the order of the triangle list and perform best with a triangle list that has been vertex cache post-transform optimised (a pre-transform cache optimisation is done as part of the compression).

It's also designed to be relatively lightweight, with a decompression throughput in the tens of millions of triangles per core.  It does not achieve state of the art levels of compression levels (which can be less than a bit per triangle, as well as providing good chances for vertex prediction), but it does maintain ordering of triangles and support arbitrary topologies. 

There are some cases where the vertices within a triangle are re-ordered, but the general winding direction is maintained.

## How does it work?

The inspiration was a mix of Fabian Giesen's [Simple loss-less index buffer compression](http://fgiesen.wordpress.com/2013/12/14/simple-lossless-index-buffer-compression/) and
the higher compression algorithms that make use of shared edges and re-order triangles. The idea was that there is probably a middle ground between them.

The basic goals were:

* Maintain the ordering of triangles, exploiting vertex cache optimal ordering.

* Exploit recent triangle connectivity.

* Make it fast, especially for decompression, without the need to maintain large extra data structures, like winged edge.

* Make it simple enough to be easily understandable. 

The vertex cache optimisation means that there will be quite a few vertices and edges shared between the next triangle in the list and the previous. We exploit this by maintaining two relatively small fixed size FIFOs, an edge FIFO and a vertex FIFO (not unlike the vertex cache itself, except we store recent indices).

The compression relies on 4 codes: 

1. A _new vertex_ code, for vertices that have not yet been seen. 

2. A _cached edge_ code, for edges that have been seen recently. This code is followed by a relative index back into the edge FIFO.

3. A _cached vertex_ code, for vertices that have been seen recently. This code is followed by a relative index back into the vertex FIFO.

4. A _free vertex_ code, for vertices that have been seen, but not recently. This code is followed by a variable length integer encoding of the index relative to the most recent new vertex.

Triangles can either consist of two codes, a cached edge followed by one of the vertex codes, or of 3 of the vertex codes. The most common codes in an optimised mesh are generally the cached edge and new vertex codes.

Cached edges are always the first code in any triangle they appear in and may correspond to any edge in the original triangle (we check all the edges against the FIFO). This means that an individual triangle may have its vertices specified in a different order (but in the same winding direction) than the original uncompressed one.

New vertex codes work because vertices are re-ordered to the order in which they appear in the mesh, meaning whenever we encounter a new vertex, we can just read and an internal counter to get
the current index, incrementing it afterwards. This has the benefit of also meaning vertices are in pre-transform cache optimised order.

## Does it actually work?

That's a better question! While my thoughts were that in theory it would average around 11-12bits a triangle, the Stanford Armadillo mesh (optimised with Tom Forsyth's vertex cache optimisation algorithm), with 345944 triangles, compresses the index buffer down to 563122 bytes, which is more like 13 and the Stanford Bunny is 12.85bits or so. This is not anywhere near the state of the art in terms of compression (which get down to less than a bit), but that isn't the goal.

Performance wise, with the code posted here, the Armadillo compresses in 18.5 milliseconds and decompresses in 6.6 milliseconds on average on my system. The Stanford bunny is more like 1.4 milliseconds to decompress, relatively.

## Update!

I've added a second more efficient (in terms of both speed and size) compression algorithm (CompressIndexBuffer2 and DecompressIndexBuffer2), as well as some changes upstream from Branimir Karadžić, who made some compiler compatibility fixes and added 16bit indice support. This uses a code per triangle instead of multiple codes for different cases.

For details of the original algorithm, please see this [blog post](http://conorstokes.github.io/graphics/2014/09/28/vertex-cache-optimised-index-buffer-compression/). For details of the second algorithm, please see this [blog post](http://conorstokes.github.io/graphics/2014/09/28/vertex-cache-optimised-index-buffer-compression/). 

