# fastfetch for MyDOS

MyDOS user-binary port of fastfetch 2.71.0.

Upstream: https://github.com/fastfetch-cli/fastfetch
Upstream commit: 216d3b24f32871da92c630e19d49c67d7b5ca7ef
Upstream license: MIT, see LICENSE.

This port keeps the upstream module registry and printing pipeline shape while using only the MyDOS user API v3. It is freestanding ELF32 and has no libc dependency.

Usage:

    fastfetch
    fastfetch --no-logo
    fastfetch --structure Title:OS:Host:Shell:Colors
    set FASTFETCH_STRUCTURE=Title:OS:Host

Modules: Title, Separator, OS, Host, Kernel, Shell, Uptime, Packages, Break, Colors.
