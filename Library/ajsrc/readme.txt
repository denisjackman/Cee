This archive contains the bits of source code that I, Andrew Jenner, have been
messing about with. Dave Clark's unmodified source is in the archive
dlcsrc.zip. Questions about the code in this archive should be directed to me,
andrew@reenigne.org

If you're interested in working on Sopwith you should join the Sopwith
developers' mailing list by visiting
  http://groups.yahoo.com/group/sopwith-dev/join

Andrew Jenner stuff:
  General stuff:
    README.TXT   - This file.
    MAKEFILE     - Make file. Works with Borland make. Doesn't work with GNU
                   make for reasons which escape me (please tell me if you
                   know). Don't know about other flavours of make.
    RESPONSE.RSP - Linker command line (response) file to link Sopwith. Works
                   with Borland TLINK 2.0.
    RESPONS2.RSP - Linker command line (response) file to link Sopwith 2. Works
                   with Borland TLINK 2.0.
    SOPWITH.PRJ  - Turbo C 2.01 project file for Sopwith.
    SOPWITH2.PRJ - Turbo C 2.01 project file for Sopwith 2.

  Code:
    SOPWITH.C    - Reverse engineered code for Sopwith.
    SOPWITH2.C   - Reverse engineered code for Sopwith 2.
    SOPWITH7.C   - File based on the code in dlcsrc.zip (not compilable).
    DEF.H        - Generic header file
    DEF7.H       - Header file for SOPWITH7.C
    SOPASM.ASM   - Assembler support routines, common to all three versions.
                   Works with A86.
    SOPASM.H     - Header file declaring the functions in SOPASM.ASM.
    GROUND.C     - Landscape height field, common to all three versions.
    SPRITES.C    - Graphics data, common to all three versions.
