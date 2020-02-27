import os

import subprocess

from collections import namedtuple
from pathlib import Path
from shutil import copyfile

import cppparser

from behave import given, when, then, step

from util import pairwise

class Expected(namedtuple("Expected", ["array_name", "array_type", "struct_name", "struct_type", "const_struct_type"])):

    @classmethod
    def get(cls, context, parameter_or_device):
        if parameter_or_device.startswith("parameter"):
            expected_array_name = "s_params_pointers"
            expected_array_type = "ParameterBase *[{:d}]".format(context.n_devices_or_params)
            expected_struct_name = "raat_params"
            expected_struct_type = "_raat_params_struct"
            const_struct_type = "const raat_params_struct"
        elif parameter_or_device.startswith("device"):
            expected_array_name = "s_device_pointers"
            expected_array_type = "DeviceBase *[{:d}]".format(context.n_devices_or_params)
            expected_struct_name = "raat_devices"
            expected_struct_type = "_raat_devices_struct"
            const_struct_type = "const raat_devices_struct"

        return cls(expected_array_name, expected_array_type, expected_struct_name, expected_struct_type, const_struct_type)

class GeneratedFile:

    def __init__(self, sketch_filename, context):

        self.context = context

        pathlib_file = Path(sketch_filename)

        self.ino_file_path = Path("test_files") / pathlib_file.stem / pathlib_file.stem / (pathlib_file.stem + ".ino")

    def copy_and_parse_ino(self):
        cpp_filename = (self.ino_file_path.stem + ".cpp")
        copy = self.ino_file_path.parent / cpp_filename
        copyfile(self.ino_file_path, copy)
        parsed_output = cppparser.ParsedFile(copy, self.context.config.userdata.get("clanginc", "").split(";"))
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

    context.generated_file =  GeneratedFile(filename, context)

    context.completedprocess = subprocess.run(
        ["python3", "raat_runner.py", "--make", str(context.generated_file.xml_path())],
        cwd="../../",
        stdout=subprocess.PIPE, stderr=subprocess.PIPE
    )

    try:
        context.parsed_cpp, context.cpp_filename = context.generated_file.copy_and_parse_ino()
    except:
        stderr = os.linesep.join([l.decode("utf-8") for l in context.completedprocess.stderr.splitlines()])
        print(stderr)
        raise


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

@then(u'the sketch should have 1 {param_or_device_type} {parameter_or_device} called "{name}"')
def the_sketch_has_a_parameter_or_device(context, param_or_device_type, parameter_or_device, name):

    if parameter_or_device not in ["parameter", "device"]:
        raise Exception("Expected 'parameter' or 'device' in Then/And step")

    ## Assert that the object has been declared in the sketch
    
    expected_variable_name = "s_" + name.lower().replace(" ", "_")

    vardefs = context.parsed_cpp.find_vardefs(expected_variable_name, param_or_device_type,
        custom_filter_func=get_filename_filter_function(context.cpp_filename))

    vardefs = cppparser.sort_by_line_number(vardefs)
    assert (len(vardefs) == 1)

    ## Assert that a pointer to the param is in the array
    expected = Expected.get(context, parameter_or_device)
    
    array_def = context.parsed_cpp.find_vardefs(expected.array_name, expected.array_type,
        custom_filter_func=get_filename_filter_function(context.cpp_filename))

    array_def = cppparser.get_child(array_def[0], 2)

    array_members = cppparser.get_children(array_def)

    array_members = [cppparser.get_child(m, 0) for m in array_members]

    names = [m.displayname for m in array_members]
    assert names.count(expected_variable_name) == 1

    ## Assert that the parameter/device pointer has been defined in the struct
    expected_pointer_name = "p" + name.replace(" ", "_")
    struct_decls = context.generated_file.parse_generated_file("raat-application.hpp").find_struct_decl(expected.struct_type)
    assert len(struct_decls) == 1

    struct_children = cppparser.get_children(struct_decls[0])
    name_matches = [child.get_definition().spelling == expected_pointer_name for child in struct_children]
    assert name_matches.count(True) == 1

    ## Assert that the parameter/device struct has been declared in the sketch
    vardefs = context.parsed_cpp.find_vardefs(expected.struct_name, (expected.const_struct_type),
        custom_filter_func=get_filename_filter_function(context.cpp_filename))

    assert len(vardefs) == 1

    struct_def = cppparser.get_child(vardefs[0], 1)
    struct_members = cppparser.get_children(struct_def)
    
    struct_matches = []

    for s in struct_members:
        struct_member1 = cppparser.get_child(s, 0)
        struct_member2 = cppparser.get_child(s, 1)
        match = struct_member1.displayname == expected_pointer_name
        assigned_variable = cppparser.get_child(struct_member2, 0)

        match = match and assigned_variable.displayname == expected_variable_name
        struct_matches.append(match)

    assert struct_matches.count(True) == 1

@then(u'the sketch should have an array of {number} {param_or_device_type} {parameters_or_devices} called "{name}"')
def the_sketch_has_array_of_parameters_or_devices(context, number, param_or_device_type, parameters_or_devices, name):

    if parameters_or_devices not in ["parameters", "devices"]:
        raise Exception("Expected 'parameters' or 'devices' in Then/And step")
        
    all_references = {}
    for i in range(0, int(number)):
        expected_variable_name = "s_{:s}{:02d}".format(name.lower().replace(" ", "_"), i)
        vardefs = context.parsed_cpp.find_vardefs(expected_variable_name,
            custom_filter_func=get_filename_filter_function(context.cpp_filename))

        all_references.update(cppparser.sort_by_line_number(vardefs))

    assert (len(all_references) == int(number))

@then(u'the sketch should have {num} {parameters_or_devices} in total')
def the_sketch_has_n_parameters_or_devices(context, parameters_or_devices, num):

    if parameters_or_devices not in ["parameters", "devices"]:
        raise Exception("Expected 'parameters' or 'devices' in Then/And step")

    context.n_devices_or_params = int(num)

    expected = Expected.get(context, parameters_or_devices)

    vardefs = context.parsed_cpp.find_vardefs(expected.array_name, expected.array_type,
        custom_filter_func=get_filename_filter_function(context.cpp_filename))

    assert (len(vardefs) == 1)
