import subprocess
from pathlib import Path
from shutil import copyfile

import cppparser

from behave import given, when, then, step

@given(u'the user runs RAAT with "{filename}"')
def step_impl(context, filename):
    pathlib_file = Path(filename)
    relative_folder = Path("raat/behavetests/test_files", pathlib_file.stem)
    relative_file_path = relative_folder / filename

    context.generated_file = Path("test_files") / pathlib_file.stem / pathlib_file.stem / (pathlib_file.stem + ".ino")

    context.completedprocess = subprocess.run(
        ["python3", "raat_runner.py", "--make", str(relative_file_path)],
        cwd="../../",
        stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

@then(u'the process should have run successfully')
def step_impl(context):
    if context.completedprocess.returncode != 0:
        raise Exception("Process '{:s}'' returned error code {:d} (stderr '{:s}')".format(
            " ".join(context.completedprocess.args),
            context.completedprocess.returncode,
            context.completedprocess.stderr.decode("utf-8") or ""
            )
        )

@then(u'a sketch should have been created with {number} {param_type} parameters called "{name}"')
def step_impl(context, number, param_type, name):

    cpp_filename = (context.generated_file.stem + ".cpp")
    
    def node_filter_function(n):
        return Path(str(n.location.file)).name == cpp_filename

    copy = context.generated_file.parent / cpp_filename
    copyfile(context.generated_file, copy)
    parsed_output = cppparser.ParsedFile(copy)
    references = parsed_output.find_typerefs(param_type, name)
    references = list(filter(node_filter_function, references))
    references = cppparser.sort_by_line_number(references)

    assert (len(references) == int(number))
