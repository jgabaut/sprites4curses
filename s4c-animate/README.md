# s4c-animate

  Before `0.4.8`, this module was the main library in this repo. Now, it's been absorbed into `src/s4c.h`.

  In the upcoming `0.5` release, this temporary stub file will be removed.

  All previous APIs will still be available in the new module, but some macros may be renamed to better namespace the new module.

  A list of all updated identifiers follows.


  ```c
  S4C_MAJOR  // Dropped
  S4C_MINOR // Dropped
  S4C_PATCH // Dropped
  S4C_VERSION // Renamed to S4C_ANIMATE_VERSION
  S4C_MAJOR_VERSION // Renamed to S4C_ANIMATE_MAJOR_VERSION
  S4C_MINOR_VERSION // Renamed to S4C_ANIMATE_MINOR_VERSION
  S4C_PATCH_VERSION // Renamed to S4C_ANIMATE_PATCH_VERSION
  int_s4c_version() // Renamed to int_s4c_animate_version()
  s4c_printVersionToFile() // Renamed to s4c_animate_printVersionToFile()
  s4c_echoVersionToFile() // Renamed to s4c_animate_echoVersionToFile()
  S4C_ECHOVERSION() // Renamed to S4C_ANIMATE_ECHOVERSION()
  S4C_PRINTVERSION() // Renamed to S4C_ANIMATE_PRINTVERSION()
  ```
