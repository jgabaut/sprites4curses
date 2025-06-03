# Changelog

## [0.4.9] - 2025-06-03
## [0.4.8] - 2024-09-02
## [0.4.7] - 2024-08-09
## [0.4.6] - 2024-06-12
## [0.4.5] - 2024-05-06
## [0.4.4] - 2024-01-26
## [0.4.3] - 2024-01-19
## [0.4.2] - 2024-01-05
## [0.4.1] - 2024-01-04
## [0.4.0] - 2024-01-03
## [0.3.6] - 2023-12-28

### Changed

- Use _WIN32 in header guard

## [0.3.5] - 2023-11-13

### Changed

- Fix trigraph issue when building with --std=c(<23)
  - Escape ? chars in output strings

## [0.3.4] - 2023-10-05

### Changed

- Pip patches, bump deps

## [0.3.3] - 2023-09-20

### Changed

- Color index range from '1'

## [0.3.2] - 2023-09-19

### Added

- Extend workable color range

## [0.3.1] - 2023-09-18

### Added

- MacOS flags configuration
- Add 16 more colors
  - Not usable yet

## [0.3.0] - 2023-09-14

### Changed

- Drop MAXFRAMES from signatures

## [0.2.14] - 2023-09-08

### Changed

- Return after pthread_exit() for MINGW32_BUILD

## [0.2.13] - 2023-09-08

### Added

- Build using autotools

## [0.2.12] - 2023-09-01

### Added

- Generate palette.c

## [0.2.11] - 2023-09-01

### Changed

- Update copy_animation()

## [0.2.10] - 2023-08-31

### Added

- Mode argument for scripts

## [0.2.9] - 2023-08-31

### Changed

- Improved header output for scripts

## [0.2.8] - 2023-08-31

### Added

- New display_sprite_at_coords() function

## [0.2.7] - 2023-08-19

### Added

- New test_s4c_color_pairs() function

## [0.2.6.2] - 2023-07-03

### Changed

- Hotfix UB in copy_animation()

## [0.2.6.1] - 2023-07-03

### Changed

- Hotfix for copy_animation(), which was using a bad loop condition to iterate over sprite lines

## [0.2.5.4] - 2023-06-30

### Changed

- Now print_spriteline() is not declared as static anymore

## [0.2.5.3] - 2023-06-02

### Changed

- Improved Makefile

## [0.2.5.2] - 2023-05-23

### Changed

- Updated scripts FILE_VERSION to 0.1.3

## [0.2.5.1] - 2023-05-21

### Changed

- Removed cursor calls from __animate_rangeof

## [0.2.5] - 2023-05-18

### Added

- New function accepting a growing range of frames

## [0.2.4] - 2023-04-17

### Changed

- Improved demo.c to show how to call animate_sprites_threaded_at()
- Now init_s4c_color_pairs() closes the passed palette_file pointer before returning
  - This means that closing operation was removed from internal calls to the init function

## [0.2.3.2] - 2023-03-09

### Added

- New function for threaded animation with animate_sprites_threaded_at()

## [0.2.2.1] - 2023-03-04

### Added

- New terminal capability checks, to ensure we avoid runtime issues
  - It's stil best to check with has_colors() and can_change_colors() before using library functions
- New function animate_sprites_at_coords() to not have the animation start at 0,0 in the boxed window
- New cut_sheet.py script to cut a spritesheet to single sprites and save them
- New sample sheets (sheet_alt.png and sheet_alt2.png)

### Changed

- Now init_s4c_color_pairs() uses palette.gpl to create the color pairs
- Color indexes were updated to avoid using values (1..=8)
- You are now expected to call both init_s4c_color_pairs() and load_sprites() before using animate_sprites()
- Renamed animate_file() to animate_sprites()
  - Now expectes a 3D char array instead of a FILE pointer
- Improved sheet_converter.py to handle bigger sheets better
- Repo structure was changed, check your include statements

## [0.1.9.2] - 2023-03-03
## [0.1.8] - 2023-03-02

### Changed

- Output files now have a version number
- Some methods now return state or error
- Chars representing pixel color now start from 'a', instead of using arbitrary ones
- Cursor is set to invisible during animation
  - Errors from terminals not supporting this feature are not handled yet

## [0.1.6] - 2023-02-26
## [0.1.5] - 2023-02-25
## [0.1.4] - 2023-02-25
## [0.1.3] - 2023-02-25
## [0.1.2] - 2023-02-25
## [0.1.1] - 2023-02-24
## [0.1.0] - 2023-02-23
