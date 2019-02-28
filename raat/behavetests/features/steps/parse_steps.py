import subprocess
from pathlib import Path
from shutil import copyfile

import cppparser

from behave import given, when, then, step

def copy_and_parse_ino(ino_file_path):
    cpp_filename = (ino_file_path.stem + ".cpp")
    copy = ino_file_path.parent / cpp_filename
    copyfile(ino_file_path, copy)
    parsed_output = cppparser.ParsedFile(copy)
    return parsed_output, cpp_filename

def get_filename_filter_function(filename):
    
    def node_filter_function(n):
        return Path(str(n.location.file)).name == filename

    return node_filter_function

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

    parsed_output, cpp_filename = copy_and_parse_ino(context.generated_file)

    expected_variable_name = "s_" + name.lower().replace(" ", "_")
 
    vardefs = parsed_output.find_vardefs(expected_variable_name, param_type,
        custom_filter_func=get_filename_filter_function(cpp_filename))

    vardefs = cppparser.sort_by_line_number(vardefs)

    assert (len(vardefs) == 1)

@then(u'the sketch should have an array of {number} {param_type} parameters called "{name}"')
def the_sketch_has_array_parameters(context, number, param_type, name):

    parsed_output, cpp_filename = copy_and_parse_ino(context.generated_file)

    all_references = {}
    for i in range(0, int(number)):
        expected_variable_name = "s_{:s}{:02d}".format(name.lower().replace(" ", "_"), i)
        vardefs = parsed_output.find_vardefs(expected_variable_name,
            custom_filter_func=get_filename_filter_function(cpp_filename))

        all_references.update(cppparser.sort_by_line_number(vardefs))

    assert (len(all_references) == int(number))

@then(u'the parameter struct should have members')
def the_parameter_struct_should_have_members(context):
    pass