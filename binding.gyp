{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cc", "jmatrix.cc", "SimpleMatrix.cc" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ]
    }
  ]
}
