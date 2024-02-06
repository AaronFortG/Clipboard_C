# PracticaSO
Integrated Clipboard Manager program.

Author: **Aaron Fort Garcia**

Program end date: **6th February, 2024**

---

## 1. Program's operations
> These are the available operations that can be handled in the Clipboard:

* ### TYPE [text]
  Insert a text (of maximum 50 characters) after the current cursor's position.

* ### SELECT [start_index] [end_index]
  Select the characters of the current text (_text[start_index] ... text[end_index]_, inclusive indices, 0-based) of length
  end_index - start_index + 1.

* ### MOVE_CURSOR [offset]
  Change the cursor's position. The <offset> specifies the direction and the value change - a negative value moves the cursor
  to the left, and a positive value moves it to the right.

* ### COPY
  Add the text from the selected area to the clipboard. If no area is selected, do nothing.

* ### PASTE (steps_back)
  Insert the copied text from the clipboard. The  number <steps_back> indicates which of the stored copied texts to insert.
  If <steps_back> is 1 then insert the last copied text, if it is 2 then insert the text copied before the last, and so on

* ### EXIT
  Finish the execution of the Clipboard's program.

_Take into account that the clipboard's cursor in the text is shown as an underscore_ ( _ ).

---

## 2. Program's execution
> There are a few ways to execute the program quickly with some default input parameters; optionally, valgrind can be run to.

**Clipboard execution without parameters without valgrind**
````sh
make run-clipboard
````

**Clipboard execution with parameters without valgrind**
````sh
make run-clipboard-args
````

**Clipboard execution with valgrind and without parameters**
````sh
make check-clipboard
````

**Clipboard execution with valgrind and parameters**
````sh
make check-clipboard-args
````
If a normal execution is desired, the following command can be executed:
```sh
./Clipboard ["Operation1 arguments", "Operation2 arguments"...]
```

## 3. Program modules (Project structure)
> The code has been properly moduled for each operation that can be handled in the Clipboard.
The hierarchy of the code is the following:
* **/clipboard** - Modules related to the clipboard itself.
  * **`/clipboard_operations`**
    * Each module that represents a different operation of the clipboard.
    
* **/libraries** - External functions that are used and complement the Clipboard's program.