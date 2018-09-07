# Emergence
Generate bitmaps using nodes.

![uk.emrg](https://image.ibb.co/eCYhey/uk2.png)
![lol.emerg](https://i.imgur.com/dY8D2aa.png)
![mandelbrot.emrg](https://i.imgur.com/1fQAxWw.png)

For more information check out the [wiki](https://github.com/bsella/Emergence/wiki).

---

# Building Emergence
For now, Emergence is supported only on the GNU/Linux system. To build it you will need `cmake` and the `Qt5Widgets` library.

It's highly recommended to build out of the source directory. For example, type the following commands:

    $ mkdir build
	$ cd build
	$ cmake ..
	$ make

---

Feel free to send your feedback to `karim.salama@univ-tlse3.fr`

---

TODO:
- [ ] Navigate/Zoom
  - [x] Zoom
  - [ ] Navigate
- [x] File oriented
- [x] Clipboard
- [x] Undo/Redo
  - [x] Add
  - [x] Remove
  - [x] Connect
  - [x] Disconnect
  - [x] Move
  - [ ] Change Constant
  - [ ] Change Image
  - [ ] Change/rename Function
- [x] Multiple outputs
- [x] Destructors
- [ ] Transparancy support
- [x] Functions
  - [x] Function Manager
  - [x] New save format
  - [x] Adapt with latest optimisation (pixel ID)
  - [x] Draw FunctionNodes
- [ ] Recursive Functions
- [x] New save format
- [ ] Data structures and lists
- [x] Preventing cycles
- [x] More icons
- [ ] Auto-arrange
- [ ] Options
- [ ] Command line
- [ ] Documentation
- [x] Modularity (Plugin system)
