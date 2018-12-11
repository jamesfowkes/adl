import logging
import os

from pathlib import Path

from collections import namedtuple

from yapsy.IPlugin import IPlugin

from adl.types import LibraryInclude, LocalInclude, Setting
from adl.devices.generic_device import GenericDevice

THIS_PATH = Path(__file__).parent

class Keypad(GenericDevice, namedtuple("Keypad", ["name", "buttons", "row_pins", "col_pins"])):

    __slots__ = ()

    sources = ("adl_keypad.cpp", )

    includes = (
        LibraryInclude("Keypad.h"),
        LocalInclude("adl_keypad.h")
    )

    @property
    def setup(self):
        return "{name}.setup();".format(name=self.cname())

    @property
    def directory(self):
        return THIS_PATH

    @property
    def name_caps(self):
        return self.cname()[2:].upper()

    @property
    def row_count(self):
        return len(self.buttons.value)
    
    @property
    def col_count(self):
        return len(self.buttons.value[0])



    @property
    def declarations(self):
        pin_lines = [
            "static const uint8_t {name_caps}_ROWPINS[] = {{{row_pins}}};".format(name_caps=self.name_caps, row_pins=self.row_pins.value),
            "static const uint8_t {name_caps}_COLPINS[] = {{{col_pins}}};".format(name_caps=self.name_caps, col_pins=self.col_pins.value)
        ]

        key_lines = [
            ["static char {name_caps}_KEYS[{row_count}][{col_count}] = {{".format(
                name_caps=self.name_caps, row_count=self.row_count, col_count=self.col_count)],
            ["{{ {key_row} }},".format(key_row=",".join(key_row)) for key_row in self.buttons.value],
            ["};"]
        ]
        key_lines = [os.linesep.join(l) for l in key_lines]

        object_lines = [
            "static Keypad {name}_keypad = Keypad(makeKeymap({name_caps}_KEYS), {name_caps}_ROWPINS, {name_caps}_COLPINS, {row_count}, {col_count});".format(
                name=self.cname(), name_caps=self.name_caps, row_count=self.row_count, col_count=self.col_count),
            "static ADLKeypad {name} = ADLKeypad({name}_keypad);".format(name=self.cname())
        ]
        
        all_lines = [
            os.linesep.join(pin_lines),
            os.linesep.join(key_lines),
            os.linesep.join(object_lines)
        ]

        return os.linesep.join(all_lines)

class KeypadPlugin(IPlugin):
    def activate(self):
        pass

    def deactivate(self):
        pass

    def get(self, device):
        button_rows = device.settings["buttons"].value.split(";")
        quoted_buttons = []
        for button_row in button_rows:
            buttons = ["'" + b + "'" for b in button_row]
            quoted_buttons.append(buttons)

        buttons = Setting("buttons", "buttons", quoted_buttons)
        row_pins = device.settings["row_pins"]
        col_pins = device.settings["col_pins"]
        return Keypad(device.name, buttons, row_pins, col_pins)

    def set_log_level(self, level):
        logging.getLogger(__name__).setLevel(level)
