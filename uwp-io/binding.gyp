{
  'targets': [
    {
      'target_name': 'uwp-io',
      'sources': [
        'addon.cpp',
        'uwpiogpio.cpp'
      ],
      'msvs_windows_target_platform_version': 'v10.0',
      'win_delay_load_hook': 'false',
      'msvs_onecore_vcpp_libs': 1,
      'msvs_settings': {
        'VCLinkerTool': {
          'IgnoreDefaultLibraryNames' : ['kernel32.lib','user32.lib' ],
          'conditions': [
            [ 'target_arch=="ia32"', {
              'AdditionalLibraryDirectories' : [ '$(VCInstallDir)lib\onecore;$(WindowsSDK_LibraryPath_x86);$(UniversalCRT_LibraryPath_x86)' ],
            } ],
            [ 'target_arch=="x64"', {
              'AdditionalLibraryDirectories' : [ '$(VCInstallDir)lib\onecore\\amd64;$(WindowsSDK_LibraryPath_x64);$(UniversalCRT_LibraryPath_x64)' ],
            } ],
            [ 'target_arch=="arm"', {
              'AdditionalLibraryDirectories' : [ '$(VCInstallDir)lib\onecore\\arm;$(WindowsSDK_LibraryPath_arm);$(UniversalCRT_LibraryPath_arm)' ],
            } ],
          ],
        },
        'VCCLCompilerTool': {
          'AdditionalUsingDirectories': [ '$(VCInstallDir)vcpackages;$(WindowsSdkDir)UnionMetadata;%(AdditionalUsingDirectories)' ],
          'CompileAsWinRT': 'true',
        },
      },
      'libraries': [
        '-lonecore.lib',
      ],
      'configurations': {
        'Release': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '2',
           }
          },
        },
        'Debug': {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'RuntimeLibrary': '3',
            }
          },
        }
      }
    },
  ],
}
