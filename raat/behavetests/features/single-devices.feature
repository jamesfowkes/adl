Feature: Single devices

  In order to create sketches with devices
  As a RAAT user
  I want to specify devices in the setup file
  and have them automatically created.

  Scenario: Make a sketch with a single device
    Given the user runs RAAT with "One_Single_Device.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 1 devices in total
      And the sketch should have 1 DigitalOutput device called "Test DigOut"

  Scenario: Make a sketch with a many single devices
    Given the user runs RAAT with "Many_Single_devices.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 9 devices in total
      And the sketch should have 1 DigitalOutput device called "Test DigOut"
      And the sketch should have 1 DigitalOutput device called "Test DigOut 2"
      And the sketch should have 1 DigitalOutput device called "Test DigOut 3"
      And the sketch should have 1 DigitalInput device called "Test DigIn"
      And the sketch should have 1 DigitalInput device called "Test DigIn 2"
      And the sketch should have 1 DigitalInput device called "Test DigIn 3"
      And the sketch should have 1 AnalogInput device called "Test AnaIn"
      And the sketch should have 1 AnalogInput device called "Test AnaIn 2"
      And the sketch should have 1 AnalogInput device called "Test AnaIn 3"