Feature: Multiple devices

  In order to create sketches with arrays of similar devices
  As a RAAT user
  I want to specify multiple devices in the setup file
  and have them automatically created.

  Scenario: Make a sketch with one type of multiple device
    Given the user runs RAAT with "One_Multiple_Device.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 5 devices in total
      And the sketch should have an array of 5 DigitalOutput devices called "Test DigOut"

  Scenario: Make a sketch with many types of multiple device
    Given the user runs RAAT with "Many_Multiple_Devices.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 10 devices in total
      And the sketch should have an array of 2 DigitalInput devices called "Test DigIn"
      And the sketch should have an array of 3 AnalogInput devices called "Test AnaIn"
      And the sketch should have an array of 5 DigitalOutput devices called "Test DigOut"

  Scenario: Make a sketch with single devices and many multiple devices
    Given the user runs RAAT with "Many_Devices.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 13 devices in total
      And the sketch should have 1 DigitalInput device called "Test Single DigIn"
      And the sketch should have 1 AnalogInput device called "Test Single AnaIn"
      And the sketch should have 1 DigitalOutput device called "Test Single DigOut"
      And the sketch should have an array of 2 DigitalInput devices called "Test DigIn"
      And the sketch should have an array of 3 AnalogInput devices called "Test AnaIn"
      And the sketch should have an array of 5 DigitalOutput devices called "Test DigOut"