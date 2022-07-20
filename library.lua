require "tundra.syntax.glob"
require "tundra.syntax.files"
local native = require "tundra.native"

-- to enable picturegradient define ENABLE_PICTUREGRADIENT, but needs stb_image as dependency

StaticLibrary {
   Name = "eastladdon_colorhandling",
   Sources = {
      Glob {
         Dir = _G.LIBROOT_EASTLADDON_COLORHANDLING,
         Extensions = { ".h", ".cpp" },
      },
   },
   Env = {
      CPPDEFS = {
        {Config="win32-*-*";     "EA_PLATFORM_WINDOWS"},
        {Config="linux_x86-*-*"; "EA_PLATFORM_LINUX"},
      },
      CPPPATH = {
         _G.LIBROOT_EASTLADDON_COLORHANDLING .. "/..",
      },
   },
   Propagate = {
      Env = {
         CPPDEFS = {
           {Config="win32-*-*";     "EA_PLATFORM_WINDOWS"},
           {Config="linux_x86-*-*"; "EA_PLATFORM_LINUX"},
         },
      },
   },
}


