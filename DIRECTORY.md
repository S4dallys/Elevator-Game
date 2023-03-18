# TABLE OF CONTENTS
---
## Headers 
> [main.h](./main.h)
>
> - [UNDER CONSTRUCTION!]()

> [global.h](global.h) (not finished)
>
> - contains every header known to man, include this if you really don't like reading the individual headers we made sadge :(

> [ansi.h](./ansi.h)
>
> - credit: [INSERT LINK!]()
> - contains ANSI codes for the 8 basic colors (most terminal-compatible).
> - **ex.** `#define RED "\e[0;31m"` which turns output red!

> [bool.h](./bool.h)
>
> - nothing special, just contains the macros `TRUE` and `FALSE` (1 and 0).

> [color.h](./color.h)
>
> - has the hardcoded macros for each graphical character, as well as functions related to rendering color.
> - **ex.** [INSERT EXAMPLES!]()

> [coordinates.h](./coordinates.h)
>
> - contains the `COORD` and `SIZE` classes.
> - also had functions related to getting and returning data related to coordinates or dimensions.

> [E_string.h](./E_string.h)
>
> - contains aliases for different string types.
> - **ex.** `STRING10` and `DIALOGUE_LG` meaning string with 10 char and a long-ass 500 char flavor text respectively.

> [file.h](./file.h)
>
> - [UNDER CONSTRUCTION!]()

> [keypress.h](./keypress.h)
>
> - contains macros for the different keypresses!
> - includes stuff like `W_KEY` meaning 'w' and `W_KEY_SHF` meaning 'shift + w'.

> [object.h](./object.h)
>
> - contains the `OBJECT` class (and related functions) which defines an object in-game whether it's an elevator, or a piece of glass on the floor.
> - the `OBJECT` class is a combination of both `COORD` and `SIZE` classes.

> [player.h](./player.h)
>
> - [UNDER CONSTRUCTION!]()

> [room.h](./room.h)
>
> - contains the `ROOM` class and useful functions related to rooms. 
> - `ROOM` defines a playfield and is the building block for a `LEVEL`. [UPDATE THIS!]()
---
## CLASSES

### 1. Object-related 
- these are classes related to the creation and display of tangible 'object' in the game window, like chairs, windows, lore-items, etc.  

> **OBJECT**
> - alias: *ELEVATOR*, *DIM*
> ```
> COORD coord; 
> SIZE size; 

> **COORD**
> - alias: *none*
> - structurally the same as `SIZE`
> ```
> int row;
> int col; 

> **SIZE**
> - alias: *none*
> ```
> int width;
> int height; 

> **ROOM**
> - alias: *ELEVATOR_ROOM*, *SECRET_ROOM*
> ```
> STRING10 file;
> int floor;
> int roomNo;
> DIM dim;

---


