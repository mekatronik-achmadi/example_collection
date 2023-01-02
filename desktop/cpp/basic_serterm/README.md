# Cross Platform Serial Terminal

This small work show a cross platform Serial Terminal using various C++ GUI toolkit

The original works can be found here: https://github.com/yan9a/serial

## wxWidgets

Requirement: wxWidget (or in Linux you may wanna install wxGtk)

To compile, go to **wx** path and run command:

```sh
make
```

then to test run command:

```
./wxserterm
```

## Qt5

Requirement: Qt5 (only Core and GUI/Widgets modules, no need SerialPort)

To compile, go to **qt** path and run command:

```sh
qmake ./
make
```

then to test run command:

```
./qtserterm
```

## Gtk

Requirement: Gtk-3 (and its C++ wrapper called Gtkmm)

To compile, go to **gtkmm** path and run command:

```sh
make
```

then to test run command:

```
./gtkserterm
```

## Example

Here example of the program:

![images](images/serial.png?raw=true)
