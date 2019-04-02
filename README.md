# QtLayerShell

This library provides support for the
[layer-shell](https://github.com/swaywm/wlr-protocols/blob/master/unstable/wlr-layer-shell-unstable-v1.xml)
Wayland extension protocol.

## Usage

`QtLayerShell/LayerView` is the primary entry point to this library, and your
`QWindow` should be a class which derives from it. Review the header for its
usage. An example is available in the `demo` directory.

**Note**

In order for this to work correctly, you must set some environment variables
before initializing your `QGuiApplication`.

```cpp
qputenv("QT_QPA_PLATFORM", QByteArray("wayland"));
qputenv("QT_WAYLAND_SHELL_INTEGRATION", QByteArray("layer-shell"));
```

We are not able to do this for you.

**Note**

This utilizes private QtWaylandClient APIs and it may break between Qt versions.

## Installation

```
meson build
ninja -C build
sudo ninja install
```

Consult the [meson documentation](http://mesonbuild.com/Running-Meson.html) if
you have special needs.
