Feature: Single parameters

  In order to create sketches with parameters
  As a RAAT user
  I want to specify parameters in the setup file
  and have them automatically created.

  Scenario: Make a sketch with a single parameter
    Given the user runs RAAT with "One_Single_Parameter.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 1 StringParam parameter called "Test String"

  Scenario: Make a sketch with a many single parameters
    Given the user runs RAAT with "Many_Single_Parameters.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 1 StringParam parameter called "Test String"
      And the sketch should have 1 StringParam parameter called "Test String 2"
      And the sketch should have 1 StringParam parameter called "Test String 3"
      And the sketch should have 1 IntegerParam parameter called "Test Integer"
      And the sketch should have 1 IntegerParam parameter called "Test Integer 2"
      And the sketch should have 1 IntegerParam parameter called "Test Integer 3"
      And the sketch should have 1 BooleanParam parameter called "Test Boolean"
      And the sketch should have 1 BooleanParam parameter called "Test Boolean 2"
      And the sketch should have 1 BooleanParam parameter called "Test Boolean 3"