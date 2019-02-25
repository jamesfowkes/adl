import subprocess
from pathlib import Path

from behave import given, when, then, step

@given(u'the user runs RAAT with "{filename}"')
def step_impl(context, filename):
    pathlib_file = Path(filename)
    relative_file_path = Path("raat/behavetests/test_files", pathlib_file.stem, filename)
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
            context.completedprocess.stderr or ""
            )
        )

@then(u'a sketch should have been created with some parameters')
def step_impl(context):
    raise NotImplementedError(u'STEP: Then a sketch should have been created with some parameters')
