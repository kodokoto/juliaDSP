#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/modii/Documents/Development/max4live/mxos/build/source/projects/julia~"
  cp /Users/modii/Documents/Development/max4live/mxos/source/max-sdk-base/script/PkgInfo /Users/modii/Documents/Development/max4live/mxos/source/projects/julia~/../../../externals/julia~.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/modii/Documents/Development/max4live/mxos/build/source/projects/julia~"
  cp /Users/modii/Documents/Development/max4live/mxos/source/max-sdk-base/script/PkgInfo /Users/modii/Documents/Development/max4live/mxos/source/projects/julia~/../../../externals/julia~.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/modii/Documents/Development/max4live/mxos/build/source/projects/julia~"
  cp /Users/modii/Documents/Development/max4live/mxos/source/max-sdk-base/script/PkgInfo /Users/modii/Documents/Development/max4live/mxos/source/projects/julia~/../../../externals/julia~.mxo/Contents/PkgInfo
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/modii/Documents/Development/max4live/mxos/build/source/projects/julia~"
  cp /Users/modii/Documents/Development/max4live/mxos/source/max-sdk-base/script/PkgInfo /Users/modii/Documents/Development/max4live/mxos/source/projects/julia~/../../../externals/julia~.mxo/Contents/PkgInfo
fi

