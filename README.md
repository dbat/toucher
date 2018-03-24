# toucher
Modify date and/or time of file, directory or symlink, recursively (for Windows)

    Copyright(C) 2003-2010, PT SOFTINDO Jakarta
    email: aa _at_ softindo.net
    All rights reserved.

    toucher version: 1.0.3.1, build: 503
    created: 2003.09.27, last revised: 2016.10.08

    Synopsys:
        Modify date and/or time of file, directory or symlink, recursively

    Usage:
        toucher [ options ] files...

    Arguments:
        files (mandatory) : filename/mask to be processed (eg. C:\*.*)
        options (optional) : similar to those of UNIX touch utility

        Note for options:
        - must be prefixed with either single HYPHEN (-) or SLASH (/)
        - (mostly) case insensitive, -a is identical with /A
        - may be a toggle (switch) or may need additional argument
        - the later argument overrides or _toggles_ the previous one
          the switch turned off the second time you typed it in as argument
          thus a switch can be turned on and off, and on and off and on..

        Options/switches are:
        -a, -m    change a:access or m:modification time (default: both)
        -x        change creation time (Not too useful as you might think,
                  all apps and file operations use m:modification time)
        -c        DO create file if not exist (disables r:recursive)
        -d DATE   translate date string (see formats below)
        -e, -f    process only e:DIRS or f:FILES, or both (default)
        -h or -l  process SYMLINK/reparse point itself, not linked file
        -n        test-mode, do not do actual modification
        -o, -q    show o:options/arguments or q:quiet (unless error)
        -Q        be very quiet while processing files, don't show error
        -r FILE   get reference datetime from file/dir: FILE
        -s        recursive. process subdirs (disables c:create)
        -t STAMP  use time in format [[[CC]YY]MMDD]hhmm[.ss]
        -v        show version
        -y, -z    set only y:DATE or z:TIME, or both (default)
        --   stop parsing the next remaining arguments as opts/switches

        DATETIME formats:
        (note that delimiter is _important_ for date/month/year order)
            mm/dd/yy OR mm/dd/yyyy AND/OR hh:mm:ss - US
            yy.mm.dd OR yyyy.mm.dd AND/OR hh:mm:ss - ISO 8601
            dd-mm-yy OR dd-mm-yyyy AND/OR hh:mm:ss - Europe/Aus/Asia
            - 2 digits year: 1938 - 2037 (32 bits UNIX last epoch)
            - "DATE + TIME" must be delimited by exactly 1 space/tab

        TIMESTAMP fields:
           CC YY MMDD hhmm .ss
           - required fields: hhmm
           - unspecified fields will be set equal to current time

    Return code:
        number of files successfully processed set in ERRORLEVEL
    

Clarification about recursive option against sub directory:

The <code>recursive switch: -s</code> should have been denoted by <code>-r</code>, unfortunaltely it has been taken as <i>reference</i> in <code>POSIX touch</code>. Option/switch <code>-s</code> <b>is not used to specify target directory</b>. The program always operates in current directory.

Option recursive against subdir: <code>-s DIRNAMES...</code> will match all occurences of <code>DIRNAMES</code> recursively in <b>current directory</b>, <b>not</b> ALL files/dirs under subdirs <code>DIRNAMES</code>.

However seems weird, this is actually a consistent and predictable way; ones might wanted to do exactly like that,
and it's not possible to be achieved if the program gives leeway to <code>-s ACTUALLY_A_FILE</code> to process <code>ACTUALLY_A_FILE</code> as subdir, and match all files/dirs under it.

In fact the program doesn't care if they are subdirs or files at all, only the name (string) and the recursive switch (-s) that matters.

To match all files/dirs under subdir <code>DIRNAME</code> you can simply add wildcard after <code>DIRNAME</code> eg. <code>-s DIRNAME\\*</code>

