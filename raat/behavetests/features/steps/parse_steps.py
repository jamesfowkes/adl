import subprocess
from pathlib import Path
from shutil import copyfile

import cppparser

from behave import given, when, then, step

from util import pairwise

class GeneratedFile:

    def __init__(self, sketch_filename):
        pathlib_file = Path(sketch_filename)

        self.ino_file_path = Path("test_files") / pathlib_file.stem / pathlib_file.stem / (pathlib_file.stem + ".ino")

    def copy_and_parse_ino(self):
        cpp_filename = (self.ino_file_path.stem + ".cpp")
        copy = self.ino_file_path.parent / cpp_filename
        copyfile(self.ino_file_path, copy)
        parsed_output = cppparser.ParsedFile(copy)
        return parsed_output, cpp_filename

    def parse_generated_file(self, filename):
        filepath = self.ino_file_path.parent / filename
        parsed_output = cppparser.ParsedFile(filepath)
        return parsed_output

    def exists(self):
        return self.ino_file_path.exists()

    def xml_path(self):
        return Path("raat/behavetests/test_files") / self.ino_file_path.stem / (self.ino_file_path.stem + ".xml")

def get_filename_filter_function(filename):
    
    def node_filter_function(n):
        return Path(str(n.location.file)).name == filename

    return node_filter_function

@given(u'the user runs RAAT with "{filename}"')
def the_user_runs_raat(context, filename):

    context.generated_file =  GeneratedFile(filename)

    context.completedprocess = subprocess.run(
        ["python3", "raat_runner.py", "--make", str(context.generated_file.xml_path())],
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

    print("------")
    print(name)
    ## Assert that the parameter has been declared in the sketch
    parsed_cpp, cpp_filename = context.generated_file.copy_and_parse_ino()

    expected_variable_name = "s_" + name.lower().replace(" ", "_")
    vardefs = parsed_cpp.find_vardefs(expected_variable_name, param_type,
        custom_filter_func=get_filename_filter_function(cpp_filename))

    vardefs = cppparser.sort_by_line_number(vardefs)

    assert (len(vardefs) == 1)

    ## Assert that the parameter pointer has been defined in the struct
    expected_pointer_name = "p" + name.replace(" ", "_")
    struct_decls = context.generated_file.parse_generated_file("raat-application.hpp").find_struct_decl("_raat_params_struct")
    assert len(struct_decls) == 1

    struct_children = cppparser.get_children(struct_decls[0])
    name_matches = [child.get_definition().spelling == expected_pointer_name for child in struct_children]
    assert name_matches.count(True) == 1

    ## Assert that the param struct has been declared in the sketch
    expected_struct_name = "raat_params"
    vardefs = parsed_cpp.find_vardefs(expected_struct_name, "const raat_params_struct",
        custom_filter_func=get_filename_filter_function(cpp_filename))

    assert len(vardefs) == 1

    struct_def = cppparser.get_child(vardefs[0], 1)
    struct_members = cppparser.get_children(struct_def)
    
    for s in struct_members:
        cppparser.print_node(s)

    struct_matches = []

    for s in struct_members:
        struct_member1 = cppparser.get_child(s, 0)
        struct_member2 = cppparser.get_child(s, 1)
        match = struct_member1.displayname == expected_pointer_name
        assigned_variable = cppparser.get_child(struct_member2, 0)

        match = match and assigned_variable.displayname == expected_variable_name
        struct_matches.append(match)

    assert struct_matches.count(True) == 1

@then(u'the sketch should have an array of {number} {param_type} parameters called "{name}"')
def the_sketch_has_array_parameters(context, number, param_type, name):

    parsed_output, cpp_filename = context.generated_file.copy_and_parse_ino()

    all_references = {}
    for i in range(0, int(number)):
        expected_variable_name = "s_{:s}{:02d}".format(name.lower().replace(" ", "_"), i)
        vardefs = parsed_output.find_vardefs(expected_variable_name,
            custom_filter_func=get_filename_filter_function(cpp_filename))

        all_references.update(cppparser.sort_by_line_number(vardefs))

    assert (len(all_references) == int(number))
