{
  "targets" : [
    {
      "target_name"   : "bouncestudio",
      "sources"       : [ "src/bouncestudio.cpp" ],
      "include_dirs"  : [ "<!(node -e \"require('nan')\")" ],
      "libraries"     : [ "-lBounceStudio64" ]
    }
  ]
}
