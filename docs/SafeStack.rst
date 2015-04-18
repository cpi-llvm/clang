=========
SafeStack
=========

.. contents::
   :local:

Introduction
============

SafeStack is an instrumentation pass that protects programs against attacks
based on stack-based buffer overflows, without introducing any measurable
performance overhead. It works by separating the program stack into two
distinct regions: the safe stack and the unsafe stack. The safe stack stores
return addresses, register spills, and local variables that are always accessed
in a safe way, while the unsafe stack stores everything else. This separation
ensures that buffer overflows on the unsafe stack cannot be used to overwrite
anything on the safe stack, which includes return addresses.

Performance
-----------

The performance overhead of the SafeStack instrumentation is less than 0.1% on
average on SPEC 2006 benchmarks. Most small functions do not have any variables
that require the unsafe stack and, hence, do not need unsafe stack frames to be
created. The cost of creating unsafe stack frames for large functions is
amortized by the cost of executing the function.

In some cases, SafeStack actually improves the performance. Objects that end up
being moved to the unsafe stack are usually large arrays or variables that are
used through multiple stack frames. Moving such objects away from the safe
stack increases the locality of frequently accessed values on the stack, such
as register spills, return addresses, and small local variables.

Compatibility
-------------

Most programs, static or shared libraries, or individual files can be compiled
with SafeStack as is. SafeStack requires basic runtime support, which, on most
platforms, is implemented as a compiler-rt library that is automatically linked
in when the program is compiled with SafeStack. On some platforms, the runtime
is integrated directly into libc, which enables certain low-level performance
optimizations.

Known compatibility limitations
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Certain code that relies on low-level stack manipulations requires adaption to
work with SafeStack. One example is mark-and-sweep garbage collection
implementations for C/C++ (e.g., Oilpan in chromium/blink), which must be
changed to look for the live pointers on both safe and unsafe stacks.

SafeStack supports linking together modules that are compiled with and without
SafeStack, both statically and dynamically. One corner case that is not
supported is using dlopen() to load a dynamic library that uses SafeStack into
a program that is not compiled with SafeStack but uses threads.

Signal handlers that use ``sigaltstack()`` must not use the unsafe stack (see
``__attribute__((no_safe_stack))`` below).

Programs that use APIs from ``ucontext.h`` are not supported yet.

Usage
=====

To enable SafeStack, just pass ``-fsafe-stack`` flag to both compile and link
command lines.

Supported Platforms
-------------------

SafeStack was tested on Linux, FreeBSD and MacOSX.

Low-level API
-------------

``__SAFESTACK__``
~~~~~~~~~~~~~~~~~

In some rare cases one may need to execute different code depending on whether
SafeStack is enabled. The define ``__SAFESTACK__`` can be used for this
purpose.

.. code-block:: c

    #ifdef __SAFESTACK__
    // code that builds only under SafeStack
    #endif

``__attribute__((no_safe_stack))``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Use ``__attribute__((no_safe_stack))`` on a function, variable or class
declaration to specify that the safe stack instrumentation should not be
applied to that declaration, even if enabled globally.  This attribute may be
required for functions that make assumptions about the exact layout of their
stack frames, or variables or classes used as stack location markers.

``__builtin___get_unsafe_stack_ptr()``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This builtin function returns current unsafe stack pointer of the current
thread.

``__builtin___get_unsafe_stack_start()``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

This builtin function returns a pointer to the start of the unsafe stack of the
current thread.

Design
======

Please refer to
`http://dslab.epfl.ch/proj/cpi/ <http://dslab.epfl.ch/proj/cpi/>`_ for more
information about the design of the SafeStack and its related technologies.


Publications
------------

`Code-Pointer Integrity <http://dslab.epfl.ch/pubs/cpi.pdf>`_.
Volodymyr Kuznetsov, Laszlo Szekeres, Mathias Payer, George Candea, R. Sekar, Dawn Song.
USENIX Symposium on Operating Systems Design and Implementation
(`OSDI <https://www.usenix.org/conference/osdi14>`_), Broomfield, CO, October 2014
