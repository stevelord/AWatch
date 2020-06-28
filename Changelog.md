# Changelog
All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
- Still investigating ways to get SPIFFS asset loading working without slowdowns so we can build themes and change mods easily.

## [0.0.4](https://github.com/stevelord/AWatch/commits/master) - 2020-06-28
### Added
- Public Changelog

### Removed
- Reverted back to PROGMEM for protracker mods as ESP8266Audio appears to stream mod data from SPIFFS and is too slow. i/o may also be blocking, need to investigate.

## [0.0.3](https://github.com/stevelord/AWatch/commit/5dd6f0bae2f82ba3bf5a5793d19cd37eb3208388) - 2020-06-27
### Added
- 2020 T-Watch Support (@steveway)

### Changed
- SPIFFS loading for protracker mods (@steveway)

## [0.0.2](https://github.com/stevelord/AWatch/commit/aa1aa3b9db881b97d4c4510d89b6f811b1d9587e) - 2020-06-04
### Added
- Link to @tobozo's raytracer repo to Readme.

## [0.0.1](https://github.com/stevelord/AWatch/commit/f54bb5cf766059f95254dfee1cb44e69939fd539) - 2020-06-03
### Added
- Initial Release
