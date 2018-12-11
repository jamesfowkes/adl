from adl.devices import devices_plugin_manager

def get_device_class(device_type):
    return devices_plugin_manager.getPluginByName(device_type).plugin_object.device_class
