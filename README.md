# Prelude
Prelude contains a subset of Chromium source. It builds following low-level components:

|Category|Library|
|:--|:--|
|Framework|base.dll|
|IPC support| ipc.dll, mojo_core.dll, service.dll|
|Rendering| gles2.dll, skia.dll|
|UI|aura.dll, views.dll|

The components **not** included are mainly browser related (e.g., *//content* and *Blink*) or Chrome OS specific (e.g., *//ash*). Because the goal is to make Prelude a compact codebase that's useful for developing general purpose applications. That being said, v8 Javascript engine is included for some additional fun.

Prelude also provides examples on how to use Chromium code. Please refer to [this github page](https://xzwang2005.github.io/Prelude/) for details.