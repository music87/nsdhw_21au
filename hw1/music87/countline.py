#!/usr/bin/env python3

import os
script_text = """
import sys
import os.path

#sys.stdout.write('current python executable: {}\\n'.format(sys.executable))

if len(sys.argv) < 2:
    sys.stdout.write('missing file name\\n')
elif len(sys.argv) > 2:
    sys.stdout.write('only one argument is allowed\\n')
else:
    fname = sys.argv[1]
    if os.path.exists(fname):
        with open(fname) as fobj:
            lines = fobj.readlines()
        sys.stdout.write('{} lines in {}\\n'.format(len(lines), fname))
    else:
        sys.stdout.write('{} not found\\n'.format(fname))
"""

python_executable = os.environ.get("PYTHON_BIN")
if python_executable == "python0":
    print("exec: python0: not found")
    exit(-1)
else:
    os.execlp(python_executable, python_executable, '-c', script_text, __file__)

