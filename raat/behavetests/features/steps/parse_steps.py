import subprocess
from pathlib import Path
from shutil import copyfile

import cppparser

from behave import given, when, then, step

@given(u'the user runs RAAT with "{filename}"')
def the_user_runs_raat(context, filename):
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
def the_process_runs_successfully(context):
    if context.completedprocess.returncode != 0:
        raise Exception("Process '{:s}'' returned error code {:d} (stderr '{:s}')".format(
            " ".join(context.completedprocess.args),
            context.completedprocess.returncode,
            context.completedprocess.stderr.decode("utf-8") or ""
            )
        )

@then(u'the sketch should have been created')
def the_sketch_has_been_created(context):
    assert context.generated_file.exists()

@then(u'the sketch should have 1 {param_type} parameter called "{name}"')
def the_sketch_has_a_parameter(context, param_type, name):

    def node_filter_function(n):
        return Path(str(n.location.file)).name == cpp_filename

    cpp_filename = (context.generated_file.stem + ".cpp")
    expected_variable_name = "s_" + name.lower().replace(" ", "_")
    copy = context.generated_file.parent / cpp_filename
    copyfile(context.generated_file, copy)
    parsed_output = cppparser.ParsedFile(copy)
  
    type_references = parsed_output.find_vardefs(expected_variable_name)
    print(type_references)
    type_references = list(filter(node_filter_function, type_references))
    print(type_references)
    type_references = cppparser.sort_by_line_number(type_references)
    print(type_references)

    assert (len(type_references) == 1)

@then(u'the sketch should have an array of {number} {param_type} parameters called "{name}"')
def the_sketch_has_array_parameters(context, number, param_type, name):

    cpp_filename = (context.generated_file.stem + ".cpp")
    
    def node_filter_function(n):
        return Path(str(n.location.file)).name == cpp_filename

    expected_variable_name = "s_" + name.lower().replace(" ", "_")

    copy = context.generated_file.parent / cpp_filename
    copyfile(context.generated_file, copy)
    parsed_output = cppparser.ParsedFile(copy)

    type_references = parsed_output.find_typerefs(param_type, expected_variable_name)
    type_references = list(filter(node_filter_function, type_references))
    type_references = cppparser.sort_by_line_number(type_references)

    assert (len(type_references) == int(number))
