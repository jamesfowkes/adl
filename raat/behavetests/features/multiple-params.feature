Feature: Multiple parameters

  In order to create sketches with arrays of similar parameters
  As a RAAT user
  I want to specify multiple parameters in the setup file
  and have them automatically created.

  Scenario: Make a sketch with one type of multiple parameter
    Given the user runs RAAT with "One_Multiple_Param.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 5 parameters in total
      And the sketch should have an array of 5 IntegerParam<int32_t> parameters called "Test Integer"

  Scenario: Make a sketch with many types of multiple parameter
    Given the user runs RAAT with "Many_Multiple_Params.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 10 parameters in total
      And the sketch should have an array of 2 StringParam parameters called "Test String"
      And the sketch should have an array of 3 BooleanParam parameters called "Test Boolean"
      And the sketch should have an array of 5 IntegerParam<int32_t> parameters called "Test Integer"

  @wip
  Scenario: Make a sketch with single parameters and many multiple parameters
    Given the user runs RAAT with "Many_Params.xml"
      Then the process should have run successfully
      And the sketch should have been created
      And the sketch should have 13 parameters in total
      And the sketch should have 1 StringParam parameter called "Test Single String"
      And the sketch should have 1 BooleanParam parameter called "Test Single Boolean"
      And the sketch should have 1 IntegerParam<int32_t> parameter called "Test Single Integer"
      And the sketch should have an array of 2 StringParam parameters called "Test String"
      And the sketch should have an array of 3 BooleanParam parameters called "Test Boolean"
      And the sketch should have an array of 5 IntegerParam<int32_t> parameters called "Test Integer"