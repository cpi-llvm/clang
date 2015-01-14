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

SafeStack typically does not introduce any measurable performance
overhead.

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

``__SAFESTACK__``
-----------------

In some cases one may need to execute different code depending on
whether SafeStack is enabled. The define ``__SAFESTACK__`` can be
used for this purpose.

.. code-block:: c

    #ifdef __SAFESTACK__
    // code that builds only under SafeStack
    #endif

``__attribute__((no_safe_stack))``
----------------------------------

Use ``__attribute__((no_safe_stack))`` on a function or variable declaration
to specify that the safe stack instrumentation should not be applied to it,
even if enabled globally (see -fsafe-stack flag). This attribute may be
required for functions that make assumptions about the exact layout of their
stack frames.

Supported Platforms
===================

SafeStack is supported on

* Linux
* FreeBSD
* MacOSX

Current Status
==============

SafeStack is an experimental tool. It is known to work on large
real-world programs, many FreeBSD packages, chromium, ...

More Information
================

`http://levee.epfl.ch/ <http://levee.epfl.ch/>`_

