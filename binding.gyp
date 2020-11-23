{
  "targets": [{
    "target_name": "xlsxio",
    "sources": [
      "xlsxio/lib/xlsxio_write.c",
      "xlsxio/lib/xlsxio_read.c",
      "xlsxio/lib/xlsxio_read_sharedstrings.c", 
      "xlsxio/src/xlsxio_csv2xlsx.c",
      "src/main.cc",
      "src/sheet.cc",
    ],
    "defines": [ "USE_MINIZIP" ],
    "include_dirs": [
      "xlsxio/include",
      "xlsxio/lib",
      "third-party/zlib-gyp/contrib/minizip",
      "third-party/zlib-gyp/contrib",
      "third-party/libexpat",
      "<!(node -p \"require('node-addon-api').include_dir\")",
    ],    
    "dependencies": [
      "third-party/libexpat/libexpat.gyp:expat",
      "third-party/zlib-gyp/zlib.gyp:minizip",
    ],
    "cflags!": [ "-fno-exceptions" ],
    "cflags_cc!": [ "-fno-exceptions" ],
    "xcode_settings": {
      "GCC_ENABLE_CPP_EXCEPTIONS": "YES",
      "CLANG_CXX_LIBRARY": "libc++",
      "MACOSX_DEPLOYMENT_TARGET": "10.7",
    },
    "msvs_settings": {
      "VCCLCompilerTool": { "ExceptionHandling": 1 },
    },
  }]
}
