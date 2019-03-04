import shutil

def after_scenario(context, scenario):

	try:
		pass
		#shutil.rmtree(context.generated_file.parent)
	except AttributeError:
		pass

