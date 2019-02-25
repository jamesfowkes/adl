Feature: Multiple parameters

  In order to create sketches with arrays of similar parameters
  As a RAAT user
  I want to specify multiple parameters in the setup file
  and have them automatically created.

  Scenario: Make a sketch with one type of multiple parameter
    Given the user runs RAAT with "one-multiple-param.xml"
      Then the process should have run successfully
      And a sketch should have been created with some parameters