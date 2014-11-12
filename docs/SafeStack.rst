=========
SafeStack
=========

.. contents::
   :local:

Introduction
============

SafeStack is an instrumentation pass to LLVM, which separates the
program stack into a safe stack, which stores return addresses,
register spills, and local variables that are statically verified
to be accessed in a safe way, and the unsafe stack, which stores
everything else. Such separation makes it much harder for an attacker
to corrupt objects on the safe stack, including function pointers
stored in spilled registers and return addresses. You can find more
information about the safe stack, as well as other parts of or
control-flow hijack protection technique in our OSDI paper on
code-pointer integrity (http://dslab.epfl.ch/pubs/cpi.pdf) and our
project website (http://levee.epfl.ch).

Typical slowdown introduced by MemorySanitizer is **1.05x**.

How to build
============

Follow the `clang build instructions <../get_started.html>`_. CMake
build is supported.

Usage
=====

Simply compile and link your program with ``-fsafe-stack`` flag.
The SafeStack run-time library should be linked to the final
executable, so make sure to use ``clang`` (not ``ld``) for the final
link step.

``__has_feature(safe_stack)``
-----------------------------

In some cases one may need to execute different code depending on
whether SafeStack is enabled. :ref:`\_\_has\_feature
<langext-__has_feature-__has_extension>` can be used for this purpose.

.. code-block:: c

    #if defined(__has_feature)
    #  if __has_feature(safe_stack)
    // code that builds only under SafeStack
    #  endif
    #endif

``__attribute__((no_safe_stack))``
----------------------------------

Some code should not be instrumented by SafeStack.
One may use the function attribute
:ref:`no_safe_stack <langext-safe_stack>`
to disable SafeStack instrumentation in a particular function.
SafeStack may still instrument such functions to avoid false positives.
This attribute may not be
supported by other compilers, so we suggest to use it together with
``__has_feature(safe_stack)``.

Supported Platforms
===================

SafeStack is supported on

* Linux
* FreeBSD
* MacOSX

Current Status
==============

SafeStack is an experimental tool. It is known to work on large
real-world programs, like the FreeBSD packages, chromium, ...

More Information
================

`http://levee.epfl.ch/ <http://levee.epfl.ch/>`_

