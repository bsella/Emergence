# Emergence
Generate bitmaps using nodes.

![Alt text](https://i.imgur.com/dY8D2aa.png)

## Nodes
Nodes are blocks that can be connected to each other to dynamically implement functions in GUI. A node can have at most one output.

To connect a node to another, simply drag one of its sockets and drop it on another node.

## Data Types
Data types are converted automatically.

Numbers by default are used between 0 and 1. They are converted to gray scale when color is used. Numbers higher or equal to 1 are converted to true, false otherwise.

[True, False] boolean values correspond to [white, black] and [1, 0].

Colors are converted to numbers by using its luminance.

---

Compile using `qmake` then `make`.

Feel free to send your feedback on `karim.salama@univ-tlse3.fr`
