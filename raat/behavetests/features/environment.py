import shutil

def after_scenario(context, scenario):

	try:
		shutil.rmtree(context.generated_file.ino_file_path.parent)
	except AttributeError:
		raise

